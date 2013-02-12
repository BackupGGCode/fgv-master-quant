
<html>
<head>
<b><center>BrASM Portfolio Monitor</center></b>
</head>
<body>
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

mysql_set_charset('utf8');
$query="SELECT id_agent as AGENT, number_stock as NUMBER_STOCK, cash as CASH FROM portfolio";
$result=mysql_query($query);

$num=mysql_num_rows($result);

mysql_close();

echo "<table border='1' cellpadding='3' cellspacing='0' width='300'>";
echo "<tbody align='center' style='font-family:verdana; color:black; background-color:yellow ; font-size: 12pt'>";
echo "<tr><td><b>Agent</b></td><td><b># Stock</b></td><td><b>Cash</b></td></tr>";
echo "<tbody align='center' style='font-family:verdana; font-size: 10pt'>";

$tot_number_stock = 0;
$tot_cash= 0;
while ($i < $num) {
	$agent=mysql_result($result,$i,"AGENT");
	$number_stock=mysql_result($result,$i,"NUMBER_STOCK");
	$cash=mysql_result($result,$i,"CASH");
	echo "<tr><td>$agent</td><td>$number_stock</td><td>$cash</td></tr>";
	
	$tot_number_stock = $tot_number_stock + $number_stock;
	$tot_cash = $tot_cash + $cash;
	$i++;
	
}
echo "<tbody align='center' style='font-size: 12pt'>";
echo "<tr><td><b>TOTAL:</b></td><td><b>$tot_number_stock</b></td><td><b>$tot_cash</b></td></tr>";
echo "</table>";
?>

</body>
</html>
