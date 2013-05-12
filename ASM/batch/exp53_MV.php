<?php 
function exportMysqlToCsv($sql_query,$filename)
{
	$fh = fopen($filename, 'w') or die("can't open file");
	
	$csv_terminated = "\n";
	$csv_separator = ",";
	//$csv_enclosed = '"';
	$csv_enclosed = '';
	$csv_escaped = "\\";

	// Gets the data from the database
	$result = mysql_query($sql_query);
	$fields_cnt = mysql_num_fields($result);

	$schema_insert = '';

	for ($i = 0; $i < $fields_cnt; $i++)
	{
	$l = $csv_enclosed . str_replace($csv_enclosed, $csv_escaped . $csv_enclosed,
			stripslashes(mysql_field_name($result, $i))) . $csv_enclosed;
			$schema_insert .= $l;
	$schema_insert .= $csv_separator;
	} // end for

	$out = trim(substr($schema_insert, 0, -1));
	$out .= $csv_terminated;

	// Format the data
	while ($row = mysql_fetch_array($result)){
		$schema_insert = '';
		for ($j = 0; $j < $fields_cnt; $j++){
			if ($row[$j] == '0' || $row[$j] != '')	{
		
				if ($csv_enclosed == ''){
					$schema_insert .= $row[$j];
				} else{
					$schema_insert .= $csv_enclosed .
					str_replace($csv_enclosed, $csv_escaped . $csv_enclosed, $row[$j]) . $csv_enclosed;
					}
			} else{
				$schema_insert .= '';
			}
		
			if ($j < $fields_cnt - 1){
				$schema_insert .= $csv_separator;
			}
		} // end for
	
		$out .= $schema_insert;
		$out .= $csv_terminated;
	} // end while

	fwrite($fh, $out);
	fclose($fh);
	mysql_free_result($result);
    //exit;

}
// ************ CONSULTA BASE DE DADOS ************
$host="localhost"; $username="quickfix";$password="quickfix";$database="quickfix";

$link = mysql_connect($host,$username,$password);
if (!$link) {die('Not connected : ' . mysql_error());}
$db_selected = mysql_select_db($database, $link);
if (!$db_selected) {die ('Can\'t use $database : ' . mysql_error());}
mysql_set_charset('utf8');

$agentList=mysql_query("SELECT id_agent, id_strategy FROM agents WHERE status='active' AND type='random' ");
$numAgent=mysql_num_rows($agentList);

// *************************************************

function stopAll($_numAgent, $_agentList){
	// parar o ORDERMATCH
	exec("./scripts/ordermatch.sh stop > /dev/null &");
	// parar o MARKET MAKER
	exec("./scripts/marketmaker.sh stop > /dev/null &");
	// parar os AGENTES
	$i=0;
	while ($i < $_numAgent) {
		$agent=mysql_result($_agentList,$i,"id_agent");
		$statusTraders = exec("./scripts/randomtraders.sh status $agent");
		if($statusTraders == "STARTED"){exec("./scripts/randomtraders.sh stop $agent > /dev/null &");}
		$i++;
	}
}


function startAll($_numAgent, $_agentList){
	// parar o ORDERMATCH
	exec("./scripts/ordermatch.sh start > /dev/null &");
	// parar o MARKET MAKER
	sleep(2);
	exec("./scripts/marketmaker.sh start > /dev/null &");
	sleep(2);
	// parar os AGENTES
	$i=0;
	while ($i < $_numAgent) {
		$agent=mysql_result($_agentList,$i,"id_agent");
		$statusTraders = exec("./scripts/randomtraders.sh status $agent");
		if($statusTraders == "STOPPED"){exec("./scripts/randomtraders.sh start $agent > /dev/null &");}
		$i++;
	}
}


function setBudget($_numAgent,$_agentList, $cash, $stock){
	$i=0;
	while ($i < $_numAgent) {
		$agent=mysql_result($_agentList,$i,"id_strategy");
		mysql_query("UPDATE strategy SET number_stock=$stock,cash=$cash WHERE id_strategy=$agent ");
		$i++;
	}
}

function setLimitOper($_numAgent,$_agentList, $limit){
	$i=0;
	while ($i < $_numAgent) {
		$agent=mysql_result($_agentList,$i,"id_strategy");
		mysql_query("UPDATE strategy SET percentual_max_neg=$limit WHERE id_strategy=$agent ");
		$i++;
	}
}

function setVol($_numAgent,$_agentList, $vol){
	$i=0;
	while ($i < $_numAgent) {
		$agent=mysql_result($_agentList,$i,"id_strategy");
		mysql_query("UPDATE strategy SET volatility=$vol WHERE id_strategy=$agent ");
		$i++;
	}
}


function setSpread($spread){
	mysql_query("UPDATE strategy SET spread=$spread WHERE id_strategy=25 ");
}

function setMMLimitOper($lim){
	mysql_query("UPDATE strategy SET percentual_max_neg=$lim WHERE id_strategy=25 ");
}
//setup inicial
setBudget($numAgent, $agentList,100000,1000);
setLimitOper($numAgent, $agentList,0.5);
setVol($numAgent, $agentList,0.10);
setSpread(10);

$lim=1;
while ($lim <= 100) {

	echo "TRIAL MM LIM OPER:$lim \n";
	stopAll($numAgent, $agentList);
	
	sleep(1*30);//sleep for 1 min 
	
	setMMLimitOper($lim/100);
	
	startAll($numAgent, $agentList);
	
	sleep(30*60); //sleep for 30 mins
	
	$query_prices="SELECT * FROM quickfix.prices";
	$filename_prices="./results/test_mmLim_".$lim."_prices.csv";
	exportMysqlToCsv($query_prices, $filename_prices);
	
	$query_portfolio="SELECT * FROM quickfix.portfolio";
	$filename_portfolio="./results/test_mmLim_".$lim."_portfolios.csv";
	exportMysqlToCsv($query_portfolio, $filename_portfolio);
	
	$query_agents="SELECT id_agent, ticker, reference_stock_price, cash, number_stock, percentual_max_neg, cycle_time, initial_time, reference_exogenous, reference_cov, volatility, spread, number_exogenous, random_type  FROM quickfix.strategy s inner join quickfix.agents a on s.id_strategy = a.id_strategy where status='active'";
	$filename_agents="./results/test_mmLim_".$lim."_agents.csv";
	exportMysqlToCsv($query_agents, $filename_agents);
	
	$lim++;
	$lim++;
}


mysql_free_result($agentList);
mysql_close($link);

?>

