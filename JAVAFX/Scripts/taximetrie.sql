-- Database: taximetrie

-- DROP DATABASE IF EXISTS taximetrie;

CREATE DATABASE taximetrie
    WITH
    OWNER = postgres
    ENCODING = 'UTF8'
    LC_COLLATE = 'English_United Kingdom.1252'
    LC_CTYPE = 'English_United Kingdom.1252'
    TABLESPACE = pg_default
    CONNECTION LIMIT = -1
    IS_TEMPLATE = False;
	

CREATE TABLE Person(
	id_person BIGINT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
	username CHARACTER VARYING UNIQUE NOT NULL, -- sare un id daca e duplicat??
	name CHARACTER VARYING NOT NULL
);

INSERT INTO Person(username, name) VALUES ('alex.pop', 'Pop Alex'), ('mihai.dobrin', 'Dobrin Mihai'), ('alex.cornel', 'Cornel Alex'), 
('costel.pal', 'Pal Costel'), ('david.piticas', 'Piticas David'), ('cosmin.bontea', 'Bontea Cosmin')

SELECT * FROM Person

CREATE TABLE Driver(
	id_driver BIGINT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
	id_person BIGINT,
	car_plate CHARACTER VARYING NOT NULL,
	
	FOREIGN KEY (id_person) REFERENCES Person(id_person) ON DELETE CASCADE
)

INSERT INTO Driver(id_person, car_plate) VALUES (2, 'BV 99 ABX'), (3, 'CJ 55 ALO'), (4, 'B 101 YES')

SELECT * FROM Driver

SELECT D.id_driver, D.car_plate, P.username FROM Driver D JOIN Person P on D.id_person = P.id_person

CREATE TABLE Taxi_Order(
	id_order BIGINT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
	id_person BIGINT,
	id_driver BIGINT,
	order_date TIMESTAMP NOT NULL,
	
	FOREIGN KEY (id_person) REFERENCES Person(id_person) ON DELETE CASCADE,
	FOREIGN KEY (id_driver) REFERENCES Driver(id_driver) ON DELETE CASCADE
)

INSERT INTO Taxi_Order(id_person, id_driver, order_date) VALUES (1, 2, '2024-01-24 12:30:54'), (1, 3, '2024-01-15 16:23:34'), 
(5, 1, '2023-12-22 19:29:55'), (7, 1, '2023-12-21 21:21:21'), (1, 2, '2023-11-30 09:15:05')

SELECT * FROM Taxi_Order