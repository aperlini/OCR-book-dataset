from typing import Optional, List
from pydantic import BaseModel

"""

Pydantic schemas
================

These classes contain common attributes
constraints for creating and reading data
from our database models

"""

class ImageBase(BaseModel):
    src: str
    
class ImageCreate(ImageBase):
    pass

class Image(ImageBase):
    id: int
    class Config:
        orm_mode=True


"""
Author
"""
class AuthorBase(BaseModel):
    firstname: str
    lastname: str
    
class AuthorCreate(AuthorBase):
    img_id: int
    class Config:
        orm_mode=True
    
class Author(AuthorBase):
    id: int
    image: Image
    class Config:
        orm_mode=True


"""
Book
"""
class BookBase(BaseModel):
    title: str
    year: int
    class Config:
        orm_mode=True

class BookCreate(BookBase):
    img_id: int
    author_id: int

class Book(BookBase):
    id: int
    image: Image
    author: Author
    class Config:
        orm_mode=True

class BookId(BookBase):
    id: int
    class Config:
        orm_mode=True


"""
Authors Books
"""
class AuthorsBooks(Author):
    books: Optional[List[BookId]] = None
    class Config:
        orm_mode=True
    

"""
Passage
"""
class PassageBase(BaseModel):
    content: str
    page: int
    class Config:
        orm_mode=True

class PassageCreate(PassageBase):
    book_id: int

class Passage(PassageBase):
    id: int
    book: Book

class PassageId(PassageBase):
    id: int


"""
Book passages
"""
class BooksPassages(Book):
    passages: Optional[List[Passage]] = None
    