select d1.d as yr, d1.c as qtr, sum(case when d1.b = 'A' then d1.e else 0 end) as store_a_sales, sum(case when d1.b = 'B' then d1.e else 0 end) as store_b_sales
from
(
select h3_stores.store, h3_stores.type, case when date_part('month',h3_sales.weekdate) <= 3 then 1 when date_part('month',h3_sales.weekdate) <= 6 then 2 when date_part('month',h3_sales.weekdate) <= 9 then 3 else 4 end as qtr, date_part('year',h3_sales.weekdate) as yr, h3_sales.weeklysales
from h3_sales, h3_stores
where h3_stores.store = h3_sales.store AND h3_stores.type != 'C') as d1(a,b,c,d,e)
group by yr, qtr
UNION ALL
select d1.d as yr, d1.c as qtr, sum(case when d1.b = 'A' then d1.e else 0 end) as a_sales, sum(case when d1.b = 'B' then d1.e else 0 end) as b_sales
from
(
select h3_stores.store, h3_stores.type, CAST(NULL as integer) as qtr, date_part('year',h3_sales.weekdate) as yr, h3_sales.weeklysales
from h3_sales, h3_stores
where h3_stores.store = h3_sales.store AND h3_stores.type != 'C') as d1(a,b,c,d,e)
group by yr, qtr
order by yr, qtr;