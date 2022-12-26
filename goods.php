<?php 
if (isset($_REQUEST[session_name()])) session_start();
$page = 'goods';
?>

<!DOCTYPE HTML>
<html>
	<head>
		<meta charset="utf-8">
		<title> Drag Store </title>
		<link rel="stylesheet" type="text/css" href="css/style.css">
	</head>
	<body>
		<?php include ("inc/str.inc");?>
	</body>
</html>