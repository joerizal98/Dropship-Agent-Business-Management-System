-- phpMyAdmin SQL Dump
-- version 5.1.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Jan 15, 2022 at 05:33 AM
-- Server version: 10.4.21-MariaDB
-- PHP Version: 8.0.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `dabm`
--
CREATE DATABASE IF NOT EXISTS `dabm` DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci;
USE `dabm`;

-- --------------------------------------------------------

--
-- Table structure for table `agent`
--

CREATE TABLE `agent` (
  `AgentID` varchar(20) NOT NULL,
  `FirstName` varchar(30) NOT NULL,
  `LastName` varchar(30) NOT NULL,
  `ContactNo` varchar(15) NOT NULL,
  `Email` varchar(25) NOT NULL,
  `Password` varchar(25) NOT NULL,
  `SecurityQuestion` varchar(30) NOT NULL,
  `CardNo` smallint(6) NOT NULL,
  `CardBank` varchar(30) NOT NULL,
  `CardExpiryDate` date NOT NULL,
  `CardCVVNo` tinyint(3) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `agent`
--

INSERT INTO `agent` (`AgentID`, `FirstName`, `LastName`, `ContactNo`, `Email`, `Password`, `SecurityQuestion`, `CardNo`, `CardBank`, `CardExpiryDate`, `CardCVVNo`) VALUES
('FC1001', 'Mia', 'Sara', '01123', 'Mia123@gmail.com', '999', 'hantu', 0, '', '0000-00-00', 0),
('FC1002', 'David', 'Beckham', '011255912', 'David@gmail.com', '12345', 'Ball', 0, '', '0000-00-00', 0),
('FC1009', 'Lina', 'Razak', '0112780', 'Lina@gmail.com', 'lina98', 'lolipop', 0, '', '0000-00-00', 0),
('FC123', 'Joe', 'Rizal', '01126880616', 'Joe@gmail.com', '12343', 'keyboard', 0, '', '0000-00-00', 0),
('FC236', 'Kenna', 'Reevas', '0138524943', 'KenaAwesome@gmail.com', 'Kena98', '007', 0, '', '0000-00-00', 0),
('FC901', 'Joe', 'Lina', '011278313', 'Joe@gmail.com', '1234', 'meow', 0, '', '0000-00-00', 0);

-- --------------------------------------------------------

--
-- Table structure for table `invoice`
--

CREATE TABLE `invoice` (
  `InvoiceID` varchar(20) NOT NULL,
  `OrderID` int(5) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `invoice`
--

INSERT INTO `invoice` (`InvoiceID`, `OrderID`) VALUES
('Xe123', 1);

-- --------------------------------------------------------

--
-- Table structure for table `order1`
--

CREATE TABLE `order1` (
  `OrderID` int(5) NOT NULL,
  `OrderDescription` varchar(100) NOT NULL,
  `OrderTime` time NOT NULL DEFAULT current_timestamp(),
  `OrderDate` date NOT NULL DEFAULT current_timestamp(),
  `TotalPrice` decimal(10,2) NOT NULL,
  `AgentID` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `order1`
--

INSERT INTO `order1` (`OrderID`, `OrderDescription`, `OrderTime`, `OrderDate`, `TotalPrice`, `AgentID`) VALUES
(1, 'Have a nice day :)', '12:11:10', '2021-11-10', '10.00', 'FC123'),
(2, 'Have a nice day :)', '12:11:10', '2021-12-10', '12.00', 'FC123'),
(3, 'New product', '20:57:03', '2022-01-12', '12.00', 'FC123'),
(4, 'Have a nice day :)', '20:57:48', '2022-01-05', '21.00', 'FC123'),
(5, 'Nice Handbag', '00:28:19', '2022-01-13', '15.00', 'FC123'),
(7, 'Have a nice day :)', '21:28:38', '2022-01-09', '12.00', 'FC123'),
(8, 'Have a nice day :)', '21:29:43', '2022-01-09', '13.00', 'FC123'),
(9, 'New Hoodie and bag', '10:51:01', '2022-01-14', '25.00', 'FC123');

-- --------------------------------------------------------

--
-- Table structure for table `payment`
--

CREATE TABLE `payment` (
  `PaymentID` varchar(20) NOT NULL,
  `InvoiceID` varchar(20) NOT NULL,
  `PaymentTime` time NOT NULL,
  `PaymentDate` date NOT NULL,
  `PaymentTypeID` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `payment`
--

INSERT INTO `payment` (`PaymentID`, `InvoiceID`, `PaymentTime`, `PaymentDate`, `PaymentTypeID`) VALUES
('HL123', 'Xe123', '21:05:08', '2022-01-12', 'CASH1');

-- --------------------------------------------------------

--
-- Table structure for table `payment_type`
--

CREATE TABLE `payment_type` (
  `PaymentTypeID` varchar(20) NOT NULL,
  `Type` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `payment_type`
--

INSERT INTO `payment_type` (`PaymentTypeID`, `Type`) VALUES
('CASH1', 'Cash and COD');

-- --------------------------------------------------------

--
-- Table structure for table `product`
--

CREATE TABLE `product` (
  `ProductID` varchar(20) NOT NULL,
  `ProductName` varchar(100) NOT NULL,
  `PricePerUnit` decimal(10,2) DEFAULT NULL,
  `Description` varchar(500) NOT NULL,
  `SKU` int(33) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `product`
--

INSERT INTO `product` (`ProductID`, `ProductName`, `PricePerUnit`, `Description`, `SKU`) VALUES
('1', 'Jasut', '15.00', 'Cheap Shoe', 15),
('2', 'Water Bottle', '15.00', 'Good Quality', 20),
('3', 'Hoodie', '25.00', 'Cheap Hoodie', 10),
('5', 'Mousepad', '13.00', 'AVF Mousepad', 15),
('6', 'Fried Chicken', '9.00', 'Ayam Goreng ', 10),
('7', 'Keyboard', '15.00', 'Razer keyboard', 5);

-- --------------------------------------------------------

--
-- Table structure for table `product_order`
--

CREATE TABLE `product_order` (
  `OrderID` int(5) NOT NULL,
  `ProductID` varchar(20) NOT NULL,
  `Quantity` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Indexes for dumped tables
--

--
-- Indexes for table `agent`
--
ALTER TABLE `agent`
  ADD PRIMARY KEY (`AgentID`);

--
-- Indexes for table `invoice`
--
ALTER TABLE `invoice`
  ADD PRIMARY KEY (`InvoiceID`),
  ADD KEY `OrderID` (`OrderID`);

--
-- Indexes for table `order1`
--
ALTER TABLE `order1`
  ADD PRIMARY KEY (`OrderID`),
  ADD KEY `AgentID` (`AgentID`);

--
-- Indexes for table `payment`
--
ALTER TABLE `payment`
  ADD PRIMARY KEY (`PaymentID`),
  ADD KEY `InvoiceID` (`InvoiceID`),
  ADD KEY `PaymentTypeID` (`PaymentTypeID`);

--
-- Indexes for table `payment_type`
--
ALTER TABLE `payment_type`
  ADD PRIMARY KEY (`PaymentTypeID`);

--
-- Indexes for table `product`
--
ALTER TABLE `product`
  ADD PRIMARY KEY (`ProductID`);

--
-- Indexes for table `product_order`
--
ALTER TABLE `product_order`
  ADD KEY `OrderID` (`OrderID`),
  ADD KEY `ProductID` (`ProductID`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `order1`
--
ALTER TABLE `order1`
  MODIFY `OrderID` int(5) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=10;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `invoice`
--
ALTER TABLE `invoice`
  ADD CONSTRAINT `invoice_ibfk_1` FOREIGN KEY (`OrderID`) REFERENCES `order1` (`OrderID`);

--
-- Constraints for table `order1`
--
ALTER TABLE `order1`
  ADD CONSTRAINT `order1_ibfk_1` FOREIGN KEY (`AgentID`) REFERENCES `agent` (`AgentID`);

--
-- Constraints for table `payment`
--
ALTER TABLE `payment`
  ADD CONSTRAINT `payment_ibfk_1` FOREIGN KEY (`InvoiceID`) REFERENCES `invoice` (`InvoiceID`),
  ADD CONSTRAINT `payment_ibfk_2` FOREIGN KEY (`PaymentTypeID`) REFERENCES `payment_type` (`PaymentTypeID`);

--
-- Constraints for table `product_order`
--
ALTER TABLE `product_order`
  ADD CONSTRAINT `product_order_ibfk_1` FOREIGN KEY (`OrderID`) REFERENCES `order1` (`OrderID`),
  ADD CONSTRAINT `product_order_ibfk_2` FOREIGN KEY (`ProductID`) REFERENCES `product` (`ProductID`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
