<?php 
$username="quickfix";
$password="quickfix";
$database="quickfix";
$host="localhost";

?>

<html>
<head>
<b><center>BrASM Setup</center></b>
<br>
<script type="text/javascript">
function SetAllCheckBoxes(FormName, FieldName, CheckValue){
	if(!document.forms[FormName])
		return;
	var objCheckBoxes = document.forms[FormName].elements[FieldName];
	if(!objCheckBoxes)
		return;
	var countCheckBoxes = objCheckBoxes.length;
	if(!countCheckBoxes)
		objCheckBoxes.checked = CheckValue;
	else
		// set the check value for all check boxes
		for(var i = 0; i < countCheckBoxes; i++)
			objCheckBoxes[i].checked = CheckValue;
}

</script>
<!-- <META HTTP-EQUIV="Cache-Control" CONTENT="no-cache"> -->
</head>
<body>


<?php 
if(isset($_POST['OrderMatch'])){
	if( $_POST['OrderMatch'] == "OrderMatchOFF"){
		$command2KillOrderMatch = "cd ./scripts/;./ordermatch.sh stop";
		exec("$command2KillOrderMatch > /dev/null &");

	}
	if( $_POST['OrderMatch'] == "OrderMatchON"){
		$command2StartOrderMatch = "cd ./scripts/;./ordermatch.sh start";
		exec("$command2StartOrderMatch > /dev/null &");
	}
	//reload
	echo "<script type='text/javascript'>window.location.reload(true);</script>";
}

if(isset($_POST['MarketMaker'])){
	if( $_POST['MarketMaker'] == "MarketMakerOFF"){
		$command2KillMarketMaker = "cd ./scripts/;./marketmaker.sh stop";
		exec("$command2KillMarketMaker > /dev/null &");

	}
	if( $_POST['MarketMaker'] == "MarketMakerON"){
		$command2StartMarketMaker = "cd ./scripts/;./marketmaker.sh start";
		exec("$command2StartMarketMaker > /dev/null &");
	}
	//reload
	echo "<script type='text/javascript'>window.location.reload(true);</script>";
}


?>
<table>
  <tr>
	<td>
		<div align='center' style='width:250px;font-size:16pt;'>
		<?php 
		$commandStatusOrderMatch = "cd ./scripts/;./ordermatch.sh status";
		$statusOrderMatch = exec($commandStatusOrderMatch);
		if($statusOrderMatch == "STARTED"){
			echo "<img src='./img/om_on.png' alt='ORDERMATCH esta ATIVO'>";
			echo "<br>";
			echo "<form name ='orderMatchForm' method='POST' action='setupBrASM.php'>";
			echo "<input  type='hidden' name='OrderMatch' value='OrderMatchOFF'>";
			echo "<input type='submit' value='Parar'>";
			echo "</form>";
			echo "<br>";
		} else 	if($statusOrderMatch == "STOPPED"){
				echo "<img src='./img/om_off.png' alt='ORDERMATCH esta INATIVO'>";
				echo "<br>";
				echo "<form name ='orderMatchForm' method='POST' action='setupBrASM.php'>";
				echo "<input  type='hidden' name='OrderMatch' value='OrderMatchON'>";
				echo "<input type='submit' value='Iniciar'>";
				echo "</form>";
				echo "<br>";		
			}else{
				echo "<form name ='orderMatchForm' method='POST' action='setupBrASM.php'>";
				echo "<input  type='hidden' name='OrderMatch' value='none'>";
				echo "</form>";
			}
			
			
			$commandStatusMarketMaker = "cd ./scripts/;./marketmaker.sh status";
			$statusMarketMaker = exec($commandStatusMarketMaker);
			if($statusMarketMaker == "STARTED"){
				echo "<img src='./img/mm_on.png' alt='MARKETMAKER esta ATIVO'>";
				echo "<br>";
				echo "<form name ='marketMakerForm' method='POST' action='setupBrASM.php'>";
				echo "<input  type='hidden' name='MarketMaker' value='MarketMakerOFF'>";
				echo "<input type='submit' value='Parar'>";
				echo "</form>";
				echo "<br>";
			} else 	if($statusMarketMaker == "STOPPED"){
				echo "<img src='./img/mm_off.png' alt='MARKETMAKER esta INATIVO'>";
				echo "<br>";
				echo "<form name ='marketMakerForm' method='POST' action='setupBrASM.php'>";
				echo "<input  type='hidden' name='MarketMaker' value='MarketMakerON'>";
				echo "<input type='submit' value='Iniciar'>";
				echo "</form>";
				echo "<br>";
			}else{
				echo "<form name ='marketMakerForm' method='POST' action='setupBrASM.php'>";
				echo "<input  type='hidden' name='MarketMaker' value='none'>";
				echo "</form>";
			}
		?>
		
		</div>
	</td>

	<td>
