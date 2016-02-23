//#ifndef TEST_DATABASE_H
//#define TEST_DATABASE_H


class Test_Database: public QObject
{
    Q_OBJECT
private slots:
    void initTest();
};

void Test_Database::initTest(){
    QVERIFY("Testing" == "Testing");
}

//#endif //TEST_DATABASE_H

QTEST_MAIN(Test_Database)
#include "test_database.moc"

