/* This is the verification file for Deliverable 6 */

/* This query tests subtraction of the Sales-Recreated_Sales tables and the result is 0 */
SELECT *
FROM Sales
Except
SELECT *
FROM
(
SELECT Sales1.Store, Sales1.Dept, Sales1.WeekDate, Sales1.WeeklySales , D2.IsHoliday, D2.Type, D2.Size, D2.Temperature, D2.FuelPrice, D2.CPI, D2.UnemploymentRate
FROM Sales1
INNER JOIN(
SELECT Sales2.Store, Sales2.Type, Sales2.Size, D1.WeekDate, D1.Temperature, D1.FuelPrice, D1.CPI, D1.UnemploymentRate, D1.IsHoliday
FROM Sales2
INNER JOIN (
SELECT Sales3.Store, Sales3.WeekDate, Sales3.Temperature, Sales3.FuelPrice, Sales3.CPI, Sales3.UnemploymentRate, Sales4.IsHoliday
FROM Sales3
INNER JOIN Sales4
ON Sales3.WeekDate = Sales4.WeekDate) as D1
ON Sales2.Store = D1.Store) as D2
ON Sales1.Store = D2.Store AND Sales1.WeekDate = D2.WeekDate
) as D3;

/* This query tests subtraction of the Recreated_Sales - Sales tables and the result is 0 */
SELECT *
FROM
(
SELECT Sales1.Store, Sales1.Dept, Sales1.WeekDate, Sales1.WeeklySales , D2.IsHoliday, D2.Type, D2.Size, D2.Temperature, D2.FuelPrice, D2.CPI, D2.UnemploymentRate
FROM Sales1
INNER JOIN(
SELECT Sales2.Store, Sales2.Type, Sales2.Size, D1.WeekDate, D1.Temperature, D1.FuelPrice, D1.CPI, D1.UnemploymentRate, D1.IsHoliday
FROM Sales2
INNER JOIN (
SELECT Sales3.Store, Sales3.WeekDate, Sales3.Temperature, Sales3.FuelPrice, Sales3.CPI, Sales3.UnemploymentRate, Sales4.IsHoliday
FROM Sales3
INNER JOIN Sales4
ON Sales3.WeekDate = Sales4.WeekDate) as D1
ON Sales2.Store = D1.Store) as D2
ON Sales1.Store = D2.Store AND Sales1.WeekDate = D2.WeekDate
) as D3
EXCEPT
SELECT *
FROM Sales;

/* Since both of these results are 0, this means that the original sales table and the recreated_sales table made from joining the BCNF decomposition are the equivalent */ 