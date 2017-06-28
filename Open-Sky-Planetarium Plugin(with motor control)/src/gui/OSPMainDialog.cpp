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

#include "OpenSkyPlanetarium.hpp"
#include "OSPMainDialog.hpp"
#include "ui_OSPMainDialog.h"
#include "Calibrate.hpp"

#include "StelApp.hpp"
#include "StelLocaleMgr.hpp"
#include "StelModule.hpp"
#include "StelModuleMgr.hpp"
#include "StelObjectMgr.hpp"
#include "StelUtils.hpp"
#include "StelFileMgr.hpp"
#include "StarMgr.hpp"
#include "StelAudioMgr.hpp"
#include "StelObjectMgr.hpp"

#include <QMediaPlayer>
#include <QCompleter>
#include <QFileDialog>
#include <QFile>
#include <QInputDialog>
#include <QException>
#include <QRegExp>
#include <QRegExpValidator>
#include <QList>
#include <QMessageBox>
#include <QWidget>
#include <QByteArray>
#include <QDateTime>
#include <QCoreApplication>

OSPMainDialog::OSPMainDialog()
{
	ui = new Ui_OSPMainDialog();
	calMode = false;
	nRef = 0;
	moduleDirectoryPath = StelFileMgr::getUserDir() + "/modules/OpenSkyPlanetarium";
	if(!StelFileMgr::exists(moduleDirectoryPath)){
		StelFileMgr::mkDir(moduleDirectoryPath);
	}
	scriptDirectoryPath = StelFileMgr::getUserDir() + "/modules/OpenSkyPlanetarium/script";
	if(!StelFileMgr::exists(scriptDirectoryPath)){
		StelFileMgr::mkDir(scriptDirectoryPath);
	}
	audioDirectoryPath = StelFileMgr::getUserDir() + "/modules/OpenSkyPlanetarium/audio";
	if(!StelFileMgr::exists(audioDirectoryPath)){
		StelFileMgr::mkDir(audioDirectoryPath);
	}

	// Objects Initialization
    player = new QMediaPlayer();
    playlist = new QMediaPlaylist();
    volumeSlider = new QAbstractSlider();
    player->setPlaylist(playlist);
    player->setVolume(50);
    playerState = QMediaPlayer::StoppedState;
	remtim = 0;
}

OSPMainDialog::~OSPMainDialog()
{
	delete ui;

}

void OSPMainDialog::retranslate()
{
	if (dialog)
	{
		ui->retranslateUi(dialog);
	}
}


void OSPMainDialog::createDialogContent()
{
	ui->setupUi(dialog);
	ui->tabWidg->setCurrentIndex(2);
	setSignals();
	connect(&StelApp::getInstance(), SIGNAL(languageChanged()), this, SLOT(retranslate()));
	connect(ui->closeStelWindow, SIGNAL(clicked()), this, SLOT(close()));
}

