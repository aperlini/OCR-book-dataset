from fastapi import FastAPI, APIRouter, Depends, HTTPException
from fastapi.middleware.cors import CORSMiddleware
from fastapi.encoders import jsonable_encoder
from sqlalchemy.orm import Session
from typing import List
from .db import get_db, engine
import src.schemas as schemas 
import src.models as models
from .crud import ImageOp, AuthorOp, BookOp, PassageOp

"""

Application entry point

"""

# FastAPI instance
app = FastAPI()

# Router instance
router = APIRouter()

# Enable CORS to authorize communication 
# with front-end server with port 3000
app.add_middleware(
 CORSMiddleware,
 allow_origins=["http://localhost:3000"], 
 allow_credentials=True,
 allow_methods=["*"],
 allow_headers=["*"],
 )

# create database tables during application startup
models.Base.metadata.create_all(bind=engine)


"""
REST endpoints definition

"""

"""
Authors

"""
@router.post("/authors/", tags=["authors"], response_model=schemas.Author, status_code=201)
def create_author(author_req: schemas.AuthorCreate, db: Session = Depends(get_db)):  
    db_author = AuthorOp.get_by_fullname(db, author_req.firstname, author_req.lastname)
    if db_author:
        raise HTTPException(status_code=400, detail="Author already exists")
    return AuthorOp.create(db, author_req)


@router.get("/authors/", tags=["authors"], response_model=List[schemas.Author])
def get_authors(db: Session = Depends(get_db)):
    return AuthorOp.all(db)


@router.get("/authors/{id}", tags=["authors"], response_model=schemas.Author)
def get_author(id:int, db:Session = Depends(get_db)):
    db_author = AuthorOp.get_by_id(db, id)
    if db_author is None:
        raise HTTPException(status_code=404, detail="Author not found")
    return db_author


@router.put("/authors/{id}", tags=["authors"], response_model=schemas.Author)
def update_author(id: int, author_req: schemas.AuthorCreate, db: Session = Depends(get_db)):
    db_author = AuthorOp.get_by_id(db, id)
    if db_author is None:
        raise HTTPException(status_code=400, detail="Author not found")
    update_item_encoded = jsonable_encoder(author_req)
    db_author.firstname = update_item_encoded['firstname']
    db_author.lastname = update_item_encoded['lastname']
    db_author.img_id = update_item_encoded['img_id']
    return AuthorOp.update(db=db, item_data=db_author)


@router.delete("/authors/{id}", tags=["authors"])
def delete_author(id:int,  db:Session = Depends(get_db)):
    db_author = AuthorOp.get_by_id(db, id)
    if db_author is None:
        raise HTTPException(status_code=404, detail="Author not found")
    AuthorOp.delete(db, id)
    return f"Author id: {id} was successfully deleted"


"""
Books

"""
@router.post("/books/", tags=["books"], response_model=schemas.Book, status_code=201)
def create_book(book_req: schemas.BookCreate, db: Session = Depends(get_db)):  
    db_book = BookOp.get_by_title(db, book_req.title)
    if db_book:
        raise HTTPException(status_code=400, detail="Book already exists")
    return BookOp.create(db, book_req)


@router.get("/books/", tags=["books"], response_model=List[schemas.Book])
def get_books(db: Session = Depends(get_db)):
    return BookOp.all(db)


@router.get("/books/{id}", tags=["books"], response_model=schemas.Book)
def get_book(id:int, db:Session = Depends(get_db)):
    db_book = BookOp.get_by_id(db, id)
    if db_book is None:
        raise HTTPException(status_code=404, detail="Book not found")
    return db_book


@router.put("/books/{id}", tags=["books"], response_model=schemas.Book)
def update_book(id: int, book_req: schemas.BookCreate, db: Session = Depends(get_db)):
    db_book = BookOp.get_by_id(db, id)
    if db_book is None:
        raise HTTPException(status_code=400, detail="Book not found")
    update_item_encoded = jsonable_encoder(book_req)
    db_book.title = update_item_encoded['title']
    db_book.year = update_item_encoded['year']
    db_book.img_id = update_item_encoded['img_id']
    db_book.author_id = update_item_encoded['author_id']
    return BookOp.update(db=db, item_data=db_book)


