
<html>
<head>
<b><center>BrASM Agent Setup</center></b>
</head>
<body>
<?php

 if(isset($_POST['stop'])){
 	echo "<div align='center' style='font-size:14pt;'>";
	echo exec("sh ./scripts/stop_randomtraders.sh");
 	echo "</div>";
}

if(isset($_POST['agent'])) {
	$cbarray = $_POST['agent'];

	foreach($cbarray as $agent2exec){
		//echo "Executando $agent2exec<br>";
		echo exec("cd scripts; sh ./start_randomtraders.sh $agent2exec &");
	}
	
	echo "<form action='setup.php' method='post'>";
	echo "<input type='submit' name='stop' value='Parar Simulação' />";
	echo "</form>";

}

else{

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
	echo "<form method='POST' action='setup.php'>";
	echo "<p>";
	;
	while ($i < $num) {
		$agent=mysql_result($result,$i,"id_agent");
		echo " <input type='checkbox' name='agent[]' value='$agent'>$agent<br>";
		$i++;
		
	}
	echo "<br>";
	echo "<input type='submit' value='Simular'>";
	echo "</p>";
	echo "</div>";
}
?>

</body>
</html>
