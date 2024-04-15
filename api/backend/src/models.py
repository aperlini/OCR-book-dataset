from sqlalchemy import Column, ForeignKey, Integer, String, Float, Text, DateTime, func
from sqlalchemy.orm import relationship
import datetime

from .db import Base


"""
Database Entities (ORM Classes)

"""

class Image(Base):
    __tablename__ = "images"
        
    id:int = Column(Integer, primary_key=True,index=True)
    src:str = Column(String(100), nullable=False, unique=True)

    created_at: datetime = Column(DateTime(timezone=True), server_default=func.now())
    updated_at: datetime = Column(DateTime(timezone=True), server_default=func.now())
    
    author = relationship("Author", back_populates="image", uselist=False)
    book = relationship("Book", back_populates="image", uselist=False)


class Author(Base):
    __tablename__ = "authors"
        
    id:int = Column(Integer, primary_key=True, index=True)
    firstname:str = Column(String(128), unique=True)
    lastname:str = Column(String(128), unique=True)

    img_id = Column(Integer(), ForeignKey('images.id'))  
    image = relationship("Image", back_populates="author")  

    books = relationship("Book", back_populates="author")

    created_at: datetime = Column(DateTime(timezone=True), server_default=func.now())
    updated_at: datetime = Column(DateTime(timezone=True), server_default=func.now())

    def __repr__(self):
        return 'AuthorModel(firstname=%s, lastname=%s)' % (self.firstname, self.lastname)


class Book(Base):
    __tablename__ = "books"

    id:int = Column(Integer(), primary_key=True)
    title:str = Column(String(100), unique=True)
    year:int = Column(Integer())   

    img_id = Column(Integer(), ForeignKey('images.id'))  
    image = relationship("Image", back_populates="book") 

    author_id = Column(Integer(), ForeignKey('authors.id'))  
    author = relationship("Author", back_populates="books") 

    passages = relationship("Passage", order_by="desc(Passage.page)", back_populates="book")

    created_at: datetime = Column(DateTime(timezone=True), server_default=func.now())
    updated_at: datetime = Column(DateTime(timezone=True), server_default=func.now())


class Passage(Base):
    __tablename__ = "passages"

    id:int = Column(Integer(), primary_key=True)
    content:str =Column(Text())
    page:int = Column(Integer())

    book_id = Column(Integer(), ForeignKey('books.id'))  
    book = relationship("Book", back_populates="passages", uselist=False) 

    created_at: datetime = Column(DateTime(timezone=True), server_default=func.now())
    updated_at: datetime = Column(DateTime(timezone=True), server_default=func.now())
