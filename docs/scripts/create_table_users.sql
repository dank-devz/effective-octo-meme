CREATE TABLE users
(
    id INT(11) PRIMARY KEY NOT NULL,
    username TINYTEXT NOT NULL,
    password MEDIUMTEXT NOT NULL,
    admin TINYINT(1) DEFAULT '0' NOT NULL
);
CREATE UNIQUE INDEX users_id_uindex ON users (id);
