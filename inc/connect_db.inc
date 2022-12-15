<?php //функции, связанные с взаимодействием с базой данных
$link=null;
function connect_it()
{
        date_default_timezone_set('Asia/Vladivostok');
        $servername = "localhost";
        $username = "root";
        $password = "";
        $db = "drag_store";

        $link = mysqli_connect($servername, $username, $password, $db);
        $link -> set_charset("utf-8");
        if (! $link)
        { $error = "<p> Не могу соедениться с сервером </p>"; return false; }
        return $link;

}

function register()
{
	$link = connect_it();
  if (isset($_POST['fio'])){
          $name = $_POST['logreg'];
          $sql = "INSERT INTO user (`fio`, `login`,  `pswd`, `address`, `phone`, `email`, `role`) VALUES ('$_POST[fio]', '$_POST[logreg]', '$_POST[pswdreg]', '$_POST[address]', '$_POST[tel]', '$_POST[email]', 'customer')";
          if ( $link -> query($sql))
          echo "ok";
          else {
            echo $link -> error;
          }
//        //$conn->query($sql);
      // $link -> query($sql);
       $link -> close();
      };
  //$query = "INSERT INTO user (`fio`, `login`,  `pswd`, `address`, `phone`, `email`, `role`) VALUES ('$_POST[fio]', '$_POST[logreg]', '$_POST[pswdreg]', '$_POST[address]', '$_POST[tel]', '$_POST[email]', 'customer')";
	//echo "<font color=green> Запрос на заполнение таблицы: </font>" . $query;
//	$link -> query($query);

}

function  login()
{
	$link = connect_it();
	$name = "user";
	$query = "SELECT * FROM `user` WHERE login = '$_POST[login]' AND pswd = '$_POST[pswd]'";
    	//echo "<font color=green> Запрос: </font>" . $query;
   	$result1 = $link->query($query);
    if (! $result1) { echo mysql_error(); return false;}
	else
  //if (mysqli_num_rows($result) != 0)
	while($result = $result1->fetch_array()){
		session_start();
		$_SESSION['session_uname'] = $result['fio'];
		$_SESSION['today'] = date("Y-n-d");
		$_SESSION['user_id'] = $result['id'];
 			/*$num = mysql_result($result, 0, 'fio');
        	$user = mysql_result($result, 0, 'login');
        	$pswd = mysql_result($result, 0, 'pswd');
       		echo "<br/> $num <br/> $user <br/> $pswd ";*/
		/*$_SESSION['role'] = mysql_result ($result, 0, 'role');*/
	}
	mysqli_close($link);
   	mysqli_free_result($result1);
}

function discount() // использовать после создания подключения
{
	$dc = 0;
	$query = "SELECT `discount` FROM `user` WHERE `id` = '".$_SESSION['user_id']."'";
	$result1 = $link -> query($query);;
	if (! $result1) { echo mysql_error(); return false;}
	else if (mysql_num_rows($result1) != 0)
		$dc = mysql_result($result1, 0, 'discount');
    mysql_free_result($result1);
	return $dc;
}