@router.delete("/books/{id}", tags=["books"])
def delete_book(id:int,  db:Session = Depends(get_db)):
    db_book = BookOp.get_by_id(db, id)
    if db_book is None:
        raise HTTPException(status_code=404, detail="Book not found")
    BookOp.delete(db, id)
    return f"Book id: {id} was successfully deleted"



"""
Authors books

"""
@router.get("/authors-books/", tags=["authors books"], response_model=List[schemas.AuthorsBooks])
def get_authors_books(db: Session = Depends(get_db)):
    return AuthorOp.all(db)



"""
Passages

"""
@router.post("/passages/", tags=["passages"], response_model=schemas.Passage, status_code=201)
def create_passage(passage_req: schemas.PassageCreate, db: Session = Depends(get_db)):  
    return PassageOp.create(db, passage_req)


@router.get("/passages/", tags=["passages"], response_model=List[schemas.Passage])
def get_passages(db: Session = Depends(get_db)):
    return PassageOp.all(db)


@router.get("/passages/{id}", tags=["passages"], response_model=schemas.Passage)
def get_passage(id:int, db:Session = Depends(get_db)):
    db_passage = PassageOp.get_by_id(db, id)
    if db_passage is None:
        raise HTTPException(status_code=404, detail="Passage not found")
    return db_passage


@router.put("/passages/{id}", tags=["passages"], response_model=schemas.Passage)
def update_passage(id: int, passage_req: schemas.PassageCreate, db: Session = Depends(get_db)):
    db_passage = PassageOp.get_by_id(db, id)
    if db_passage is None:
        raise HTTPException(status_code=400, detail="Passage not found")
    update_item_encoded = jsonable_encoder(passage_req)
    db_passage.content = update_item_encoded['content']
    db_passage.page = update_item_encoded['page']
    db_passage.book_id = update_item_encoded['book_id']
    return PassageOp.update(db=db, item_data=db_passage)


@router.delete("/passages/{id}", tags=["passages"])
def delete_passage(id:int,  db:Session = Depends(get_db)):
    db_passage = PassageOp.get_by_id(db, id)
    if db_passage is None:
        raise HTTPException(status_code=404, detail="Passage not found")
    PassageOp.delete(db, id)
    return f"Passage id: {id} was successfully deleted"



"""
Books passages

"""
@router.get("/books/{id}/passages", tags=["books"], response_model=schemas.BooksPassages)
def get_book(id:int, db:Session = Depends(get_db)):
    db_book = BookOp.get_by_id(db, id)
    if db_book is None:
        raise HTTPException(status_code=404, detail="Book not found")
    return db_book



"""
Images :

"""
@router.post("/images/", tags=["images"], response_model=schemas.Image, status_code=201)
def create_img(img_req: schemas.ImageCreate, db: Session = Depends(get_db)):  
    db_img = ImageOp.get_by_src(db, img_req.src)
    if db_img:
        raise HTTPException(status_code=400, detail="Image already exists")
    return ImageOp.create(db, img_req)


@router.get("/images/", tags=["images"], response_model=List[schemas.Image])
def get_images(db: Session = Depends(get_db)):
    return ImageOp.all(db)


@router.get("/images/{id}", tags=["images"], response_model=schemas.Image)
def get_image(id:int, db:Session = Depends(get_db)):
    db_img = ImageOp.get_by_id(db, id)
    if db_img is None:
        raise HTTPException(status_code=404, detail="Image not found")
    return db_img


@router.put("/images/{id}", tags=["images"], response_model=schemas.Image)
async def update_image(id: int, img_req: schemas.ImageCreate, db: Session = Depends(get_db)):
    db_img = ImageOp.get_by_id(db, id)
    if db_img is None:
        raise HTTPException(status_code=400, detail="Image not found")
    update_item_encoded = jsonable_encoder(img_req)
    db_img.src = update_item_encoded['src']
    return ImageOp.update(db=db, item_data=db_img)

        
@router.delete("/images/{id}", tags=["images"])
def delete_img(id:int,  db:Session = Depends(get_db)):
    db_img = ImageOp.get_by_id(db, id)
    if db_img is None:
        raise HTTPException(status_code=404, detail="Image not found")
    ImageOp.delete(db, id)
    return f"Image id: {id} was successfully deleted"


# include main router
app.include_router(router)
