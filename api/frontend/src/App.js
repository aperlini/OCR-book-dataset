import "bootstrap/dist/css/bootstrap.css";
import "./App.css";
import { useState, MyButton } from "react";
import Container from "react-bootstrap/Container";
import Nav from "react-bootstrap/Nav";
import Navbar from "react-bootstrap/Navbar";
import Row from "react-bootstrap/Row";
import Col from "react-bootstrap/Col";
import {
  BrowserRouter as Router,
  Routes,
  Route,
  Link,
  Outlet,
  useParams,
} from "react-router-dom";
import { Home } from "./components/Home";
import { Books } from "./components/Books";
import { BookDetail } from "./components/BookDetail";
import { Authors } from "./components/Authors";
import { NotFound } from "./components/NotFound";

export default function App() {

  return (
    <Router>
      <Container fluid className="h-100">
        <header>
          <Navbar expand="lg" className="text-white fixed-top p-2">
            <Navbar.Toggle aria-controls="navbarScroll" />
            <Navbar.Collapse id="navbarScroll">
              <Nav
                className="me-auto my-2 my-lg-0"
                style={{ maxHeight: "100px" }}
                navbarScroll
              >
                <Link to="/authors">
                  Authors
                </Link>
                <Link to="/books">
                  Books
                </Link>
              </Nav>
            </Navbar.Collapse>
          </Navbar>
        </header>

        <Routes>
          <Route path="/" element={<Authors />}></Route>
          <Route path="/books" element={<Books />}></Route>
          <Route path="/books/:itemId" element={<BookDetail />}></Route>
          <Route path="/authors" element={<Authors />}></Route>
          <Route path="/404" element={<NotFound />}></Route>
          <Route path="*" element={<NotFound />}></Route>
        </Routes>
        
      </Container>
    </Router>
  );
}