<?php

if(isset($_POST['agent'])) {
	$cbarrayAgent = $_POST['agent'];
	
	$link = mysql_connect($host,$username,$password);
	if (!$link) {
		die('Not connected : ' . mysql_error());
	}
	
	$db_selected = mysql_select_db($database, $link);
	if (!$db_selected) {
		die ('Can\'t use $database : ' . mysql_error());
	}
	
	mysql_set_charset('utf8');

	foreach($cbarrayAgent as $agent2exec){
		$query="SELECT type FROM agents WHERE id_agent='$agent2exec'";
		$resultt=mysql_query($query);
		$agenttype=mysql_result($resultt,0,"type");
		$command ="";
		if($agenttype == "random"){
			$command = "cd ./scripts/;./randomtraders.sh change ".$agent2exec;
		}
		if($agenttype == "mv"){
			$command = "cd ./scripts/;./mvtraders.sh change ".$agent2exec;
		}
		if($agenttype == "bband"){
			$command = "cd ./scripts/;./bbandtraders.sh change ".$agent2exec;	
		}
		exec("$command > /dev/null &");

	}
	
	mysql_close();

}


	$link = mysql_connect($host,$username,$password);
	if (!$link) {
		die('Not connected : ' . mysql_error());
	}
	
	$db_selected = mysql_select_db($database, $link);
	if (!$db_selected) {
		die ('Can\'t use $database : ' . mysql_error());
	}
	
	mysql_set_charset('utf8');
	$query="SELECT id_agent FROM agents WHERE status='active' AND type NOT IN('mm', 'ordermatch','banzai') ";
	$result=mysql_query($query);
	
	$num=mysql_num_rows($result);
	
	mysql_close();
	echo "<div align='left' style='font-size:14pt;'>";
	echo "<form name ='agentForm' method='POST' action='setupBrASM.php'>";
	echo "<p>";
	while ($i < $num) {
		$agent=mysql_result($result,$i,"id_agent");
		$commandStatusTraders = "./scripts/statusTrader.sh $agent";
		$statusTraders = exec($commandStatusTraders);
		if($statusTraders == "STARTED"){
			echo "<font color='green'> <input type='checkbox' name='agent[]' value='$agent'>$agent<br></font>";
		}
		if($statusTraders == "STOPPED"){
				echo "<font color='red'> <input type='checkbox' name='agent[]' value='$agent'>$agent<br></font>";
		}

		$i++;
	}
	echo "<br>";
	echo "<input type='button' onclick=\"SetAllCheckBoxes('agentForm','agent[]',true)\" value='Selecionar Tudo'>";
	echo "<input type='button' onclick=\"SetAllCheckBoxes('agentForm','agent[]',false)\" value='Limpar Seleção'>";
	echo "<br>";
	echo "<br>";
	echo "<input type='submit' value='Ligar / Desligar'> ";
	
	echo "</p>";
	echo "</form>";
	echo "</div>";

?>
		</div>
	</td>
 </tr>
</table>
</body>
</html>
