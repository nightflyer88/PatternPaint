#ifndef PATTERN_WRITER_H
#define PATTERN_WRITER_H

#include "pattern.h"

#include <QImage>
#include <QString>

/// Container for a compressed pattern
/// This class performs a 1-shot compression of an image from a QIMage.
class PatternWriter
{
public:
    // TODO: Move me to a converter class
    enum ColorMode {
        RGB,
        GRB,
        COLOR_MODE_COUNT,
    };

    enum Encoding {
        RGB24       = 0,     /// RGB24 mode (uncompressed 24 bit)
        RGB565_RLE  = 1,     /// RGB 565 + RLE mode (compressed 16 bit)
//        INDEXED     = 2,     /// 8-bit indexed mode (pallated 8 bit)
//        INDEXED_RLE = 3,     /// 8-bit indexed mode + RLE (pallated 8 bit)
    };

    // Create an pattern from a QImage
    PatternWriter(const Pattern *pattern, int frameDelay, Encoding encoding, ColorMode colorMode);

    Encoding getEncoding() const { return encoding; }
    QByteArray getData() const { return data; }
    QString getHeader() const { return header; }


    int colorCount() const;  /// Number of unique colors in the original image

    int getFrameCount() const { return frameCount; }
    int getLedCount() const { return ledCount; }
    int getFrameDelay() const { return frameDelay; }
    ColorMode getColorMode() const { return colorMode; }

private:

    Encoding encoding;  /// Encoding used to compress the pattern
    QByteArray data;    /// Byte array representation of the pattern
    QString header;     /// C++ header representation of the pattern


    int frameCount;     /// Number of frames in this pattern
    int ledCount;       /// Number of LEDs attached to this blinky
    int frameDelay;     /// Length of time between frames of data, in ms
    ColorMode colorMode;    /// Pattern color mode

    // Compress an RGB color to the 565 color space
    // TODO: Improve this conversion using a lookup table, instead of
    // decimation.
    int QRgbTo565(QColor color);

    void encodeImageRGB24(const Pattern *pattern);
    void encodeImageRGB16_RLE(const Pattern *pattern);
//    void encodeImageIndexed(const Pattern *pattern);
//    void encodeImageIndexed_RLE(const Pattern *pattern);
};



struct ColorModes {
    PatternWriter::ColorMode colorMode;
    QString name;
};

Q_DECLARE_METATYPE(PatternWriter::ColorMode);

extern ColorModes colorModes[PatternWriter::COLOR_MODE_COUNT];

#endif // PATTERN_WRITER_H