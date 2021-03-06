#ifndef MATRIXFIXTURE_H
#define MATRIXFIXTURE_H

#include <QObject>

#include "fixture.h"

class MatrixFixture : public Fixture
{
    Q_OBJECT

public:
    enum MatrixMode {
        MODE_ZIGZAG,
        MODE_ROWS
    };

    MatrixFixture(QSize size, MatrixMode matrixMode,
                  QObject *parent = 0);

    QSize getSize() const;
    void setSize(QSize newSize);

    MatrixFixture::MatrixMode getMode() const;
    void setMode(MatrixFixture::MatrixMode newMode);

private:
    QSize size;
    MatrixMode matrixMode;

    void recalculateLocations();
};

#endif // MATRIXFIXTURE_H
