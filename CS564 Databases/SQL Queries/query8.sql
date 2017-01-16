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
limit 10;