function good_type_select($filename)
{
	$file = fopen ($filename, 'w');

	$code = "<?php ";
	$link = connect_it();
	$name = "categories";
	$query = "SELECT * FROM $name";
    	//echo "<font color=green> Запрос: </font>" . $query;
	$result1 = $link -> query($query);
  $i=0;
	if (! $result1) { echo mysql_error(); return false;}
	else while($result = $result1->fetch_array())
	{ $i=$i+1;
		?>
			<form action="<?php echo "search_res.php?".session_name().'='.session_id() ?>" method="post"> <table>
		<?php
			$type = $result['name'];
			echo "<tr>";
			echo "<td> <input type='submit' name='type" . $i ."' value='$type' class='b'> </td>";
			echo "</tr>";
			// генерация кода последующей выборки товаров опр категории, для динамичного использования бд
      $code .= "if(isset(\$_POST['type" .$i."'])) \n { \$link = connect_it(); \n \$name = \"goods\";\n \$query = \"SELECT * FROM \$name WHERE type = '".$type."'\"; \n ";

  $code .= "\$result1 = \$link->query(\$query); \n if (! \$result1) { echo \$link->error; return false;} \n else while(\$result = \$result1->fetch_array()) \n { echo '<form method=\"post\"> <table border = 5 >'; \n";
  $code .= "{\$img = \$result['img'];\n \$g_name = \$result['name'];\n \$price = \$result['price'];\n";
  $code .= "echo \"<tr> <td> <img src='\$img'> <b>\$g_name</b> \$price </td> <td> <button name='readmore' value='\$g_name' formaction = \\\"readmore.php?\" .session_name().'='.session_id() .\"\\\"> Подробнее </button> </td> </tr> \"; }";
  $code .= "\n echo '</table>'; } \n mysqli_close(\$link); mysqli_free_result(\$result1);}\n";
		echo "</tr></table></form>";
	}
  mysqli_close($link);
	mysqli_free_result($result1);
	$code .= "?>";
	fwrite ($file, $code);
	fclose ($file);
}

function good_only_name_search($search_name)
{
	 $link = connect_it();
	 $name = "goods";
	 $query = "SELECT * FROM $name WHERE name LIKE '%".$search_name."%'";
		//echo "<font color=green> Запрос: </font>" . $query;
	 $result1 = $link -> query($query);
	 if (! $result1) { echo mysql_error(); return false;}
	 else while($result = $result1->fetch_array())
	 {
		 echo "<form method='post'> <table border = 5 >";
		 for($j = 0; $j < mysql_num_rows($result); $j++)
		 {
			 $img = mysql_result($result, $j, 'img');
			 $g_name = mysql_result($result, $j, 'name');
			 $price =  mysql_result($result, $j, 'price');
			 echo "<tr> <td> <img src='$img'> <b>$g_name</b> $price </td> <td> <button name='readmore' value='$g_name' formaction = \"readmore.php?".session_name().'='.session_id() ." \"> Подробнее </button> </td> </tr> ";
		 }
		 echo '</table> </form>';
	 }
   mysqli_close($link);
 	mysqli_free_result($result1);
}

function good_readmore($search_name)
{
	$link = connect_it();
	$name = "goods";
	$query = "SELECT * FROM $name WHERE name ='" .$search_name. "'";
		//echo "<font color=green> Запрос: </font>" . $query;
	$result1 = $link -> query($query);
	if (! $result1) { echo mysql_error(); return false;}
	else while($result = $result1->fetch_array())
	{
		$img = $result['img'];
		$g_name = $result['name'];
		$type =  $result['type'];
		$about =  $result['about'];
		$price =  $result['price'];
		$g_id = $result['id'];
	 	echo "<a href='store.php?".session_name().'='.session_id()."'> Вернуться на страницу выбора товара </a> <table> <tr> <td rowspan=3> <img src='$img'> </td> <td> <H1> $g_name </H1> </td> </tr> <tr> <td> <h3> $type </h3> </td> </tr> <tr> <td> <b> $price </b> <form method='post'> <button name='to_busket'  value='$g_id' formaction = 'busket.php?".session_name().'='.session_id()."'> В корзину </button> <input name = 'count' type = 'number' min=1 > </form> </td> </tr> <tr> <td colspan=2> <p> $about </p></td></tr></table>";

	}
  mysqli_close($link);
	mysqli_free_result($result1);
}

function to_busket($g_id, $count)
{
	$link = connect_it();

	$query = "SELECT `price` FROM `goods` WHERE `id`= $g_id";
	$result = $link -> query($query);
	if (! $result) { echo mysql_error(); return false;}
	else if (mysql_num_rows($result) != 0)
		$cost = $result['price'] * (100 - discount()) / 100;

	$name = 'zakaz';
	$query = "INSERT INTO $name (client, date,  good, count, sended, done, cost) VALUES ($_SESSION[user_id], '$_SESSION[today]', $g_id, $count, 0, 0, $cost)";
       // echo "<font color=green> Запрос на заполнение таблицы: </font>" . $query;
    $result = $link -> query($query);
	if (! $result) { echo mysql_error(); return false;}
    else { echo "Данные введены"; return true;}
    mysqli_close($link);
  	mysqli_free_result($result);
}

