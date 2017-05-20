#include "mainwindow.h"

#include <QApplication>
#include <QSettings>
#include <QString>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    translator.load("patternpaint_de");
    a.installTranslator(&translator);

    a.setOrganizationName(ORGANIZATION_NAME);
    a.setOrganizationDomain(ORGANIZATION_DOMAIN);
    a.setApplicationName(APPLICATION_NAME);

    qSetMessagePattern("%{type} %{function}: %{message}");

    MainWindow w;
    w.show();

    return a.exec();
}
