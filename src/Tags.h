/** -*- mode: c++ ; c-basic-offset: 2 -*-
 *
 *  @file Tags.h
 *
 *  Copyright 2017 Sebastien Fourey
 *
 *  This file is part of G'MIC-Qt, a generic plug-in for raster graphics
 *  editors, offering hundreds of filters thanks to the underlying G'MIC
 *  image processing framework.
 *
 *  gmic_qt is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  gmic_qt is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with gmic_qt.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#ifndef GMIC_QT_TAGS_H
#define GMIC_QT_TAGS_H

#include <QColor>
#include <QIcon>
#include <QString>
#include <QVector>
class QAction;
class QObject;

namespace GmicQt
{

enum class TagColor
{
  None,
  Red,
  Green,
  Blue,
  Cyan,
  Magenta,
  Yellow,
  Count
};

extern const char * TagColorNames[];

class TagAssets {

public:
  enum class IconMark
  {
    None,
    Check,
    Disk
  };
  static const QString & markerHtml(TagColor color, unsigned int sideSize);
  static const QIcon & menuIcon(TagColor color, IconMark mark);
  static QColor colors[static_cast<unsigned int>(TagColor::Count)];
  static QAction * action(QObject * parent, TagColor color, IconMark mark);

private:
  static QString _markerHtml[static_cast<unsigned int>(TagColor::Count)];
  static QIcon _menuIcons[static_cast<unsigned int>(TagColor::Count)];
  static QIcon _menuIconsWithCheck[static_cast<unsigned int>(TagColor::Count)];
  static QIcon _menuIconsWithDisk[static_cast<unsigned int>(TagColor::Count)];
  static unsigned int _markerSideSize[static_cast<unsigned int>(TagColor::Count)];
};

} // namespace GmicQt

#endif // GMIC_QT_TAGS_H
