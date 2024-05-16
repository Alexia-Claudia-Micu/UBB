select * from Position
select * from Department
select * from Person
select * from Users
select * from Employee
select * from Sponsors
select * from Review
select * from Servicee
select * from Business
select * from Service_Business
select * from Ad

CREATE TABLE Person (
    pid INT PRIMARY KEY IDENTITY,
    FirstName VARCHAR(20),
    LastName VARCHAR(20),
    BirthDate DATE,
    Address VARCHAR(100)
);

CREATE TABLE Position (
    pid INT PRIMARY KEY IDENTITY,
    PositionName VARCHAR(50)
);

CREATE TABLE Department (
    did INT PRIMARY KEY IDENTITY,
    DepartmentName VARCHAR(50)
);

CREATE TABLE Business (
    bid INT PRIMARY KEY IDENTITY,
    Title VARCHAR(50),
    Category VARCHAR(50)
);

create table Sponsors(
Person int foreign key references Person(pid),
Business int foreign key references Business(bid),
Sum int,
primary key(Person, Business)
);

CREATE TABLE Employee (
    eid INT PRIMARY KEY IDENTITY,
    pid INT FOREIGN KEY REFERENCES Person(pid),
    Business INT FOREIGN KEY REFERENCES Business(bid),
    Position INT FOREIGN KEY REFERENCES Position(pid),
    Department INT FOREIGN KEY REFERENCES Department(did),
    Salary INT,
    HireDate DATE
);

CREATE TABLE Servicee (
    sid INT PRIMARY KEY IDENTITY,
    Name VARCHAR(50)
);

CREATE TABLE Service_Business (
    Service INT FOREIGN KEY REFERENCES Servicee(sid),
    Business INT FOREIGN KEY REFERENCES Business(bid),
    PRIMARY KEY (Service, Business)
);

CREATE TABLE Ad (
    aid INT IDENTITY,
    Buyer INT,
    Length DECIMAL(10, 2),
    Video VARCHAR(100) NULL,
    CONSTRAINT PK_Ad_aid PRIMARY KEY (aid),
    CONSTRAINT FK_Ad_Buyer FOREIGN KEY (Buyer) REFERENCES Business(bid)
);

CREATE TABLE Users (
    uid INT PRIMARY KEY IDENTITY,
    Person INT FOREIGN KEY REFERENCES Person(pid),
    Username VARCHAR(20),
    Password VARCHAR(20),
    Email VARCHAR(50),
    CONSTRAINT unique_pid UNIQUE (Person)
);

CREATE TABLE Review (
    rid INT PRIMARY KEY IDENTITY,
    Business INT FOREIGN KEY REFERENCES Business(bid),
    Users INT FOREIGN KEY REFERENCES Users(uid),
    Rating INT,
    Comment VARCHAR(200)
);
