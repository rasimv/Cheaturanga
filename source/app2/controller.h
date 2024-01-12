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

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QProcess>
#include <QTimer>

class Controller: public QObject
{
    Q_OBJECT

public:
    explicit Controller(QObject *parent = nullptr);

    void init();
    void start();

signals:
    void log(const QStringList &piece);
    void toss(const QString &dice);

public slots:
    void submitDice(const QString &dice);

private slots:
    void outputReady();

private:
    QProcess *m_engine = nullptr;
    QByteArray m_rawQueue;
    QStringList m_queue;

    QTimer m_timer;
};

#endif // CONTROLLER_H