function user_acc()
{
	$link = connect_it();
	$name = 'user';
	$query = "SELECT * FROM `user` WHERE `id` = '" . $_SESSION['user_id'] . "'";
		//echo "<font color=green> Запрос: </font>" . $query;
   	$result1 = $link -> query($query);
    if (! $result1) { echo mysql_error(); return false;}
	else 	while($result = $result1->fetch_array()){

		echo "<form method='post' action=\"account.php?".session_name().'='.session_id() ." \"> <table>";
		$fio = $result['fio'];
		$pswd = $result['pswd'];
		$address  = $result['address'];
		$phone  = $result['phone'];
		$email  = $result['email'];
		$dc  = $result['discount'];
		$bday  = $result['bday'];
		$photo  = $result['photo'];
		echo "<tr> <td> ФИО </td> <td> <input type = 'text' name ='fio' value= '$fio'> </td> <td rowspan=6> <img src='$photo' class='mine'> <br/> <input type='file' name='photo'> </td> </tr>";
		echo "<tr> <td> Логин </td> <td> <input type = 'text' name ='login' value= '$login'  maxlength=20> </td> </tr>";
		echo "<tr> <td> Пароль </td> <td> <input type = 'text' name ='pswd' value= '$pswd'  maxlength=20> </td> </tr>";
		echo "<tr> <td> Телефон </td> <td> <input type = 'text' name ='phone' value= '$phone'  pattern='8-[0-9]{3}-[0-9]{3}-[0-9]{2}-[0-9]{2}' size=21> </td> </tr>";
		echo "<tr> <td> Эл. почта </td> <td> <input type = 'email' name='email' value= '$email'> </td> </tr>";
		echo "<tr> <td> День рождения </td> <td> <input type = 'date' name='bday' value= '$bday'> </td> </tr>";
		echo "<tr> <td rowspan=3> Адрес </td> <td rowspan=3 colspan=2> <textarea name='address' rows=3> $address </textarea> </td> </tr>";
		echo "</table> <table> <tr> <td> Размер скидки </td> <td> <input type = 'text' disabled value= '". $dc ."%'> </td> </tr>";

			$role = $result['role'];
			$since = $result['workS'];
			echo "<tr> <td> Должность </td> <td> <input type = 'text' disabled value= '$role'> </td> </tr>";
			echo "<tr> <td> Дата приема на работу </td> <td> <input type = 'date' disabled value= '$since'> </td> </tr>";
	}
	echo "<tr> <td colspan=2> <input type='submit' name='acc_change' value='Сохранить изменения'> </td> </tr> </table></form>";
  mysqli_close($link);
	mysqli_free_result($result1);
}

function acc_change($fio, $login, $pswd, $address, $phone, $email, $bday, $photo)
{
	$link = connect_it();
	$name = 'user';
	$photocode = "";
	if ($photo != "") $photocode = ", `photo` = '/kozlova/img/users/" . $photo . "'";
	$query = "UPDATE $name SET `fio` = '$fio', `login` = '$login', `pswd` = '$pswd', `address` = '$address', `phone` = '$phone', `email` = '$email', `bday` = '$bday'" . $photocode ." WHERE `id` = " . $_SESSION['user_id'];
		//echo "<font color=green> Запрос на заполнение таблицы: </font>" . $query;
    $result = $link -> query($query);
	if (! $result) { echo mysql_error(); return false;}
    else
	{
		echo "Данные введены";
		$_SESSION['session_uname'] = $fio;
		return true;
	}
    mysql_close();
    mysql_free_result($result);
}

function delete_from_busket($z_id)
{
	$link = connect_it();
	$name = 'zakaz';
	$query = "DELETE FROM `$name` WHERE `id` = $z_id";
		//echo "<font color=green> Запрос на удаление записи: </font>" . $query;
  $result = $link -> query($query);
    if (! $result) { echo mysql_error(); return false;}
	else { echo "Данные удалены"; return true;}
    mysql_close();
    mysql_free_result($result);
}

