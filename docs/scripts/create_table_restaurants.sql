CREATE TABLE `restaurants` (
      `id` int(11) NOT NULL AUTO_INCREMENT,
      `name` tinytext NOT NULL,
      PRIMARY KEY (`id`),
      UNIQUE KEY `restaurants_id_uindex` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=33 DEFAULT CHARSET=latin1
