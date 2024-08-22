📚 Library Management System

📜 Overview

The Library Management System is a simple command-line application written in C that allows users to manage a collection of books. 
The system enables users to add new books, search for books, view lists of books by author or title, and delete books from the library. 
The data is stored in a binary file named knjiznica.bin.

🚀 Features

- Add Book: Add a new book to the library with details like title, author, genre, and year of publication.
- Display Books: List all books in the library with their details.
- Search Books: Search for books by title, author, genre, or year of publication.
- Sort and Display: Display books sorted by author or title.
- Delete Book: Remove a specific book from the library.
- Delete All Data: Remove all books and clear the library.
- Exit: Exit the application.

📖 Usage

Once the program is running, you will be presented with a menu of options:

- Add Book: Prompts you to enter the title, author, genre, and publication year of the book.
- Display Books: Displays all books stored in the library with their details.
- Search Books: Allows you to search for books by title, author, genre, or year of publication.
- Display Books by Author: Lists all books sorted by the author’s name.
- Display Books by Title: Lists all books sorted by the title.
- Delete Book: Prompts you to enter the title of the book you wish to delete.
- Delete All Data: Clears all data from the library, effectively deleting the knjiznica.bin file.
- Exit: Exits the program.

💾 Data Storage

The application uses a binary file named knjiznica.bin to store book data. This file is created in the working directory if it does not exist. The file format is as follows:

An integer representing the number of books.
Followed by the records for each book, including title, author, genre, and publication year.

⚠️ Error Handling

Memory Allocation Errors: The program checks for memory allocation failures and reports errors if they occur.

File Handling Errors: The program checks for errors related to file operations and provides appropriate error messages.
