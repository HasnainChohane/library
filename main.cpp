#include <iostream>
#include <mysql.h>
#include <string>

using namespace std;

MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;

string host = "localhost";
string user = "root";
string password = "";
string database = "library_system";

void connectDatabase() {

    conn = mysql_init(0);

    conn = mysql_real_connect(
        conn,
        host.c_str(),
        user.c_str(),
        password.c_str(),
        database.c_str(),
        3306,
        NULL,
        0
    );

    if(conn) {
        cout << "\nDatabase Connected Successfully\n";
    }
    else {
        cout << "\nDatabase Connection Failed\n";
        exit(1);
    }
}

bool adminLogin() {

    string username, pass;

    cout << "\n========== ADMIN LOGIN ==========\n";

    cin.ignore();

    cout << "Enter Username: ";
    getline(cin, username);

    cout << "Enter Password: ";
    getline(cin, pass);

    string query =
        "SELECT * FROM admins WHERE username='" +
        username +
        "' AND password='" +
        pass + "'";

    mysql_query(conn, query.c_str());

    res = mysql_store_result(conn);

    row = mysql_fetch_row(res);

    if(row) {
        cout << "\nLogin Successful\n";
        return true;
    }
    else {
        cout << "\nInvalid Username or Password\n";
        return false;
    }
}

void addBook() {

    string title, author, category;
    int quantity;

    cin.ignore();

    cout << "\nEnter Book Title: ";
    getline(cin, title);

    cout << "Enter Author Name: ";
    getline(cin, author);

    cout << "Enter Category: ";
    getline(cin, category);

    cout << "Enter Quantity: ";
    cin >> quantity;

    string query =
        "INSERT INTO books(title, author, category, quantity, available)"
        " VALUES('" +
        title + "','" +
        author + "','" +
        category + "'," +
        to_string(quantity) + "," +
        to_string(quantity) + ")";

    int state = mysql_query(conn, query.c_str());

    if(!state) {
        cout << "\nBook Added Successfully\n";
    }
    else {
        cout << "\nBook Insertion Failed\n";
    }
}

void viewBooks() {

    mysql_query(conn, "SELECT * FROM books");

    res = mysql_store_result(conn);

    cout << "\n========== BOOK LIST ==========\n";

    while((row = mysql_fetch_row(res))) {

        cout << "\nBook ID: " << row[0]
             << "\nTitle: " << row[1]
             << "\nAuthor: " << row[2]
             << "\nCategory: " << row[3]
             << "\nQuantity: " << row[4]
             << "\nAvailable: " << row[5]
             << "\n---------------------------\n";
    }
}

void searchBook() {

    string keyword;

    cin.ignore();

    cout << "\nEnter Book Title: ";
    getline(cin, keyword);

    string query =
        "SELECT * FROM books WHERE title LIKE '%" +
        keyword + "%'";

    mysql_query(conn, query.c_str());

    res = mysql_store_result(conn);

    cout << "\n========== SEARCH RESULT ==========\n";

    while((row = mysql_fetch_row(res))) {

        cout << "\nBook ID: " << row[0]
             << "\nTitle: " << row[1]
             << "\nAuthor: " << row[2]
             << "\nAvailable: " << row[5]
             << "\n---------------------------\n";
    }
}

void deleteBook() {

    int id;

    cout << "\nEnter Book ID to Delete: ";
    cin >> id;

    string query =
        "DELETE FROM books WHERE book_id=" +
        to_string(id);

    int state = mysql_query(conn, query.c_str());

    if(!state) {
        cout << "\nBook Deleted Successfully\n";
    }
    else {
        cout << "\nDeletion Failed\n";
    }
}

void addStudent() {

    string name, department, phone;

    cin.ignore();

    cout << "\nEnter Student Name: ";
    getline(cin, name);

    cout << "Enter Department: ";
    getline(cin, department);

    cout << "Enter Phone Number: ";
    getline(cin, phone);

    string query =
        "INSERT INTO students(student_name, department, phone)"
        " VALUES('" +
        name + "','" +
        department + "','" +
        phone + "')";

    int state = mysql_query(conn, query.c_str());

    if(!state) {
        cout << "\nStudent Added Successfully\n";
    }
    else {
        cout << "\nStudent Insertion Failed\n";
    }
}

