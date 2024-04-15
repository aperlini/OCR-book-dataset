# syntax=docker/dockerfile:1.7

# Ubuntu base image (smaller than python image)
FROM ubuntu:22.04

# set working directory
WORKDIR /api

# install python3 and pip
RUN apt-get update
RUN apt-get install -y python3 python3-pip

# Copy and install dependencies
COPY ./src/requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

# Copy project 
COPY ./src .



