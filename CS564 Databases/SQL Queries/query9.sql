select q8.a as dept, d4.c as yr, d4.b as mo, sum(d4.d) over (partition by q8.a order by q8.a,d4.c,d4.b) as cumulative_sales
from
(
select d3.a as dept, sum(d3.b) as normsales
from
(
select d1.b as dept, d1.c/d2.b as normsales
from 
(
select h3_sales.store, h3_sales.dept, sum(h3_sales.weeklysales)
from h3_sales
group by h3_sales.store, h3_sales.dept
) as d1(a,b,c) INNER JOIN
(
select h3_stores.store, h3_stores.size
from h3_stores) as d2(a,b) ON d1.a = d2.a) as d3(a,b)
group by d3.a
order by normsales desc
limit 10) as q8(a,b),
(
select h3_sales.dept, date_part('month',h3_sales.weekdate) as month, date_part('year',h3_sales.weekdate) as yr, sum(h3_sales.weeklysales)
from h3_sales
group by h3_sales.dept, date_part('month',h3_sales.weekdate), date_part('year',h3_sales.weekdate)
) as d4(a,b,c,d)
where q8.a = d4.a
order by dept,yr,mo
;