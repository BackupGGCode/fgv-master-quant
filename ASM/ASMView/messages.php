<?php
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

#mysql_connect($host,$username,$password);
#@mysql_select_db($database) or die( "Unable to select database");


mysql_set_charset('utf8');
$query="SELECT SUBSTRING(message,1,512) AS MSG FROM messages ORDER BY msgseqnum";
$result=mysql_query($query);

$num=mysql_numrows($result);

mysql_close();

echo "<b><center>ASM FIX Messages</center></b><br><br>";

$quote_bid_array = array();
$quote_ask_array = array();

$QuoteMsgType=false;
$BidPX=0.0;
$OfferPx=0.0;
$TransTime="";

$i=0;
while ($i < $num) {
	$msg=mysql_result($result,$i,"MSG");
	$fields = explode("\1",$msg);
	
	foreach($fields as $value){
		$tmp = explode("=",$value);

		switch($tmp[0]){
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
		//$dateformatted = date_format($date, 'H:i:s.u');
		echo  "TIME=$dateformatted   BID=$BidPX   ASK=$OfferPx";

	
		//$row_bid_array=array($dateformatted,(float)$BidPX);
		//$row_ask_array=array($dateformatted,(float)$OfferPx);
		
		$row_bid_array=array($i,(float)$BidPX);
		$row_ask_array=array($i,(float)$OfferPx);
		
		
		$QuoteMsgType=false;
		echo "<br><hr><br>";
				
		array_push($quote_bid_array,$row_bid_array);
		array_push($quote_ask_array,$row_ask_array);
	}
		
	#echo "<br><hr><br>";
	$i++;
}

echo "<script type='text/javascript'> var bid_array = ".json_encode($quote_bid_array).";</script>";
echo "<script type='text/javascript'> var ask_array = ".json_encode($quote_ask_array).";</script>";


$my_page_title = 'My first PHP/JS';
?>

<html>
<head>

<script type="text/javascript" src="scripts/jquery.min.js"></script>
<script type="text/javascript" src="scripts/jquery.jqplot.min.js"></script>
<script type="text/javascript" src="scripts/plugins/jqplot.canvasTextRenderer.min.js"></script>
<script type="text/javascript" src="scripts/plugins/jqplot.canvasAxisLabelRenderer.min.js"></script>
<script type="text/javascript" src="scripts/plugins/jqplot.jqplot.dateAxisRenderer.js"></script>
<script type="text/javascript" src="scripts/plugins/jqplot.jqplot.dateAxisRenderer.min.js"></script>
<link rel="stylesheet" type="text/css" hrf="scripts/jquery.jqplot.min.css" />

</head>
<body>

<h1><?php echo $my_page_title; ?></h1>

<div id="chart1" style="height:300px; width:500px;"></div>
</div>

</body>
</html>

<script type="text/javascript">
$(document).ready(function(){
	  var plot1 = $.jqplot('chart1', [bid_array], {  
	     series:[{showMarker:false}],
	      axes:{
	        xaxis:{
	            renderer:$.jqplot.DateAxisRenderer,
	        },
	        yaxis:{
	          label:'Price'
	        }
	      }
	  });
	});

</script>
