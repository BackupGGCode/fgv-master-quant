SELECT SUBSTRING(message,1,512) AS MSG FROM messages ORDER BY msgseqnum;
DELETE FROM messages WHERE beginstring like 'FIX%';
DELETE FROM quickfix.portfolio WHERE id_agent like 'RAND%';
DELETE FROM sessions WHERE beginstring like 'FIX%';
REPLACE INTO quickfix.portfolio (id_agent, number_stock, cash) VALUES ('RANDOMTRADER01', 1,120.0);
SELECT * FROM rates;
DELETE FROM rates WHERE time >= '00:00:00';