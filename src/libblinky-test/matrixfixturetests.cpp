#include <QTest>

#include "matrixfixturetests.h"
#include "matrixfixture.h"

void MatrixFixtureTests::constructorTest()
{
    MatrixFixture matrixFixture(QSize(),MatrixFixture::MODE_ROWS);

    QVERIFY(matrixFixture.getMode() == MatrixFixture::MODE_ROWS);
    QVERIFY(matrixFixture.getSize() == QSize());
    QVERIFY(matrixFixture.getCount() == 0);
}

void MatrixFixtureTests::setSizeTest_data()
{
    QTest::addColumn<QSize>("size");

    QTest::newRow("0x0") << QSize(0,0);
    QTest::newRow("1x0") << QSize(1,0);
    QTest::newRow("1x1") << QSize(1,1);
    QTest::newRow("1x10") << QSize(1,10);
    QTest::newRow("10x1") << QSize(10,1);
}

void MatrixFixtureTests::setSizeTest()
{
    QFETCH(QSize, size);

    MatrixFixture matrixFixture(QSize(),MatrixFixture::MODE_ROWS);

    matrixFixture.setSize(size);

    QVERIFY(matrixFixture.getSize() == size);
    QVERIFY(matrixFixture.getCount() == static_cast<unsigned int>(size.width()*size.height()));
}

void MatrixFixtureTests::setModeRowsTest_data()
{
    QTest::addColumn<QSize>("size");

    QTest::newRow("0x0") << QSize(0,0);
    QTest::newRow("1x1") << QSize(1,1);
    QTest::newRow("2x3") << QSize(2,3);
    QTest::newRow("3x2") << QSize(3,2);
    QTest::newRow("123x321") << QSize(123,321);
}

void MatrixFixtureTests::setModeRowsTest()
{
    QFETCH(QSize, size);

    MatrixFixture matrixFixture(QSize(),MatrixFixture::MODE_ROWS);

    matrixFixture.setSize(size);

    QVERIFY(matrixFixture.getSize() == size);

    for(int x = 0; x < size.width(); x++) {
        for(int y = 0; y < size.height(); y++) {
            int offset = x*size.height() + y;
            QVERIFY(matrixFixture.getLocations().at(offset) == QPoint(x,y));
        }
    }
}

void MatrixFixtureTests::setModeZigZagTest_data()
{
    QTest::addColumn<QSize>("size");

    QTest::newRow("0x0") << QSize(0,0);
    QTest::newRow("1x1") << QSize(1,1);
    QTest::newRow("2x3") << QSize(2,3);
    QTest::newRow("3x2") << QSize(3,2);
    QTest::newRow("123x321") << QSize(123,321);
}

void MatrixFixtureTests::setModeZigZagTest()
{
    QFETCH(QSize, size);

    MatrixFixture matrixFixture(QSize(),MatrixFixture::MODE_ZIGZAG);

    matrixFixture.setSize(size);

    QVERIFY(matrixFixture.getSize() == size);
    QVERIFY(matrixFixture.getCount() == static_cast<unsigned int>(size.width()*size.height()));

    for(int x = 0; x < size.width(); x++) {
        for(int y = 0; y < size.height(); y++) {
            int offset = x*size.height() + y;

            if((x % 2) == 0) {
                QVERIFY(matrixFixture.getLocations().at(offset) == QPoint(x,y));
            }
            else {
                QVERIFY(matrixFixture.getLocations().at(offset) == QPoint(x, size.height() - 1 - y));
            }
        }
    }
}
