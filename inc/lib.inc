<?php // функции пользовательского интерфейса 

function headerer()
{ ?>
	<div class='slider'>
		<input type='radio' name='slider1' id='sl1' checked="checked">
		<label for='sl1'></label>
			<div>
				<p> 1</p> <img src='img/1.jpg' >
			</div>
		<input type='radio' name='slider1' id='sl2'>
		<label for='sl2'></label>
			<div>
				<p> 2 </p> <img src='img/2.jpg' >
			</div>
		<input type='radio' name='slider1' id='sl3'>
		<label for='sl3'></label>
			<div>
				<p> 3 </p> <img src='img/3.jpg' >
			</div>
	</div> 
<?php }

function loging_in($page)
{ 
	if(isset($_SESSION['session_uname']))
		echo " <p>Добро пожаловать, " .$_SESSION['session_uname']. ". </p> <form method='post' action='index.php'> <button name='quit'> Выйти из аккаунта </button> </form> <div>";
	else 
	{
		if ($page =='index') echo "<form action='account.php'"; else echo "<form action='" . $_SERVER['PHP_SELF'] ."' ";
		echo "method=\"post\" > <fieldset> <legend> Войти  </legend> <input type='text' name='login' maxlength=20 autofocus ";
		if (isset($_POST['pass'])) echo "value='" . $_POST['login'] . "'";
		echo "> <input type='password' name='pswd' maxlength=20 > <input type='submit' name='pass' value='Зайти' > <p> Ещё не зарегистрированы? <button formaction='nopass.php'> Зарегистрироваться </button> </p> ";
		echo "<a href = 'remember.php'> Забыли пароль? </a> </fieldset></form> ";
	}
}

function menu($page)
{ ?>

	<table><tr><td><img src='img/icon.jpg' class='icon'></td>
	<td><center> <form action="<?php echo $_SERVER['PHP_SELF']?>" method="post">
    
		<input type="submit" name="sub" value="Главная"  class="<?php if ($page == "index") echo 'on'; else echo 'off' ?>"> 
		<input type="submit" name="sub2" value="Магазин" class="<?php if (($page == "store") || ($page =="search") || ($page == 'readmore')) echo 'on'; else echo 'off' ?>"> 
		<input type="submit" name="sub3" value="Аккаунт" class="<?php if ($page == "acc") echo 'on'; else echo 'off' ?>"> 
		<input type="submit" name="sub4" value="Корзина" class="<?php if ($page == "busket") echo 'on'; else echo 'off' ?>"> 
		<?php
			if(isset($_SESSION['role']))
			{
				if (($_SESSION['role'] == 'provisor')||($_SESSION['role'] == 'director')) 
				{
					echo " <input type='submit' name='sub5' value='Заказы' class='";
					if ($page == "buy") echo 'on'; else echo 'off';
					echo "' >  <input type='submit' name='sub6' value='Товары' class='";
					if ($page == "goods") echo 'on'; else echo 'off';
					echo "' >";
				}
				if ($_SESSION['role'] == 'director') 
				{
					echo "<input type='submit' name='sub7' value='Пользователи' class='";
					if ($page == "users") echo 'on'; else echo 'off';
					echo "'> ";
				}
			}
		?>
	  </form> </center></td><td>
	<?php loging_in($page); ?> </td></tr></table> <?php
}

function search_string($address)
{
	echo "<center> <form action=\"" . $address . "?" .session_name().'='.session_id()." \" method=\"post\"> <input type='search' name='searcher' placeholder='Введите название искомого товара' size=100> <input type='submit' name='search'></form></center>";
}

function new_g()
{
	echo "<a href='goods.php?".session_name().'='.session_id()."'> Вернуться на страницу выбора товара </a>";
	echo_good_types('types');
	echo "<form method = 'post' action='goods.php?".session_name().'='.session_id()."'> <table>";
	?>
	<tr> <td> Наименование </td> <td> <input type = 'text' name ='name'> </td> </tr>
	<tr> <td> Изображение </td> <td> <input type='file' name='img'>  </td> </tr>
	<tr> <td> Категория </td> <td> <input type = 'text' name ='type' list='types'> </td> </tr>
	<tr> <td> Цена </td> <td> <input type = 'number' min='0.01' step='0.01' name ='price'> </td> </tr>
	<tr> <td> Подробнее о товаре </td> <td> <textarea name='about' rows=3> </textarea> </td> </tr>
	</table>
	<input type='submit' name='add_new_good' value='Добавить новый товар'> </form>
	<?php 
}

