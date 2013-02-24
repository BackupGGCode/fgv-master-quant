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

SELECT AVG(price) as mean,STDDEV(price) as sd  FROM prices;
DELETE FROM quickfix.prices WHERE time <> '';
INSERT INTO quickfix.prices (time, volume, price) VALUES ('000-00-00 00:00:00',0,100);
SELECT reference_stock_price FROM quickfix.strategy s inner join quickfix.agents a on s.id_strategy = a.id_strategy where id_agent='ORDERMATCH';


DELETE FROM prices WHERE time <> '000-00-00 00:00:00';



