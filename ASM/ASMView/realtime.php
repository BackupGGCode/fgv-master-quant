<?php

header('Refresh: 2');

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
$query="SELECT SUBSTRING(message,1,512) AS MSG FROM messages ORDER BY msgseqnum";
$result=mysql_query($query);

$num=mysql_num_rows($result);


$query_portfolio="SELECT id_agent as AGENT, number_stock as NUMBER_STOCK, cash as CASH FROM portfolio";
$result_portfolio=mysql_query($query_portfolio);

$num_portfolio=mysql_num_rows($result_portfolio);



mysql_close();

echo "<b><center>BrASM Monitor</center></b><br>";

$quote_bid_array = array();
$quote_ask_array = array();

$QuoteMsgType=false;
$BidPX=0.0;
$OfferPx=0.0;
$LastPx=0.0;
$LastLastPx=0.0;
$TransTime="";

$i=0;
$j=0;
while ($i < $num) {
	$msg=mysql_result($result,$i,"MSG");
	$fields = explode("\1",$msg);
	
	foreach($fields as $value){
		$tmp = explode("=",$value);

		switch($tmp[0]){
			case "31":
				$LastLastPx=$LastPx;
				$LastPx=$tmp[1];
				break;
			case "35": 
				switch($tmp[1]){ 
					case "D": 
						$QuoteMsgType=true;
						break;
					case "8": 
						break;
					case "D": 
						break;
					default:
						break;
				}
				break;
			case "52": 
				$TransTime=$tmp[1];
				break;
				
			case "132":
				$BidPX=$tmp[1];
				break;
			case "133":
				$OfferPx=$tmp[1];
				break;
			default:
				break;
		}
		#echo "$value    |    ";
	}
	if ($QuoteMsgType && $BidPX > 0.0 && $OfferPx > 0.0){
		$BidPX = round($BidPX, 2);
		$OfferPx = round($OfferPx, 2);
		
		//$TransTime = $TransTime."000";

		
		$date = date_create_from_format('Ymd-H:i:s.u', $TransTime);
		$dateformatted = date_format($date, 'd-m-Y H:i:s.u');
		
		//echo  "TIME=$dateformatted   BID=$BidPX   ASK=$OfferPx<br><hr><br>";

	
		//$row_bid_array=array($dateformatted,(float)$BidPX);
		//$row_ask_array=array($dateformatted,(float)$OfferPx);
		
		$row_bid_array=array($j++,(float)$BidPX);
		$row_ask_array=array($j++,(float)$OfferPx);
		
		
		$QuoteMsgType=false;

		array_push($quote_bid_array,$row_bid_array);
		array_push($quote_ask_array,$row_ask_array);
	}
	
	$i++;
}

echo "<script type='text/javascript'> var bid_array = ".json_encode($quote_bid_array).";</script>";
echo "<script type='text/javascript'> var ask_array = ".json_encode($quote_ask_array).";</script>";

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
		<div id="chart1" style="height:500px; width:700px; font-size:10pt;"></div>
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
		echo "<table border='0' cellpadding='6' cellspacing='6' width='400'>";
		echo "<tbody align='center' style='font-family:verdana; color:red ; font-size: 16pt'>";
		echo "<tr><td>Stock price: <b>$$LastPx  $arrow</b></td></tr>";
		echo "</table>";
		
		
		echo "<table border='1' cellpadding='3' cellspacing='0' width='400'>";
		echo "<tbody align='center' style='font-family:verdana; color:black; background-color:yellow ; font-size: 12pt'>";
		echo "<tr><td><b>Agent</b></td><td><b>Stock (#)</b></td><td><b>Cash ($)</b></td><td><b>Wealth ($)</b></td></tr>";
		echo "<tbody align='center' style='font-family:verdana; font-size: 10pt'>";
		
		$tot_number_stock = 0;
		$tot_cash= 0;
		$tot_wealth =0;
		$i=0;

		while ($i < $num_portfolio) {
			$agent=mysql_result($result_portfolio,$i,"AGENT");
			$number_stock=mysql_result($result_portfolio,$i,"NUMBER_STOCK");
			$cash=mysql_result($result_portfolio,$i,"CASH");
			$wealth = $cash + $number_stock*$LastPx;
			
			$tot_number_stock = $tot_number_stock + $number_stock;
			$tot_cash = $tot_cash + $cash;
			$tot_wealth = $tot_wealth + $wealth;
			
			$wealth = sprintf('%0.2f', $wealth);
			$cash = sprintf('%0.2f', $cash);
			echo "<tr><td>$agent</td><td>$number_stock</td><td>$cash</td><td>$wealth</td></tr>";
			

			$i++;
		}
		echo "<tbody align='center' style='font-size: 12pt'>";
		$tot_cash = sprintf('%0.2f', $tot_cash);
		$tot_wealth = sprintf('%0.2f', $tot_wealth);
		echo "<tr><td><b>TOTAL:</b></td><td><b>$tot_number_stock</b></td><td><b>$tot_cash</b></td><td><b>$tot_wealth</b></td></tr>";
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
	  var plot1 = $.jqplot('chart1', [bid_array, ask_array], {  
		 title:'Bid and Ask Prices',
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
