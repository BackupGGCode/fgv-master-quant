<?php
$username="quickfix";
$password="quickfix";
$database="quickfix";

mysql_connect(localhost,$username,$password);
@mysql_select_db($database) or die( "Unable to select database");
mysql_set_charset('utf8');
$query="SELECT SUBSTRING(message,1,512) AS MSG FROM messages ORDER BY msgseqnum";
$result=mysql_query($query);

$num=mysql_numrows($result);

mysql_close();

echo "<b><center>ASM FIX Messages</center></b><br><br>";

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
		echo "$value    |    ";
	}
	//if ($QuoteMsgType){
	//	echo "TIME=$TransTime   BID=$BidPX     ASK=$OfferPx";
	//	$QuoteMsgType=false;
	//}
	
	echo "<br><hr><br>";
	$i++;
}

$my_page_title = 'My first PHP/JS';
?>

<html>
<head>

<script type="text/javascript" src="scripts/jquery.min.js"></script>
<script type="text/javascript" src="scripts/jquery.jqplot.min.js"></script>
<script type="text/javascript" src="scripts/plugins/jqplot.canvasTextRenderer.min.js"></script>
<script type="text/javascript" src="scripts/plugins/jqplot.canvasAxisLabelRenderer.min.js"></script>
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
	  var cosPoints = []; 
	  for (var i=0; i<2*Math.PI; i+=0.1){ 
	     cosPoints.push([i, Math.cos(i)]); 
	  } 
	  var plot1 = $.jqplot('chart1', [cosPoints], {  
	      series:[{showMarker:false}],
	      axes:{
	        xaxis:{
	          label:'Time'
	        },
	        yaxis:{
	          label:'Price'
	        }
	      }
	  });
	});

</script>