function busket_stop()
{
	$link = connect_it();
	$name = 'zakaz';
	$query = "UPDATE $name SET `sended` = 1 WHERE `client` = " . $_SESSION['user_id'] . " AND `date` = \"" . 	$_SESSION['today'] ."\" AND `sended` = 0";
		//echo "<font color=green> Запрос на изменение записи: </font>" . $query;
	$result = $link -> query($query);
    if (! $result) { echo mysql_error(); return false;}
	else { echo "Данные изменены"; return true;}
    mysql_close();
    mysql_free_result($result);
}

function show_busket() // хотите изменить заказ - удаляйте товар и по новой. и повторное добавление товара не контролирую пока
{
	$link = connect_it();
	$name1 = 'goods';
	$name2 = 'zakaz';
	$query = "SELECT `$name1`.`img`, `$name2`.`id`, `$name1`.`name`, `$name2`.`cost`, `$name2`.`count` FROM $name1, $name2 WHERE `$name2`.`client` = " . $_SESSION['user_id'] . " AND `$name2`.`date` = \"" . 	$_SESSION['today'] ."\" AND `$name2`.`sended` = 0 AND `$name1`.`id` = `$name2`.`good`"; // сложный запрос
        //echo "<font color=green> Запрос на заполнение таблицы: </font>" . $query;
    $result1 = $link -> query($query);
    if (! $result1) { echo mysql_error(); return false;}
	else while($result = $result1->fetch_array())
	{
		$dc = discount();
		if($dc != 0) echo "<center> <h3> У вас есть скидка на все товары в ". $dc ."%! </h3> <center>";

		$sum = 0;
		echo "<form method='post' action='busket.php?".session_name().'='.session_id()."'> <table border = 5 >";
		for ($i = 0; $i < mysql_num_rows($result); $i++)
		{


			$img = $result['.img'];
			$g_name = $result['.name'];
			$z_id = $result['.id'];
			$count = $result['.count'];
			$price = $result['.cost'];
			$sum += $price* $count;
			echo "<tr> <td> <img src='$img'> <b> $g_name </b> $price </td> <td> $count шт </td>";
			echo "<td> <button name='delete' value = $z_id> Удалить </button> </td> </tr>";
		}
		echo "</table> <h3> Итого: <b> $sum руб. </b> </h3> <input type='submit' name='continue' value='Завершить данную покупку'> </form>";

	} //echo "Вы еще не выбрали никакие товары";
    mysqli_close($link);
    mysqli_free_result($result1);
}

function already_bought()
{
	echo "<form method = 'post' action='purchases.php?".session_name().'='.session_id()."'> <button name='show_done'> Показать завершенные покупки </button> <table>";
	$link = connect_it();
	$name1 = 'user';
	$name2 = 'zakaz';
	$name3 = 'goods';
	$query = "SELECT `$name1`.`fio`, `$name2`.`id`, `$name2`.`date`, `$name2`.`count`, `$name2`.`cost`, `$name2`.`done`, `$name3`.`name` FROM $name1, $name2, $name3 WHERE `$name2`.`client` = `$name1`.`id` AND `$name2`.`good` = `$name3`.`id` AND `$name2`.`sended` = 1 AND `$name2`.`done` = 0 ";
       // echo "<font color=green> Запрос на заполнение таблицы: </font>" . $query;
    $result = $link -> query($query);
    if (! $result) { echo mysql_error(); return false;}
	else if (mysql_num_rows($result) != 0)
	{
		for($i=0; $i < mysql_num_rows($result); $i++)
		{
			$fio = $result['.fio'];
			$date = $result['.date'];
			$count = $result['.count'];
			$cost = $result['.cost'];
			$done = $result['.done'];
			$g_name = $result['.name'];
			$z_id =$result['.id'];
			$sum = $cost * $count;
			echo "<tr> <td> $fio </td> <td> $date </td> <td> $g_name </td> <td> $count шт. </td> <td> $sum руб. </td> <td> <button name = 'z_done' value = $z_id > V </button> </td> <td> <button name = 'z_delete' value = $z_id> X </button> </td> </tr>";
		}
	}
	echo "</table> </form>";
	mysql_close();
    mysql_free_result($result);
}

