<?php
if (isset($_REQUEST[session_name()])) session_start();
$page = 'index';

include ("inc/connect_db.inc");
include ("inc/lib.inc");
?>

<!DOCTYPE HTML>
<html>
	<head>
		<title> Drag Store </title>
		<link rel="stylesheet" type="text/css" href="css/style.css">
		<link rel="shortcut icon" href="pills.png" type="image/png">
	</head>
	<body>
		<?php include ("inc/str.inc");?>
	</body>
</html>
