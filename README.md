# Library Management System in C++ and MySQL

## Project Overview

The Library Management System is a console-based software application developed using C++ and MySQL. This project is designed to manage library operations efficiently through database integration and real-world software engineering concepts.

The system allows administrators to manage books, students, issued books, return records, and fines using a simple command-line interface connected to a MySQL database.

This project demonstrates practical implementation of:

- Object-Oriented Programming (OOP)
- Database Management Systems (DBMS)
- CRUD Operations
- MySQL Connectivity in C++
- SQL Queries and JOIN Operations
- Real-World Software Development Concepts

---

# Features

## Admin Features

- Secure Admin Login
- Manage Library Database
- Add New Books
- Delete Books
- Search Books
- View All Books
- Add Students
- Issue Books
- Return Books
- Fine Calculation
- View Issued Books

---

# Technologies Used

| Technology | Purpose |
|---|---|
| C++ | Application Development |
| MySQL | Database Management |
| MySQL Connector/C | Database Connectivity |
| SQL | Database Queries |
| VS Code / CodeBlocks | Development Environment |

---

# Database Structure

The project uses the following tables:

- admins
- students
- books
- issued_books

---

# Database Schema

## Admin Table

Stores administrator credentials.

```sql
CREATE TABLE admins (
    admin_id INT PRIMARY KEY AUTO_INCREMENT,
    username VARCHAR(50),
    password VARCHAR(100)
);