function already_done()
{
	echo "<form method = 'post' action='purchases.php?".session_name().'='.session_id()."'> <button> Показать текущие покупки </button> <table>";
	$link = connect_it();
	$name1 = 'user';
	$name2 = 'zakaz';
	$name3 = 'goods';
	$query = "SELECT `$name1`.`fio`, `$name2`.`id`, `$name2`.`date`, `$name2`.`count`, `$name2`.`cost`, `$name2`.`done`, `$name3`.`name` FROM $name1, $name2, $name3 WHERE `$name2`.`client` = `$name1`.`id` AND `$name2`.`good` = `$name3`.`id` AND `$name2`.`done` = 1";
       // echo "<font color=green> Запрос на заполнение таблицы: </font>" . $query;
    $result = $link -> query($query);
    if (! $result) { echo mysql_error(); return false;}
	else if (mysql_num_rows($result) != 0)
	{
		for($i=0; $i < mysql_num_rows($result); $i++)
		{
			$fio = $result['.fio'];
			$date = $result['.date'];
			$count = $result['.count'];
			$cost = $result['.cost'];
			$done = $result['.done'];
			$g_name = $result['.name'];
			$z_id = $result['.id'];
			$sum = $cost * $count;
			echo "<tr> <td> $fio </td> <td> $date </td> <td> $g_name </td> <td> $count шт. </td> <td> $sum руб. </td> <td> <button name = 'z_delete' value = $z_id> X </button> </td> </tr>";
		}
	}
	echo "</table> </form>";
	mysql_close();
    mysql_free_result($result);
}

function z_done($z_id)
{
	$link = connect_it();
	$name = 'zakaz';
	$query = "UPDATE `$name`SET `done` = 1 WHERE `id` = $z_id";
		//echo "<font color=green> Запрос на удаление записи: </font>" . $query;
	$result = $link -> query($query);
    if (! $result) { echo mysql_error(); return false;}
	else { echo "Данные удалены"; return true;}
    mysql_close();
    mysql_free_result($result);
}

function all_goods()
{
	echo "<form method = 'post' action='goods.php?".session_name().'='.session_id()."'> <table> <tr> <td colspan=3> <button name='new_g'> Новый товар </button> </td> <td colspan=2> <button name='new_t'> Новая категория </button> </td> </tr>";
	$link = connect_it();
	$name = 'goods';
	$query = "SELECT `id`, `name`, `type`, `price` FROM `$name` ORDER BY `type`";
		//echo "<font color=green> Запрос на заполнение таблицы: </font>" . $query;
    $result = $link -> query($query);
    if (! $result) { echo mysql_error(); return false;}
	else if (mysql_num_rows($result) != 0)
	{
		for($i=0; $i < mysql_num_rows($result); $i++)
		{
			$g_id = $result['id'];
			$g_name = $result['name'];
			$type = $result['type'];
			$price = $result['price'];
			echo "<tr> <td> $g_name </td> <td> $type </td> <td> $price </td> <td> <button name='g_edit' value=$g_id> Изменить </button> </td> <td> <button name='g_delete' value=$g_id> Х </button> </td> </tr>";
		}
	}
	echo "</table> </form>";
	mysql_close();
    mysql_free_result($result);
}

function echo_types()
{
	$link = connect_it();
	echo "<datalist id='types'>";
	$query = "SELECT * FROM `categories`";
	$result = $link -> query($query);
	if (! $result) { echo mysql_error(); return false;}
	else if (mysql_num_rows($result) != 0)
		for($i=0; $i < mysql_num_rows($result); $i++)
			echo "<option>" . mysql_result($result, $i, 'name') ." </option>";
	echo "</datalist>";
	mysql_close();
    mysql_free_result($result);
}

