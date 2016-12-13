#include "systeminformation.h"
#include "ui_systeminformation.h"

#include "blinkytape.h"
#include "usbutils.h"
#include "blinkycontroller.h"

#include <QSysInfo>
#include <QLibraryInfo>
#include <QtWidgetsDepends>
#include <QPointer>

SystemInformation::SystemInformation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SystemInformation)
{
    ui->setupUi(this);

    on_refresh_clicked();
}

SystemInformation::~SystemInformation()
{
    delete ui;
}

void SystemInformation::on_refresh_clicked()
{
    QString report;

    report.append("Pattern Paint ");
    report.append(GIT_VERSION);
    report.append("\n");
    report.append("  Build Date: ");
    report.append(__DATE__);
    report.append(" ");
    report.append(__TIME__);
    report.append("\n");

#if QT_VERSION > QT_VERSION_CHECK(5, 4, 0)
    report.append("Operating system: " + QSysInfo::prettyProductName() + "\n");
#else
    report.append("Operating system: ???\n");
#endif

    // TODO: Get this from the controllers rather than building them here.
    report.append("Detected Blinkies: \n");
    foreach (const QPointer<ControllerInfo> &info, BlinkyTape::probe())
        report.append("  BlinkyTape:" + info->resourceName() + "\n");
    foreach (const QSerialPortInfo &info, BlinkyTape::probeBootloaders())
        report.append("  BlinkyTape:" + info.portName() + " (bootloader)\n");

    report.append("Detected Serial Ports: \n");
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        int version = getVersionForDevice(info.vendorIdentifier(), info.productIdentifier());

        report.append("  " + info.portName() + "\n");
        report.append("    Manufacturer: " + info.manufacturer() + "\n");
        report.append("    Description: " + info.description() + "\n");
        report.append("    VID: 0x" + QString::number(info.vendorIdentifier(), 16) + "\n");
        report.append("    PID: 0x" + QString::number(info.productIdentifier(), 16) + "\n");
        if (version > -1)
            report.append("    Version: 0x" + QString::number(version, 16) + "\n");

#if QT_VERSION > QT_VERSION_CHECK(5, 3, 0)
        report.append("    Serial: " + info.serialNumber() + "\n");
#else
        report.append("    Serial: ???\n");
#endif
    }

    ui->infoBrowser->setText(report);
}

void SystemInformation::on_copyToClipboard_clicked()
{
    QClipboard *clip = QApplication::clipboard();
    QString input = ui->infoBrowser->toPlainText();
    clip->setText(input);
}

void SystemInformation::on_sendToSupport_clicked()
{
    QString body = "Thanks for helping make Pattern Paint a better program!\n"
                   "Please fill out this brief questionaire to help us better understand your issue.\n\n"
                   "1. Please describe the issue you are having:\n\n\n\n"
                   "2. How can we reproduce it? Be as detailed as possible. If there is a specific pattern that causes the problem, please attach it:\n\n\n\n"
                   "3. Has this worked for you before?\n\n\n\n"
                   "============ System Information generated by PatternPaint ============\n"
                   + ui->infoBrowser->toPlainText();

    QDesktopServices::openUrl(QUrl(
                                  "mailto:support@blinkinlabs.com?subject=Pattern Paint issue&body="
                                  + body,
                                  QUrl::TolerantMode));
}
