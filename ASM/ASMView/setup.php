
<html>
<head>
<b><center>BrASM Setup</center></b>
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
$query="SELECT id_agent FROM agents";
$result=mysql_query($query);

$num=mysql_num_rows($result);

mysql_close();
echo "<div align='center' style='font-size:14pt;'>";
echo "<form method='POST' action='recebe_dados.php'>";
echo "<p>";
;
while ($i < $num) {
	$agent=mysql_result($result,$i,"id_agent");
	echo " <input type='checkbox' name='chk1' value='$agent'>$agent<br>";
	$i++;
	
}
echo "<br>";
echo "<input type='submit'' value='Simular'>";
echo "</p>";
echo "</div>";
?>

</body>
</html>
