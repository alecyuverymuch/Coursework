select *, 100*d1.c/sum(d1.c) over (partition by d1.b) as perc_contribution
from (
select date_part('month',h3_sales.weekdate), h3_stores.type, SUM(h3_sales.weeklysales)
from h3_sales, h3_stores
where h3_stores.store = h3_sales.store
group by date_part('month',h3_sales.weekdate), h3_stores.type
) as d1(a,b,c)
order by d1.b,d1.a;