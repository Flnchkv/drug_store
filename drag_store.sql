-- phpMyAdmin SQL Dump
-- version 5.2.0
-- https://www.phpmyadmin.net/
--
-- Хост: 127.0.0.1:3306
-- Время создания: Дек 26 2022 г., 16:57
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
(1, '9 месяцев Омегамама капсулы №30', 'БАД', 'Омегамама - биологически активная добавка к пище для беременных и кормящих матерей на основе полинасыщенных жирных кислот Омега-3. Омегамама изготавливается на основе экстракта жира из анчоусов и сардин.', '/img/goods/omegamama.jpeg', '572.00'),
(2, 'Ад минус таблетки №40 БАД Эвалар', 'БАД', 'Способствует поддержанию артериального давления в норме. 1 таблетка содержит: Трава и цветки гречихи 225 мг, Экстракт гречихи и сушеницы 110 мг, Экстракт плодоножек вишни 50 мг, Витамин С 15 мг, Рутин 10 мг', '/img/goods/adminus.jpeg', '274.00'),
(3, 'Азарга 10мг+5мг капли глазные флакон-капельница 5мл', 'Офтальмология', 'Глазные капли Азарга назначают при повышенном внутриглазном давлении, связанном с открытоугольной глаукомой или внутриглазной гипертензией в тех случаях, когда терапия препаратами с одним активным компонентом оказалась недостаточной для стойкого снижения внутриглазного давления.', '/img/goods/azarga.jpeg', '960.00'),
(10, 'Фезам 400мг+25мг 60 шт. капсулы', 'Сосудосуживающие', 'Комбинированный лекарственный препарат с выраженным антигипоксическим, ноотропным и сосудорасширяющим эффектом. Компоненты взаимно потенцируют снижение сопротивления сосудов мозга и способствуют повышению в них кровотока.', '/img/goods/fezam.jpeg', '480.00'),
(11, 'Avicenna Black Seed Oil', 'БАД', 'Наслышаны о пользе масла черного тмина, но опасаетесь его горького вкуса? С его капсулированной формой от Avicenna вы улучшите свое самочувствие, не испытывая дискомфорта. В составе упаковки – 90 капсул с масляным концентратом, насыщенным тимохиноном и линолевой кислотой.\r\n\r\nСредство рекомендовано к приему с 14 лет по 2 капсулы в сутки. Продолжительность курса – 1 месяц. Добавка повышает иммунитет, защищает от вирусов, паразитов и инфекций, обладает противоопухолевым действием.\r\n\r\nКроме того, масло черного тмина улучшает химические показатели крови, моторику кишечника и стимулирует рост здоровых и густых волос. Avicenna Black Seed Oil улучшает физическое самочувствие и внешнюю привлекательность, дарит заряд энергии и защищает в сезон простуд.\r\n\r\nВ числе противопоказаний к приему – детский возраст, беременность, лактация и индивидуальная непереносимость.', '/img/goods/seeg.jpeg', '27535.00'),
(15, 'Амитриптилин, таблетки 25 мг 50 шт', 'Антидепрессанты', 'Один из основных представителей трициклических антидепрессантов, наряду с имипрамином и кломипрамином. Амитриптилин является препаратом, в основном используемым для лечения ряда психических заболеваний: депрессивных и тревожных расстройств, реже синдрома дефицита внимания и гиперактивности и биполярного расстройства[2]. Другие показания включают профилактику мигрени, лечение нейропатической боли, такой как фибромиалгия и постгерпетическая невралгия, и реже бессонницы[3]. Препарат относится к классу трициклических антидепрессантов (ТЦА), и его точный механизм действия неясен. Амитриптилин применяется перорально и в виде инъекций.', '/img/goods/amit.jpeg', '67.00'),
(16, 'Ново-Пассит, таблетки покрыт.плен.об. 60 шт', 'Снотворные средства', 'Комбинированный препарат, фармакологическая активность которого обусловлена входящими в его состав компонентами экстракта на основе лекарственного растительного сырья с преимущественно седативным (успокаивающим) действием и гвайфенезином, обладающим анксиолитическим (противотревожным) эффектом.', '/img/goods/novopassit.png', '1079.00');

-- --------------------------------------------------------

--
-- Структура таблицы `user`
--

CREATE TABLE `user` (
  `id` int NOT NULL,
  `fio` varchar(150) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL DEFAULT '',
  `login` varchar(20) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci DEFAULT '',
  `pswd` varchar(20) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci DEFAULT '',
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
(1, 'Коновалов Андрей Михайлович', 'director', 'pswd', ' Артем, ул. Западная 8 ', '8-880-987-35-35', 'director@mail.ru', 10, '0000-00-00', '/kozlova/img/users/director.jpg', 'director', '2017-10-01'),
(2, 'Коновал Михайл', 'kn', 'knm', ' Артем, ул. Кирова 15 ', '8-800-555-35-35', 'konovam@mail.ru', 5, '0000-00-00', '/kozlova/img/users/l9I5e5yPDy8.jpg', 'provisor', '2017-11-01'),
(3, 'Козлова Светлана Евгеньевна', 'koz', 'koz123', 'Артем, ул. Фрунзе 10', '8-914-756-35-35', 'kozlova@mail.ru', 0, NULL, '', 'customer', '0000-00-00'),
(4, 'Филончикова Анна Сергеевна', 'fil', '123', 'г Владивосток, ул Державина, д 21, кв 916а', '8-983-508-57-60', 'afilonchikova2@gmail.com', 0, '2001-01-01', '', 'customer', '2001-01-01');

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
  MODIFY `id` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=17;

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
