/** -*- mode: c++ ; c-basic-offset: 2 -*-
 *
 *  @file VisibleTagSelector.cpp
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
#include "Widgets/VisibleTagSelector.h"

#include <QActionGroup>
#include <QDebug>
#include <QToolButton>
#include "Common.h"
#include "FilterSelector/FilterTagMap.h"
#include "Tags.h"
namespace GmicQt
{

VisibleTagSelector::VisibleTagSelector(QWidget * parent) : QMenu(parent)
{
  _selectedColor = TagColor::None;
  _toolButton = nullptr;
}

void VisibleTagSelector::setToolButton(QToolButton * button)
{
  _toolButton = button;
  connect(button, &QToolButton::clicked, [this]() {
    updateColors();
    exec(_toolButton->mapToGlobal(_toolButton->rect().center()));
    // _filtersPresenter->toggleSelectionMode(false);
    emit visibleColorChanged(int(_selectedColor));
    // FIXME : Preserve expanded then Unfold all
  });
}

void VisibleTagSelector::updateColors()
{
  QVector<TagColor> colors = FiltersTagMap::usedColors();
  clear();
  QAction * action = addAction(tr("Show all filters"));
  action->setIcon(TagAssets::menuIcon(TagColor::None, (_selectedColor == TagColor::None) ? TagAssets::IconMark::Disk : TagAssets::IconMark::None));
  connect(action, &QAction::triggered, [this]() { _selectedColor = TagColor::None; });
  for (const TagColor & color : colors) {
    int iColor = (int)color;
    QAction * action = addAction(tr("Show only %1 tags").arg(QString::fromUtf8(TagColorNames[iColor])));
    action->setIcon(TagAssets::menuIcon(color, (color == _selectedColor) ? TagAssets::IconMark::Disk : TagAssets::IconMark::None));
    connect(action, &QAction::triggered, [this, color](bool) { //
      _selectedColor = color;
    });
  }
  if (colors.isEmpty() || !colors.contains(_selectedColor)) {
    _selectedColor = TagColor::None;
  }
  if (_toolButton) {
    _toolButton->setEnabled(!colors.isEmpty());
  }
}

TagColor VisibleTagSelector::selectedColor() const
{
  return _selectedColor;
}

VisibleTagSelector::~VisibleTagSelector() {}

} // namespace GmicQt
