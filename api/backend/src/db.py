from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker
from sqlalchemy.ext.declarative import declarative_base
import os


# get mysql database config
DATABASE_URL= 'mysql+pymysql://{}:{}@{}/{}'.format(
    os.getenv('MYSQL_USER', 'root'),
    os.getenv('MYSQL_PASSWORD'),
    os.getenv('MYSQL_HOST'),
    os.getenv('MYSQL_DATABASE')
)

# Database engine creation to handle connection to MySQL
engine = create_engine(DATABASE_URL)

# Class to create database session instances
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=engine)

# Base class to be inherited in our database (ORM) models
Base = declarative_base()


"""
- Managing session instance on each request
- using the same session through all requests
- `finally` block always ensure db session is closed after each request
"""
def get_db():
    db = SessionLocal()
    try:
        yield db
    finally:
        db.close()



