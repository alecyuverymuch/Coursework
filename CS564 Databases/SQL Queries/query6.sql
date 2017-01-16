select 'Temperature' as attribute, case when corr(h3_temporaldata.temperature,h3_sales.weeklysales) < 0 then '-' else '+' end as corr_sign, corr(h3_temporaldata.temperature,h3_sales.weeklysales)as correlation
from h3_temporaldata, h3_sales
where h3_sales.weekdate = h3_temporaldata.weekdate AND h3_sales.store = h3_temporaldata.store
UNION ALL
select 'Fuel Price' as attribute, case when corr(h3_temporaldata.fuelprice,h3_sales.weeklysales) < 0 then '-' else '+' end as corr_sign, corr(h3_temporaldata.fuelprice,h3_sales.weeklysales)as correlation
from h3_temporaldata, h3_sales
where h3_sales.weekdate = h3_temporaldata.weekdate AND h3_sales.store = h3_temporaldata.store
UNION ALL
select 'CPI' as attribute, case when corr(h3_temporaldata.cpi,h3_sales.weeklysales) < 0 then '-' else '+' end as corr_sign, corr(h3_temporaldata.cpi,h3_sales.weeklysales)as correlation
from h3_temporaldata, h3_sales
where h3_sales.weekdate = h3_temporaldata.weekdate AND h3_sales.store = h3_temporaldata.store
UNION ALL
select 'UnemploymentRate' as attribute, case when corr(h3_temporaldata.unemploymentrate,h3_sales.weeklysales) < 0 then '-' else '+' end as corr_sign, corr(h3_temporaldata.unemploymentrate,h3_sales.weeklysales)as correlation
from h3_temporaldata, h3_sales
where h3_sales.weekdate = h3_temporaldata.weekdate AND h3_sales.store = h3_temporaldata.store;