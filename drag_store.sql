-- phpMyAdmin SQL Dump
-- version 5.2.0
-- https://www.phpmyadmin.net/
--
-- Хост: 127.0.0.1:3306
-- Время создания: Дек 26 2022 г., 20:11
-- Версия сервера: 8.0.30
-- Версия PHP: 7.2.34

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- База данных: `drag_store`
--

-- --------------------------------------------------------

--
-- Структура таблицы `categories`
--

CREATE TABLE `categories` (
  `name` varchar(150) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;

--
-- Дамп данных таблицы `categories`
--

INSERT INTO `categories` (`name`) VALUES
('Антидепрессанты'),
('БАД'),
('Нейролептики'),
('Обезболивающие'),
('Офтальмология'),
('Противосудорожные'),
('Седативные средства'),
('Снотворные средства'),
('Сосудосуживающие'),
('Транквилизаторы');

-- --------------------------------------------------------

--
-- Структура таблицы `goods`
--

CREATE TABLE `goods` (
  `id` int NOT NULL,
  `name` varchar(150) NOT NULL,
  `type` varchar(150) NOT NULL,
  `about` varchar(1000) DEFAULT NULL,
  `img` varchar(200) NOT NULL,
  `price` decimal(8,2) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;

--
-- Дамп данных таблицы `goods`
--

INSERT INTO `goods` (`id`, `name`, `type`, `about`, `img`, `price`) VALUES
(1, '9 месяцев Омегамама капсулы №30', 'Обезболивающие', ' Омегамама - биологически активная добавка к пище для беременных и кормящих матерей на основе полинасыщенных жирных кислот Омега-3. Омегамама изготавливается на основе экстракта жира из анчоусов и сардин. ', '/img/goods/omegamama.jpeg', '572.00'),
(2, 'Ад минус таблетки №40 БАД Эвалар', 'БАД', 'Способствует поддержанию артериального давления в норме. 1 таблетка содержит: Трава и цветки гречихи 225 мг, Экстракт гречихи и сушеницы 110 мг, Экстракт плодоножек вишни 50 мг, Витамин С 15 мг, Рутин 10 мг', '/img/goods/adminus.jpeg', '274.00'),
(3, 'Азарга 10мг+5мг капли глазные флакон-капельница 5мл', 'Офтальмология', 'Глазные капли Азарга назначают при повышенном внутриглазном давлении, связанном с открытоугольной глаукомой или внутриглазной гипертензией в тех случаях, когда терапия препаратами с одним активным компонентом оказалась недостаточной для стойкого снижения внутриглазного давления.', '/img/goods/azarga.jpeg', '960.00'),
(10, 'Фезам', 'Сосудосуживающие', 'fdgl\'d;flkg;lksjfdg;lksdf;lkghj;l.khj', '/img/goods/omegamama.jpeg', '480.00'),
(11, 'gfdhfgh;joasd;liguruatoerhy', 'БАД', 'fgshgfrhksjtr;kyhglkusehyrstuyieurpsoighkfdjhgoiau', '/img/goods/adminus.jpeg', '27535.00'),
(12, 'dyuyruytkjjyt', 'Офтальмология', 'dshsrthjswyjrsgreg', '/img/goods/azarga.jpeg', '960345.00');

-- --------------------------------------------------------

--
-- Структура таблицы `user`
--

CREATE TABLE `user` (
  `id` int NOT NULL,
  `fio` varchar(150) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL DEFAULT '',
  `login` varchar(20) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci DEFAULT '',
  `pswd` varchar(60) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci DEFAULT '',
  `address` varchar(80) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci DEFAULT '',
  `phone` varchar(15) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL DEFAULT '',
  `email` varchar(50) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci DEFAULT '',
  `discount` int DEFAULT '0',
  `bday` date DEFAULT '2001-01-01',
  `photo` varchar(50) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL DEFAULT '',
  `role` varchar(10) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL DEFAULT '',
  `workS` date NOT NULL DEFAULT '2001-01-01'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;

--
-- Дамп данных таблицы `user`
--

INSERT INTO `user` (`id`, `fio`, `login`, `pswd`, `address`, `phone`, `email`, `discount`, `bday`, `photo`, `role`, `workS`) VALUES
(1, 'Коновалов Андрей Михайлович', 'director', '$2y$12$BPD/i0YT/A5Xkh7ikWKnv./YeSK7tBeipz7DxUeuL09fiMi027bDW', ' Артем, ул. Западная 8 ', '8-880-987-35-35', 'director@mail.ru', 10, '2012-12-01', '/img/users/director.jpg', 'director', '2017-10-01'),
(2, 'Коновал Михайл', 'kn', '$2y$12$KKBePIHb3oqw4aINQy0V5eQplnjCUTvx3D.xI4QYLmCIniCVmXUMa', ' Артем, ул. Кирова 15 ', '8-800-555-35-35', 'konovam@mail.ru', 5, '1998-09-08', '/img/users/l9I5e5yPDy8.jpg', 'provisor', '2017-11-01'),
(4, 'Филончикова Анна Сергеевна', 'fil', '$2y$12$S9RIcUxD8de/7ZXYGricUeDdQUxLaJT870q4eNnnfmb5aGEZz2j3i', 'г Владивосток, ул Державина, д 21, кв 916а', '8-983-508-57-60', 'afilonchikova2@gmail.com', 2, '2001-01-01', '', 'customer', '2001-01-01');

-- --------------------------------------------------------

--
-- Структура таблицы `zakaz`
--

CREATE TABLE `zakaz` (
  `id` int NOT NULL,
  `client` int NOT NULL,
  `date` date NOT NULL,
  `good` int NOT NULL,
  `count` int NOT NULL,
  `cost` decimal(8,2) DEFAULT NULL,
  `sended` tinyint(1) DEFAULT NULL,
  `done` tinyint(1) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;

--
-- Дамп данных таблицы `zakaz`
--

INSERT INTO `zakaz` (`id`, `client`, `date`, `good`, `count`, `cost`, `sended`, `done`) VALUES
(1, 1, '2017-12-22', 1, 3, '543.40', 0, 0),
(2, 1, '2017-12-22', 2, 2, '520.60', 1, 1),
(3, 1, '2017-12-22', 1, 5, '543.40', 1, 0);

--
-- Индексы сохранённых таблиц
--

--
-- Индексы таблицы `categories`
--
ALTER TABLE `categories`
  ADD PRIMARY KEY (`name`);

--
-- Индексы таблицы `goods`
--
ALTER TABLE `goods`
  ADD PRIMARY KEY (`id`),
  ADD KEY `type` (`type`);

--
-- Индексы таблицы `user`
--
ALTER TABLE `user`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `zakaz`
--
ALTER TABLE `zakaz`
  ADD PRIMARY KEY (`id`),
  ADD KEY `client` (`client`),
  ADD KEY `good` (`good`);

--
-- AUTO_INCREMENT для сохранённых таблиц
--

--
-- AUTO_INCREMENT для таблицы `goods`
--
ALTER TABLE `goods`
  MODIFY `id` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=13;

--
-- AUTO_INCREMENT для таблицы `user`
--
ALTER TABLE `user`
  MODIFY `id` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=11;

--
-- AUTO_INCREMENT для таблицы `zakaz`
--
ALTER TABLE `zakaz`
  MODIFY `id` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

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
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
