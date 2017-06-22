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
#include<QDateTime>
#include <QMessageBox>
#include <Coords.hpp>

/*
COnstructor:
*/
LaserDev::LaserDev(QObject *parent)
            :QObject(parent)
{
    osp_ba = QByteArray("");
    //connect(&osp_serialPort, SIGNAL(readyRead()), this, SLOT(sread()));
}


/*
Destructor:
*/
LaserDev::~LaserDev(){
    //TODO: add destrtuctor functions
    closeConnection();
}


/*
closeConnection():
	this function closes the device connections
*/
void LaserDev :: closeConnection(){
	osp_serialPort.close();
}


/*
isNull():
	this function returns true/false if device is open/close respectively
*/
bool LaserDev :: isNull(){
	return !osp_serialPort.isOpen();
}


/*
configure(QSerialPortInfo):
	this function configures and opens the port, returns the status of the port
	if the port is successfully opened return true else returns false
*/
bool LaserDev :: configure(const QSerialPortInfo serialPortInfo){
    osp_serialPort.setReadBufferSize(20);
    if(!serialPortInfo.isNull()){
    	osp_serialPort.setPort(serialPortInfo);
    }
  return osp_serialPort.open(QIODevice::ReadWrite);
} 


/*
sread(QString,int):
	this function is called after writing to the serial port
	this function performs various steps like echoData,getSteps,getHorizontalCoords,getVerticalCoords
*/
/*QString LaserDev::sread(QString expect,int wait){
    QStringList d;
    QRegExp exp(expect);
    QString line;
    QRegExp tag_steps("^p_.*$");
    QRegExp tag_horizontal("^h_.*$");
    QRegExp tag_equatorial("^e_.*$");
    int count = 0;
    if(osp_serialPort.canReadLine()){
        line = QString::fromUtf8(osp_serialPort.readLine());
    }
    while(!exp.exactMatch(line) && count <= wait){
        if (tag_steps.exactMatch(line)){
            QString resp = line.replace(QString("p_"),QString(""));
            d = resp.split(QString(" "));
            qDebug() << "[OpenSkyPlanetarium] Steps: ("<<d.at(0)<<","<<d.at(1)<<")"<<endl;
        }
        else if (tag_horizontal.exactMatch(line)){
            QString resp = line.replace(QString("h_"),QString(""));
            d = resp.split(QString(" "));
            emit pos_received(d.at(0),d.at(1));
            qDebug() << "[OpenSkyPlanetarium] Position Horizontal: ("<<coords.deg_2_degStr(360.0 - coords.radStr_2_deg(d.at(0)))<<","<<coords.deg_2_degStr(coords.radStr_2_deg(d.at(1)))<<")"<<endl;
        }
        else if (tag_equatorial.exactMatch(line)){
            QString resp = line.replace(QString("e_"),QString(""));
            d = resp.split(QString(" "));
            emit pos_e_received(d.at(0),d.at(1));
            qDebug() << "[OpenSkyPlanetarium] Position Equatorial: ("<<coords.hour_2_hourStr(coords.rad_2_hour(coords.degStr_2_rad(coords.radStr_2_degStr(d.at(0)))))<<","<<coords.deg_2_degStr(coords.radStr_2_deg(d.at(1)));
        }
        if (line.compare(QString(""))==0){
            count++;
        }
        else {
            qDebug()<<QString("[OpenSkyPlanetarium] _debug_ :")<< QString(line) << endl;
        }
	if(osp_serialPort.canReadLine()){
	        line = QString::fromUtf8(osp_serialPort.readLine());
	}
    }
    return line;
}*/
void LaserDev :: sread(){
    QRegExp exp(expect);
    QRegExp tag_steps("^p_.*$");
    QRegExp tag_horizontal("^h_.*$");
    QRegExp tag_equatorial("^e_.*$");
    QStringList d;
    line = QString::fromUtf8(osp_serialPort.readAll());
    if(!exp.exactMatch(line)){
        if (tag_steps.exactMatch(line)){
            QString resp = line.replace(QString("p_"),QString(""));
            d = resp.split(QString(" "));
            qDebug() << "[OpenSkyPlanetarium] Steps: ("<<d.at(0)<<","<<d.at(1)<<")"<<endl;
        }
        else if (tag_horizontal.exactMatch(line)){
            QString resp = line.replace(QString("h_"),QString(""));
            d = resp.split(QString(" "));
            emit pos_received(d.at(0),d.at(1));
            qDebug() << "[OpenSkyPlanetarium] Position Horizontal: ("<<coords.deg_2_degStr(360.0 - coords.radStr_2_deg(d.at(0)))<<","<<coords.deg_2_degStr(coords.radStr_2_deg(d.at(1)))<<")"<<endl;
        }
        else if (tag_equatorial.exactMatch(line)){
            QString resp = line.replace(QString("e_"),QString(""));
            d = resp.split(QString(" "));
            emit pos_e_received(d.at(0),d.at(1));
            qDebug() << "[OpenSkyPlanetarium] Position Equatorial: ("<<coords.hour_2_hourStr(coords.rad_2_hour(coords.degStr_2_rad(coords.radStr_2_degStr(d.at(0)))))<<","<<coords.deg_2_degStr(coords.radStr_2_deg(d.at(1)));
        }
        else if(line.compare(QString("float"))==0 && cmd.compare(QString("time"))==0){
            osp_serialPort.write(QString(coords.rad_2_radStr(coords.hourStr_2_rad(set_time))).toLocal8Bit());     //ToDo
            osp_serialPort.waitForBytesWritten(5000);
            osp_serialPort.flush();
        }
	else if(line.compare(QString("float"))==0 && cmd.compare(QString("setRef"))==0){
		osp_serialPort.write(sra.toLocal8Bit());       
	        osp_serialPort.flush();
        	osp_serialPort.write(sdec.toLocal8Bit());         
        	osp_serialPort.flush();
        	osp_serialPort.write(stime.toLocal8Bit());       
        	osp_serialPort.flush();
	}
   }
   else {
        if(expect.compare(QString("^done_init$"))==0){
		emit init_received();
	}
	qDebug()<<QString("[OpenSkyPlanetarium] _debug_ :")<< QString(line) << endl;
   }
   expect=QString("^cmd$");
}


