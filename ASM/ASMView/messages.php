
<html>
<head>
<b><center>ASM FIX Messages</center></b>
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
$query="SELECT SUBSTRING(message,1,512) AS MSG FROM messages ORDER BY msgseqnum";
$result=mysql_query($query);

$num=mysql_numrows($result);

mysql_close();

while ($i < $num) {
	$msg=mysql_result($result,$i,"MSG");
	$fields = explode("\1",$msg);
	echo "$value    |    ";
	foreach($fields as $value){
		echo "$value    |    ";
	}
	echo "<br>";
	$i++;
}

?>

</body>
</html>
