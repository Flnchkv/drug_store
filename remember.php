<!DOCTYPE HTML>
<html>
<head>
<title> Drag Store </title>
<link rel="stylesheet" type="text/css" href="css/style.css">
</head>
<body>
<p> <a href="index.php" > Назад </a></p>
<br/>

<form action="index.php" method="post" >
	<fieldset>
	<legend> Вспомнить все </legend>
	<p> Введите адрес электронной почты и номер телефона, использовавшиеся при регистрации </p>
	<input type='email' name='email' size=25 autofocus required > 
	<input type='text' name='phone' size=25 autofocus required  pattern="8-[0-9]{3}-[0-9]{3}-[0-9]{2}-[0-9]{2}"> 
	<input type="submit" name="remember"  value="Напомнить пароль">
</fieldset></form>
</body>
</html>