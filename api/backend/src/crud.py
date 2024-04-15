from sqlalchemy.orm import Session, joinedload, join
from sqlalchemy import desc, asc
from . import models, schemas


"""
CRUD operations

"""

class ImageOp():
    
    def create(db: Session, img: schemas.ImageCreate):
        db_img = models.Image(src=img.src)
        db.add(db_img)
        db.commit()
        db.refresh(db_img)
        return db_img
    
    def get_by_id(db: Session, id:int):
        return db.query(models.Image).filter(models.Image.id == id).first()
    
    def get_by_src(db: Session, src:str):
        return db.query(models.Image).filter(models.Image.src == src).first()
    
    def all(db: Session, skip: int = 0, limit: int = 100):
        return db.query(models.Image).offset(skip).limit(limit).all()
    
    def update(db: Session,item_data):
        updated_item = db.merge(item_data)
        db.commit()
        return updated_item
    
    def delete(db: Session, id:int):
        db_entry = db.query(models.Image).filter(models.Image.id == id).first()
        db.delete(db_entry)
        db.commit()


class AuthorOp():
    
    def create(db: Session, author: schemas.AuthorCreate):
        db_author = models.Author(**author.dict())
        db.add(db_author)
        db.commit()
        db.refresh(db_author)
        return db_author
    
    def get_by_id(db: Session, id:int):
        return db.query(models.Author).filter(models.Author.id == id).first()
    
    def get_by_fullname(db: Session, firstname:str, lastname: str):
        return db.query(models.Author).filter(models.Author.firstname == firstname, models.Author.lastname == lastname).first()
    
    def all(db: Session, skip: int = 0, limit: int = 100):
        return db.query(models.Author).offset(skip).limit(limit).all()
    
    def update(db: Session,item_data):
        updated_item = db.merge(item_data)
        db.commit()
        return updated_item

    def delete(db: Session, id:int):
        db_entry = db.query(models.Author).filter(models.Author.id == id).first()
        db.delete(db_entry)
        db.commit()


class BookOp():
    
    def create(db: Session, book: schemas.BookCreate):
        db_book = models.Book(**book.dict())
        db.add(db_book)
        db.commit()
        db.refresh(db_book)
        return db_book
    
    def get_by_id(db: Session, id:int):
        return db.query(models.Book).filter(models.Book.id == id).first()
    
    def get_by_title(db: Session, title:str):
        return db.query(models.Book).filter(models.Book.title == title).first()
    
    def all(db: Session, skip: int = 0, limit: int = 100):
        return db.query(models.Book).offset(skip).limit(limit).all()
    
    def update(db: Session,item_data):
        updated_item = db.merge(item_data)
        db.commit()
        return updated_item

    def delete(db: Session, id:int):
        db_entry = db.query(models.Book).filter(models.Book.id == id).first()
        db.delete(db_entry)
        db.commit()


class PassageOp():
    
    def create(db: Session, book: schemas.PassageCreate):
        db_book = models.Passage(**book.dict())
        db.add(db_book)
        db.commit()
        db.refresh(db_book)
        return db_book
    
    def get_by_id(db: Session, id:int):
        return db.query(models.Passage).filter(models.Passage.id == id).first()
    
    def all(db: Session, skip: int = 0, limit: int = 100):
        return db.query(models.Passage).offset(skip).limit(limit).all()
    
    def update(db: Session,item_data):
        updated_item = db.merge(item_data)
        db.commit()
        return updated_item

    def delete(db: Session, id:int):
        db_entry = db.query(models.Passage).filter(models.Passage.id == id).first()
        db.delete(db_entry)
        db.commit()

