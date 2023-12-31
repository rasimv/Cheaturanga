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
#include <QtSvgWidgets/QSvgWidget>

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

    Square(QWidget *parent = nullptr);
    ~Square();

signals:
    void down(const QByteArray &d);

public slots:
    void init(int id, char type);
    void setWarrior(char warrior);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QByteArray mouseData(DownCode code, QMouseEvent *event);

    int m_id = -1;
    QGridLayout *m_layout = nullptr;
    QSvgWidget *m_content = nullptr;
};

#endif // SQUARE_H
