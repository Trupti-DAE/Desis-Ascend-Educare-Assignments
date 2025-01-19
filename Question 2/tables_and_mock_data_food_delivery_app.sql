CREATE TABLE User (
    User_Id INT PRIMARY KEY AUTO_INCREMENT,
    Name VARCHAR(100) NOT NULL,
    Email VARCHAR(100) UNIQUE NOT NULL,
    Phone VARCHAR(15) UNIQUE NOT NULL,
    Address TEXT,
    Payment_Prefer VARCHAR(50),
    Order_History TEXT
);

CREATE TABLE Restaurant (
    Restaurant_Id INT PRIMARY KEY AUTO_INCREMENT,
    Name VARCHAR(100) NOT NULL,
    Location TEXT NOT NULL,
    Contact VARCHAR(15),
    Rating DECIMAL(3,2),
    Menu_Id INT UNIQUE
);

CREATE TABLE Menu (
    Menu_Id INT PRIMARY KEY AUTO_INCREMENT,
    Restaurant_Id INT NOT NULL,
    Cuisine_Type VARCHAR(50),
    Available BOOLEAN DEFAULT TRUE,
    FOREIGN KEY (Restaurant_Id) REFERENCES Restaurant(Restaurant_Id) ON DELETE CASCADE
);

CREATE TABLE Dish (
    Dish_Id INT PRIMARY KEY AUTO_INCREMENT,
    Name VARCHAR(100) NOT NULL,
    Price DECIMAL(10,2) NOT NULL,
    Category VARCHAR(50),
    Description TEXT,
    Prep_Time INT,
    Rating DECIMAL(3,2)
);

CREATE TABLE `Order` (
    Order_Id INT PRIMARY KEY AUTO_INCREMENT,
    User_Id INT NOT NULL,
    Restaurant_Id INT NOT NULL,
    Total_Amount DECIMAL(10,2) NOT NULL,
    Order_Status VARCHAR(50),
    Timestamp DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
    Delivery_Address TEXT,
    Payment_Id INT,
    Discount_Id INT,
    FOREIGN KEY (User_Id) REFERENCES User(User_Id),
    FOREIGN KEY (Restaurant_Id) REFERENCES Restaurant(Restaurant_Id)
);

CREATE TABLE Delivery_Partner (
    Partner_Id INT PRIMARY KEY AUTO_INCREMENT,
    Name VARCHAR(100) NOT NULL,
    Phone VARCHAR(15) UNIQUE,
    Vehicle_Type VARCHAR(50),
    Available BOOLEAN DEFAULT TRUE,
    Curr_Location TEXT,
    Rating DECIMAL(3,2)
);

CREATE TABLE Order_Delivery (
    Delivery_Id INT PRIMARY KEY AUTO_INCREMENT,
    Order_Id INT NOT NULL,
    Partner_Id INT NOT NULL,
    Delivery_Status VARCHAR(50),
    Tracking_Info TEXT,
    FOREIGN KEY (Order_Id) REFERENCES `Order`(Order_Id),
    FOREIGN KEY (Partner_Id) REFERENCES Delivery_Partner(Partner_Id)
);

CREATE TABLE Payment (
    Payment_Id INT PRIMARY KEY AUTO_INCREMENT,
    Order_Id INT NOT NULL,
    Payment_Mode VARCHAR(50),
    Payment_Status VARCHAR(50),
    Transaction_Id VARCHAR(100),
    FOREIGN KEY (Order_Id) REFERENCES `Order`(Order_Id)
);

CREATE TABLE Discount (
    Discount_Id INT PRIMARY KEY AUTO_INCREMENT,
    Code VARCHAR(50) UNIQUE,
    Description TEXT,
    Discount_Percent DECIMAL(5,2),
    Validity DATE,
    Applicable_To TEXT
);

INSERT INTO User (Name, Email, Phone, Address, Payment_Prefer) 
VALUES
('Trupti', 'trupti@gmail.com', '1234567890', 'Hosur Road, Electronic City', 'UPI');

INSERT INTO Restaurant (Name, Location, Contact, Rating) 
VALUES
('Dominos', 'Hosur Road, Electronic City', '1111112222', 4.5);

INSERT INTO Menu (Restaurant_Id, Cuisine_Type) 
VALUES
(1, 'Italian'),
(2, 'Indian');

INSERT INTO Dish (Name, Price, Category, Description, Prep_Time, Rating) 
VALUES
('Margherita Pizza', 100.99, 'Main Course', 'Classic pizza with mozzarella cheese', 15, 4.8);

INSERT INTO `Order` (User_Id, Restaurant_Id, Total_Amount, Order_Status, Delivery_Address) 
VALUES
(1, 1, 100.99, 'Delivered', 'Electronic City');

INSERT INTO Delivery_Partner (Name, Phone, Vehicle_Type, Curr_Location, Rating) 
VALUES
('Gopu', '4445556666', 'Bike', 'Near Just Fresh', 4.7);

INSERT INTO Order_Delivery (Order_Id, Partner_Id, Delivery_Status, Tracking_Info) 
VALUES
(1, 1, 'Delivered', 'Delivered on time'),
(2, 1, 'Pending', 'Order is being prepared');

INSERT INTO Payment (Order_Id, Payment_Mode, Payment_Status, Transaction_Id) 
VALUES
(1, 'UPI', 'Completed', '123456'),
(2, 'Cash', 'Pending', NULL);

INSERT INTO Discount (Code, Description, Discount_Percent, Validity, Applicable_To) 
VALUES
('WELCOME10', '10% off on first order', 10.00, '2025-12-31', 'Dominos');