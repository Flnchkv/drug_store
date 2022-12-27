<?php //функции, связанные с взаимодействием с базой данных
//****************************************************************
//доп функции
function get_roles_array()
{
	$arr = array("director", "provisor", "customer");
	return $arr;
}
function get_choice_html($arr, $name)
{
	$res = "";
	if(is_array($arr))
	{
		$res = "<datalist id='$name'>";
		foreach ($arr as $value)
			$res .= "<option> $value </option>";
		$res .= "</datalist>";
	}
	return $res;
}

function pswd_in_db($pswd)
{
	$options = ['cost' => 12,];
	return password_hash($pswd, PASSWORD_BCRYPT, $options);
}

function message($text)
{
	return '<dir class="message">' . $text . '</dir>';
}


//****************************************************************
//подключение
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
        { $error = message('Не могу соедениться с сервером'); return false; }
        return $link;
}

//****************************************************************
//пользователи
function register()
{
    $link = connect_it();
	if (isset($_POST['fio'])){
          $name = $_POST['logreg'];
		  $pswd = pswd_in_db($_POST[pswdreg]);
          $sql = "INSERT INTO user (`fio`, `login`,  `pswd`, `address`, `phone`, `email`, `role`) VALUES ('$_POST[fio]', '$_POST[logreg]', '$pswd', '$_POST[address]', '$_POST[tel]', '$_POST[email]', 'customer')";
          if ( $link -> query($sql))
          echo message("ok");
          else {
            echo message($link -> error);
          }
       $link -> close();
	   };
}

function login()
{
    $link = connect_it();
    $name = "user";
	$pswd = $_POST['pswd'];
    $query = "SELECT * FROM `user` WHERE login = '$_POST[login]'";
        //echo "<font color=green> Запрос: </font>" . $query;
    $result1 = $link->query($query);
    if (! $result1) { echo message($link -> error); return false;}
    else
		while($result = $result1->fetch_array())
		{
		if (password_verify($pswd, $result['pswd']))
		{
			echo message("Password is valid!");
			session_start();
			$_SESSION['session_uname'] = $result['fio'];
			$_SESSION['today'] = date("Y-n-d");
			$_SESSION['user_id'] = $result['id'];
			$_SESSION['role'] = $result['role'];
		}
		else {
			echo message("Invalid password.");
		}
		}
    mysqli_close($link);
    mysqli_free_result($result1);
}

function remember_pswd($email, $phone)
{
    $link = connect_it();
    $name = 'user';
    $query = "SELECT `login` FROM $name WHERE `email` = '$email' AND `phone` = '$phone'";
        //echo "<font color=green> Запрос: </font>" . $query;
    $result1 = $link -> query($query);
    if (! $result1) { echo message($link -> error); return false;}
    else if($result1->num_rows == 0 )
		echo message("Проверочные данные были введены неправильно.");
	else if($result1->num_rows > 1)
		echo message("Ошибка в данных, обратитесь к администратору.");
	else
		while($result = $result1->fetch_array())
		{
			$login = $result['login'];
			echo "<form action='index.php' method='post'><table><tr> ";
			echo "<tr><td> Введите новый пароль </td> <td> <input type='submit' name='undate_pswd' value='Сохранить изменения'> </td> </tr>";
			echo "<tr> <td> Логин </td> <td> <input readonly type = 'text' name ='login' value= '$login'  maxlength=20> </td> </tr>";
			echo "<tr> <td> Пароль </td> <td> <input type = 'password' name ='pswd' value= ''  maxlength=20> </td> </tr>";
  			echo "</tr></table></form>";
		}
    mysqli_free_result($result1);
    mysqli_close($link);
}
function undate_pswd($login, $pswd)
{
	$link = connect_it();
	$pswd = pswd_in_db($pswd);
	$query = "UPDATE `user` SET `pswd` = '$pswd' WHERE `login` = '$login'";
	$result = $link -> query($query);
    if (! $result) { echo message($link -> error); return false;}
    else { echo message("Выполнено"); return true;}
}

function discount()
{
    $link = connect_it();
	$dc = 0;
    $query = "SELECT `discount` FROM `user` WHERE `id` = '".$_SESSION['user_id']."'";
    $result1 = $link -> query($query);
    if (! $result1) { echo message($link -> error); return false;}
    else while($result = $result1->fetch_array()){
        $dc = $result['discount'];
    mysqli_close($link);
    mysqli_free_result($result1);
    return $dc;
}
}

