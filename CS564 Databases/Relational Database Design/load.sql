CREATE TABLE Sales(Store integer, Dept integer, WeekDate date, WeeklySales real, IsHoliday boolean, Type varchar(1), Size integer, Temperature real, FuelPrice real, CPI real, UnemploymentRate real);

\copy Sales FROM './SalesFile.csv' DELIMITER ',' CSV;

INSERT INTO Sales4
SELECT DISTINCT WeekDate,IsHoliday
FROM Sales;

INSERT INTO Sales3
SELECT DISTINCT Store, WeekDate, Temperature, FuelPrice, CPI, UnemploymentRate
FROM Sales;

INSERT INTO Sales2
SELECT DISTINCT Store, Type, Size
FROM Sales;

INSERT INTO Sales1
SELECT DISTINCT Store, Dept, WeekDate, WeeklySales
FROM Sales;

/* As a side note, the Sales1 table must be loaded last as it has the primary/foreign key constraints */

\copy (SELECT * FROM Sales1) TO 'results1.out' WITH CSV DELIMITER ','; 
\copy (SELECT * FROM Sales2) TO 'results2.out' WITH CSV DELIMITER ',';
\copy (SELECT * FROM Sales3) TO 'results3.out' WITH CSV DELIMITER ',';
\copy (SELECT * FROM Sales4) TO 'results4.out' WITH CSV DELIMITER ',';

/* Since UNION Requires the same amount of columns, I concatenated the outputs in linux terminal
   Commands:
	cat results1.out >> results.out
	cat results2.out >> results.out
	cat results3.out >> results.out
	cat results4.out >> results.out
*/