/*
setSignals():
	THis function connects the various gui signals to its corresponding slots
	this function is called in the createDialogContent() function of this classs
*/
void OSPMainDialog :: setSignals(){

	//Setting signals for the laser movements
	connect(ui->mvUp,SIGNAL(pressed()),this,SLOT(upPressed()));
	connect(ui->mvDown,SIGNAL(pressed()),this,SLOT(downPressed()));
	connect(ui->mvLeft,SIGNAL(pressed()),this,SLOT(leftPressed()));
	connect(ui->mvRight,SIGNAL(pressed()),this,SLOT(rightPressed()));
	connect(ui->mvUp,SIGNAL(released()),this,SLOT(arrow_released()));
	connect(ui->mvDown,SIGNAL(released()),this,SLOT(arrow_released()));
	connect(ui->mvRight,SIGNAL(released()),this,SLOT(arrow_released()));
	connect(ui->mvLeft,SIGNAL(released()),this,SLOT(arrow_released()));
        connect(ui->reset,SIGNAL(clicked()),this,SLOT(reset()));

	//Connecting LaserDev signals to their respective slots
	connect(&device,SIGNAL(debug_send(QString)),this,SLOT(debug_received(QString)));
	connect(&device,SIGNAL(pos_received(QString,QString)),this,SLOT(pos_received(QString,QString)));

	//Device connection and Calibration buttons
	connect(ui->selectDev,SIGNAL(clicked()),this,SLOT(selectDevice()));
	connect(ui->startCal,SIGNAL(clicked()),this,SLOT(initDevice()));

        //LASER on/off
	connect(ui->laserOn,SIGNAL(clicked()),this,SLOT(laserToggled()));
	connect(ui->laserOff,SIGNAL(clicked()),this,SLOT(laserToggled()));
        connect(ui->intensity,SIGNAL(valueChanged(int)),this,SLOT(setIntensity(int)));

        // Motor speed control
        connect(ui->CoarseAdj,SIGNAL(clicked()),this,SLOT(adjToggled()));
        connect(ui->FineAdj,SIGNAL(clicked()),this,SLOT(adjToggled()));

	//setReference and goTo button
	connect(ui->setRef,SIGNAL(clicked()),this,SLOT(setReference()));
	connect(ui->goTo,SIGNAL(clicked()),this,SLOT(goTo()));
	
	//script engine buttons
	connect(ui->compScript,SIGNAL(clicked()),this,SLOT(compileScript()));
	connect(ui->openScript,SIGNAL(clicked()),this,SLOT(openScript()));
	connect(ui->saveScript,SIGNAL(clicked()),this,SLOT(saveScript()));
	connect(ui->execScript,SIGNAL(clicked()),this,SLOT(execScript()));

	//scriptEngine Command Buttons
	connect(ui->gt,SIGNAL(clicked()),this,SLOT(gt()));
	connect(ui->pl,SIGNAL(clicked()),this,SLOT(pl()));
	connect(ui->wt,SIGNAL(clicked()),this,SLOT(wt()));
	connect(ui->lo,SIGNAL(clicked()),this,SLOT(lo()));

	//all emit signals for our scriptEngine connected to their respective functions
	connect(this,SIGNAL(comGOTO(QString,QString)),this,SLOT(move(QString,QString)));
	connect(this,SIGNAL(comTURN(bool)),this,SLOT(laser(bool)));
	connect(this,SIGNAL(comPLAY(QString)),this,SLOT(playAudio(QString)));
	connect(this,SIGNAL(comWAIT(int,int)),this,SLOT(waitforsec(int,int)));
	
	//Signals for audio 
        connect(ui->playui,SIGNAL(clicked()),this,SLOT(playClicked()));
        connect(ui->stopui,SIGNAL(clicked()),this,SLOT(stopClick()));
        connect(ui->volumeChanged,SIGNAL(sliderMoved(int)),this,SLOT(setVolume(int)));
        connect(this,SIGNAL(play()),player,SLOT(play()));
        connect(this,SIGNAL(pause()),player,SLOT(pause()));
        connect(this,SIGNAL(stop()),player,SLOT(stop()));
}


/*
/////////////////////////////////////User Defined Functions and Slots//////////////////////////////////////
			All the required functions and slots for the gui written below
*/

///////////////////////////////////////////////Programmer helper slots////////////////////////////////////////////

/*
debug_received():
	Connected to many signals for debugging purpose
*/
void OSPMainDialog :: debug_received(QString s){
	qDebug() << "[OpenSkyPlanetarium] __debug__"<<s;
}

/*
pos_received():
	This slot is called when the laser device sends us the coordinates
	The coordinates are then used for setting the references in transformation matrix
*/
void OSPMainDialog :: pos_received(QString x,QString y){
	qDebug() << "Printing X and Y = ["<<x <<","<<y<<"]";
            acTemp = x;
            altTemp = y;
            double l=x.toDouble()*(180.0/3.14159);
            double m=y.toDouble()*(180.0/3.14159);
            QString s=QString::number(l);
            QString t=QString::number(m);
            ui->X->setText(s);
            ui->Y->setText(t);

}

/*
showMessage(QString):
	this function is called to display error/information messages
*/
void OSPMainDialog :: showMessage(QString m){
	QMessageBox msgBox;
    msgBox.setWindowTitle("OpenSkyPlanetarium");
	msgBox.setText(m);
	msgBox.exec();
}

//////////////////////////////////////////DEvice RElated slots////////////////////////////////////////////////////////////////////////////

