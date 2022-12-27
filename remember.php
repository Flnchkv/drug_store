<!DOCTYPE HTML>
<html>
<head>
	<meta charset="utf-8">
	<title> Drag Store </title>
	<link rel="stylesheet" type="text/css" href="css/style.css">
	<link rel="shortcut icon" href="img/pills.png" type="image/png">
</head>
<body>
<p> <a href="index.php" > Назад </a></p>
<br/>

<form action="index.php" method="post" >
	<fieldset class = back_reg>
	<legend class = reg> Восстановление пароля </legend>
	<p> Введите адрес электронной почты и номер телефона, использовавшиеся при регистрации </p>
	<input type='email' name='email' size=25 placeholder="e-mail" autofocus required > 
	<input type='text' name='phone' size=25 placeholder="8-800-555-35-35" autofocus required  pattern="8-[0-9]{3}-[0-9]{3}-[0-9]{2}-[0-9]{2}"> 
	<input type="submit" name="remember"  value="Напомнить пароль">
</fieldset></form>
</body>
</html>