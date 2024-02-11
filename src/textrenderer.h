/**************************************************************************
 *  Karlyriceditor - a lyrics editor and CD+G / video export for Karaoke  *
 *  songs.                                                                *
 *  Copyright (C) 2009-2013 George Yunaev, support@ulduzsoft.com          *
 *                                                                        *
 *  This program is free software: you can redistribute it and/or modify  *
 *  it under the terms of the GNU General Public License as published by  *
 *  the Free Software Foundation, either version 3 of the License, or     *
 *  (at your option) any later version.                                   *
 *																	      *
 *  This program is distributed in the hope that it will be useful,       *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *  GNU General Public License for more details.                          *
 *                                                                        *
 *  You should have received a copy of the GNU General Public License     *
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 **************************************************************************/

#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include <QFont>
#include <QColor>
#include <QString>
#include <QStringBuilder>
#include <QTextBoundaryFinder>

#include "lyricsrenderer.h"
#include "lyricsevents.h"
#include "lyrics.h"

class Project;

class TextRenderer : public LyricsRenderer
{
public:
    enum VerticalAlignment
    {
        VerticalBottom = 0,
        VerticalMiddle = 1,
        VerticalTop = 2
    };

    TextRenderer(int width, int height);

    void setLyrics(const Lyrics &lyrics);
    void setRenderFont(const QFont &font);
    void setColorBackground(const QColor &color);
    void setColorTitle(const QColor &color);
    void setColorToSing(const QColor &color);
    void setColorSang(const QColor &color);
    void setPreambleData(unsigned int height, unsigned int timems, unsigned int count);
    void setTitlePageData(const QString &artist, const QString &title, const QString &userCreatedBy, unsigned int msec);
    void setColorAlpha(int alpha);
    void setDefaultVerticalAlign(VerticalAlignment align);
    void forceCDGmode();
    void setDurations(unsigned int before, unsigned int after);
    void setPrefetch(unsigned int prefetch);

    virtual int update(qint64 timing);

    static bool checkFit(const QSize &imagesize, const QFont &font, const QString &text);

    int autodetectFontSize(const QSize &imagesize, const QFont &font);
    bool verifyFontSize(const QSize &imagesize, const QFont &font);

private:
    struct LyricBlockInfo
    {
        qint64 timestart;
        qint64 timeend;
        QString text;
        QMap<qint64, unsigned int> offsets;
        QMap<unsigned int, QString> colors;
        QMap<unsigned int, int> fonts;
        int verticalAlignment;
    };

    QVector<LyricBlockInfo> m_lyricBlocks;
    bool m_forceRedraw;
    bool m_cdgMode;
    QColor m_colorBackground;
    QColor m_colorTitle;
    QColor m_colorToSing;
    QColor m_colorSang;
    QFont m_renderFont;
    unsigned int m_preambleHeight;
    unsigned int m_preambleLengthMs;
    unsigned int m_preambleCount;
    unsigned int m_beforeDuration;
    unsigned int m_afterDuration;
    unsigned int m_prefetchDuration;
    int m_preambleTimeLeft;
    int m_lastDrawnPreamble;
    qint64 m_lastSungTime;
    bool m_drawPreamble;
    int m_lastBlockPlayed;
    int m_lastPosition;
    LyricsEvents m_lyricEvents;
    int m_currentAlignment;

    // Function to normalize Bengali text using NFC
    QString normalizeBengali(const QString &input)
    {
        QString normalizedText = input.normalized(QString::NormalizationForm_C);

        // Additional processing if needed

        return normalizedText;
    }

    QRect boundingRect(int blockid, const QFont &font);
    void init();
    void prepareEvents();
    int lyricForTime(qint64 tickmark, int *sungpos);
    QString titleScreen() const;
    void fixActionSequences(QString &block);
    void drawLyrics(int blockid, int pos, const QRect &boundingRect);
    void drawPreamble();
    void drawBackground(qint64 timing);
};

#endif // TEXTRENDERER_H
