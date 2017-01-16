select p1.a as dept, p2.b as avg
from
(
select d3.c as dept, avg(d3.f)
from 
(
select *, d2.b2/d1.b1 as percent_cont
from
(
select h3_sales.store, sum(h3_sales.weeklysales)
from h3_sales
group by h3_sales.store) as d1(a1,b1),
(
select h3_sales.dept, sum(h3_sales.weeklysales), h3_sales.store
from h3_sales
group by h3_sales.dept, h3_sales.store) as d2(a2,b2,c2)
where d2.b2/d1.b1 >= .05 AND d2.c2 = d1.a1) as d3(a,b,c,d,e,f)
group by d3.c
having count(a) >= 3
) as p1(a,b),
(
select d4.c as dept, avg(d4.f)
from 
(
select *, d2.b2/d1.b1 as percent_cont
from
(
select h3_sales.store, sum(h3_sales.weeklysales)
from h3_sales
group by h3_sales.store) as d1(a1,b1) INNER JOIN
(
select h3_sales.dept, sum(h3_sales.weeklysales), h3_sales.store
from h3_sales
group by h3_sales.dept, h3_sales.store) as d2(a2,b2,c2) ON d1.a1 = d2.c2) as d4(a,b,c,d,e,f)
group by d4.c) as p2(a,b)
where p1.a = p2.a;