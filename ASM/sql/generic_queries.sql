SELECT SUBSTRING(message,1,512) AS MSG FROM messages ORDER BY msgseqnum;
DELETE FROM messages WHERE beginstring like 'FIX%';
DELETE FROM quickfix.portfolio WHERE id_agent like 'RAND%';
DELETE FROM sessions WHERE beginstring like 'FIX%';
REPLACE INTO quickfix.portfolio (id_agent, number_stock, cash) VALUES ('RANDOMTRADER01', 1,120.0);
SELECT * FROM rates;
DELETE FROM rates WHERE time >= '00:00:00';

SELECT rate FROM quickfix.rates WHERE simulation_time >= '20130224T095347' AND simulation_time<='20130224T095347';

SELECT price FROM prices ORDER BY time DESC LIMIT 1;
SELECT * FROM prices;
SELECT count(price) FROM prices;

SELECT AVG(price) as mean,STDDEV(price) as sd  FROM prices;
DELETE FROM quickfix.prices WHERE time <> '';
INSERT INTO quickfix.prices (time, volume, price) VALUES ('000-00-00 00:00:00',0,100);
SELECT reference_stock_price FROM quickfix.strategy s inner join quickfix.agents a on s.id_strategy = a.id_strategy where id_agent='ORDERMATCH';


SELECT id_agent FROM agents WHERE status='active' AND type NOT IN('mm', 'ordermatch');


DELETE FROM prices WHERE time <> '000-00-00 00:00:00';


SELECT (SELECT price FROM prices ORDER BY time DESC LIMIT 7) ORDER BY time ASC;
SELECT price FROM prices ORDER BY time DESC LIMIT 7;

DELETE FROM portfolio WHERE time <> '';

SELECT * FROM quickfix.portfolio;


SELECT g.price FROM (SELECT p.time, p.price FROM prices p ORDER BY p.time DESC LIMIT 7) g ORDER BY g.time ASC;





SELECT p.id_agent as AGENT,p.number_stock as NUMBER_STOCK,	p.cash as CASH, p.number_exogenous as EXO FROM (SELECT pt1.id_agent, pt1.number_stock, pt1.cash, pt1.number_exogenous FROM quickfix.portfolio pt1 INNER JOIN (SELECT MAX(pt2.time) as maxtime, pt2.id_agent FROM quickfix.portfolio pt2 GROUP BY pt2.id_agent) pt3 ON pt1.id_agent = pt3.id_agent AND pt1.time = pt3.maxtime) p INNER JOIN quickfix.agents a ON p.id_agent = a.id_agent WHERE a.status='active';



SELECT 
	p.id_agent as AGENT,
	p.number_stock as NUMBER_STOCK,
	p.cash as CASH,
	p.number_exogenous as EXO
FROM 
	(SELECT pt1.id_agent, pt1.number_stock, pt1.cash, pt1.number_exogenous FROM quickfix.portfolio pt1 INNER JOIN (SELECT MAX(pt2.time) as maxtime, pt2.id_agent FROM quickfix.portfolio pt2 GROUP BY pt2.id_agent) pt3 ON pt1.id_agent = pt3.id_agent AND pt1.time = pt3.maxtime) p
INNER JOIN 
	quickfix.agents a 
	ON 
		p.id_agent = a.id_agent 
WHERE 
	a.status='active';




SELECT pt1.id_agent, pt1.number_stock, pt1.cash, pt1.number_exogenous FROM quickfix.portfolio pt1 INNER JOIN (SELECT MAX(pt2.time) as maxtime, pt2.id_agent FROM quickfix.portfolio pt2 GROUP BY pt2.id_agent) pt3 ON pt1.id_agent = pt3.id_agent AND pt1.time = pt3.maxtime;



SELECT pt1.id_agent, pt1.number_stock, pt1.cash, pt1.number_exogenous 
	FROM quickfix.portfolio pt1 
INNER JOIN
	(SELECT MAX(pt2.time) as maxtime, pt2.id_agent FROM quickfix.portfolio pt2 GROUP BY pt2.id_agent) pt3
ON
	pt1.id_agent = pt3.id_agent AND
	pt1.time = pt3.maxtime;



SELECT * FROM quickfix.portfolio WHERE id_agent = 'MARKETMAKER';