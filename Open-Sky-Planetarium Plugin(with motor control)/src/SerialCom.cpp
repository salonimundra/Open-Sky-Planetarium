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
#include "SerialCom.hpp"
#include <QtSerialPort/QSerialPort>
#include <QTime>

QT_USE_NAMESPACE

/**
Constructor:
*/
SerialCom::SerialCom(QObject *parent)
    : QThread(parent), waitTime(0), quit(false)
{
}

/**
Destructor:
*/
SerialCom::~SerialCom()
{
    mutex.lock();
    quit = true;
    cond.wakeOne();
    mutex.unlock();
    wait();
}

/**
sendRequest(const QString, int, const QString):
	Send a request to arduino
*/
void SerialCom::sendRequest(const QString &port, int waitTime, const QString &request)
{
    QMutexLocker locker(&mutex);
    this->port = port;
    this->waitTime = waitTime;
    this->request = request;
    if (!isRunning())
        start();
    else
        cond.wakeOne();
}

/**
run()
	
*/
void SerialCom::run()
{
    bool myPortNameChanged = false;

    //mutex.lock();
    QString myPortName;
    if (myPortName != port) {
        myPortName = port;
        myPortNameChanged = true;
    }

    int myWaitTimeout = waitTime;
    QString myRequest = request;
    //mutex.unlock();
    QSerialPort serial;

    while (!quit) {
        if (myPortNameChanged) {
            serial.close();
            serial.setPortName(myPortName);

            if (!serial.open(QIODevice::ReadWrite)) {
                emit error(tr("Can't open %1, error code %2")
                           .arg(port).arg(serial.error()));
                return;
            }
        }
        QByteArray requestData = myRequest.toLocal8Bit();
        serial.write(requestData);
        if (serial.waitForBytesWritten(waitTime)) {
            if (serial.waitForReadyRead(myWaitTimeout)) {
                QByteArray responseData = serial.readAll();
                while (serial.waitForReadyRead(10))
                    responseData += serial.readAll();
                QString response(responseData);
                emit this->response(response);
            } else {
                emit timeout(tr("Wait Read Request Timed Out %1")
                             .arg(QTime::currentTime().toString()));
            }
        } else {
            emit timeout(tr("Wait Write Request Timed Out %1")
                         .arg(QTime::currentTime().toString()));
        }
        //mutex.lock();
        cond.wait(&mutex);
        if (myPortName != port) {
            myPortName = port;
            myPortNameChanged = true;
        } else {
            myPortNameChanged = false;
        }
        myWaitTimeout = waitTime;
        myRequest = request;
       // mutex.unlock();
    }
}