/*
initDevice():
	This function initiates the arduino device i-e:Counts the no. of steps and sets device's postion .
	This function is connected to "Start Calibration" (startCal) button of the gui
*/
void OSPMainDialog :: initDevice(){
		nRef=0;
		QDateTime dt = QDateTime::currentDateTime();
		double time = StelUtils::hmsToRad (dt.time().hour(), dt.time().minute(), dt.time().second());
		calib.setTime(time);
		qDebug() << "t0 =["<<time<<"] //Initial time";
		device.init();
		ui->setRef->setEnabled(true);
		ui->goTo->setEnabled(false);
		ui->execScript->setEnabled(true); //change after testing to false
                ui->mvUp->setEnabled(true);
                ui->mvLeft->setEnabled(true);
                ui->mvDown->setEnabled(true);
                ui->mvRight->setEnabled(true);
                ui->reset->setEnabled(true);
		ui->refStat->setText("0/3");
}

/*
selectDevice():
	this slot is connected to the selectDev button of the gui
	this slot shows a list of connected device to select from
	after selection enables many buttons
*/
void OSPMainDialog :: selectDevice(){
	nRef=0;
	QStringList itemsList;		
	bool ok;
	foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        itemsList.append(info.portName());
    	portName = QInputDialog::getItem(NULL, "Open Sky Planetarium","Select Device:",itemsList, 0, false, &ok);
	device.setPortName(portName);
    	if (ok && !portName.isEmpty()){
        ui->mvUp->setEnabled(false);
        ui->mvDown->setEnabled(false);
        ui->mvRight->setEnabled(false);
        ui->mvLeft->setEnabled(false);
		ui->selectDev->setEnabled(true);
		ui->startCal->setEnabled(true);
        ui->reset->setEnabled(false);
		ui->setRef->setEnabled(false);
		ui->goTo->setEnabled(false);
		ui->execScript->setEnabled(true);     //change after testing to false
		ui->laserOn->setEnabled(true);
		ui->laserOff->setEnabled(true);
        ui->CoarseAdj->setEnabled(true);
        ui->FineAdj->setEnabled(true);
		ui->refStat->setText("0/3");
	}
	else{
                showMessage("Please select the device");
	}
}

/*
arrow_released():
	this function is called when the Up(mvUp), Down(mvDown), Right(mvRight) and Left(mvLeft) button is released
	this function sends the stop command to the arduino device to stop its movement along any of the four directions
*/
void OSPMainDialog :: arrow_released(){
		device.stop();
}

/*
upPressed(), downPressed(), rightPressed(), leftPressed():
	these functions are called when the buttons Up(mvUp), Down(mvDown), Right(mvRight) and Left(mvLeft) is pressed
	these functions send appropriate move signals to the arduino device
*/
void OSPMainDialog :: upPressed(){
		device.movy(1);
}

void OSPMainDialog :: downPressed(){
		device.movy(0);
}

void OSPMainDialog :: rightPressed(){
		device.movx(1);
}

void OSPMainDialog :: leftPressed(){
		device.movx(0);
}

void OSPMainDialog ::reset(){
    //this->initDevice();
    device.resetAll();
    QString val="0.000000";
        ui->X->setText(val);
        ui->Y->setText(val);
}


/*
laserToggled():
	this slot is connected to the laser turnOn/turnOff radioButtons of the gui
*/
void OSPMainDialog :: laserToggled(){
		if (ui->laserOn->isChecked()){
			device.laserOn();
                        ui->intensity->setEnabled(true);
                        qDebug() << "[OpenSkyPlanetarium]:Turning LASER on" << endl;
		}
		else{
                    ui->intensity->setEnabled(false);
                    ui->intensity->setSliderPosition(50);
                    device.laserOff();
                        qDebug() << "[OpenSkyPlanetarium]:Turning LASER off" << endl;
		}	
}


///////////////////////////////////Calibration Related SLots/////////////////////////////////////////////////////////////////////////


void OSPMainDialog :: setIntensity(int x){
    int l=ui->intensity->value();
    device.setIntensity(l);
    qDebug() << "[OpenSkyPlanetarium]:Changing intensity" << endl;
}