function new_t()
{
	echo "<a href='goods.php?".session_name().'='.session_id()."'> Вернуться на страницу выбора товара </a> <form method = 'post' action='goods.php?".session_name().'='.session_id()."'> <table>";
	?>
	<tr> <td> Наименование новой категории </td> <td> </td> </tr>
	<tr> <td> <input type = 'text' name ='name' maxlength=150 size=152> </td> </tr>
	</table>
	<input type='submit' name='add_type' value='Добавить новую категорию товаров'> </form>
<?php }

function page_contest($page)
{ 
	if (isset($_POST['sub'])) header("Location: index.php?".session_name().'='.session_id());
	else if (isset($_POST['sub2'])) header("Location: store.php?".session_name().'='.session_id());
	else if (isset($_POST['sub3'])) header("Location: account.php?".session_name().'='.session_id());
	else if (isset($_POST['sub4'])) header("Location: busket.php?".session_name().'='.session_id());

	else if (isset($_POST['sub5'])) header("Location: purchases.php?".session_name().'='.session_id());
	else if (isset($_POST['sub6'])) header("Location: goods.php?".session_name().'='.session_id());
	else if (isset($_POST['sub7'])) header("Location: users.php?".session_name().'='.session_id());

	if(isset($_POST['quit']))
	{
		if (ini_get("session.use_cookies")) 
		{
			$params = session_get_cookie_params();
			setcookie(session_name(), '', time() - 42000,
			$params["path"], $params["domain"],
			$params["secure"], $params["httponly"]);
		}
		session_unset();

	}

	if (isset($_POST['reg'])) register();
	if (isset($_POST['remember'])) remember_pswd($_POST['email'], $_POST['phone']);
	
	if (!isset($_SESSION['session_uname'])) 
	{
		echo "Пожалуйста, зайдите в свою учетную запись или зарегистрируйтесь <br/>";
		if ($page == "index") readfile ("inc/page1.inc");
	}
	else
	{
		//echo $_SESSION['session_uname'];
		$filename = 'inc/temp/code.txt';
		switch ($page)
		{
			case "index": //Главная
				readfile ("inc/page1.inc");
				break;

			case "store": //Товары
				search_string('search_res.php');
				good_type_select($filename);
				break;
		
			case "search":
				search_string('search_res.php');
				if (isset($_POST['search'])) good_only_name_search($_POST['searcher']);
				include ($filename);			
				break;
		
			case "readmore":
				if (isset($_POST['readmore'])) good_readmore($_POST['readmore']);
				break;

			case "acc": //Аккаунт
				if (isset($_POST['acc_change'])) acc_change($_POST['fio'], $_POST['login'], $_POST['pswd'], $_POST['address'], $_POST['phone'], $_POST['email'], $_POST['bday'], $_POST['photo']);
				user_acc();
				break;

			case "busket": //Корзина
				if (isset($_POST['to_busket'])) to_busket($_POST['to_busket'], $_POST['count']);
				if (isset($_POST['delete'])) delete_from_busket($_POST['delete']);
				if (isset($_POST['continue'])) busket_stop();
				show_busket();
				break;

			case "buy": //Заказы 
				if (isset($_POST['z_done'])) z_done($_POST['z_done']);
				if (isset($_POST['z_delete'])) delete_from_busket($_POST['z_delete']);
				if (isset($_POST['show_done'])) already_done();
				else already_bought();
				break;

			case "goods": //Товары
				if (isset($_POST['g_delete'])) g_delete($_POST['g_delete']);
				if (isset($_POST['good_change'])) good_change($_POST['good_change'], $_POST['name'], $_POST['type'], $_POST['about'], $_POST['img'], $_POST['price']);
				if (isset($_POST['add_new_good'])) add_new_good( $_POST['name'], $_POST['type'], $_POST['about'], $_POST['img'], $_POST['price']);
				if (isset($_POST['add_type'])) add_type($_POST['name']);

				if (isset($_POST['new_g'])) new_g();
				else if (isset($_POST['new_t'])) new_t();
				else if (isset($_POST['g_edit'])) g_edit($_POST['g_edit']);
				else all_goods();
				break;

			case "users": //Пользователи
				if (isset($_POST['u_delete'])) u_delete($_POST['u_delete']);
				if (isset($_POST['u_change'])) u_change($_POST['u_change'], $_POST['dc'], $_POST['role'],  $_POST['since']);
				if (isset($_POST['u_edit'])) u_edit($_POST['u_edit']); else	all_users();
				break;

			default:
				echo ("Ошибка. Вызов данной странцы не должен был быть произведен.");
				break;
		}
	}
}
?>