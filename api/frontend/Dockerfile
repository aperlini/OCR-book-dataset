# Node runtime as dev base image
FROM node:14-alpine as development

# set working directory
WORKDIR /app

# add `/app/node_modules/.bin` to $PATH
ENV PATH /app/node_modules/.bin:$PATH

# Copy and install dependencies
COPY package.json package-lock.json ./
RUN npm install --silent

# Copy project 
COPY . .

# start app
CMD ["npm", "start"]



# Node runtime as build base image
FROM node:14-alpine as build

# Set the working 
WORKDIR /app

# Copy and install dependencies
COPY package.json package-lock.json ./
RUN npm install --silent

# Copy project 
COPY . .

# Build project
RUN npm run build

# Production environment
FROM nginx:alpine as production

# Copy build files to Nginx server directory
COPY --from=build /app/build /usr/share/nginx/html
COPY --from=build /app/.nginx/nginx.conf /etc/nginx/conf.d/default.conf

# Expose port 3000
EXPOSE 3000

# Start Nginx server
CMD ["nginx", "-g", "daemon off;"]

