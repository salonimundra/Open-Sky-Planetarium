/*
 * Copyright (C) 2016 Dhiraj Salian
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Suite 500, Boston, MA  02110-1335, USA.
 */

#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QSerialPort>
#include <QTextStream>
#include <QCoreApplication>
#include <QString>
#include <QObject>
#include <QThread>
#include <QTime>
#include <QTimer>
#include "Coords.hpp"
#ifndef LASERDEV_HPP
#define LASERDEV_HPP


class LaserDev : public QObject
{
    Q_OBJECT
    QThread ldevThread;
public:
    LaserDev(QObject *parent=0);
    ~LaserDev();
    QSerialPort osp_serialPort;
    //virtual QString sread(QString expect=QString("^cmd$"),int wait=0);
    QList<QSerialPortInfo> getAvailablePorts();
    bool isNull();
    bool configure(const QSerialPortInfo serialPortInfo);
    void closeConnection();
signals:
    void init_received();
    void pos_received(QString,QString);
    void pos_e_received(QString,QString);
private:
    QString line;
    QString cmd;
    QString set_time;
    QString expect;
    QString sra,sdec,stime;
    QTimer* timer;
    QByteArray osp_ba;
    Coords coords;
public slots:
    void sread();
    void setTime();
    void init();
    void setRef(int id_ref,QString ra,QString dec,QString time);
    void goTo(QString ra,QString dec,QString time);
    void move(QString ac,QString alt);
    void movx(QString signDir);
    void movy(QString signDir);
    void stop();
    void laserOn();
    void laserOff();
};

#endif // LASERDEV_HPP
