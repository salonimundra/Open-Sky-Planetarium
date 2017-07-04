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
#ifndef SERIALCOM_H
#define SERIALCOM_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QtSerialPort/QSerialPort>

//! This class is used for funtions related to serial communication with the arduino
class SerialCom : public QThread
{
    Q_OBJECT

private:
    QString port;
    QString request;
    int waitTime;
    QMutex mutex;
    QWaitCondition cond;
    bool quit;

public:
	QSerialPort serial;
	/**
	*	Class constructor
	*/
    SerialCom(QObject *parent = 0);

	/**
	*	Class destructor
	*/
    ~SerialCom();

	/**
	*	To set the parameters that needed to sent to arduino
	*	\param port name of the port on which request need to be sent
	*	\param waitTime wait time for the response from arduino
	*	\param request a string to be sent to arduino
	*/
    void sendRequest(const QString &port, int waitTime, const QString &request);

	/**
	*	To send a request to arduino and wait for response and to save it
	*/    
	void run();

signals:

	/**
	*	Response from the arduino
	*/
    void response(const QString &s);

	/**
	*	Error from arduino
	*/
    void error(const QString &s);

	/**
	*	Timeout error from arduio
	*/
    void timeout(const QString &s);

};


#endif // SERIALCOM_H