function user_acc()
{
    $link = connect_it();
    $name = 'user';
    $query = "SELECT * FROM `user` WHERE `id` = '" . $_SESSION['user_id'] . "'";
        //echo "<font color=green> Запрос: </font>" . $query;
    $result1 = $link -> query($query);
    if (! $result1) { echo message($link -> error); return false;}
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
		$login = $result['login'];

        echo "<tr> <td> ФИО </td> <td> <input type = 'text' name ='fio' value= '$fio'> </td> <td rowspan=6> <img src='$photo' class='mine'> <br/> <input type='file' name='photo'> </td> </tr>";
        echo "<tr> <td> Логин </td> <td> <input type = 'text' name ='login' value= '$login'  maxlength=20> </td> </tr>";
        echo "<tr> <td> Пароль </td> <td> <input type = 'password' name ='pswd' value= '$pswd'  maxlength=20> </td> </tr>";
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
	$pswd = pswd_in_db($pswd);
    if ($photo != "") $photocode = ", `photo` = '/img/users/" . $photo . "'";
    $query = "UPDATE $name SET `fio` = '$fio', `login` = '$login', `pswd` = '$pswd', `address` = '$address', `phone` = '$phone', `email` = '$email', `bday` = '$bday'" . $photocode ." WHERE `id` = " . $_SESSION['user_id'];
        //echo "<font color=green> Запрос на заполнение таблицы: </font>" . $query;
    $result = $link -> query($query);
    if (! $result) { echo message($link -> error); return false;}
    else
    {
        echo message("Данные введены");
        $_SESSION['session_uname'] = $fio;
        return true;
    }
    mysqli_close($link);
    mysqli_free_result($result);
}

function u_delete($id)
{
    $link = connect_it();
    $name = 'user';
    $query = "DELETE FROM `$name` WHERE `id` = $id";
        //echo "<font color=green> Запрос на удаление записи: </font>" . $query;
    $result = $link -> query($query);
    if (! $result) { echo message($link -> error); return false;}
    else { echo message("Выполнено"); return true;}
}

function u_change($id, $dc, $role, $since)
{
    $link = connect_it();
    $name = 'user';
    $query = "UPDATE `$name` SET `discount` = '$dc' , `role` = '$role', `workS` = '$since' WHERE `id` = $id";
        //echo "<font color=green> Запрос на удаление записи: </font>" . $query;
    $result = $link -> query($query);
    if (! $result) { echo message($link -> error); return false;}
    else { echo message("Выполнено"); return true;}
    mysqli_free_result($result);
    mysqli_close($link);
}

function all_users()
{
    $link = connect_it();
    $name = 'user';
    $query = " SELECT * FROM $name";
        //echo "<font color=green> Запрос: </font>" . $query;
    $result1 = $link -> query($query);
    if (! $result1) { echo message($link -> error); return false;}
    else while($result = $result1->fetch_array())
    {
        echo "<table>";
        while($result = $result1->fetch_array())
        {
            $name = $result['fio'];
            $phone = $result['phone'];
            $discount = $result['discount'];
            $id = $result['id'];
            $u_role = $result['role'];
            $since = $result['workS'];
            echo "<tr> <td> $name </td> <td> $phone </td> <td>". $discount. "% </td> <td> $u_role </td> <td> работает с $since </td> <form method = 'post' action='users.php?".session_name().'='.session_id()."'> <td> <button name='u_edit' value=$id > Изменить </button> </td> <td> <button name='u_delete' value=$id > X </button> </td> </form> </tr>";
        }
        echo "</table>";
    }
    mysqli_close($link);
    mysqli_free_result($result1);
}

function u_edit($id)
{
    echo "<a href='users.php?".session_name().'='.session_id()."'> Вернуться на страницу выбора товара </a> ";
    $link = connect_it();
    $name = 'user';
    $query = " SELECT * FROM $name WHERE `id` = $id";
        //echo "<font color=green> Запрос: </font>" . $query;
    $result1 = $link -> query($query);
    if (! $result1) { echo message($link -> error); return false;}
    else while($result = $result1->fetch_array())
    {
        echo "<form method = 'post' action='users.php?".session_name().'='.session_id()."'> <table>";
        $name = $result['fio'];
        $email = $result['email'];
        $phone = $result['phone'];
        $discount = $result['discount'];
        $u_role = $result['role'];
        $since = $result['workS'];
        echo "<tr> <td colspan=2> $name </td> <td> $phone </td> <td> $email </td> </tr>";
		echo "<tr> <td> <input name='dc' type='number' value = $discount min=0 max=99 > </td> <td> <input type='text' name='role' list='roles' value='" . $u_role. "' > </td>";

		if($u_role == "customer")
		{
			echo "<td> зарегистирован с <input type='date' name='since' value='" . $since ."' > </td>";
		}
		else
		{
			echo "<td> работает с <input type='date' name='since' value='" . $since ."' > </td>";
		}

		echo "<td> <button name='u_change' value=$id > Сохранить </button> </td>  </tr> </table>";
		echo get_choice_html(get_roles_array(), 'roles');
		echo "</form>";
    }
    mysqli_close($link);
    mysqli_free_result($result1);
}

