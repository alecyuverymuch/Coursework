CREATE TABLE Movie ( movie_ID integer , director_ID integer , year integer , rating float , title varchar(255) , genre varchar(255) , studio varchar(255) , 
primary key (movie_ID));

CREATE TABLE Casting ( movie_ID integer , actor_ID integer , role varchar(255) , primary key (movie_ID , actor_ID));

CREATE TABLE Actor ( actor_ID integer , age integer , name varchar(255) , gender varchar(255) , primary key (actor_ID));

CREATE TABLE Director ( director_ID integer , age integer , rating integer , name varchar(255) , primary key (director_ID));

ALTER TABLE Movie
ADD FOREIGN KEY (director_ID)
REFERENCES Director(director_ID);

ALTER TABLE Casting
ADD FOREIGN KEY (actor_ID)
REFERENCES Actor(actor_ID);

ALTER TABLE Casting
ADD FOREIGN KEY (movie_ID)
REFERENCES Movie(movie_ID);

INSERT INTO Director (director_ID, age, rating, name)
VALUES (0,45,9.3,'Charles');

INSERT INTO Movie (movie_ID, director_ID, year, rating, title, genre, studio)
VALUES (0,0,2016,7.5,'My Movie','Horror','My Studio');

INSERT INTO Actor (actor_ID, age, name, gender)
VALUES (0,25,'Rem','female');

INSERT INTO Actor (actor_ID, age, name, gender)
VALUES (1,21,'Andrew','male');

INSERT INTO Actor (actor_ID, age, name, gender)
VALUES (2,20,'Alec','male');

INSERT INTO Casting (movie_ID, actor_ID, role)
VALUES (0,0,'Female Lead');

INSERT INTO Casting (movie_ID, actor_ID, role)
VALUES (0,1,'Male Lead');

INSERT INTO Casting (movie_ID, actor_ID, role)
VALUES (0,2,'Male Extra');