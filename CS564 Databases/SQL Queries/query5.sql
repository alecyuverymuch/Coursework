select distinct d4.store
from
(
select d3.store, d3.yr, sum(d3.num_sales) as total_sales, d3.max_sales
from
(
select d2.store, d2.dept, d2.yr, d2.num_sales, d1.num_dept*52 as max_sales
from
(
select store, count(distinct dept) as num_dept
from h3_sales
group by store
) as d1 JOIN
(
select store, dept, date_part('year',h3_sales.weekdate) as yr, count(weeklysales) as num_sales
from h3_sales
group by store, dept, date_part('year',h3_sales.weekdate)
) as d2 ON d1.store = d2.store
) as d3
group by d3.store, d3.yr, d3.max_sales
) as d4
where d4.total_sales = d4.max_sales;