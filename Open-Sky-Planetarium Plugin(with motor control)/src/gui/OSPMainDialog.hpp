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

#ifndef OSPMAINDIALOG_H
#define OSPMAINDIALOG_H

#include "Calibrate.hpp"
#include "StelDialog.hpp"
#include "LaserDev.hpp"
#include "StarMgr.hpp"
#include<QMediaPlayer>
#include <QWidget>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include<QList>
#include<QHash>
#include <QMediaPlaylist>
#include <QAbstractSlider>


class Ui_OSPMainDialog;

//! This is the main class used in connecting all the signals to gui.
class OSPMainDialog : public StelDialog
{
    	Q_OBJECT

public:
        OSPMainDialog();

    	~OSPMainDialog();


	/**
	*	This function connects the various gui signals to its corresponding slots.
	*   This function is called in the createDialogContent() function of this class.
	*/
	void setSignals();

	/**
	*	This function is called to display error/information messages
	*/
	void showMessage(QString m);
	
	
public slots:

	/**
	*	This function retranslate the language of plugin.
	*/
	void retranslate();
	/**
	*	This funtion is connected to many signals for debugging purpose.
	*	\param s Debug string
	*/
    void debug_received(QString s);
	/**
	*	This slot is called when the laser device sends us the coordinates
	*	The coordinates are then used for setting the references in transformation matrix
	* 	\param x Azimuth in string.
	*	\param y Altitude in string.
	*/	
    void pos_received(QString x,QString y);
	/**
	*	This slot is connected to the selectDev button of the gui.
	*	This slot shows a list of connected device to select from after selection enables many buttons.
	*/
    void selectDevice();
	/**
	*	This function initiates the arduino device i-e: Counts the no. of steps and sets device's postion.
	*	This function is connected to "Start Calibration" (startCal) button of the gui
	*/
	void initDevice();
	/**
	*	This function is called when the Up(mvUp), Down(mvDown), Right(mvRight) and Left(mvLeft) button is released
	*	This function sends the stop command to the arduino device to stop its movement along any of the four directions
	*/    
	void arrow_released();
	/**
	*	This functions is called when the buttons Up(mvUp) is pressed
	*/
    void upPressed();    
	/**
	*	This functions is called when the buttons Down(mvDown) is pressed
	*/
	void downPressed();
	/**
	*	This functions is called when the buttons Right(mvRight) is pressed
	*/
    void rightPressed();
	/**
	*	This functions is called when the buttons Left(mvLeft) is pressed
	*/
    void leftPressed();
	/**
	*	This function is connected to the laser turnOn/turnOff radioButtons of the gui
	*/
	void laserToggled();

	/**
	*	This function sets three references for the matrix transformation basically it sends three references for matrix transformation to the device for its calculations  
        */

        void setIntensity(int x);
          /**
          *    This function is connected to the laser intensity control slider
          */

        void adjToggled();

	void setReference();

	/**
	*	This function sends the coordinates from stellarium to device so that the laser could point the star. This function is enabled only after calibration is performed
	*/	
	void goTo();

	/**
	*	This function opens an existing file if present in the script directory of our module.
	*/		
	void openScript();

	/**
	*	This function is used to save the script
	*/	
	void saveScript();

	/**
	*	This function is used to execute script. This function calls compile function before executing
	*/	
	void execScript();

	/**
	*	This function is used to compile script. This function maps the user script commands to the C++ functions
	*/	
	void compileScript();

	/**
	*	This is a slot for our script engine emit signal comTURN. This is used when playing the script
	*/
	void laser(bool stat);
	
	/**
	*		This function is used to play audio files. This is used to give play Audio functionality in our script
	*/
	void playAudio(QString fname);

	/**
	*	This is used when playing the script. This is used to give wait functionality in the script
	*	\param min time in minute
	*	\param sec time in second
	*/
	void waitforsec(int min,int sec);

	/**
	*	This is slot connected to goto command from our script engine. It takes ra/dec of star as its parameters and converts them to move
	*	\param sra Right Ascension (equatorial coordinates).
 	*	\param dec Declination (equatorial coordinates).
	*/
	void move(QString,QString);
	
	/**
	*	This slot is connected to Goto Button of the Script Engine. Adds the goto command to your script
	*/
	void gt();

	/**
	*	This slot is connected to Play Button of the Script Engine. Adds the play audio command to your script
	*/
	void pl();

	/**
	*	This slot is connected to laser on/off button of the Script Engine. Adds the laser on/off command to your script
	*/
	void lo();

	/**
	*	This slot is connected to wait button of the Script Engine. Adds the wait command to your script
	*/
	void wt();
    /**
    *   This slot is for hard reset of the arduino.
    */
    void reset();

signals:

	/**
	*	This signal is connected to move of OSPMainDialog class 
	*	\param sra Right Ascension (equatorial coordinates).
 	*	\param dec Declination (equatorial coordinates).
	*/
	void comGOTO(QString sra,QString sdec);

	/**
	*	This signal is connected to laser of OSPMainDialog class 
	*	\param stat status of laser
	*/
	void comTURN(bool stat);

	/**
	*	This signal is connected to waitforsec of OSPMainDialog class 
	*	\param min time in minute
	*	\param sec time in second
	*/
	void comWAIT(int min,int sec);


	/**
	*	This signal is connected to playAudio of OSPMainDialog class 
	*	\param fname file name
	*/
	void comPLAY(QString fname);
        
protected:

	/**
	*	This function is used to create a dialog box and set the current index of the box
	*/
    void createDialogContent();

private:
	OpenSkyPlanetarium *osp;
	Ui_OSPMainDialog *ui;
	LaserDev device;
	Calibrate calib;
        QString acTemp;
        QString altTemp;
	double osp_time;
	double osp_ra;
	double osp_dec;
	bool buildStatus;
	QString portName;
	QHash<QString,QString> i18n_to_coords;
	QString moduleDirectoryPath;
	QString scriptDirectoryPath;
	QString audioDirectoryPath;
	QStringList commandsList;
    bool calMode;
    int nRef;

	// Audio functions

signals:

	/**
	*	This signal is connected to play of QMediaPlayer class 
	*/
    void play();


	/**
	*	This signal is connected to pause of QMediaPlayer class 
	*/
    void pause();

	/**
	*	This signal is connected to stop of QMediaPlayer class 
	*/
    void stop();

public slots:

	/**
	*	This slot is connected to volume slider.
	*	\param volume by slider
	*/
    void setVolume(int volume);
    
	/**
	*	This slot is connected to play and pause button.
	*/
	void playClicked();

	/**
	*	This slot is connected to stop button.
	*/
    void stopClick();

private:
    QMediaPlayer* player;
    QMediaPlaylist* playlist;
    QMediaPlayer::State playerState;
    QAbstractSlider *volumeSlider;
	QTime dieTime;
	QTime pauseWait;
	qint32 remtim;
};

#endif // OSPMAINDIALOG_H
