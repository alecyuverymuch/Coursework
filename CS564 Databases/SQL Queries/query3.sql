select count(*)
from 
(select avg(hol.avg_sales)
from
(select h3_sales.weekdate, h3_sales.weeklysales
from h3_sales, h3_holidays
where h3_sales.weekdate = h3_holidays.weekdate AND h3_holidays.isholiday = true) as hol(date,avg_sales)) as hol1(k),
(select nonhol.date, avg(nonhol.avg_sales)
from
(select h3_sales.weekdate, h3_sales.weeklysales
from h3_sales, h3_holidays
where h3_sales.weekdate = h3_holidays.weekdate AND h3_holidays.isholiday = false) as nonhol(date,avg_sales)
group by nonhol.date) as nonhol1(w,a)
where nonhol1.a > hol1.k;