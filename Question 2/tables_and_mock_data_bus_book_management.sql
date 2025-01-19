-- USERS TABLE
CREATE TABLE Users (
    User_Id INT AUTO_INCREMENT PRIMARY KEY,
    Name VARCHAR(100) NOT NULL,
    Email VARCHAR(100) UNIQUE NOT NULL,
    Phone_No VARCHAR(15) UNIQUE NOT NULL,
    Password VARCHAR(100) NOT NULL,
    User_Type ENUM('Passenger', 'Admin') NOT NULL
);

-- OPERATORS TABLE
CREATE TABLE Operators (
    Operator_Id INT AUTO_INCREMENT PRIMARY KEY,
    Name VARCHAR(100) NOT NULL,
    Phone_No VARCHAR(15) UNIQUE NOT NULL,
    Email VARCHAR(100) UNIQUE NOT NULL
);

-- ROUTES TABLE
CREATE TABLE Routes (
    Route_Id INT AUTO_INCREMENT PRIMARY KEY,
    Start_Point VARCHAR(100) NOT NULL,
    End_Point VARCHAR(100) NOT NULL,
    Stops TEXT NOT NULL, -- Denormalized to store multiple stops
    Distance DECIMAL(6, 2) NOT NULL
);

-- BUSES TABLE
CREATE TABLE Buses (
    Bus_Id INT AUTO_INCREMENT PRIMARY KEY,
    Bus_Number VARCHAR(20) UNIQUE NOT NULL,
    Bus_Type ENUM('AC', 'Non-AC', 'Sleeper') NOT NULL,
    Capacity INT NOT NULL CHECK (Capacity > 0),
    Operator_Id INT NOT NULL,
    Route_Id INT NOT NULL,
    Curr_Location VARCHAR(100),
    Status ENUM('Active', 'Inactive') NOT NULL,
    FOREIGN KEY (Operator_Id) REFERENCES Operators(Operator_Id),
    FOREIGN KEY (Route_Id) REFERENCES Routes(Route_Id)
);

-- TRIPS TABLE
CREATE TABLE Trips (
    Trip_Id INT AUTO_INCREMENT PRIMARY KEY,
    Bus_Id INT NOT NULL,
    Route_Id INT NOT NULL,
    Departure_Time DATETIME NOT NULL,
    Arrival_Time DATETIME NOT NULL,
    Trip_Date DATE NOT NULL,
    Status ENUM('Scheduled', 'Ongoing', 'Completed') NOT NULL,
    FOREIGN KEY (Bus_Id) REFERENCES Buses(Bus_Id),
    FOREIGN KEY (Route_Id) REFERENCES Routes(Route_Id)
);

-- TICKETS TABLE
CREATE TABLE Tickets (
    Ticket_Id INT AUTO_INCREMENT PRIMARY KEY,
    Trip_Id INT NOT NULL,
    User_Id INT NOT NULL,
    Seat_Number INT NOT NULL CHECK (Seat_Number > 0),
    Booking_Status ENUM('Booked', 'Cancelled') NOT NULL,
    Payment_Status ENUM('Paid', 'Pending') NOT NULL,
    Booking_Date DATETIME NOT NULL,
    FOREIGN KEY (Trip_Id) REFERENCES Trips(Trip_Id),
    FOREIGN KEY (User_Id) REFERENCES Users(User_Id)
);

-- PAYMENTS TABLE
CREATE TABLE Payments (
    Payment_Id INT AUTO_INCREMENT PRIMARY KEY,
    Ticket_Id INT NOT NULL,
    Payment_Date DATETIME NOT NULL,
    Amount DECIMAL(10, 2) NOT NULL CHECK (Amount > 0),
    Payment_Method ENUM('Card', 'UPI', 'Cash') NOT NULL,
    Payment_Status ENUM('Success', 'Failed') NOT NULL,
    FOREIGN KEY (Ticket_Id) REFERENCES Tickets(Ticket_Id)
);

