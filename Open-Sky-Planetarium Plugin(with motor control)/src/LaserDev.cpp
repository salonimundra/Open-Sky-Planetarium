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

#include "LaserDev.hpp"
#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QSerialPort>
#include <QCoreApplication>
#include <QTextStream>
#include <QObject>
#include <QDebug>
#include <QString>
#include <QTime>
#include <QDateTime>
#include <QMessageBox>
#include "SerialCom.hpp"

/*
Constructor:
*/
LaserDev::LaserDev(QObject *parent)
            :QObject(parent)
{
    move_count=0;
    connect(&thread, &SerialCom::response, this, &LaserDev::sread);
    connect(&thread, &SerialCom::error, this, &LaserDev::processError);
    connect(&thread, &SerialCom::timeout, this, &LaserDev::processTimeout);
}


/*
Destructor:
*/
LaserDev::~LaserDev(){

}

/*
processError(const QString):
	slot for the error, sends the signal to OSPMainDialog
*/
void LaserDev :: processError(const QString &s){
}

/*
processTimeout(const QString):
	slot for the timeout , sends the signal to OSPMainDialog
*/
void LaserDev :: processTimeout(const QString &s){
}


/*
setPortName(const QString):
	function for setting the portName
*/
void LaserDev :: setPortName(const QString &s){
	osp_serialPort=s;
	thread.sendRequest(osp_serialPort,5000,QString(""));
}

/*
sread(const QString):
	this function is called after writing to the serial port
	this function performs various steps like echoData,getSteps,getHorizontalCoords,getVerticalCoords
*/
void LaserDev::sread(const QString &s){
	QString recvd = s.trimmed();
	QRegExp exp("t_([0-9\\.\\-]{4,9})_([0-9\\.\\-]{4,9})");
	if(recvd.compare("done_init")==0){
		emit debug_send(recvd);
            getPos();
	}
	else if(recvd.compare("done_movu")==0){
		emit debug_send(recvd);
            getPos();
	}
	else if(recvd.compare("done_movd")==0){
		emit debug_send(recvd);
            getPos();
	}
	else if(recvd.compare("done_movr")==0){
		emit debug_send(recvd);
            getPos();
	}
	else if(recvd.compare("done_movl")==0){
		emit debug_send(recvd);
            getPos();
	}
	else if(recvd.compare("done_move")==0){
		emit debug_send(recvd);
	}
	else if(recvd.compare("done_laon")==0){
		emit debug_send(recvd);
	}
	else if(recvd.compare("done_loff")==0){
		emit debug_send(recvd);
	}
        else if(recvd.compare("done_high_speed")==0){
                emit debug_send(recvd);
        }
        else if(recvd.compare("done_low_speed")==0){
                emit debug_send(recvd);
        }
        else if(recvd.compare("done_reset")==0){
               emit debug_send(recvd);
            getPos();
           }
        else if(recvd.compare("done_lase")==0){
               emit debug_send("intensity");
               comm=intense;
               thread.sendRequest(osp_serialPort,1000,QString(comm));
               emit debug_send(comm);
           }
        else if(recvd.compare("float")==0){
                emit debug_send("float");
                bool ac_neg=false,alt_neg=false;
                if(dac<0) ac_neg=true;
                if(dalt<0) alt_neg=true;
                ac=QString::number(dac,'f',4);
                alt=QString::number(dalt,'f',4);
                if(!ac_neg){
                        ac = QString("+"+ac);
                }
                if(!alt_neg){
                        alt = QString("+"+alt);
                }
                comm=QString("m_%1_%2").arg(ac).arg(alt);
                thread.sendRequest(osp_serialPort,1000,QString(comm));
                emit debug_send(comm);
                }
	else if(exp.exactMatch(recvd)){
		QStringList items = exp.capturedTexts();
		emit pos_received(items[1],items[2]);
	}
	else {
		//emit debug_send(QString("Unexpected Byte Received.Please Restart the device: %1 if problems persist").arg(recvd));
		//thread.sendRequest(osp_serialPort,1000,QString("clear"));
	} 
}

/*
init():
	sends the "init" command to the device and after "done_init" is received from the device,
	emits "init_received" signal
	
*/
void LaserDev :: init(){
	comm=QString("init");
	thread.sendRequest(osp_serialPort,5000,QString(comm));
}


/*
getPos():
	This function is called to get the current position of the telescope in radians
*/
void LaserDev :: getPos(){
	comm=QString("post");
        thread.sendRequest(osp_serialPort,100,QString(comm));
}



/*
move(double,double):
	sends the telescope coordinates to the device
*/
void LaserDev :: move(double x,double y){
        //move_count=1;
        //ac.setNum(x);
        //alt.setNum(y);
        dac=x;
        dalt=y;

        comm=QString("move");
        thread.sendRequest(osp_serialPort,1000,QString(comm));

}

	/*
movy(int):
	to move the laser in y direction depending on signDir
*/
void LaserDev :: movy(int signDir){
	if(signDir)
		comm=QString("movu");
	else
		comm=QString("movd");
        thread.sendRequest(osp_serialPort,100,QString(comm));
			
}

/*
	movx(int):
	to move the laser in x direction depending on signDir
*/
void LaserDev :: movx(int signDir){
	if(signDir)
		comm=QString("movr");
	else
		comm=QString("movl");
        thread.sendRequest(osp_serialPort,100,QString(comm));
}

/*
stop():
	to stop the laser movements in either of the direction x or y
*/
void LaserDev :: stop(){
	comm=QString("stop");
        thread.sendRequest(osp_serialPort,100,QString(comm));
}

/*
laserOn():
	to turn the laser on
*/
void LaserDev :: laserOn(){
	comm=QString("laon");
	thread.sendRequest(osp_serialPort,1000,QString(comm));
}

void LaserDev :: resetAll(){
    /*comm=QString("rest");
    thread.sendRequest(osp_serialPort,100,QString(comm));
    */
    move(0,0);
}


/*
laserOff():
	to turn the laser off
*/
void LaserDev :: laserOff(){
	comm=QString("loff");
	thread.sendRequest(osp_serialPort,1000,QString(comm));
}


/*
 setIntensity():
     to set the intensity of the laser
*/
void LaserDev ::setIntensity(int x){
    QString s=QString::number(x);
    if(s.length()==2)
        s="00"+s;
    else if(s.length()==3)
        s="0"+s;
    intense=s;
    comm=QString("lase");
    emit debug_send(comm);
    thread.sendRequest(osp_serialPort,1000,QString(comm));
}

/*
CoarseAdj():
    to let the motors go on high speed
*/
void LaserDev :: CoarseAdj(){
    comm=QString("coad");
    thread.sendRequest(osp_serialPort,1000,QString(comm));
}
/*
FineAdj():
    to let the motors go on a low speed
*/
void LaserDev :: FineAdj(){
    comm=QString("fiad");
    thread.sendRequest(osp_serialPort,1000,QString(comm));
}
