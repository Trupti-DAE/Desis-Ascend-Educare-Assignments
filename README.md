# Desis-Ascend-Educare-Assignments
Contains code and details about the assignments being done as a part of the program.


## Assignment 1
Design and implement a bookstore’s inventory management system. A typical bookstore ecosystem has the following items:
- Books
- Magazines
- Store manager
- Cashier
- Customer

Apart from this, the bookstore needs to keep an inventory of the books it has, how many copies it has, the price of each book, cost of each book to the store, etc. Whenever books are sold by the store, or new stock is added to the store, the inventory needs to be updated. Your task is to implement a bookstore with the above entities. Define the attributes and behaviours of these entities and develop the bookstore using an OOP model. Feel free to add any other features that you might want to.

### Implementation Details
**Features of the Program**
- Customer Features
  - View all books in the inventory.
  - Search for books by title or book ID.
  - View books within a given budget.
  - Buy books.
- Cashier Features
  - View all books in the inventory.
  - Sell books by ID.
  - Restock books by ID.
- Manager Features
  - View all books in the inventory.
  - Add new books to the inventory.
  - View details of the store manager and cashier.

**Classes and Methods**
1. Person
- Purpose: Base class for all individuals (store manager, cashier, customer).
- Methods:
  - get_name(), get_id(): Get the name and ID of the person.
  - set_name(), set_id(): Set or change the name and ID.
  - DisplayDetails(): A virtual method overridden by derived classes.

2. StoreManager, Cashier, Customer
- Purpose: Derived classes of Person for specific roles.
- Methods:
  - DisplayDetails(): Print details like name and ID.

3. Book
- Purpose: Represents a book in the inventory.
- Methods:
  - get_title(), get_author(), get_book_id(), get_no_of_copies(), get_price(): get information for the books.
  - add_stock(): Add more copies of the book to inventory.
  - sell_book(): Reduce the stock of a book after selling.
  - display_book_details(): Print book details.

4. Inventory
- Purpose: Manages the collection of books in the bookstore.
- Methods:
  - addBook(): Add a book to the inventory.
  - display_Inventory(): Print details of all books in inventory.
  - find_book_by_book_id(), find_book_by_title(): Search books in inventory.
  - display_books_within_budget(): List books within a specified budget.

5. BookStore
- Purpose: Main class that integrates inventory and roles (manager, cashier).
- Methods:
  - add_book_to_inventory(): Add or update books in inventory.
  - display_inventory(): Show all books.
  - find_book_by_title(), find_book_by_id(): Search books.
  - sell_book_by_id(), sell_book_by_title(): Handle book sales.
  - restock_book(): Add more copies of an existing book.
  - display_staff_details(): Print details of the manager and cashier.

**OOP Concepts Used**
- Encapsulation
  - Classes like Person, Book, and Inventory encapsulate data and provide methods to access and modify it securely.
  - Private members like name, id, books ensure controlled access through getter and setter methods.

- Inheritance
  - StoreManager, Cashier, and Customer inherit from the base class Person.
  - They share common properties but override the DisplayDetails() method for specific behavior.

- Polymorphism
  - The DisplayDetails() function is a pure virtual function in Person, making it polymorphic.
  - Each derived class provides its own implementation of DisplayDetails().

- Abstraction
  - The user interacts with the system without knowing the internal details (e.g., how books are managed in inventory or how staff details are stored).

- Composition
  - The BookStore class contains an Inventory object and manages it using its methods.