void issueBook() {

    int student_id, book_id;

    cout << "\nEnter Student ID: ";
    cin >> student_id;

    cout << "Enter Book ID: ";
    cin >> book_id;

    string checkQuery =
        "SELECT available FROM books WHERE book_id=" +
        to_string(book_id);

    mysql_query(conn, checkQuery.c_str());

    res = mysql_store_result(conn);

    row = mysql_fetch_row(res);

    if(row && stoi(row[0]) > 0) {

        string issueQuery =
            "INSERT INTO issued_books(student_id, book_id, issue_date)"
            " VALUES(" +
            to_string(student_id) + "," +
            to_string(book_id) +
            ", CURDATE())";

        mysql_query(conn, issueQuery.c_str());

        string updateQuery =
            "UPDATE books SET available = available - 1 "
            "WHERE book_id=" +
            to_string(book_id);

        mysql_query(conn, updateQuery.c_str());

        cout << "\nBook Issued Successfully\n";
    }
    else {
        cout << "\nBook Not Available\n";
    }
}

void returnBook() {

    int issue_id, daysLate;
    int fine = 0;

    cout << "\nEnter Issue ID: ";
    cin >> issue_id;

    cout << "Enter Late Days: ";
    cin >> daysLate;

    if(daysLate > 0) {
        fine = daysLate * 50;
    }

    string query =
        "UPDATE issued_books "
        "SET return_date = CURDATE(), fine=" +
        to_string(fine) +
        " WHERE issue_id=" +
        to_string(issue_id);

    mysql_query(conn, query.c_str());

    string getBookQuery =
        "SELECT book_id FROM issued_books "
        "WHERE issue_id=" +
        to_string(issue_id);

    mysql_query(conn, getBookQuery.c_str());

    res = mysql_store_result(conn);

    row = mysql_fetch_row(res);

    if(row) {

        int book_id = stoi(row[0]);

        string updateBook =
            "UPDATE books SET available = available + 1 "
            "WHERE book_id=" +
            to_string(book_id);

        mysql_query(conn, updateBook.c_str());
    }

    cout << "\nBook Returned Successfully\n";

    if(fine > 0) {
        cout << "Late Fine: Rs. " << fine << endl;
    }
}

void viewIssuedBooks() {

    string query =
        "SELECT issued_books.issue_id, students.student_name, "
        "books.title, issued_books.issue_date, "
        "issued_books.return_date, issued_books.fine "
        "FROM issued_books "
        "JOIN students "
        "ON issued_books.student_id = students.student_id "
        "JOIN books "
        "ON issued_books.book_id = books.book_id";

    mysql_query(conn, query.c_str());

    res = mysql_store_result(conn);

    cout << "\n========== ISSUED BOOKS ==========\n";

    while((row = mysql_fetch_row(res))) {

        cout << "\nIssue ID: " << row[0]
             << "\nStudent: " << row[1]
             << "\nBook: " << row[2]
             << "\nIssue Date: " << row[3]
             << "\nReturn Date: "
             << (row[4] ? row[4] : "Not Returned")
             << "\nFine: " << row[5]
             << "\n---------------------------\n";
    }
}

void menu() {

    int choice;

    while(true) {

        cout << "\n========== LIBRARY MANAGEMENT SYSTEM ==========\n";

        cout << "1. Add Book\n";
        cout << "2. View Books\n";
        cout << "3. Search Book\n";
        cout << "4. Delete Book\n";
        cout << "5. Add Student\n";
        cout << "6. Issue Book\n";
        cout << "7. Return Book\n";
        cout << "8. View Issued Books\n";
        cout << "9. Exit\n";

        cout << "\nEnter Choice: ";
        cin >> choice;

        switch(choice) {

            case 1:
                addBook();
                break;

            case 2:
                viewBooks();
                break;

            case 3:
                searchBook();
                break;

            case 4:
                deleteBook();
                break;

            case 5:
                addStudent();
                break;

            case 6:
                issueBook();
                break;

            case 7:
                returnBook();
                break;

            case 8:
                viewIssuedBooks();
                break;

            case 9:
                cout << "\nProgram Closed\n";
                exit(0);

            default:
                cout << "\nInvalid Choice\n";
        }
    }
}

int main() {

    connectDatabase();

    if(adminLogin()) {
        menu();
    }

    return 0;
}
