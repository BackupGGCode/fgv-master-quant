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
	
	if($_POST['pricesType']){
	$query_prices="SELECT * FROM quickfix.prices";
	$filename_prices="test".$_POST['testnumber']."_prices.csv";
	exportMysqlToCsv($query_prices, $filename_prices);
	}
	
	if($_POST['portfoliosType']){
	$query_portfolio="SELECT * FROM quickfix.portfolio";
	$filename_portfolio="test".$_POST['testnumber']."_portfolios.csv";
	exportMysqlToCsv($query_portfolio, $filename_portfolio);
	}
	
	if($_POST['agentsType']){
	$query_agents="SELECT id_agent, ticker, reference_stock_price, cash, number_stock, percentual_max_neg, cycle_time, initial_time, reference_exogenous, reference_cov, volatility, spread, number_exogenous, random_type  FROM quickfix.strategy s inner join quickfix.agents a on s.id_strategy = a.id_strategy where status='active'";
	$filename_agents="test".$_POST['testnumber']."_agents.csv";
	exportMysqlToCsv($query_agents, $filename_agents);
	}
}

 


?>


<html>
<body>
<div style="width:200px;height:35px;border:2px dotted blue;vertical-align:middle" align="center" >
<form name='formPrices'  action="download.php" method="post" style="vertical-align:middle" >
<b>Test #:</b> <input type="text" name="testnumber" size="3" style="vertical-align:middle">
<input name ="pricesType" type="image" src='./img/prices.png' value="Prices"  style="vertical-align:middle">
<input name="portfoliosType" type="image" src='./img/portfolios.png' value="Portfolios" style="vertical-align:middle">
<input name="agentsType" type="image" src='./img/agents.png' value="Agents" style="vertical-align:middle">
</form>
<div>
</body>
</html>