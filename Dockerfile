# Use the official GCC image as a base
FROM gcc:latest

# Set the working directory inside the container
WORKDIR /usr/src/app

# Copy the C++ source files into the container
COPY . .

# Compile the C++ program
RUN g++ -o exam_management_system main.cpp

# Command to run the compiled program
CMD ["./exam_management_system"]
