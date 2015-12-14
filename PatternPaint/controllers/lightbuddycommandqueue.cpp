#include "lightbuddycommandqueue.h"

QByteArray commandHeader()
{
    QByteArray output;
    for (int i = 0; i < 12; i++)
        output.append((char)0xFF);
    return output;
}

QByteArray encodeInt(int data)
{
    QByteArray output;
    output.append((char)((data >> 24) & 0xFF));
    output.append((char)((data >> 16) & 0xFF));
    output.append((char)((data >>  8) & 0xFF));
    output.append((char)((data) & 0xFF));
    return output;
}

LightBuddySerialQueue::LightBuddySerialQueue(QObject *parent) :
    SerialCommandQueue(parent)
{
}

void LightBuddySerialQueue::eraseFlash()
{
    QByteArray command;
    command + commandHeader();

    command.append((char)0x20); // Erase flash
    command.append('E');        // Checksum sequence
    command.append('e');

    QByteArray ret;
    ret.append('P');
    ret.append((char)0x00);
    ret.append((char)0x00);

    QByteArray mask;
    mask.append((char)0xFF);
    mask.append((char)0x00);
    mask.append((char)0x00);

    // Note: only the length matters for the response, the response data
    // will be ignored.
    queueCommand("eraseFlash", command, ret, mask);
}

void LightBuddySerialQueue::fileNew(int sizeBytes)
{
    QByteArray command;
    command + commandHeader();

    command.append((char)0x18);   // New file
    command.append((char)0x12);   // filetype = animation
    command += encodeInt(sizeBytes);

    QByteArray ret;
    ret.append('P');
    ret.append((char)0x03);
    ret.append((char)0x00);     // 4 bytes containing the sector data
    ret.append((char)0x00);
    ret.append((char)0x00);
    ret.append((char)0x00);

    QByteArray mask;
    mask.append((char)0xFF);
    mask.append((char)0xFF);
    mask.append((char)0x00);
    mask.append((char)0x00);
    mask.append((char)0x00);
    mask.append((char)0x00);

    queueCommand("fileNew", command, ret, mask);
}

void LightBuddySerialQueue::writePage(int sector, int offset, QByteArray data)
{
    if (data.size() != 256) {
        // TODO: How to error out here?
        return;
    }

    QByteArray command;
    command + commandHeader();

    command.append((char)0x19);     // Write page
    command += encodeInt(sector);
    command += encodeInt(offset);
    command += data;

    QByteArray ret;
    ret.append('P');
    ret.append((char)0x00);
    ret.append((char)0x00);

    QByteArray mask;
    mask.append((char)0xFF);
    mask.append((char)0xFF);
    mask.append((char)0x00);

    // Note: only the length matters for the response, the response data
    // will be ignored.
    queueCommand("writePage", command, ret, mask);
}

void LightBuddySerialQueue::reloadAnimations()
{
    QByteArray command;
    command + commandHeader();

    command.append((char)0x02);     // Reload animations

    QByteArray ret;
    ret.append('P');
    ret.append((char)0x00);
    ret.append((char)0x00);

    QByteArray mask;
    mask.append((char)0xFF);
    mask.append((char)0xFF);
    mask.append((char)0x00);

    // Note: only the length matters for the response, the response data
    // will be ignored.
    queueCommand("reloadAnimations", command, ret, mask);
}