/*
adjToggled():
    this slot is connected to the motor speed control radio buttons of the gui
*/
void OSPMainDialog :: adjToggled(){
        if (ui->CoarseAdj->isChecked()){
            device.CoarseAdj();
            qDebug() << "[OpenSkyPlanetarium]:High Speed ON" << endl;
        }
        else{
            device.FineAdj();
            qDebug() << "[OpenSkyPlanetarium]:Low Speed ON" << endl;
        }
}


/*
setReference():
	this function sets three references for the matrix transformation
	basically it sends three references for matrix transformation to the device for its calculations  	
*/

void OSPMainDialog :: setReference(){
        nRef++;
        QString sRef;
        double dec = 0,ra = 0;
        QDateTime dt = QDateTime::currentDateTime();
        double time = StelUtils::hmsToRad (dt.time().hour(), dt.time().minute(), dt.time().second());
        const QList<StelObjectP>& selected = GETSTELMODULE(StelObjectMgr)->getSelectedObject();
        if(nRef>3)
        {
            nRef=3;
        ui->setRef->setEnabled(false);
        }
        if (!selected.isEmpty()) {
            StelUtils::rectToSphe(&ra,&dec,selected[0]->getEquinoxEquatorialPos(StelApp::getInstance().getCore()));
            osp_ra=ra - 3.14159;
            osp_dec=dec;
            osp_time=time;
            qDebug() << "Star = ["<<osp_time <<"," <<osp_ra <<"," <<osp_dec<<"]";

            double ac,alt;
        switch(nRef){
            case 1:
             device.getPos();
             ac = acTemp.toDouble();
             alt = altTemp.toDouble();
                calib.setRef_1(osp_ra,osp_dec,osp_time,ac,alt);
                            showMessage(QString("First reference point has been set\n az = %1; alt = %2").arg(ac).arg(alt));
                break;
            case 2:
            device.getPos();
             ac = acTemp.toDouble();
             alt = altTemp.toDouble();
                calib.setRef_2(osp_ra,osp_dec,osp_time,ac,alt);
                ui->goTo->setEnabled(true);
                ui->execScript->setEnabled(true);
                            showMessage(QString("Second reference point has been set\n az = %1; alt = %2").arg(ac).arg(alt));
                    //showMessage("Second reference point has been set");
                break;
            case 3:
            device.getPos();
             ac = acTemp.toDouble();
             alt = altTemp.toDouble();
                calib.setRef_3(osp_ra,osp_dec,osp_time,ac,alt);
                ui->setRef->setEnabled(false);
                ui->goTo->setEnabled(true);
                ui->execScript->setEnabled(true);
                            ui->mvDown->setEnabled(false);
                            ui->mvUp->setEnabled(false);
                            ui->mvRight->setEnabled(false);
                            ui->mvLeft->setEnabled(false);
                            showMessage(QString("Third reference point has been set\n az = %1; alt = %2").arg(ac).arg(alt));
                        //showMessage("Third reference point has been set");
                break;


                    }
                    sRef.setNum(nRef);
            ui->refStat->setText(sRef+"/3");

        }
        else{
            showMessage("Please select a star to set as a Reference");
        }
}

