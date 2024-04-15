import {React, useState, useEffect} from "react";
import axios from "axios";
import Row from "react-bootstrap/Row";
import Col from "react-bootstrap/Col";
import { Link } from "react-router-dom";

export function Authors() {

  const [authorItems, setAuthorItems] = useState([]);
  const [bgImg, setBgImg] = useState(null);
  const [isActive, setActive] = useState(false);

  useEffect(() => {

    axios.get(`${process.env.REACT_APP_API_URL}/authors-books`).then((response) => {
      setAuthorItems(response.data);
    });
  }, []);

  if (!authorItems) return null;

  // authors w/ books only
  const listItems = authorItems
    .filter((author) => author.books.length > 0)
    .map((author) => (
      <div key={author.id}>
        <h4 className="text-center">

          <Link
            to={`/books/${author.books[0].id}`}
            className="no-bg author-link"
            onMouseOver={() => {
              setBgImg(author.image.src);
              setActive(true);
            }}
            onMouseOut={() => {
              setBgImg("");
              setActive(false);
            }}
          >
            {author.firstname} {author.lastname} 
          </Link>
        </h4>
      </div>
    ));

  const overlayCls = isActive ? "active" : "";

  return (
    <section
      id="main-section"
      className="text-white"
      style={{ backgroundImage: `url(/ressources/${process.env.REACT_APP_RESSOURCES}/authors/${bgImg})` }}
    >
      <div id="overlay" className={overlayCls}></div>
      <Row className="justify-content-md-center h-100 align-h">
        <Col md="auto">
          <article className="" align-items="center">
            {listItems}
          </article>
        </Col>
      </Row>
    </section>
  );
}
