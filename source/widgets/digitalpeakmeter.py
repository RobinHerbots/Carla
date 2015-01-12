#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# Digital Peak Meter, a custom Qt4 widget
# Copyright (C) 2011-2015 Filipe Coelho <falktx@falktx.com>
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation; either version 2 of
# the License, or any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# For a full copy of the GNU General Public License see the doc/GPL.txt file.

# ------------------------------------------------------------------------------------------------------------
# Imports (Config)

from carla_config import *

# ------------------------------------------------------------------------------------------------------------
# Imports (Global)

if config_UseQt5:
    from PyQt5.QtCore import qCritical, Qt, QTimer, QSize
    from PyQt5.QtGui import QColor, QLinearGradient, QPainter
    from PyQt5.QtWidgets import QWidget
else:
    from PyQt4.QtCore import qCritical, Qt, QTimer, QSize
    from PyQt4.QtGui import QColor, QLinearGradient, QPainter, QWidget

# ------------------------------------------------------------------------------------------------------------
# Widget Class

class DigitalPeakMeter(QWidget):
    # enum Color
    COLOR_GREEN = 1
    COLOR_BLUE  = 2

    # enum Orientation
    HORIZONTAL = 1
    VERTICAL   = 2

    # enum Style
    STYLE_DEFAULT = 1
    STYLE_OPENAV  = 2
    STYLE_RNCBC   = 3

    def __init__(self, parent):
        QWidget.__init__(self, parent)

        # defaults are VERTICAL, COLOR_GREEN, STYLE_DEFAULT

        self.fChannelCount    = 0
        self.fChannelData     = []
        self.fLastChannelData = []

        self.fMeterColor        = self.COLOR_GREEN
        self.fMeterColorBase    = QColor(93, 231, 61)
        self.fMeterColorBaseAlt = QColor(15, 110, 15, 100)

        self.fMeterLinesEnabled = True
        self.fMeterOrientation  = self.VERTICAL
        self.fMeterStyle        = self.STYLE_DEFAULT

        self.fMeterBackground = QColor("#111111")
        self.fMeterGradient   = QLinearGradient(0, 0, 0, 0)

        self.fSmoothMultiplier = 1

        self.updateGrandient()

    # --------------------------------------------------------------------------------------------------------

    def channelCount(self):
        return self.fChannelCount

    def setChannelCount(self, count):
        if self.fChannelCount == count:
            return

        if count < 0:
            return qCritical("DigitalPeakMeter::setChannelCount(%i) - channel count must be a positive integer or zero" % count)

        self.fChannelCount    = count
        self.fChannelData     = []
        self.fLastChannelData = []

        for x in range(count):
            self.fChannelData.append(0.0)
            self.fLastChannelData.append(0.0)

    # --------------------------------------------------------------------------------------------------------

    def meterColor(self):
        return self.fMeterColor

    def setMeterColor(self, color):
        if self.fMeterColor == color:
            return

        if color not in (self.COLOR_GREEN, self.COLOR_BLUE):
            return qCritical("DigitalPeakMeter::setMeterColor(%i) - invalid color" % color)

        self.fMeterColor = color

        if color == self.COLOR_GREEN:
            self.fMeterColorBase    = QColor(93, 231, 61)
            self.fMeterColorBaseAlt = QColor(15, 110, 15, 100)
        elif color == self.COLOR_BLUE:
            self.fMeterColorBase    = QColor(82, 238, 248)
            self.fMeterColorBaseAlt = QColor(15, 15, 110, 100)

        self.updateGrandient()

    # --------------------------------------------------------------------------------------------------------

    def meterLinesEnabled(self):
        return self.fMeterLinesEnabled

    def setMeterLinesEnabled(self, yesNo):
        if self.fMeterLinesEnabled == yesNo:
            return

        self.fMeterLinesEnabled = yesNo

    # --------------------------------------------------------------------------------------------------------

    def meterOrientation(self):
        return self.fMeterOrientation

    def setMeterOrientation(self, orientation):
        if self.fMeterOrientation == orientation:
            return

        if orientation not in (self.HORIZONTAL, self.VERTICAL):
            return qCritical("DigitalPeakMeter::setMeterOrientation(%i) - invalid orientation" % orientation)

        self.fMeterOrientation = orientation

        self.updateGrandient()

    # --------------------------------------------------------------------------------------------------------

    def meterStyle(self):
        return self.fMeterStyle

    def setMeterStyle(self, style):
        if self.fMeterStyle == style:
            return

        if style not in (self.STYLE_DEFAULT, self.STYLE_OPENAV, self.STYLE_RNCBC):
            return qCritical("DigitalPeakMeter::setMeterStyle(%i) - invalid style" % style)

        self.fMeterStyle = style

        if style == self.STYLE_DEFAULT:
            self.fMeterBackground = QColor("#111111")
        elif style == self.STYLE_OPENAV:
            self.fMeterBackground = QColor("#1A1A1A")
        elif style == self.STYLE_RNCBC:
            self.fMeterBackground = QColor("#111111")

        self.updateGrandient()

    # --------------------------------------------------------------------------------------------------------

    def smoothMultiplier(self):
        return self.fSmoothMultiplier

    def setSmoothMultiplier(self, value):
        if self.fSmoothMultiplier == value:
            return

        if not isinstance(value, int):
            return qCritical("DigitalPeakMeter::setSmoothMultiplier() - value must be an integer")
        if value < 0:
            return qCritical("DigitalPeakMeter::setSmoothMultiplier(%i) - value must be >= 0" % value)
        if value > 5:
            return qCritical("DigitalPeakMeter::setSmoothMultiplier(%i) - value must be < 5" % value)

        self.fSmoothMultiplier = value

    # --------------------------------------------------------------------------------------------------------

    def displayMeter(self, meter, level, forced = False):
        if not isinstance(meter, int):
            return qCritical("DigitalPeakMeter::displayMeter(,) - meter value must be an integer")
        if not isinstance(level, float):
            return qCritical("DigitalPeakMeter::displayMeter(%i,) - level value must be a float" % (meter,))
        if meter <= 0 or meter > self.fChannelCount:
            return qCritical("DigitalPeakMeter::displayMeter(%i, %f) - invalid meter number" % (meter, level))

        i = meter - 1

        if self.fSmoothMultiplier > 0 and not forced:
            level = (self.fLastChannelData[i] * float(self.fSmoothMultiplier) + level) / float(self.fSmoothMultiplier + 1)

        if level < 0.001:
            level = 0.0
        elif level > 0.999:
            level = 1.0

        if self.fChannelData[i] != level:
            self.fChannelData[i] = level
            self.update()

        self.fLastChannelData[i] = level

    # --------------------------------------------------------------------------------------------------------

    def updateGrandient(self):
        self.fMeterGradient = QLinearGradient(0, 0, 1, 1)

        if self.fMeterStyle == self.STYLE_OPENAV:
            self.fMeterGradient.setColorAt(0.0, self.fMeterColorBase)
            self.fMeterGradient.setColorAt(1.0, self.fMeterColorBase)

        elif self.fMeterOrientation == self.HORIZONTAL:
            self.fMeterGradient.setColorAt(0.0, self.fMeterColorBase)
            self.fMeterGradient.setColorAt(0.2, self.fMeterColorBase)
            self.fMeterGradient.setColorAt(0.4, self.fMeterColorBase)
            self.fMeterGradient.setColorAt(0.6, self.fMeterColorBase)
            self.fMeterGradient.setColorAt(0.8, Qt.yellow)
            self.fMeterGradient.setColorAt(1.0, Qt.red)

        elif self.fMeterOrientation == self.VERTICAL:
            self.fMeterGradient.setColorAt(0.0, Qt.red)
            self.fMeterGradient.setColorAt(0.2, Qt.yellow)
            self.fMeterGradient.setColorAt(0.4, self.fMeterColorBase)
            self.fMeterGradient.setColorAt(0.6, self.fMeterColorBase)
            self.fMeterGradient.setColorAt(0.8, self.fMeterColorBase)
            self.fMeterGradient.setColorAt(1.0, self.fMeterColorBase)

        self.updateGrandientFinalStop()

    def updateGrandientFinalStop(self):
        if self.fMeterOrientation == self.HORIZONTAL:
            self.fMeterGradient.setFinalStop(self.width(), 0)

        elif self.fMeterOrientation == self.VERTICAL:
            self.fMeterGradient.setFinalStop(0, self.height())

    # --------------------------------------------------------------------------------------------------------

    def minimumSizeHint(self):
        return QSize(10, 10)

    def sizeHint(self):
        return QSize(self.width(), self.height())

    # --------------------------------------------------------------------------------------------------------

    def paintEvent(self, event):
        painter = QPainter(self)
        event.accept()

        width  = self.width()
        height = self.height()

        if self.fMeterStyle == self.STYLE_OPENAV:
            painter.setPen(QColor("#1A1A1A"))
            painter.setBrush(QColor("#1A1A1A"))
        else:
            painter.setPen(Qt.black)
            painter.setBrush(Qt.black)

        painter.drawRect(0, 0, width, height)

        meterX  = 0
        startX  = -1 if self.fMeterStyle == self.STYLE_OPENAV else 0
        padding =  2 if self.fMeterStyle == self.STYLE_OPENAV else 0

        painter.setPen(self.fMeterBackground) # FIXME ?
        painter.setBrush(self.fMeterGradient)

        #if self.fMeterStyle == self.STYLE_OPENAV:
            #color = self.fMeterGradient.stops()[0][1]
            #painter.setPen(color)
            #color.setAlphaF(0.5)
            #painter.setBrush(color)
            #del color

        for i in range(self.fChannelCount):
            level = self.fChannelsData[i]

            if self.fMeterOrientation == self.HORIZONTAL:
                value = level * float(width)
            elif self.fMeterOrientation == self.VERTICAL:
                value = float(height) - (level * float(height))
            else:
                value = 0.0

            if self.fMeterOrientation == self.HORIZONTAL:
                painter.drawRect(startX, meterX+padding, int(value), self.fSizeMeter-padding*(1 if self.fChannels > 1 else 2))
            elif self.fMeterOrientation == self.VERTICAL:
                painter.drawRect(meterX, int(value), self.fSizeMeter, self.fHeight)

            meterX += self.fSizeMeter

        if not self.fDrawLines:
            return

        painter.setBrush(Qt.black)

        if self.fOrientation == self.HORIZONTAL:
            # Variables
            lsmall = float(self.fWidth)
            lfull  = float(self.fHeight - 1)

            if self.fMeterStyle == self.STYLE_OPENAV:
                painter.setPen(QColor(37, 37, 37, 100))
                painter.drawLine(lsmall * 0.25, 2, lsmall * 0.25, lfull-2.0)
                painter.drawLine(lsmall * 0.50, 2, lsmall * 0.50, lfull-2.0)
                painter.drawLine(lsmall * 0.75, 2, lsmall * 0.75, lfull-2.0)

                if self.fChannels > 1:
                    painter.drawLine(1, lfull/2, lsmall-1, lfull/2)

            else:
                # Base
                painter.setPen(self.fColorBaseAlt)
                painter.drawLine(lsmall * 0.25, 2, lsmall * 0.25, lfull-2.0)
                painter.drawLine(lsmall * 0.50, 2, lsmall * 0.50, lfull-2.0)

                # Yellow
                painter.setPen(QColor(110, 110, 15, 100))
                painter.drawLine(lsmall * 0.70, 2, lsmall * 0.70, lfull-2.0)
                painter.drawLine(lsmall * 0.83, 2, lsmall * 0.83, lfull-2.0)

                # Orange
                painter.setPen(QColor(180, 110, 15, 100))
                painter.drawLine(lsmall * 0.90, 2, lsmall * 0.90, lfull-2.0)

                # Red
                painter.setPen(QColor(110, 15, 15, 100))
                painter.drawLine(lsmall * 0.96, 2, lsmall * 0.96, lfull-2.0)

        elif self.fOrientation == self.VERTICAL:
            # Variables
            lsmall = float(self.fHeight)
            lfull  = float(self.fWidth - 1)

            if self.fMeterStyle == self.STYLE_OPENAV:
                # TODO
                pass

            else:
                # Base
                painter.setPen(self.fColorBaseAlt)
                painter.drawLine(2, lsmall - (lsmall * 0.25), lfull-2.0, lsmall - (lsmall * 0.25))
                painter.drawLine(2, lsmall - (lsmall * 0.50), lfull-2.0, lsmall - (lsmall * 0.50))

                # Yellow
                painter.setPen(QColor(110, 110, 15, 100))
                painter.drawLine(2, lsmall - (lsmall * 0.70), lfull-2.0, lsmall - (lsmall * 0.70))
                painter.drawLine(2, lsmall - (lsmall * 0.82), lfull-2.0, lsmall - (lsmall * 0.82))

                # Orange
                painter.setPen(QColor(180, 110, 15, 100))
                painter.drawLine(2, lsmall - (lsmall * 0.90), lfull-2.0, lsmall - (lsmall * 0.90))

                # Red
                painter.setPen(QColor(110, 15, 15, 100))
                painter.drawLine(2, lsmall - (lsmall * 0.96), lfull-2.0, lsmall - (lsmall * 0.96))

    # --------------------------------------------------------------------------------------------------------

    def resizeEvent(self, event):
        self.updateGrandientFinalStop()
        QWidget.resizeEvent(self, event)

# ------------------------------------------------------------------------------------------------------------
# Main Testing

if __name__ == '__main__':
    import sys
    import resources_rc

    if config_UseQt5:
        from PyQt5.QtWidgets import QApplication
    else:
        from PyQt4.QtGui import QApplication

    app = QApplication(sys.argv)

    gui = DigitalPeakMeter(None)
    gui.setChannelCount(2)
    gui.displayMeter(1, 0.5)
    gui.displayMeter(2, 0.8)
    gui.show()

    sys.exit(app.exec_())