function add_new_good($g_name, $type, $about, $img, $price)
{
	$link = connect_it();
	$name = "goods";
	$query = "INSERT INTO $name (`name`, `type`, `about`, `img`, `price`) VALUES ('$g_name','$type', '$about','/kozlova/img/goods/" . $img . "', $price)";
		//echo "<font color=green> Запрос на удаление записи: </font>" . $query;
	$result = $link -> query($query);
    if (! $result) { echo mysql_error(); return false;}
	else { echo "Данные удалены"; return true;}
    mysql_close();
    mysql_free_result($result);
}

function add_type($name)
{
	$link = connect_it();
	$query = "INSERT INTO `categories` (`name`) VALUES ('$name')";
		//echo "<font color=green> Запрос на удаление записи: </font>" . $query;
	$result = $link -> query($query);
    if (! $result) { echo mysql_error(); return false;}
	else { echo "Данные удалены"; return true;}
    mysql_close();
    mysql_free_result($result);
}

function g_edit($g_id)
{
	echo "<a href='goods.php?".session_name().'='.session_id()."'> Вернуться на страницу выбора товара </a> <form method = 'post' action='goods.php?".session_name().'='.session_id()."'> <table>";
	$link = connect_it();
	$name = "goods";
	$query = "SELECT * FROM $name WHERE id = $g_id ";
		//echo "<font color=green> Запрос: </font>" . $query;
	$result = $link -> query($query);
	if (! $result) { echo mysql_error(); return false;}
	else if (mysql_num_rows($result) != 0)
	{
		$img = $result['img'];
		$g_name = $result['name'];
		$type =  $result['type'];
		$about =  $result['about'];
		$price =  $result['price'];
		$g_id = $result['id'];
	 	echo "<tr> <td rowspan=4> <img src='$img'>  <br/> <input type='file' name='img'>  </td> <td> Наименование </td> <td>  <input type = 'text' name ='name' value= '$g_name'> </td> </tr> <tr> <td> Категория </td> <td> <input type = 'text' name ='type' list='types' value= '$type'> </td> </tr> <tr> <td> Цена </td> <td> <input type = 'number' min='0.01' step='0.01' name ='price' value= '$price'> </td> </tr> <tr> <td rowspan=3> Подробнее о товаре </td> <td rowspan=3 colspan=2> <textarea name='about' rows=3> $about </textarea> </td> </tr>";
	}
	echo "</table>";
	mysql_close();
    mysql_free_result($result);
	echo_types();
	echo "<button name='good_change'  value='$g_id'> Сохранить изменения </button> </form>";
}

function good_change($g_id, $g_name, $type, $about, $img, $price)
{
	$link = connect_it();
	$name = "goods";
	$photocode = "";
	if ($img != "") $photocode = ", `photo` = '/kozlova/img/goods/" . $img . "'";
	$query = "UPDATE $name SET `name` = '$g_name', `type` = '$type', `about` = '$about'" . $photocode. ", `price` = $price WHERE `id` = $g_id";
		//echo "<font color=green> Запрос на удаление записи: </font>" . $query;
	$result = $link -> query($query);
    if (! $result) { echo mysql_error(); return false;}
	else { echo "Данные удалены"; return true;}
    mysql_close();
    mysql_free_result($result);
}

function g_delete($g_id)
{
	$link = connect_it();
	$name = 'goods';
	$query = "DELETE FROM `$name` WHERE `id` = $g_id";
		//echo "<font color=green> Запрос на удаление записи: </font>" . $query;
	$result = $link -> query($query);
    if (! $result) { echo mysql_error(); return false;}
	else { echo "Данные удалены"; return true;}
    mysql_close();
    mysql_free_result($result);
}