/*
setTime(QTime):
	this function is used to send time to device for the matrix transformation
*/
void LaserDev :: setTime(){
    QDateTime dt = QDateTime::currentDateTime();
    cmd=QString("time");
    set_time=QString("%1h%2m%3s").arg(dt.time().hour()).arg(dt.time().minute()).arg(dt.time().second());
    osp_serialPort.write(cmd.toLocal8Bit());
    osp_serialPort.flush();
    /*if(QString(osp_serialPort.readLine()).compare(QString("float"))==0){
        osp_serialPort.write(QString(coords.rad_2_radStr(coords.hourStr_2_rad(time))).toLocal8Bit());     //ToDo
        osp_serialPort.waitForBytesWritten(5000);
        osp_serialPort.flush();
    }*/
}


/*
init():
	sends the "init" command to the device and after "done_init" is received from the device,
	emits "init_received" signal
	
*/
void LaserDev :: init(){
    /*if(osp_serialPort.canReadLine()){
        osp_ba = osp_serialPort.readLine();
    }
    qDebug()<<"[OpenSkyPlanetarium] "<<QString(osp_ba)<<endl;
    osp_ba = QByteArray("");*/
    expect=QString("^done_init$");
    cmd=QString("init");
    osp_serialPort.write(cmd.toLocal8Bit());
    osp_serialPort.flush();
    /*sread(QString("^done_init$"),20);
    emit init_received();*/
}


/*
setRef(int,QString,QString,time):
	sends the references to the device for the matrix transformation
*/
void LaserDev :: setRef(int id_ref,QString ra,QString dec,QString time){
     QHash<int, QString> setf;
     cmd = QString("setref");
     setf.insert(1,QString("set1"));
     setf.insert(2,QString("set2"));
     setf.insert(3,QString("set3"));
     qDebug()<<"[OpenSkyPlanetarium] "<<setf[id_ref]<<"("<<ra<<","<<dec<<","<<time<<")"<<endl;
     sra = ra;
     sdec = dec;
     stime = time;
     /*if(QString(osp_serialPort.readLine()).compare(QString("float"))==0){
        osp_serialPort.write(QString(coords.rad_2_radStr(coords.hourStr_2_rad(ra))).toLocal8Bit());       
        osp_serialPort.flush();
        osp_serialPort.write(QString(coords.rad_2_radStr(coords.degStr_2_rad(dec))).toLocal8Bit());         
        osp_serialPort.flush();
        osp_serialPort.write(QString(coords.rad_2_radStr(coords.hourStr_2_rad(time))).toLocal8Bit());       
        osp_serialPort.flush();
     }*/
     //sread(QString("^cmd$"),5);
}