//****************************************************************
//товары
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
    if (! $result1) { echo message($link -> error); return false;}
    else
	{
		echo "<form action='search_res.php?".session_name()."=".session_id()."' method='post'> <table>";
		while($result = $result1->fetch_array())
		{ $i=$i+1;
				$type = $result['name'];
				echo "<tr>";
				echo "<td> <input class='good_type' type='submit' name='type" . $i ."' value='$type' class='b'> </td>";
				echo "</tr>";
				echo "</tr>";
				// генерация кода последующей выборки товаров опр категории, для динамичного использования бд
				$code .= "if(isset(\$_POST['type" .$i."'])) \n { \$link = connect_it(); \n \$name = \"goods\";\n \$query = \"SELECT * FROM \$name WHERE type = '".$type."'\"; \n ";
				$code .= file_get_contents("inc/good_type_button.inc");
		}
		echo "</table>";
	}
    mysqli_close($link);
    mysqli_free_result($result1);
    $code .= " ?>";
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
     if (! $result1) { echo message($link -> error); return false;}
     else while($result = $result1->fetch_array())
     {
         echo "<form method='post'> <table border = 5 >";
         while($result = $result1->fetch_array())
         {
             $img = $result['img'];
             $g_name = $result['name'];
             $price =  $result['price'];
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
    if (! $result1) { echo message($link -> error); return false;}
    else while($result = $result1->fetch_array())
    {
        $img = $result['img'];
        $g_name = $result['name'];
        $type =  $result['type'];
        $about =  $result['about'];
        $price =  $result['price'];
        $g_id = $result['id'];
        echo "<a href='store.php?".session_name().'='.session_id()."'> Вернуться на страницу выбора товара </a>";
        echo "<table> <tr> <td rowspan=3> <img src='$img'> </td> <td> <H1> $g_name </H1> </td> </tr> <tr> <td> <h3> $type </h3> </td> </tr> <tr> <td> <b> $price </b> <form method='post'> <button name='to_busket'  value='$g_id' formaction = 'busket.php?".session_name().'='.session_id()."'> В корзину </button> <input name = 'count' type = 'number' min=1 > </form> </td> </tr> <tr> <td colspan=2> <p> $about </p></td></tr></table>";

    }
	mysqli_close($link);
    mysqli_free_result($result1);
}

function all_goods()
{
    echo "<form method = 'post' action='goods.php?".session_name().'='.session_id()."'> <table> <tr> <td colspan=3> <button name='new_g'> Новый товар </button> </td> <td colspan=2> <button name='new_t'> Новая категория </button> </td> </tr>";
    $link = connect_it();
    $query = "SELECT `id`, `name`, `type`, `price` FROM `goods` ORDER BY `type`";
        //echo "<font color=green> Запрос на заполнение таблицы: </font>" . $query;
    $result1 = $link -> query($query);
    if (! $result1) { echo message($link -> error); return false;}
    else while($result = $result1->fetch_array())
    {
        $g_id = $result['id'];
        $g_name = $result['name'];
        $type = $result['type'];
        $price = $result['price'];
        echo "<tr> <td> $g_name </td> <td> $type </td> <td> $price </td> <td> <button name='g_edit' value=$g_id> Изменить </button> </td> <td> <button name='g_delete' value=$g_id> Х </button> </td> </tr>";
    }
    echo "</table> </form>";
    mysqli_close($link);
    mysqli_free_result($result1);
}

function echo_good_types($fild_name)
{
    $link = connect_it();
    echo "<datalist id='$fild_name'>";
    $query = "SELECT * FROM `categories`";
    $result1 = $link -> query($query);
    if (! $result1) { echo message($link -> error); return false;}
    else
		while($result = $result1->fetch_array())
	        echo "<option>" . $result['name'] ." </option>";
    echo "</datalist>";
    mysqli_close($link);
    mysqli_free_result($result1);
}

function add_new_good($g_name, $type, $about, $img, $price)
{
    $link = connect_it();
    $query = "INSERT INTO `goods` (`name`, `type`, `about`, `img`, `price`) VALUES ('$g_name','$type', '$about','/img/goods/" . $img . "', $price)";
        //echo "<font color=green> Запрос на удаление записи: </font>" . $query;
    $result = $link -> query($query);
    if (! $result) { echo message($link -> error); return false;}
    else { echo message("Выполнено"); return true;}
    mysqli_close($link);
    mysqli_free_result($result);
}

function add_type($name)
{
    $link = connect_it();
    $query = "INSERT INTO `categories` (`name`) VALUES ('$name')";
        //echo "<font color=green> Запрос на удаление записи: </font>" . $query;
    $result = $link -> query($query);
    if (! $result) { echo message($link -> error); return false;}
    else { echo message("Выполнено"); return true;}
    mysqli_close($link);
    mysqli_free_result($result);
}

function g_edit($g_id)
{
    echo "<a href='goods.php?".session_name().'='.session_id()."'> Вернуться на страницу выбора товара </a> <form method = 'post' action='goods.php?".session_name().'='.session_id()."'> <table>";
    $link = connect_it();
    $name = "goods";
    $query = "SELECT * FROM $name WHERE id = $g_id ";
        //echo "<font color=green> Запрос: </font>" . $query;
    $result1 = $link -> query($query);
    if (! $result1) { echo message($link -> error); return false;}
    else while($result = $result1->fetch_array())
    {
        $img = $result['img'];
        $g_name = $result['name'];
        $type =  $result['type'];
        $about =  $result['about'];
        $price =  $result['price'];
        $g_id = $result['id'];
        echo "<tr> <td rowspan=4> <img src='$img'width='500' height='600'>  <br/> <input type='file' name='img'>  </td> <td> Наименование </td> <td>  <input type = 'text' name ='name' value= '$g_name'> </td> </tr> <tr> <td> Категория </td> <td> <input type = 'text' name ='type' list='types' value= '$type'> </td> </tr> <tr> <td> Цена </td> <td> <input type = 'number' min='0.01' step='0.01' name ='price' value= '$price'> </td> </tr> <tr> <td rowspan=3> Подробнее о товаре </td> <td rowspan=3 colspan=2> <textarea name='about' rows=3> $about </textarea> </td> </tr>";
    }
    echo "</table>";
    mysqli_close($link);
    mysqli_free_result($result1);
    echo_good_types('types');
    echo "<button name='good_change'  value='$g_id'> Сохранить изменения </button> </form>";
}

function good_change($g_id, $g_name, $type, $about, $img, $price)
{
    $link = connect_it();
    $name = "goods";
    $photocode = "";
    if ($img != "") $photocode = ", `photo` = '/img/goods/" . $img . "'";
    $query = "UPDATE $name SET `name` = '$g_name', `type` = '$type', `about` = '$about'" . $photocode. ", `price` = $price WHERE `id` = $g_id";
        //echo "<font color=green> Запрос на удаление записи: </font>" . $query;
    $result = $link -> query($query);
    if (! $result) { echo message($link -> error); return false;}
    else { echo message("Выполнено"); return true;}
    mysqli_close($link);
    mysqli_free_result($result);
}

function g_delete($g_id)
{
    $link = connect_it();
    $name = 'goods';
    $query = "DELETE FROM `$name` WHERE `id` = $g_id";
        //echo "<font color=green> Запрос на удаление записи: </font>" . $query;
    $result = $link -> query($query);
    if (! $result) { echo message($link -> error); return false;}
    else { echo message("Выполнено"); return true;}
    mysqli_close($link);
    mysqli_free_result($result);
}

//****************************************************************
//корзина
function to_busket($g_id, $count)
{
    $link = connect_it();

    $query = "SELECT `price` FROM `goods` WHERE `id`= $g_id";
    $result1 = $link -> query($query);
    if (! $result1) { echo message($link -> error); return false;}
    else while($result = $result1->fetch_array())
        $cost = $result['price'] * (100 - discount()) / 100;

    $name = 'zakaz';
    $query = "INSERT INTO $name (client, date,  good, count, sended, done, cost) VALUES ($_SESSION[user_id], '$_SESSION[today]', $g_id, $count, 0, 0, $cost)";
       // echo "<font color=green> Запрос на заполнение таблицы: </font>" . $query;
    $result = $link -> query($query);
    if (! $result) { echo message($link -> error); return false;}
    else { echo message("Данные введены"); return true;}
    mysqli_close($link);
    mysqli_free_result($result1);
}

function delete_from_busket($z_id)
{
    $link = connect_it();
    $name = 'zakaz';
    $query = "DELETE FROM `$name` WHERE `id` = $z_id";
        //echo "<font color=green> Запрос на удаление записи: </font>" . $query;
	$result = $link -> query($query);
    if (! $result) { echo message($link -> error); return false;}
    else { echo message("Выполнено"); return true;}
    mysqli_close($link);
    mysqli_free_result($result);
}

function busket_stop()
{
    $link = connect_it();
    $name = 'zakaz';
    $query = "UPDATE $name SET `sended` = 1 WHERE `client` = " . $_SESSION['user_id'] . " AND `date` = \"" . 	$_SESSION['today'] ."\" AND `sended` = 0";
        //echo "<font color=green> Запрос на изменение записи: </font>" . $query;
    $result = $link -> query($query);
    if (! $result) { echo message($link -> error); return false;}
    else { echo message("Данные изменены"); return true;}
    mysqli_close($link);
    mysqli_free_result($result);
}

function show_busket() // хотите изменить заказ - удаляйте товар и по новой. и повторное добавление товара не контролирую пока
{
    $link = connect_it();
    $name1 = 'goods';
    $name2 = 'zakaz';
    $query = "SELECT `$name1`.`img`, `$name2`.`id`, `$name1`.`name`, `$name2`.`cost`, `$name2`.`count` FROM $name1, $name2 WHERE `$name2`.`client` = " . $_SESSION['user_id'] . " AND `$name2`.`date` = \"" . 	$_SESSION['today'] ."\" AND `$name2`.`sended` = 0 AND `$name1`.`id` = `$name2`.`good`"; // сложный запрос
        //echo "<font color=green> Запрос на заполнение таблицы: </font>" . $query;
    $result1 = $link -> query($query);
    if (! $result1) { echo message($link -> error); return false;}
    else
	{ $i = 0;
	while($result = $result1->fetch_array())
    {	$i+=1;
        $dc = discount();
        if($dc != 0) echo "<center> <h3> У вас есть скидка на все товары в ". $dc ."%! </h3> <center>";

        $sum = 0;
        echo "<form method='post' action='busket.php?".session_name().'='.session_id()."'> <table border = 5 >";

            $img = $result['img'];
            $g_name = $result['name'];
            $z_id = $result['id'];
            $count = $result['count'];
            $price = $result['cost'];
            $sum += $price* $count;
            echo "<tr> <td> <img src='$img'> <b> $g_name </b> $price </td> <td> $count шт </td>";
            echo "<td> <button name='delete' value = $z_id> Удалить </button> </td> </tr>";

        echo "</table> <h3> Итого: <b> $sum руб. </b> </h3> <input type='submit' name='continue' value='Завершить данную покупку'> </form>";
	}
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
    $result1 = $link -> query($query);
    if (! $result1) { echo message($link -> error); return false;}
    else while($result = $result1->fetch_array())
    {
			$fio = $result['fio'];
            $date = $result['date'];
            $count = $result['count'];
            $cost = $result['cost'];
            $done = $result['done'];
            $g_name = $result['name'];
            $z_id =$result['id'];
            $sum = $cost * $count;
            echo "<tr> <td> $fio </td> <td> $date </td> <td> $g_name </td> <td> $count шт. </td> <td> $sum руб. </td> <td> <button name = 'z_done' value = $z_id > V </button> </td> <td> <button name = 'z_delete' value = $z_id> X </button> </td> </tr>";

    }
    echo "</table> </form>";
	mysqli_close($link);
	mysqli_free_result($result1);
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
    $result1 = $link -> query($query);
    if (! $result1) { echo message($link -> error); return false;}
    else while($result = $result1->fetch_array())
    {
			$fio = $result['fio'];
            $date = $result['date'];
            $count = $result['count'];
            $cost = $result['cost'];
            $done = $result['done'];
            $g_name = $result['name'];
            $z_id = $result['id'];
            $sum = $cost * $count;
            echo "<tr> <td> $fio </td> <td> $date </td> <td> $g_name </td> <td> $count шт. </td> <td> $sum руб. </td> <td> <button name = 'z_delete' value = $z_id> X </button> </td> </tr>";
    }
    echo "</table> </form>";
	mysqli_close($link);
	mysqli_free_result($result1);
}

function z_done($z_id)
{
    $link = connect_it();
    $name = 'zakaz';
    $query = "UPDATE `$name`SET `done` = 1 WHERE `id` = $z_id";
        //echo "<font color=green> Запрос на удаление записи: </font>" . $query;
    $result = $link -> query($query);
    if (! $result) { echo message($link -> error); return false;}
    else { echo message("Выполнено"); return true;}
    mysqli_close($link);
    mysqli_free_result($result);
}

?>
