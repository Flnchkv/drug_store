
	$result1 = $link->query($query); 

	if (! $result1) { echo $link->error; return false;} 
	else while($result = $result1->fetch_array()) 
	{ 
		echo '<form method="post"> <table border = 5 >'; 
		$img = $result['img'];
		$g_name = $result['name'];
		$price = $result['price'];

		echo "<tr> <td> <img src='$img'> <b>$g_name</b> $price </td> <td>";
		echo "<button name='readmore' value='$g_name' formaction = 'readmore.php?" .session_name()."=".session_id()."'> Подробнее </button> </td> </tr> ";
		echo "</table>"; 
	} 
	mysqli_close($link); 
	mysqli_free_result($result1);
}