/*
goTo(QString,QString,QString):
	sends the coordinates received from stellarium to the device
*/
void LaserDev :: goTo(QString ra,QString dec,QString time){
    qDebug() << "[OpenSkyPlanetarium] ("<<ra<<","<<dec<<","<<time<<")"<<endl;
    osp_serialPort.write(QString("goto").toLocal8Bit()); 
    if(QString(osp_serialPort.readLine()).compare("float")==0){
        osp_serialPort.write(QString(coords.rad_2_radStr(coords.hourStr_2_rad(ra))).toLocal8Bit());        
        osp_serialPort.flush();
        osp_serialPort.write(QString(coords.rad_2_radStr(coords.degStr_2_rad(dec))).toLocal8Bit());        
        osp_serialPort.flush();
        osp_serialPort.write(QString(coords.rad_2_radStr(coords.hourStr_2_rad(time))).toLocal8Bit());        
        osp_serialPort.flush();
    }
    //sread(QString("^cmd$"),10);
}


/*
move(QString,QString):
	sends the telescope coordinates to the device
*/
void LaserDev :: move(QString ac,QString alt){
    qDebug() << "[OpenSkyPlanetarium] ("<<ac<<","<<alt<<")"<<endl;
    QDateTime dt = QDateTime::currentDateTime();
    QString time=QString("%1h%2m%3s").arg(dt.time().hour()).arg(dt.time().minute()).arg(dt.time().second());
    osp_serialPort.write("move");
    if(QString(osp_serialPort.readLine()).compare("float")==0){
        osp_serialPort.write(QString(coords.rad_2_radStr(6.283185 - coords.degStr_2_rad(ac))).toLocal8Bit());        
        osp_serialPort.waitForBytesWritten(2000);
        osp_serialPort.flush();
        osp_serialPort.write(QString(coords.rad_2_radStr(coords.degStr_2_rad(alt))).toLocal8Bit());        
        osp_serialPort.waitForBytesWritten(2000);
        osp_serialPort.flush();
        osp_serialPort.write(QString(coords.rad_2_radStr(coords.hourStr_2_rad(time))).toLocal8Bit());        
        osp_serialPort.waitForBytesWritten(2000);
        osp_serialPort.flush();
    }
    //sread(QString("^cmd$"),10);
}


/*
movx(QString):
	to move the laser in x direction depending on signDir
*/
void LaserDev :: movx(QString signDir){
    osp_serialPort.write(QString("movx").toLocal8Bit());
    osp_serialPort.waitForBytesWritten(2000);
    osp_serialPort.flush();
    osp_serialPort.write(signDir.toLocal8Bit());
    osp_serialPort.waitForBytesWritten(2000);
    osp_serialPort.flush();
}


/*
movy(QString):
	to move the laser in y direction depending on signDir
*/
void LaserDev :: movy(QString signDir){
    osp_serialPort.write(QString("movy").toLocal8Bit());
    osp_serialPort.waitForBytesWritten(2000);
    osp_serialPort.flush();
    osp_serialPort.write(signDir.toLocal8Bit());
    osp_serialPort.waitForBytesWritten(2000);
    osp_serialPort.flush();
}


/*
stop():
	to stop the laser movements in either of the direction x or y
*/
void LaserDev :: stop(){
    osp_serialPort.write(QString("stop").toLocal8Bit());
    osp_serialPort.waitForBytesWritten(2000);
    osp_serialPort.flush();
    /*QString resp = sread(QString("^done$"));
    if (resp.compare(QString("done_end"))==0){
        sread();
        sread();
    }
    else{
        sread();
    }*/

}


/*
laserOn():
	to turn the laser on
*/
void LaserDev :: laserOn(){
    osp_serialPort.write(QString("laon").toLocal8Bit());
    osp_serialPort.waitForBytesWritten(2000);
    osp_serialPort.flush();
    //sread(QString("^cmd$"),3);
}


/*
laserOff():
	to turn the laser off
*/
void LaserDev :: laserOff(){
    osp_serialPort.write(QString("loff").toLocal8Bit());
    osp_serialPort.waitForBytesWritten(2000);
    osp_serialPort.flush();
    //sread(QString("^cmd$"),3);
}


/*
getAvailablePorts():
	to get the available serial ports that are connected
	returns a list of available serialports
*/
QList<QSerialPortInfo> LaserDev :: getAvailablePorts(){
    QList<QSerialPortInfo> available;
    const auto serialPortInfos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &serialPortInfo : serialPortInfos){
        available.append(serialPortInfo);
    }
    return available;
}

