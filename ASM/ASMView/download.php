 <?php 
 
 $user="quickfix";
 $pass="quickfix";
 $db="quickfix";
 $host="localhost";
 
// Connect to the database
$link = mysql_connect($host, $user, $pass);
mysql_select_db($db);
 
require 'exportcsv.inc.php';



if(isset($_POST['testnumber'])){
	
	
	$query_prices="SELECT * FROM quickfix.prices";
	$filename_prices="test".$_POST['testnumber']."_prices.csv";
	exportMysqlToCsv($query_prices, $filename_prices);
	
	$query_portfolio="SELECT * FROM quickfix.portfolio";
	$filename_portfolio="test".$_POST['testnumber']."_portfolios.csv";
	exportMysqlToCsv($query_portfolio, $filename_portfolio);
	
	$query_agents="SELECT id_agent, ticker, reference_stock_price, cash, number_stock, percentual_max_neg, cycle_time, initial_time, reference_exogenous, reference_cov, volatility, spread, number_exogenous, random_type  FROM quickfix.strategy s inner join quickfix.agents a on s.id_strategy = a.id_strategy where status='active'";
	$filename_agents="test".$_POST['testnumber']."_agents.csv";
	exportMysqlToCsv($query_agents, $filename_agents);
}

 


?>

<html>
<body>

<form action="download.php" method="post">
Test Number: <input type="text" name="testnumber">
<input type="submit"  value="Download">
</form>

</body>
</html>