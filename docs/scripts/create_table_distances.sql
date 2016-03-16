CREATE TABLE distances
(
        `from` INT(11) NOT NULL,
            `to` INT(11) NOT NULL,
                distance DOUBLE NOT NULL,
                    CONSTRAINT distances_restaurants_id2_fk FOREIGN KEY (`to`) REFERENCES restaurants (id),
                        CONSTRAINT distances_restaurants_id_fk FOREIGN KEY (`from`) REFERENCES restaurants (id)
                    );
                    CREATE INDEX distances_restaurants_id2_fk ON distances (`to`);
                    CREATE INDEX distances_restaurants_id_fk ON distances (`from`);
