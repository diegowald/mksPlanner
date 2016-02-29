#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include "../mksPlanner/models/unit.h"

class MksPlannerTestTest : public QObject
{
    Q_OBJECT

public:
    MksPlannerTestTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase1_data();
    void testCase1();

    void testUnit_data();
    void testUnit();
};

MksPlannerTestTest::MksPlannerTestTest()
{
}

void MksPlannerTestTest::initTestCase()
{
}

void MksPlannerTestTest::cleanupTestCase()
{
}

void MksPlannerTestTest::testCase1_data()
{
    QTest::addColumn<QString>("data");
    QTest::newRow("0") << QString();
}

void MksPlannerTestTest::testCase1()
{
    QFETCH(QString, data);
    QVERIFY2(true, "Failure");
}

void MksPlannerTestTest::testUnit_data()
{
    QTest::addColumn<int>("id");
    QTest::addColumn<QString>("name");
    QTest::addColumn<QString>("description");
    QTest::newRow("0") << 1 << "kg" << "kilogramo";
}

void MksPlannerTestTest::testUnit()
{
    QFETCH(int, id);
    QFETCH(QString, name);
    QFETCH(QString, description);
    Unit unit(id);
    unit.setName(name);
    unit.setDescripcion(description);
    QVERIFY2(id == unit.id(), "unit::id");
    QVERIFY2(name == unit.name(), "unit::name");
    QVERIFY2(description == unit.description(), "unit::description");
    QVERIFY2(EntityStatus::added == unit.status(), "unit::status");

    Unit unit2(id, name, description);
    QVERIFY2(id == unit2.id(), "unit::id");
    QVERIFY2(name == unit2.name(), "unit::name");
    QVERIFY2(description == unit2.description(), "unit::description");
    QVERIFY2(EntityStatus::unchanged == unit2.status(), "unit::status");

    unit2.setName("x");
    QVERIFY2(EntityStatus::modified == unit2.status(), "unit::status");

    unit2.deleteEntity();
    QVERIFY2(EntityStatus::deleted == unit2.status(), "unit::status");

}

QTEST_MAIN(MksPlannerTestTest)

#include "tst_mksplannertesttest.moc"