function all_users() // доделать
{
	$link = connect_it();
	$name = 'user';
	$query = " SELECT * FROM $name";
		//echo "<font color=green> Запрос: </font>" . $query;
	$result = $link -> query($query);
	if (! $result) { echo mysql_error(); return false;}
	else if (mysql_num_rows($result) != 0)
	{
		echo "<table>";
		for ($i = 0; $i < mysql_num_rows($result); $i++)
		{
			$name = mysql_result($result, $i, 'fio');
			$phone = mysql_result($result, $i, 'phone');
			$discount = mysql_result($result, $i, 'discount');
			$id = mysql_result($result, $i, 'id');
			$u_role = mysql_result($result, $i, 'role');
			$since = mysql_result($result, $i, 'workS');
			echo "<tr> <td> $name </td> <td> $phone </td> <td>". $discount. "% </td> <td> $u_role </td> <td> работает с $since </td> <form method = 'post' action='users.php?".session_name().'='.session_id()."'> <td> <button name='u_edit' value=$id > Изменить </button> </td> <td> <button name='u_delete' value=$id > X </button> </td> </form> </tr>";
		}
		echo "</table>";
	}
	mysql_close();
    mysql_free_result($result);
}

function u_edit($id) // доделать
{
	echo "<a href='users.php?".session_name().'='.session_id()."'> Вернуться на страницу выбора товара </a> ";
	$link = connect_it();
	$name = 'user';
	$query = " SELECT * FROM $name WHERE `id` = $id";
		//echo "<font color=green> Запрос: </font>" . $query;
	$result = $link -> query($query);
	if (! $result) { echo mysql_error(); return false;}
	else if (mysql_num_rows($result) != 0)
	{
		echo "<form method = 'post' action='users.php?".session_name().'='.session_id()."'> <table>";
			$name = mysql_result($result, 0, 'fio');
			$email = mysql_result($result, 0, 'email');
			$phone = mysql_result($result, 0, 'phone');
			$discount = mysql_result($result, 0, 'discount');
			$u_role = mysql_result($result, 0, 'role');
			$since = mysql_result($result, 0, 'workS');
			echo "<tr> <td colspan=2> $name </td> <td> $phone </td> <td> $email </td> </tr> <tr>  <td> <input name='dc' type='number' value = $discount min=0 max=99 > </td> <td> <input type='text' name='role' list='roles' value='" . $u_role. "' > </td> <td> работает с <input type='date' name='since' value='" . $since ."' > </td> <td> <button name='u_change' value=$id > Сохранить </button> </td>  </tr> </table> <datalist id='roles'> <option> customer </option> <option> provisor </option> <option> director </option> </datalist> </form>";
	}
	mysql_close();
    mysql_free_result($result);
}

function u_delete($id)
{
	$link = connect_it();
	$name = 'user';
	$query = "DELETE FROM `$name` WHERE `id` = $id";
		//echo "<font color=green> Запрос на удаление записи: </font>" . $query;
	$result = $link -> query($query);
    if (! $result) { echo mysql_error(); return false;}
	else { echo "Данные удалены"; return true;}
}

function u_change($id, $dc, $role, $since)
{
	$link = connect_it();
	$name = 'user';
	$query = "UPDATE `$name` SET `discount` = '$dc' , `role` = '$role', `workS` = '$since' WHERE `id` = $id";
		//echo "<font color=green> Запрос на удаление записи: </font>" . $query;
	$result = $link -> query($query);
    if (! $result) { echo mysql_error(); return false;}
	else { echo "Данные удалены"; return true;}
	mysql_free_result($result);
	mysql_close();
}

function remember_pswd($email, $phone)
{
	$link = connect_it();
	$name = 'user';
	$query = "SELECT `pswd` FROM $name WHERE `email` = '$email' AND `phone` = '$phone'";
		//echo "<font color=green> Запрос: </font>" . $query;
	$result = $link -> query($query);
	if (! $result) { echo mysql_error(); return false;}
	else if (mysql_num_rows($result) != 0)
		echo "Ваш пароль - " . mysql_result($result, 0, 'pswd') . ". Запишите его куда-нибудь, и постарайтесь более не терять.";
	else echo "Проверочные данные были введены неправильно.";
	mysql_free_result($result);
	mysql_close();
}
?>
