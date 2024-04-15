import React from "react";
import axios from "axios";

export function Books() {

  const [books, setBooks] = React.useState([]);

  React.useEffect(() => {
    axios.get(`${process.env.REACT_APP_API_URL}/books`).then((response) => {
      setBooks(response.data);
    });
  }, []);

  if (!books) return null;

  const listItems = books.map((book, index) => (
    <div className="col" key={index}>
      <a
        href={`/books/${book.id}`}
        to={`/books/${book.id}`}
        className="card border-primary mb-3 card-book-list"
      >
        <img
          src={process.env.PUBLIC_URL + "/ressources/"+ process.env.REACT_APP_RESSOURCES +"/books/" + book.image.src}
          className="card-img-top"
          alt="..."
        />
        <div className="card-body">
          <h2>{book.title}</h2>
          <h5>{book.year}</h5>
        </div>
      </a>
    </div>
  ));

  return (
    <div className="container-fluid h-100">
        <div className="offset-md-2 row row-cols-1 row-cols-lg-3 g-4 book-list-offset-tr">{listItems}</div>
    </div>
  );
}
