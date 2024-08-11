# Base image Node v10
FROM node:10

# Create app directory
WORKDIR /usr/src/lafs

# Wildcard ensures app dependencies (package.json and package-lock.json) are copied where available (npm@5+)
COPY package*.json ./

# Install dependencies
RUN npm install
# RUN npm ci --only=production  # production only

# Bundle app source (copies all files in the app)
COPY . .

# Expose port 3000 outside container
EXPOSE 3000
# http://localhost:3000 or http://localhost:3000/explorer

# Default command to start application
CMD ["node", "server/server.js"]