/*
goTo():
	This function sends the coordinates from stellarium to device so that the laser could point the star
	this function is enabled only after calibration is performed
*/
void OSPMainDialog :: goTo(){
	QString sora,sodec,snra,sndec,sac,salt; //for testing purpose
	double dec=0,ra=0,ac=0,alt=0;
	QDateTime dt = QDateTime::currentDateTime();
	double time = StelUtils::hmsToRad (dt.time().hour(), dt.time().minute(), dt.time().second());
	const QList<StelObjectP>& selected = GETSTELMODULE(StelObjectMgr)->getSelectedObject();
	if (!selected.isEmpty()) {
		StelUtils::rectToSphe(&ra,&dec,selected[0]->getEquinoxEquatorialPos(StelApp::getInstance().getCore()));
	}
	qDebug() << "[goto_star_ra,dec,time]:"<<ra <<"," <<dec <<"," <<time;
        calib.getHCoords(ra-3.14159,dec,time,&ac,&alt);
	salt.setNum(alt);			//for testing purpose
	sac.setNum(ac);				//for testing purpose
        sora.setNum(3.14159+ra);		//for testing purpose
	sodec.setNum(dec);			//for testing purpose
	calib.getECoords(ac,alt,time,&ra,&dec); //for testing purpose
	snra.setNum(ra);			//for testing purpose
	sndec.setNum(dec);			//for testing purpose
        showMessage(QString("Old ra/dec = %1/%2 ; New ra/dec = %3/%4 ; LASER Coordinates = %5/%6").arg(sora).arg(sodec).arg(snra).arg(sndec).arg(sac).arg(salt));				//for testing purpose
	device.move(ac,alt);
    double xo=ac*(180.0/3.14159);
    double yo=alt*(180.0/3.14159);
    QString s=QString::number(xo);
    QString t=QString::number(yo);
        ui->X->setText(s);
        ui->Y->setText(t);
	qDebug() << "[goto_telescope_ac,alt]:"<<ac <<"," <<alt;
}

/*
openScript():
	This function opens an existing file if present in the script directory of our module
*/
void OSPMainDialog :: openScript(){
	QString fileName = QFileDialog::getOpenFileName(NULL,QString("Open Script"), scriptDirectoryPath,QString("Script Files (*.osp)"));
	if(!fileName.isNull()){
		QFile file(fileName);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
			showMessage("File Not Accessible");
          		return;
		}
		ui->scriptEdit->setText(file.readAll());
		file.close();
	}

}

/*
saveScript():
	This function is used to save the script
*/
void OSPMainDialog :: saveScript(){
	if(!ui->scriptEdit->toPlainText().isEmpty()){
		QString fileName = QFileDialog::getSaveFileName(NULL,QString("Save Script"), scriptDirectoryPath,QString("Script Files (*.osp)"));
		if(!fileName.isNull()){
			QFile file(fileName+".osp");
			if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
				showMessage("File Not Accessible");
        	  		return;
			}
			file.write(ui->scriptEdit->toPlainText().toLocal8Bit());
			file.close();
		}
	}
}


/*
execScript():
	This function is used to execute script
	This function calls compile function before executing
*/
void OSPMainDialog :: execScript(){
	compileScript();
	if(buildStatus){
		foreach(QString commands, commandsList){
			QStringList com = commands.split("_");
			if(com[0].compare("goto")==0){
				qDebug()<<com;
				emit comGOTO(com[1],com[2]);
			}
			else if(com[0].compare("wait")==0){
				emit comWAIT(com[1].toInt(),com[2].toInt());
			}
			else if(com[0].compare("turn")==0){
				if(com[1].compare("on")==0){
					emit comTURN(true);
				}
				else{
					emit comTURN(false);
				}
			}
			else if(com[0].compare("play")==0){
					emit comPLAY(com[1]);
			}
		}	
	}
}


