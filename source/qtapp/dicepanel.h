// Cheaturanga. A simple dice-chess program
// Copyright (C) 2024  Rasim Valiullin

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// rasimvaliullin@hotmail.com

#ifndef DICEPANEL_H
#define DICEPANEL_H

#include <QWidget>
#include "grid.h"
#include "constants.h"

class DicePanel: public QWidget
{
    Q_OBJECT

public:
    DicePanel(QWidget *parent = nullptr);

    void init();

signals:
    void submitDice(const QString &dice);

public slots:
    void drop(const DropInfo &info);
    void set(const QString &dice);
    void submit();

private:
    void setupGrid();

    Grid *m_grid = nullptr;
};

#endif // DICEPANEL_H
