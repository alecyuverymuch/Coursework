select *
from (	
SELECT dd.store, MIN(dd.hol_sales) as hol_sales
from 
(SELECT h3_sales.store, SUM(h3_sales.weeklysales)
from h3_holidays, h3_sales
where h3_holidays.isholiday = true AND h3_holidays.weekdate = h3_sales.weekdate
group by h3_sales.store) as dd(store,hol_sales)
group by dd.store
order by MIN(dd.hol_sales) asc
limit 1) first
UNION ALL
select *
from (	
SELECT dd.store, MAX(dd.hol_sales)
from 
(SELECT h3_sales.store, SUM(h3_sales.weeklysales)
from h3_holidays, h3_sales
where h3_holidays.isholiday = true AND h3_holidays.weekdate = h3_sales.weekdate
group by h3_sales.store) as dd(store,hol_sales)
group by dd.store
order by MAX(dd.hol_sales) desc
limit 1) second;