/*
compileScript():
	This function is used to compile script
	this function maps the user script commands to the C++ functions
*/
void OSPMainDialog :: compileScript(){
	QRegExp scriptExp("^([goto | wait | turn | play]{4})\\s*([\u0370-\u03FF0-9a-zA-Z\\.\\s]*)\\s*;$");
	bool compileStatus = true,i;
	int line_count=0;
	commandsList.clear();
	i = playlist->clear();

	if(nRef<2)
	{
		compileStatus=false;
		showMessage(QString("Please do the calibration"));	
	}
	else{

		foreach(QString w, ui->scriptEdit->toPlainText().split("\n")){
			line_count++;
			if(!scriptExp.exactMatch(w) && w.compare("")!=0){
				compileStatus=false;
				showMessage(QString("Syntax Error at line %1").arg(line_count));
			}
			else{
				QStringList com_par=scriptExp.capturedTexts();
					if(com_par[1].compare("goto")==0){
						double ra=0.0,dec=0.0;
						QString sra,sdec;
						//Todo:add checks before going down
						StelObjectP star = GETSTELMODULE(StelObjectMgr)->searchByNameI18n(com_par[2].trimmed());
						if(!star.isNull()){
	 						StelUtils::rectToSphe(&ra,&dec,star->getEquinoxEquatorialPos(StelApp::getInstance().getCore()));
							sra.setNum(ra);
							sdec.setNum(dec);
							commandsList << QString("goto_"+sra+"_"+sdec);
							qDebug()<<sra<<sdec;
						}
						else{
							showMessage("Could not find the star with the given name");
						}
					}
					else if(com_par[1].compare("turn")==0){
						if(com_par[2].trimmed().compare("on")!=0 && com_par[2].trimmed().compare("off")!=0){
							compileStatus=false;
							showMessage(QString("The parameter for laser must be either 'on' or 'off' at line %1").arg(line_count));
							break;
						}
						else{
							commandsList << QString("turn_"+com_par[2].trimmed());
						}
					}
					else if(com_par[1].compare("play")==0){
						QFile f(QString(audioDirectoryPath+"/"+com_par[2].trimmed()));
						if(!f.exists()){
							compileStatus=false;
							showMessage(QString("File not found in [{Stellarium User Directory}/modules/OpenSkyPlanetarium/audio/] at line %1").arg(line_count));
							break;
						}
						else{
							commandsList << QString("play_"+com_par[2].trimmed());
						}
					}
					else if(com_par[1].compare("wait")==0){
						QRegExp a("([1-5]?[0-9])\\s*m\\s*([1-5]?[0-9])\\s*s");
						if(!a.exactMatch(com_par[2].trimmed())){
							showMessage(QString("(X)m(Y)s format expected as argument for wait at line %1").arg(line_count));
							compileStatus=false;
							break;
						}
						else{
							QStringList temp = a.capturedTexts();
							commandsList << QString("wait_"+temp[1].trimmed()+"_"+temp[2].trimmed());
						}
					}
			}
		}
	}
	if (!compileStatus){
		commandsList.clear();
	}
	else{
		//showMessage("Build Successful");
	}
	buildStatus=compileStatus;
}

////////////////////////SLOTS FOR FUNCTIONS TO BE CALLED WHILE EXECUTION OF SCRIPT///////////////////////////////////////////

/*
move(QString,QString):
	This is slot connected to goto command from our script engine
	It takes ra/dec of star as its parameters and converts them to move
*/
void OSPMainDialog :: move(QString x,QString y){
	qDebug() << "Moveto X and Y = ["<<x <<","<<y<<"]";
	double ra,dec,ac,alt;	
	ra=x.toDouble();
	dec=y.toDouble();
	QDateTime dt = QDateTime::currentDateTime();
	double time = StelUtils::hmsToRad (dt.time().hour(), dt.time().minute(), dt.time().second());
        calib.getHCoords(ra - 3.14159,dec,time,&ac,&alt);
	device.move(ac,alt);
}

/*
laser(bool):
	This is a slot for our script engine emit signal comTURN
	This is used when playing the script
*/
void OSPMainDialog :: laser(bool stat){
	if(stat){
		device.laserOn();
		ui->laserOn->setChecked(true);
		ui->laserOff->setChecked(false);
	}
	else{
		device.laserOff();
		ui->laserOff->setChecked(true);
		ui->laserOn->setChecked(false);
	}
}

/*
waitforsec(int,int):
	this is used when playing the script
	this is used to give wait functionality in the script
*/
void OSPMainDialog :: waitforsec(int min,int sec){
	dieTime = QTime::currentTime().addSecs(min*60 + sec);
	qDebug()<<"Current Time"<<QTime::currentTime();
	qDebug()<<"before While"<<dieTime;	
	while( QTime::currentTime() < dieTime || playerState == QMediaPlayer::PausedState)
	{		
	   	QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
	}
	qDebug()<<"remTim"<<remtim;
	qDebug()<<"After while"<<dieTime;
}
/*
playAudio(QString):
	This function is used to play audio files
	This is used to give play Audio functionality in our script
*/
void OSPMainDialog :: playAudio(QString fname){
	playlist->addMedia(QUrl::fromLocalFile(QString(audioDirectoryPath+QString("/")+fname)));
	emit play();
    ui->playui->setEnabled(true);	
    ui->playui->setText(QString("Pause"));
    playerState = QMediaPlayer::PlayingState;
}


