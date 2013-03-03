
<html>
<head>
<b><center>BrASM Agent Setup</center></b>
</head>
<body>
<?php

 if(isset($_POST['agents2die'])){
 	$cbarray2 = $_POST['agents2die'];
 	//echo "<div align='center' style='font-size:14pt;'>";
	//echo shell_exec('kill `ps -A | grep lt-randomtrader`');
 	//echo "</div>";
 	foreach($cbarray2 as $agent2die ){
 		$command2 = "kill `ps -aux | grep $agent2die`";
 		exec("$command2 > /dev/null &");

 	}
 	
 	

}

if(isset($_POST['agent'])) {
	$cbarray = $_POST['agent'];
	
	
	echo "<div align='left' style='font-size:14pt;'>";
	echo "<form method='POST' action='setup.php'>";
	echo "<p>";
	
	foreach($cbarray as $agent2exec){
		$command = "cd ./scripts/;./start_randomtraders.sh ".$agent2exec;
		exec("$command > /dev/null &");
		echo " <input type='checkbox' name='agents2die[]' value='$agent2exec'>$agent2exec<br>";
	}
	echo "<br>";
	echo "<input type='submit' value='Parar Simulação'>";
	echo "</p>";
	echo "</form>";
	echo "</div>";
	
	
	//echo "<form action='setup.php' method='post'>";
	//echo "<input type='submit' name='stop' value='Parar Simulação' />";
	//echo "</form>";
	


	
	
	
	
	
	

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
	$query="SELECT id_agent FROM agents WHERE status='active'";
	$result=mysql_query($query);
	
	$num=mysql_num_rows($result);
	
	mysql_close();
	echo "<div align='left' style='font-size:14pt;'>";
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
	echo "</form>";
	echo "</div>";
}
?>

</body>
</html>
