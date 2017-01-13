CREATE TABLE Sales1(Store integer, Dept integer, WeekDate date, WeeklySales real, primary key (Store, Dept, WeekDate));

CREATE TABLE Sales2(Store integer, Type varchar(1), Size integer, primary key(Store));

CREATE TABLE Sales3(Store integer, WeekDate date, Temperature real, FuelPrice real, CPI real, UnemploymentRate real, primary key(Store, WeekDate));

CREATE TABLE Sales4(WeekDate date, IsHoliday boolean, primary key(WeekDate));

ALTER TABLE Sales1
ADD FOREIGN KEY (Store)
REFERENCES Sales2(Store);

ALTER TABLE Sales1
ADD FOREIGN KEY (Store,WeekDate)
REFERENCES Sales3(Store,WeekDate);

ALTER TABLE Sales1
ADD FOREIGN KEY (WeekDate)
REFERENCES Sales4(WeekDate);
