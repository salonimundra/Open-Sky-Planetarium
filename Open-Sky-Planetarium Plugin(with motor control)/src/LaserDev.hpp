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
#ifndef LASERDEV_HPP
#define LASERDEV_HPP

#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QSerialPort>
#include <QTextStream>
#include <QCoreApplication>
#include <QString>
#include <QObject>
#include <QThread>
#include <QTime>
#include "SerialCom.hpp"

//! This class is used for funtions related to motion and turning the laser on and off.
class LaserDev : public QObject
{
    Q_OBJECT
public:
	/**
	 *	Class constructor.
	 */
    LaserDev(QObject *parent=0);

	/**
	 *	Class destructor.
	 */
    ~LaserDev();

	/**
	*	function for setting the portName
	*	\param s port name
	*/
    void setPortName(const QString &s);
signals:

	/**
	*	Sending the debug signal
	*/
    void debug_send(QString s);

	/**
	*	Recieving the position from arduino
	*/
    void pos_received(QString,QString);
private:
	
	/**
	*	Constant for counting the motion in stpper motor.
	*/
    int move_count;

	/**
	*	Constant string for azimuth recieved from servo.
	*/
    QString ac;

	/**
	*	Constant string for altitude recieved from servo.
	*/
    QString alt;

	/**
	*	Constant for sending string.
	*/

    QString intense;

      /**
      *    Constant string for varying the intensity of LASER.
      */
	QString comm;

	/**
	*	Constant double for azimuth recieved from servo.
	*/
    double dac;

	/**
	*	Constant double for altitude recieved from servo.
	*/
	double dalt;

	/**
	*	Object for using serial class.
	*/
    SerialCom thread;

	/**
	*	Constant string for serial port name.
	*/
    QString osp_serialPort;

    QByteArray osp_ba;

public slots:

	/**
	*	This function is called to get the current position of the telescope in radians
	*/
    void getPos();

	/**
	*	slot for the error, sends the signal to OSPMainDialog
	*/
    void processError(const QString &s);

	/**
	*	slot for the timeout , sends the signal to OSPMainDialog
	*/
    void processTimeout(const QString &s);

	/**
	*	This function is called after writing to the serial port. This function performs various steps like echoData, getSteps, getHorizontalCoords, getVerticalCoords
	*/
	void sread(const QString &s);

    /**
	*	sends the "init" command to the device and after "done_init" is received from the device, emits "init_received" signal
	*/
	void init();

	/**
	*	Sends the telescope coordinates to the device
	* \param x Azimuth fed to arduino.
	* \param y Altitude fed to arduino.
	*/
    void move(double x,double y);

	/**
	*	To move the laser in x direction depending on signDir
	*/
    void movx(int signDir);

	/**
	*	To move the laser in y direction depending on signDir
	*	/param signDir 0 to move up 1 to move down
	*/
    void movy(int signDir);

	/**
	*	to stop the laser movements in either of the direction x or y
	*	/param signDir 0 to move up 1 to move down
	*/
    void stop();

	/**
	*	to turn the laser on
	*/
    void laserOn();

	/**
	*	To turn the laser off
	*/
    void laserOff();

       /**    To set the intensity of the laser
        */
     void setIntensity(int x);

    /**
    *	To hard reset the arduino
    */
    void resetAll();

    /**
        *	to turn the motor's high speed on
        */
        void CoarseAdj();

        /**
        *	To turn the motor's high speed off
        */
        void FineAdj();
};



#endif // LASERDEV_HPP