-- CHECK-INS TABLE
CREATE TABLE Check_Ins (
    Checkin_Id INT AUTO_INCREMENT PRIMARY KEY,
    Ticket_Id INT NOT NULL,
    Checkin_Time DATETIME,
    Status ENUM('Checked In', 'Missed') NOT NULL,
    FOREIGN KEY (Ticket_Id) REFERENCES Tickets(Ticket_Id)
);

-- FEEDBACK TABLE
CREATE TABLE Feedback (
    Feedback_Id INT AUTO_INCREMENT PRIMARY KEY,
    User_Id INT NOT NULL,
    Trip_Id INT NOT NULL,
    Rating INT NOT NULL CHECK (Rating BETWEEN 1 AND 5),
    Comments TEXT,
    FOREIGN KEY (User_Id) REFERENCES Users(User_Id),
    FOREIGN KEY (Trip_Id) REFERENCES Trips(Trip_Id)
);

-- NOTIFICATIONS TABLE
CREATE TABLE Notifications (
    Notification_Id INT AUTO_INCREMENT PRIMARY KEY,
    User_Id INT NOT NULL,
    Message TEXT NOT NULL,
    Timestamp DATETIME NOT NULL,
    Status ENUM('Read', 'Unread') NOT NULL,
    FOREIGN KEY (User_Id) REFERENCES Users(User_Id)
);

-- Insert Users
INSERT INTO Users (Name, Email, Phone_No, Password, User_Type)
VALUES 
('Trupti Khodwe', 'trupti@gmail.com', '1234567890', 'password123', 'Passenger');

-- Insert Operators
INSERT INTO Operators (Name, Phone_No, Email)
VALUES 
('Rajdhani Travels', '9876543210', 'rajdhani.travels@example.com');

-- Insert Routes
INSERT INTO Routes (Start_Point, End_Point, Stops, Distance)
VALUES 
('City A', 'City B', 'Stop 1, Stop 2, Stop 3', 100.0),
('City C', 'City D', 'Stop 4, Stop 5', 100.0);

-- Insert Buses
INSERT INTO Buses (Bus_Number, Bus_Type, Capacity, Operator_Id, Route_Id, Curr_Location, Status)
VALUES 
('123', 'AC', 40, 1, 1, 'Stop 1', 'Active'),
('456', 'Sleeper', 30, 2, 2, 'Stop 5', 'Inactive');

-- Insert Trips
INSERT INTO Trips (Bus_Id, Route_Id, Departure_Time, Arrival_Time, Trip_Date, Status)
VALUES 
(1, 1, '2025-01-19 08:00:00', '2025-01-20 14:00:00', '2025-01-20', 'Scheduled');

-- Insert Tickets
INSERT INTO Tickets (Trip_Id, User_Id, Seat_Number, Booking_Status, Payment_Status, Booking_Date)
VALUES 
(1, 1, 12, 'Booked', 'Paid', '2025-01-19 12:00:00');

-- Insert Payments
INSERT INTO Payments (Ticket_Id, Payment_Date, Amount, Payment_Method, Payment_Status)
VALUES 
(1, '2025-01-19 12:05:00', 500.00, 'Card', 'Success'),
(2, '2025-01-19 13:05:00', 500.00, 'UPI', 'Success');

-- Insert Check-Ins
INSERT INTO Check_Ins (Ticket_Id, Checkin_Time, Status)
VALUES 
(1, '2025-01-20 07:50:00', 'Checked In'),
(2, NULL, 'Missed');

-- Insert Feedback
INSERT INTO Feedback (User_Id, Trip_Id, Rating, Comments)
VALUES 
(1, 1, 4, 'good service.'),
(2, 1, 5, 'nice experience!');

-- Insert Notifications
INSERT INTO Notifications (User_Id, Message, Timestamp, Status)
VALUES 
(1, 'Your trip is scheduled for tomorrow.', '2025-01-19 15:00:00', 'Unread'),
(2, 'Your payment is confirmed.', '2025-01-19 13:06:00', 'Read');