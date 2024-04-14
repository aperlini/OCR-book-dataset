# OCR-book-dataset

**work in progress**

Simple project made using OpenCV and Tesseract with Qt to read screenshots from book pages and extract text content to be fetch into a dataset. The aim was to automate the process of taking notes manually and to implement an interface where the user can select book extracts to be saved.

The project involves python FastAPI web framework with MySQL to provide an api and a simple front-end client using Nginx web server and React. Qt offers a GUI to process and translate image to text to generate new entry for the dataset.

## Current Usage

### 1. Default Client 

![webservice](img/webservice.gif)

### 2. OCR GUI while translating image selection to text

![ocr](img/ocr.gif)

### 3. OCR GUI saving new book extract to database

![new-entry]img/new-entry.gif)

### 4. Refreshing client to see effective change

![refresh](img/refresh.gif)

