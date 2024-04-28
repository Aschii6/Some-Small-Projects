-- Database: trenuri

-- DROP DATABASE IF EXISTS trenuri;

CREATE DATABASE trenuri
    WITH
    OWNER = postgres
    ENCODING = 'UTF8'
    LC_COLLATE = 'English_United Kingdom.1252'
    LC_CTYPE = 'English_United Kingdom.1252'
    TABLESPACE = pg_default
    CONNECTION LIMIT = -1
    IS_TEMPLATE = False;
	
	
CREATE TABLE City(
	id_city BIGINT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
	name CHARACTER VARYING NOT NULL
);

CREATE TABLE TrainStation(
	id_station BIGINT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
	id_train BIGINT NOT NULL,
	id_departure_city BIGINT NOT NULL,
	id_destination_city BIGINT NOT NULL,
	
	FOREIGN KEY (id_departure_city) REFERENCES City(id_city),
	FOREIGN KEY (id_destination_city) REFERENCES City(id_city)
);

CREATE TABLE Ticket(
	id_ticket BIGINT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
	id_train BIGINT NOT NULL,
	id_departure_city BIGINT NOT NULL,
	ticket_date DATE NOT NULL,
	
	FOREIGN KEY (id_departure_city) REFERENCES City(id_city)
);

INSERT INTO City(name) VALUES ('Cluj-Napoca'), ('Brasov'), ('Sibiu'), ('Alba Iulia')

INSERT INTO TrainStation(id_train, id_departure_city, id_destination_city) VALUES
(1, 1, 3), (1, 3, 2), (2, 2, 3), (3, 3, 4), (3, 4, 1), (4, 1, 2)


SELECT * FROM City
SELECT * FROM TrainStation
SELECT * FROM Ticket