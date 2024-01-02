// Cheaturanga. A simple dice-chess program
// Copyright (C) 2023  Rasim Valiullin

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

#ifndef SQUARE_H
#define SQUARE_H

#include <QWidget>
#include <QGridLayout>
#include <QSvgRenderer>

class Square: public QWidget
{
    Q_OBJECT

public:
    enum DownCode
    {
        DCMousePress,
        DCMouseMove,
        DCMouseRelease
    };

    Square(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~Square();

    void init(int id);
    int id() const;

    char warrior() const;

public slots:
    void setBackground(QColor color, bool repaint = true);
    void setWarrior(char warrior, bool repaint = true);
    void setWarriorVisible(bool visible, bool repaint = true);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int m_id = -1;
    char m_warrior = 0;
    bool m_warriorVisible = true;

    QColor m_background{0, 0, 0, 0};
    QSvgRenderer *m_svgRenderer = nullptr;
};

#endif // SQUARE_H
