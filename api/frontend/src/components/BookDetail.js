import React from "react";
import axios from "axios";
import { useParams, useNavigate } from "react-router-dom";

export function BookDetail() {

  const { itemId } = useParams();
  const id = itemId;

  const [book, setBook] = React.useState(null);
  const navigate = useNavigate();

  React.useEffect(() => {
    axios.get(`${process.env.REACT_APP_API_URL}/books/${id}/passages`).then((response) => {
      setBook(response.data);   
    }).catch((error) => {
      navigate("/404");
    });
  }, [id, navigate]);

  if (!book) return null;

  const { title, year } = book;
  const { firstname, lastname } = book.author;
  const { src } = book.image;
  let listPassages = null;
  if (book.passages) {
    listPassages = book.passages.map((p, index) => (
      <p key={index}>
        <span className="page_number">{p.page}</span>
        {p.content}
      </p>
    ));
    
  }

  return (
    <div className="container-fluid" >
      <div className="row">
        <div className="col-md-12">
          <div className="centered-wrapper">           
            <h2 className="author">
              <a href="#" className="no-bg">
                {firstname} {lastname}
              </a>
            </h2>
            <h2 className="year subtitle">{year}</h2>
          </div>
        </div>
      </div>
      <div className="">
        <div className="offset-md-1 book__title__wrap">
          <h1 className="title">{title}</h1>
        </div>
      </div>
      <div className="row book-detail-content">
        <div className="col-md-4 offset-md-1 tags-wrapper">
          <div className="img-wrap">
            <div id="cover-display" style={{ backgroundImage: `url(/ressources/${process.env.REACT_APP_RESSOURCES}/books/${src})` }}></div>
            <div className="overlay"></div>
          </div>               
        </div>
        <div className="col-md-7">
          <div className="main-content">
            {listPassages}
          </div>
        </div>
      </div>
    </div>
  );
}
