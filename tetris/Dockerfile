# Use an Ubuntu base image
FROM ubuntu:latest

# Install necessary dependencies
RUN apt-get update && \
    apt-get install -y g++ libsfml-dev sqlite3 libsqlite3-dev x11-apps

# Set the working directory inside the container
WORKDIR /app

# Copy the game files to the container
COPY . /app

# Build the game
RUN g++ -o tetris tetris.cpp tetris_test.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsqlite3

# Set the command to run the game
CMD ["/bin/bash", "-c", "export DISPLAY=:0 && ./tetris"]
