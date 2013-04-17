<head>
<b><center>BrASM Test Report</center></b>
<br>
</head>
<body>
<?php
$previewGraph="";
$previewStats="";
if(isset($_POST['testnumber'])){
	// Connect to the database
	$link = mysql_connect($host, $username, $password);
	mysql_select_db($database);
	require 'exportcsv.inc.php';

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

	if($_POST['Preview']){
		$testNumber = $_POST['testnumber'];
		$cmd ="cd ./scripts/;Rscript report.R $testNumber";
		$previewStats = shell_exec($cmd);
	
		$previewGraph .="<div align='center'>";
		$previewGraph .= "<img src='./trials/test".$testNumber."_graphPriceVolume.png'/>";
		$previewGraph .="</div>";
		$previewGraph .="";
		$previewGraph .= "<br>";
		$previewGraph .= "<table>";
		$previewGraph .= "<tr>";
		$previewGraph .= "<td>";
		$previewGraph .= "<img src='./trials/test".$testNumber."_graphRt.png'/>";
		$previewGraph .= "</td>";
		$previewGraph .= "<td>";
		$previewGraph .= "<img src='./trials/test".$testNumber."_graphHistogramRt.png' />";
		$previewGraph .= "</td>";
		$previewGraph .= "</tr>";
		$previewGraph .= "</table>";
	}

}

?>

<div align='center' style='width:400px;height:70px;vertical-align:middle'  >
<form name='formPrices'  action="report.php" method="post" style="vertical-align:middle" >
<b>Test number:</b> <input type="text" name="testnumber" size="3" style="vertical-align:middle" value="<?php echo $_POST['testnumber']; ?>">
<input name ="pricesType" type="image" src='./img/prices.png' value="Prices"  style="vertical-align:middle">
<input name="portfoliosType" type="image" src='./img/portfolios.png' value="Portfolios" style="vertical-align:middle">
<input name="agentsType" type="image" src='./img/agents.png' value="Agents" style="vertical-align:middle">
<input name="Preview" type="image" src='./img/preview.png' value="Preview" style="vertical-align:middle">
</form>
</div>

<div> <?php echo $previewStats; ?> </div>
<div> <?php echo $previewGraph; ?> </div>
</body>