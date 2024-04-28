-- Database: oferteDeVacanta

-- DROP DATABASE IF EXISTS "oferteDeVacanta";

CREATE DATABASE "oferteDeVacanta"
    WITH
    OWNER = postgres
    ENCODING = 'UTF8'
    LC_COLLATE = 'English_United Kingdom.1252'
    LC_CTYPE = 'English_United Kingdom.1252'
    TABLESPACE = pg_default
    CONNECTION LIMIT = -1
    IS_TEMPLATE = False;
	
	
CREATE TABLE Location(
	id_location BIGINT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
	name CHARACTER VARYING
);

CREATE TABLE Hotel(
	id_hotel BIGINT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
	id_location BIGINT,
	name CHARACTER VARYING,
	no_of_rooms INT,
	price_per_night DOUBLE PRECISION,
	type CHARACTER VARYING,
	
	FOREIGN KEY (id_location) REFERENCES Location(id_location)
);

CREATE TABLE SpecialOffer(
	id_offer BIGINT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
	id_hotel BIGINT,
	start_date DATE,
	end_date DATE,
	percents INT,
	
	FOREIGN KEY (id_hotel) REFERENCES Hotel(id_hotel)
);

CREATE TABLE Client(
	id_client BIGINT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
	name CHARACTER VARYING,
	fidelity_grade INT,
	age INT,
	hobby CHARACTER VARYING
);

CREATE TABLE Reservation(
	id_reservation BIGINT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
	id_client BIGINT,
	id_hotel BIGINT,
	start_date DATE,
	no_of_nights INT,
	
	FOREIGN KEY (id_client) REFERENCES Client(id_client),
	FOREIGN KEY (id_hotel) REFERENCES Hotel(id_hotel)
);

INSERT INTO Location(name) VALUES ('Brasov'), ('Sibiu'), ('Cluj-Napoca')

INSERT INTO Hotel(id_location, name, no_of_rooms, price_per_night, type) VALUES
(1, 'Hotel 1', 20, 100, 'Teenagers'), (2, 'Hotel 2', 15, 150, 'Family'), (3, 'Hotel 3', 10, 120, 'OldPeople')

INSERT INTO SpecialOffer(id_hotel, start_date, end_date, percents) VALUES
(1, '2024-01-25', '2024-01-29', 40), (2, '2024-01-29', '2024-02-02', 50), (2, '2024-02-12', '2024-02-15', 60),
(3, '2024-02-01', '2024-02-05', 15)

INSERT INTO Client(name, fidelity_grade, age, hobby) VALUES
('Alex P.', 55, 20, 'Reading'), ('Cosmin B.', 40, 21, 'Reading'), ('Denis L.', 60, 24, 'Music')

SELECT * FROM Location
SELECT * FROM Hotel
SELECT * FROM SpecialOffer
SELECT * FROM Client
SELECT * FROM Reservation