//////////////////////////////////////////////////////////////////SLOTS FOR SCRIPT ENGINE COMMAND BUTTONS///////////////////////////////



/*
gt():
	This slot is connected to Goto Button of the Script Engine
	Adds the goto command to your script
*/
void OSPMainDialog :: gt(){
	QString sra,sdec;
	const QList<StelObjectP>& selected = GETSTELMODULE(StelObjectMgr)->getSelectedObject();
	if (!selected.isEmpty()) {
		double dec_equinox = 0;
		double ra_equinox = 0;
		StelUtils::rectToSphe(&ra_equinox,&dec_equinox,selected[0]->getEquinoxEquatorialPos(StelApp::getInstance().getCore()));
		ui->scriptEdit->setText(ui->scriptEdit->toPlainText().append(QString("goto %1;\n").arg(selected[0]->getNameI18n())));
	}
	else {
		showMessage("Please select an object first");	
	}
}

/*
pl():
	This slot is connected to Play Button of the Script Engine
	Adds the play audio command to your script
*/
void OSPMainDialog :: pl(){
	QString fileName = QFileDialog::getOpenFileName(NULL,QString("Select Audio File"), audioDirectoryPath,QString("Audio Files (*.mp3)"));
	if (!fileName.isNull()){
		QFileInfo f(fileName);
		ui->scriptEdit->setText(ui->scriptEdit->toPlainText().append(QString("play %1;\n").arg(f.fileName())));
	}
	else{
		showMessage("Please select the audio file");
	}
}

/*
lo():
	This slot is connected to laser on/off button of the Script Engine
	Adds the laser on/off command to your script
*/
void OSPMainDialog :: lo(){
	QStringList items;
    	items << "on"<<"off";
	bool ok;
    	QString item = QInputDialog::getItem(NULL, "Open Sky Planetarium","Select State(on/off):", items, 0, false, &ok);
    	if (ok && !item.isEmpty()){
		ui->scriptEdit->setText(ui->scriptEdit->toPlainText().append(QString("turn %1;\n").arg(item)));
	}
	else{
		showMessage("Please select either on/off");
	}
}

/*
wt():
	This slot is connected to wait button of the Script Engine
	Adds the wait command to your script
*/
void OSPMainDialog :: wt(){
	bool ok;
	QRegExp a("([1-5][0-9])\\s*m\\s*([1-5][0-9])\\s*s");
    	QString time = QInputDialog::getText(NULL,"Open Sky Planetarium","Enter time(in [X]m[Y]s):",QLineEdit::Normal,"", &ok);
    	if (ok && !time.isEmpty() && !a.exactMatch(time)){
		ui->scriptEdit->setText(ui->scriptEdit->toPlainText().append(QString("wait %1;\n").arg(time)));
	}
	else{
		showMessage("Please enter time in (X)m(Y)s format");
	}	
}

////////////////////// Media Functions /////////////////////////////

/*
setVolume(int):
	This slot is connected to the volume slider of the Script Engine
	Sets the volume for the player.
*/

void OSPMainDialog::setVolume(int volume)
{
    player->setVolume(volume);
}

/*
stopClick():
	This slot is connected to the stopui function of the Script Engine
	Stops the player.
*/

void OSPMainDialog::stopClick()
{
    playerState = QMediaPlayer::StoppedState;
    ui->playui->setText(QString("Play"));
    player->stop();
}

/*
playClicked():
	This slot is connected to the playui function of the Script Engine	
	Play or pause the audio in the script engine.
*/

void OSPMainDialog::playClicked()
{
    switch (playerState) {
    case QMediaPlayer::StoppedState:
		emit play();
		emit execScript();
        ui->playui->setText(QString("Pause"));
        playerState = QMediaPlayer::PlayingState;
        break;
    case QMediaPlayer::PausedState:
        emit play();
        ui->playui->setText(QString("Pause"));
		remtim = pauseWait.restart();
        dieTime = dieTime.addMSecs(remtim);
        playerState = QMediaPlayer::PlayingState;
        break;
    case QMediaPlayer::PlayingState:
        emit pause();
		pauseWait.start();
        ui->playui->setText(QString("Play"));
        playerState = QMediaPlayer::PausedState;
        break;
    }
}

