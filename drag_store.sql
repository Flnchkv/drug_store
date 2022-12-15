-- phpMyAdmin SQL Dump
-- version 3.4.9
-- http://www.phpmyadmin.net
--
-- Хост: localhost
-- Время создания: Дек 22 2017 г., 16:02
-- Версия сервера: 5.5.20
-- Версия PHP: 5.3.9

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- База данных: `drag_store`
--

-- --------------------------------------------------------

--
-- Структура таблицы `categories`
--

CREATE TABLE IF NOT EXISTS `categories` (
  `name` varchar(150) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Дамп данных таблицы `categories`
--

INSERT INTO `categories` (`name`) VALUES
('Антидепрессанты'),
('БАД'),
('Офтальмология'),
('Противосудорожные'),
('Седативные средства'),
('Снотворные средства'),
('Транквилизаторы');

-- --------------------------------------------------------

--
-- Структура таблицы `goods`
--

CREATE TABLE IF NOT EXISTS `goods` (
  `id` int(4) NOT NULL AUTO_INCREMENT,
  `name` varchar(150) NOT NULL,
  `type` varchar(150) NOT NULL,
  `about` varchar(1000) DEFAULT NULL,
  `img` varchar(200) NOT NULL,
  `price` decimal(8,2) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `type` (`type`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=4 ;

--
-- Дамп данных таблицы `goods`
--

INSERT INTO `goods` (`id`, `name`, `type`, `about`, `img`, `price`) VALUES
(1, '9 месяцев Омегамама капсулы №30', 'БАД', 'Омегамама - биологически активная добавка к пище для беременных и кормящих матерей на основе полинасыщенных жирных кислот Омега-3. Омегамама изготавливается на основе экстракта жира из анчоусов и сардин.', '/kozlova/img/goods/omegamama.jpeg', 572.00),
(2, 'Ад минус таблетки №40 БАД Эвалар', 'БАД', 'Способствует поддержанию артериального давления в норме. 1 таблетка содержит: Трава и цветки гречихи 225 мг, Экстракт гречихи и сушеницы 110 мг, Экстракт плодоножек вишни 50 мг, Витамин С 15 мг, Рутин 10 мг', '/kozlova/img/goods/adminus.jpeg', 274.00),
(3, 'Азарга 10мг+5мг капли глазные флакон-капельница 5мл', 'Офтальмология', 'Глазные капли Азарга назначают при повышенном внутриглазном давлении, связанном с открытоугольной глаукомой или внутриглазной гипертензией в тех случаях, когда терапия препаратами с одним активным компонентом оказалась недостаточной для стойкого снижения внутриглазного давления.', '/kozlova/img/goods/azarga.jpeg', 960.00);

-- --------------------------------------------------------

--
-- Структура таблицы `user`
--

CREATE TABLE IF NOT EXISTS `user` (
  `id` int(4) NOT NULL AUTO_INCREMENT,
  `fio` varchar(150) NOT NULL,
  `login` varchar(20) DEFAULT NULL,
  `pswd` varchar(20) DEFAULT NULL,
  `address` varchar(80) DEFAULT NULL,
  `phone` varchar(15) NOT NULL,
  `email` varchar(50) DEFAULT NULL,
  `discount` int(2) DEFAULT NULL,
  `bday` date DEFAULT NULL,
  `photo` varchar(50) NOT NULL,
  `role` varchar(10) NOT NULL,
  `workS` date NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=4 ;

--
-- Дамп данных таблицы `user`
--

INSERT INTO `user` (`id`, `fio`, `login`, `pswd`, `address`, `phone`, `email`, `discount`, `bday`, `photo`, `role`, `workS`) VALUES
(1, 'Коновалов Андрей Михайлович', 'director', 'pswd', ' Артем, ул. Западная 8 ', '8-880-987-35-35', 'director@mail.ru', 10, '0000-00-00', '/kozlova/img/users/director.jpg', 'director', '2017-10-01'),
(2, 'Коновал Михайл', 'kn', 'knm', ' Артем, ул. Кирова 15 ', '8-800-555-35-35', 'konovam@mail.ru', 5, '0000-00-00', '/kozlova/img/users/l9I5e5yPDy8.jpg', 'provisor', '2017-11-01'),
(3, 'Козлова Светлана Евгеньевна', 'koz', 'koz123', 'Артем, ул. Фрунзе 10', '8-914-756-35-35', 'kozlova@mail.ru', 0, NULL, '', 'customer', '0000-00-00');

-- --------------------------------------------------------

--
-- Структура таблицы `zakaz`
--

CREATE TABLE IF NOT EXISTS `zakaz` (
  `id` int(4) NOT NULL AUTO_INCREMENT,
  `client` int(4) NOT NULL,
  `date` date NOT NULL,
  `good` int(4) NOT NULL,
  `count` int(10) NOT NULL,
  `cost` decimal(8,2) DEFAULT NULL,
  `sended` tinyint(1) DEFAULT NULL,
  `done` tinyint(1) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `client` (`client`),
  KEY `good` (`good`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=4 ;

--
-- Дамп данных таблицы `zakaz`
--

INSERT INTO `zakaz` (`id`, `client`, `date`, `good`, `count`, `cost`, `sended`, `done`) VALUES
(1, 1, '2017-12-22', 1, 3, 543.40, 0, 0),
(2, 1, '2017-12-22', 2, 2, 520.60, 1, 1),
(3, 1, '2017-12-22', 1, 5, 543.40, 1, 0);

--
-- Ограничения внешнего ключа сохраненных таблиц
--

--
-- Ограничения внешнего ключа таблицы `goods`
--
ALTER TABLE `goods`
  ADD CONSTRAINT `goods_ibfk_1` FOREIGN KEY (`type`) REFERENCES `categories` (`name`);

--
-- Ограничения внешнего ключа таблицы `zakaz`
--
ALTER TABLE `zakaz`
  ADD CONSTRAINT `zakaz_ibfk_1` FOREIGN KEY (`client`) REFERENCES `user` (`id`),
  ADD CONSTRAINT `zakaz_ibfk_2` FOREIGN KEY (`good`) REFERENCES `goods` (`id`);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
