-- Database: fapteBune

-- DROP DATABASE IF EXISTS "fapteBune";

CREATE DATABASE "fapteBune"
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
	last_name CHARACTER VARYING,
	first_name CHARACTER VARYING,
	username CHARACTER VARYING,
	password CHARACTER VARYING,
	city CHARACTER VARYING,
	street CHARACTER VARYING,
	street_no CHARACTER VARYING,
	phone_no CHARACTER VARYING
);

CREATE TABLE Need(
	id_need BIGINT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
	title CHARACTER VARYING,
	description CHARACTER VARYING,
	deadline TIMESTAMP,
	id_person_in_need BIGINT,
	id_person_helping BIGINT,
	status CHARACTER VARYING,
	
	FOREIGN KEY (id_person_in_need) REFERENCES Person(id_person),
	FOREIGN KEY (id_person_helping) REFERENCES Person(id_person)
);

INSERT INTO Person(last_name, first_name, username, password, city, street, street_no, phone_no) VALUES
('Pop', 'Alex', 'alex.pop', 'parola1', 'Cluj-Napoca', 'B.P. Hasdeu', '25', '0268355428'),
('Pal', 'Cosmin', 'cosmin.pal', 'parola2', 'Brasov', 'Memo', '28', '0755689287')

INSERT INTO Need(title, description, deadline, id_person_in_need, id_person_helping, status) VALUES
('Caut muzicanti', 'Muzicanti petrecere aniversara', '2024-02-02 18:45:00', 6, null, 'Caut erou!')
('Pisica disparuta', 'Mi-a disparut pisica', '2024-01-30 12:00:00', 1, null, 'Caut erou!')
('Nevoie tuns iarba', 'Ajutor iarba de la poarta', '2024-02-05 15:30:00', 2, null, 'Caut erou!'),
('Adu-mi mancare', 'Mi-e foame', '2024-02-01 10:45:00', 5, null, 'Caut erou!')

SELECT * FROM Person
SELECT * FROM Need