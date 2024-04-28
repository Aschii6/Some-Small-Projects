-- Database: zboruri

-- DROP DATABASE IF EXISTS zboruri;

CREATE DATABASE zboruri
    WITH
    OWNER = postgres
    ENCODING = 'UTF8'
    LC_COLLATE = 'English_United Kingdom.1252'
    LC_CTYPE = 'English_United Kingdom.1252'
    TABLESPACE = pg_default
    CONNECTION LIMIT = -1
    IS_TEMPLATE = False;
	
	
CREATE TABLE Client(
	id_client BIGINT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
	username CHARACTER VARYING UNIQUE NOT NULL,
	name CHARACTER VARYING NOT NULL
);

CREATE TABLE Flight(
	id_flight BIGINT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
	is_from CHARACTER VARYING NOT NULL,
	goes_to CHARACTER VARYING NOT NULL,
	departure_time TIMESTAMP NOT NULL,
	landing_time TIMESTAMP NOT NULL,
	seats INT NOT NULL
);

CREATE TABLE Ticket(
	id_ticket BIGINT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
	username CHARACTER VARYING NOT NULL,
	id_flight BIGINT NOT NULL,
	purchase_time TIMESTAMP NOT NULL,
	
	FOREIGN KEY (username) REFERENCES Client(username),
	FOREIGN KEY (id_flight) REFERENCES Flight(id_flight)
)

INSERT INTO Client(username, name) VALUES ('alex.pop', 'Pop Alex'), ('mihai.dobrin', 'Dobrin Mihai'), ('alex.cornel', 'Cornel Alex'), 
('costel.pal', 'Pal Costel')

INSERT INTO Flight(is_from, goes_to, departure_time, landing_time, seats) VALUES
('Romania', 'USA', '2024-01-24 13:38:00', '2024-01-24 23:11:00', 70),
('Austria', 'Germany', '2024-02-01 10:30:00', '2024-02-01 12:25:00', 60),
('Japan', 'South Korea', '2024-01-29 16:30:00', '2024-01-29 20:35:00', 80)

INSERT INTO Ticket(username, id_flight, purchase_time) VALUES ('alex.pop', 1, '2024-01-05 13:40:55'),
('costel.pal', 2, '2024-01-25 19:24:56'), ('alex.cornel', 3, '2024-01-24 12:25:43')

SELECT * FROM Client

SELECT * FROM Flight

SELECT * FROM Ticket