<!DOCTYPE HTML>
<html>
<head>
	<meta charset="utf-8">
	<title> Drag Store </title>
	<link rel="stylesheet" type="text/css" href="css/style.css">
</head>
<body>
<p> <a href="index.php" > Назад </a></p>
<br/>

<form action="index.php" method="post" >
	<fieldset class = back_reg>
	<legend class = reg> Регистрация </legend>
	<table > <tr>
	   <td> <input type='text' name='logreg' placeholder="Логин" maxlength=20 size=21 autofocus required > </td>
	   <td> <input type='text' name='pswdreg' placeholder="Пароль" maxlength=20 size=21 required > </td> </tr> <tr>
	   <td colspan=2> <input type='text' name='fio' placeholder="Фамилия Имя Отчество" size=44  > </td> </tr> <tr>
	   <td colspan=2> <input type='text' name='address' placeholder="Адрес (Город, ул. Улица №дома-№квартиры )" size=44  > </td> </tr> <tr>
	   <td> <input type='text' name='tel' placeholder="8-800-555-35-35"  pattern="8-[0-9]{3}-[0-9]{3}-[0-9]{2}-[0-9]{2}" size=21  > </td>
	   <td> <input type='email' name='email' placeholder="e-mail" size=21  > </td> </tr> <tr>
	   <td> <input type="submit" name="reg" value="Создать аккаунт" > </td> </tr> 
	</table>
	<p> Логин и пароль к регистру не чувствительны, т.е. БОЛЬШИЕ и маленькие буквы значения не имеют </p>
	</fieldset></form>
</body>
</html>
