CREATE DATABASE library_system;

USE library_system;

-- Admin Table
CREATE TABLE admins (
    admin_id INT PRIMARY KEY AUTO_INCREMENT,
    username VARCHAR(50) UNIQUE,
    password VARCHAR(100)
);

-- Students Table
CREATE TABLE students (
    student_id INT PRIMARY KEY AUTO_INCREMENT,
    student_name VARCHAR(100),
    department VARCHAR(100),
    phone VARCHAR(20)
);

-- Books Table
CREATE TABLE books (
    book_id INT PRIMARY KEY AUTO_INCREMENT,
    title VARCHAR(200),
    author VARCHAR(100),
    category VARCHAR(100),
    quantity INT,
    available INT
);

-- Issued Books Table
CREATE TABLE issued_books (
    issue_id INT PRIMARY KEY AUTO_INCREMENT,
    student_id INT,
    book_id INT,
    issue_date DATE,
    return_date DATE,
    fine INT DEFAULT 0,

    FOREIGN KEY(student_id)
    REFERENCES students(student_id),

    FOREIGN KEY(book_id)
    REFERENCES books(book_id)
);

-- Insert Default Admin
INSERT INTO admins(username, password)
VALUES('admin', 'admin123');

-- Sample Books
INSERT INTO books(title, author, category, quantity, available)
VALUES
('Database Systems', 'Navathe', 'Database', 10, 10),
('Operating Systems', 'Galvin', 'Computer Science', 8, 8),
('C++ Programming', 'Bjarne Stroustrup', 'Programming', 15, 15);

-- Sample Students
INSERT INTO students(student_name, department, phone)
VALUES
('Ali Khan', 'Computer Science', '03001234567'),
('Ahmed Raza', 'Software Engineering', '03111234567');
