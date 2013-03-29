<?php

header('Refresh: 3');

$username="quickfix";
$password="quickfix";
$database="quickfix";
$host="localhost";


$link = mysql_connect($host,$username,$password);
if (!$link) {
	die('Not connected : ' . mysql_error());
}

$db_selected = mysql_select_db($database, $link);
if (!$db_selected) {
	die ('Can\'t use $database : ' . mysql_error());
}


mysql_set_charset('utf8');
$query="SELECT price, time FROM prices";
$result=mysql_query($query);

$num=mysql_num_rows($result);


#$query_portfolio="SELECT id_agent as AGENT, number_stock as NUMBER_STOCK, cash as CASH FROM portfolio";
$query_portfolio="SELECT p.id_agent as AGENT,p.number_stock as NUMBER_STOCK,	p.cash as CASH, p.number_exogenous as EXO FROM (SELECT pt1.id_agent, pt1.number_stock, pt1.cash, pt1.number_exogenous FROM quickfix.portfolio pt1 INNER JOIN (SELECT MAX(pt2.time) as maxtime, pt2.id_agent FROM quickfix.portfolio pt2 GROUP BY pt2.id_agent) pt3 ON pt1.id_agent = pt3.id_agent AND pt1.time = pt3.maxtime) p INNER JOIN quickfix.agents a ON p.id_agent = a.id_agent WHERE a.status='active'";
$result_portfolio=mysql_query($query_portfolio);

$num_portfolio=mysql_num_rows($result_portfolio);



mysql_close();

echo "<b><center>BrASM Monitor</center></b>";

$price_array = array();

$LastPx=0.0;
$LastLastPx=0.0;

$i=0;
$j=0;

while ($i < $num) {
	
	$LastLastPx=$LastPx;
	
	$LastPx=mysql_result($result,$i,"price");

	$LastPx = round($LastPx, 2);

	$row_price_array=array($j++,(float)$LastPx);
		
	array_push($price_array,$row_price_array);
	
	$i++;
}



$i--;
$LastPxTime =mysql_result($result,$i,"time");
$query_exogenous="SELECT value FROM quickfix.exogenous WHERE simulation_time <= '$LastPxTime' ORDER BY simulation_time DESC LIMIT 1";
$result_exogenous=mysql_query($query_exogenous);
$num_exo=mysql_num_rows($result_exogenous);
$i=0;
$LastExoPrice=0;
while ($i < $num_exo) {
	$LastExoPrice=mysql_result($result_exogenous,$i,"value");
	$i++;
}



echo "<script type='text/javascript'> var price_array = ".json_encode($price_array).";</script>";

?>

<html>
<head>

<script type="text/javascript" src="scripts/jquery.min.js"></script>
<script type="text/javascript" src="scripts/jquery.jqplot.min.js"></script>
<script type="text/javascript" src="scripts/plugins/jqplot.canvasTextRenderer.min.js"></script>
<script type="text/javascript" src="scripts/plugins/jqplot.canvasAxisLabelRenderer.min.js"></script>
<!--  <script type="text/javascript" src="scripts/plugins/jqplot.jqplot.dateAxisRenderer.js"></script>
<script type="text/javascript" src="scripts/plugins/jqplot.jqplot.dateAxisRenderer.min.js"></script> -->
<link type="text/css" rel="stylesheet" hrf="scripts/jquery.jqplot.min.css" />

</head>
<body>

<table>
  <tr>
  
	<td>
		<div id="chart1" style="height:500px; width:600px; font-size:8pt;"></div>
	</td>

	<td>
		<div>
		<?php 
		
		$arrow="";
		if ($LastPx > $LastLastPx){
			$arrow="&uarr;";
		}
		if ($LastPx < $LastLastPx){
			$arrow="&darr;";
		}
		if ($LastPx == $LastLastPx){
			$arrow="&ndash;";
		}
		$LastPx = sprintf('%0.2f', $LastPx);
		$LastExoPrice = sprintf('%0.2f', $LastExoPrice);
		echo "<table border='0' cellpadding='3' cellspacing='3' width='350'>";
		echo "<tbody align='center' style='font-family:verdana; color:red ; font-size: 12pt'>";
		echo "<tr><td>Stock price: <b>$$LastPx  $arrow</b></td><td>Exogenous Price: <b>$$LastExoPrice</b></td></tr>";
		echo "</table>";
		
		
		echo "<table border='1' cellpadding='3' cellspacing='0' width='350'>";
		echo "<tbody align='center' style='font-family:verdana; color:black; background-color:yellow ; font-size: 10pt'>";
		echo "<tr><td><b>Agent</b></td><td><b>Stock (#)</b></td><td><b>Exog (#)</b></td><td><b>Cash ($)</b></td><td><b>Wealth ($)</b></td></tr>";
		echo "<tbody align='center' style='font-family:verdana; font-size: 8pt'>";
		
		$tot_number_stock = 0;
		$tot_number_exo = 0;
		$tot_cash= 0;
		$tot_wealth =0;
		$i=0;

		while ($i < $num_portfolio) {
			$agent=mysql_result($result_portfolio,$i,"AGENT");
			$number_stock=mysql_result($result_portfolio,$i,"NUMBER_STOCK");
			$number_exogenous=mysql_result($result_portfolio,$i,"EXO");
			$cash=mysql_result($result_portfolio,$i,"CASH");
			$wealth = $cash + $number_stock*$LastPx +$number_exogenous*$LastExoPrice;
			
			$tot_number_stock = $tot_number_stock + $number_stock;
			$tot_number_exo = $tot_number_exo + $number_exogenous;
			$tot_cash = $tot_cash + $cash;
			$tot_wealth = $tot_wealth + $wealth;
			
			$wealth = sprintf('%0.2f', $wealth);
			$cash = sprintf('%0.2f', $cash);
			echo "<tr><td>$agent</td><td>$number_stock</td><td>$number_exogenous</td><td>$cash</td><td>$wealth</td></tr>";
			

			$i++;
		}
		echo "<tbody align='center' style='font-size: 10pt'>";
		$tot_cash = sprintf('%0.2f', $tot_cash);
		$tot_wealth = sprintf('%0.2f', $tot_wealth);
		echo "<tr><td><b>TOTAL:</b></td><td><b>$tot_number_stock</b></td><td><b>$tot_number_exo</b></td><td><b>$tot_cash</b></td><td><b>$tot_wealth</b></td></tr>";
		echo "</table>";
		?>
		</div>
	</td>
 </tr>
</table>

</body>

</html>

<script type="text/javascript">
$(document).ready(function(){
	  var plot1 = $.jqplot('chart1', [price_array], {  
		 title:'Price',
		 series:[ 
		          {
		            lineWidth:1, 
		            showMarker:false
		          }, 
		          {
			        lineWidth:1, 
			        showMarker:false
		          }
		  ]
	  });
	});

</script>
