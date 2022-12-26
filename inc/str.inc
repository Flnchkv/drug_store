<?php 

include ("connect_db.inc");
include ("lib.inc");

if (isset($_POST['pass'])) login();
if (isset($_POST['undate_pswd'])) undate_pswd($_POST['login'], $_POST['pswd']);?>
<header> <?php headerer(); ?> </header>
<menu> <?php menu($page); ?> </menu>
<article> <?php page_contest($page); ?> </article>
<footer> Козлова Светлана. Артем, 2018 г </footer>