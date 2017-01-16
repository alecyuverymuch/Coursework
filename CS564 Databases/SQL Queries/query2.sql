select distinct h3_temporaldata.store
from h3_temporaldata, (select h3_temporaldata.store, max(h3_temporaldata.fuelprice) from h3_temporaldata group by h3_temporaldata.store) as td(s,m)
where h3_temporaldata.unemploymentrate > 10 AND td.s = h3_temporaldata.store AND td.m < 4;