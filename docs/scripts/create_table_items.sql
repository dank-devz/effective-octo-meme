CREATE TABLE items
(
    id INT(11) NOT NULL,
    name TINYTEXT NOT NULL,
    price DOUBLE NOT NULL,
    itemId INT(11) PRIMARY KEY NOT NULL,
    CONSTRAINT items_restaurants_id_fk FOREIGN KEY (id) REFERENCES restaurants (id)
);
CREATE UNIQUE INDEX items_itemId_uindex ON items (itemId);
CREATE INDEX items_restaurants_id_fk ON items (id);
