/*
The MIT License (MIT)

Copyright (c) 2012 Juan Ramón

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "Calibrate.hpp"
#include <QMediaPlayer>
#include <QCompleter>
#include <QFileDialog>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QObject>
#include <QDebug>
#include <QString>
#include <QTime>
#include <QDateTime>
#include <QMessageBox>
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
#include <stdio.h>
Calibrate::Calibrate(){
	_t0 = 0;
	_k =  1.002737908; // Constant.. Relationship between the solar time (M) and the sidereal time (S): (S = M * 1.002737908)
	_isSetR1 = false;
	_isSetR2 = false;
	_isSetR3 = false;
}

/*
 * Calculates the inverse of the m[3x3] matrix and returns it in the second parameter.
 */
void Calibrate::_inv(double m[3][3], double res[3][3]){
	double idet;

	//Inverse of the determinant
	idet = 1/(
				(m[0][0]*m[1][1]*m[2][2]) + (m[0][1]*m[1][2]*m[2][0]) + (m[0][2]*m[1][0]*m[2][1])
			  -	(m[0][2]*m[1][1]*m[2][0]) - (m[0][1]*m[1][0]*m[2][2]) - (m[0][0]*m[1][2]*m[2][1]) 
			 );

	res[0][0] = ((m[1][1]*m[2][2]) - (m[2][1]*m[1][2]))*idet;
	res[0][1] = ((m[2][1]*m[0][2]) - (m[0][1]*m[2][2]))*idet;
	res[0][2] = ((m[0][1]*m[1][2]) - (m[1][1]*m[0][2]))*idet;

	res[1][0] = ((m[1][2]*m[2][0]) - (m[2][2]*m[1][0]))*idet;
	res[1][1] = ((m[2][2]*m[0][0]) - (m[0][2]*m[2][0]))*idet;
	res[1][2] = ((m[0][2]*m[1][0]) - (m[1][2]*m[0][0]))*idet;

	res[2][0] = ((m[1][0]*m[2][1]) - (m[2][0]*m[1][1]))*idet;
	res[2][1] = ((m[2][0]*m[0][1]) - (m[0][0]*m[2][1]))*idet;
	res[2][2] = ((m[0][0]*m[1][1]) - (m[1][0]*m[0][1]))*idet;
}

/*
 * Multiplies two matrices, m1[3x3] and m2[3x3], and returns the result in 
 * the third parameter.
 */
void Calibrate::_m_prod(double m1[3][3], double m2[3][3], double res[3][3]){
	for(int i=0; i<3; i++)
		for(int j=0; j<3; j++){
			res[i][j] = 0.0;
			for(int k=0; k<3; k++) //multiplying row by column
				res[i][j] += m1[i][k] * m2[k][j];
		}
}

/*
 * Calculates the Vector cosines (EVC) from the equatorial coordinates (ar, dec, t).
 */
void Calibrate::_setEVC(double ar, double dec, double t, double* EVC){
	EVC[0] = cos(dec)*cos(ar - _k*(t-_t0));
	EVC[1] = cos(dec)*sin(ar - _k*(t-_t0));
	EVC[2] = sin(dec);
	qDebug() << "ardec = ["<<ar <<"," <<dec<<"]";	
	qDebug() << "LMN = ["<<EVC[0] <<"," <<EVC[1] <<"," <<EVC[2]<<"]";
}

/*
 * Calculates the Vector cosines (HVC) from the horizontal coordinates (ac, alt).
 */
void Calibrate::_setHVC(double ac, double alt, double* HVC){
	HVC[0] = cos(alt)*cos(ac);
	HVC[1] = cos(alt)*sin(ac);
	HVC[2] = sin(alt);
	qDebug() << "altac = ["<<alt <<"," <<ac<<"]";
	qDebug() << "clmn=["<<HVC[0] <<"," <<HVC[1] <<"," <<HVC[2]<<"]";
}

/*
 * Sets the initial observation time.
 */
void Calibrate::setTime(double t0){
	_t0 = t0;
}

/*
 * Sets the first reference object.
 * If all the reference objects have been established, calls the function that calculates T and iT.
 */
void Calibrate::setRef_1(double ar, double dec, double t, double ac, double alt){
	_setEVC(ar, dec, t, _LMN1);
	_setHVC(ac, alt, _lmn1);
	_isSetR1 = true;
	_isSetR3 = false;

	if(_isSetR1 && _isSetR2 && _isSetR3)
		_setT();
}

/*
 * Sets the second reference object.
 * If all the reference objects have been established, calls the function that calculates T and iT.
 */
void Calibrate::setRef_2(double ar, double dec, double t, double ac, double alt){
	_setEVC(ar, dec, t, _LMN2);
	_setHVC(ac, alt, _lmn2);
	_isSetR2 = true;
	_isSetR3 = false;

	if(_isSetR1 && _isSetR2 && _isSetR3)
		_setT();
}

/*
 * Sets the third reference object.
 * If all the reference objects have been established, calls the function that calculates T and iT.
 */
void Calibrate::setRef_3(double ar, double dec, double t, double ac, double alt){
	_setEVC(ar, dec, t, _LMN3);
	_setHVC(ac, alt, _lmn3);
	_isSetR3 = true;

	if(_isSetR1 && _isSetR2 && _isSetR3)
		_setT();
}

/*
 * Indicates if the three reference objects have been established.
 */
bool Calibrate::isConfigured(){
	return (_isSetR1 && _isSetR2 && _isSetR3);
}

/*
 * Third reference object calculated from the cross product of the two first ones.
 * Then calls the function that calculates T and iT.
 */
void Calibrate::autoRef_3(){
	float sqrt1, sqrt2;
	qDebug() << "inside autoref";
	_isSetR3 = true;	
	if(_isSetR1 && _isSetR2){
		sqrt1 = (1/(  sqrt( pow(( (_lmn1[1]*_lmn2[2]) - (_lmn1[2]*_lmn2[1])),2) +
							pow(( (_lmn1[2]*_lmn2[0]) - (_lmn1[0]*_lmn2[2])),2) +
							pow(( (_lmn1[0]*_lmn2[1]) - (_lmn1[1]*_lmn2[0])),2))
				));
		_lmn3[0] = sqrt1 * ( (_lmn1[1]*_lmn2[2]) - (_lmn1[2]*_lmn2[1]) );
		_lmn3[1] = sqrt1 * ( (_lmn1[2]*_lmn2[0]) - (_lmn1[0]*_lmn2[2]) );
		_lmn3[2] = sqrt1 * ( (_lmn1[0]*_lmn2[1]) - (_lmn1[1]*_lmn2[0]) );

		sqrt2 = (1/(  sqrt( pow(( (_LMN1[1]*_LMN2[2]) - (_LMN1[2]*_LMN2[1])),2) +
							pow(( (_LMN1[2]*_LMN2[0]) - (_LMN1[0]*_LMN2[2])),2) +
							pow(( (_LMN1[0]*_LMN2[1]) - (_LMN1[1]*_LMN2[0])),2))
				));
		_LMN3[0] = sqrt2 * ( (_LMN1[1]*_LMN2[2]) - (_LMN1[2]*_LMN2[1]) );
		_LMN3[1] = sqrt2 * ( (_LMN1[2]*_LMN2[0]) - (_LMN1[0]*_LMN2[2]) );
		_LMN3[2] = sqrt2 * ( (_LMN1[0]*_LMN2[1]) - (_LMN1[1]*_LMN2[0]) );

		if(_isSetR1 && _isSetR2 && _isSetR3)
			_setT();
	}
}

/*
 *	Sets the transformation matrix and its inverse (T and iT, respectively).
 */
void Calibrate::_setT(){
	double subT1[3][3], subT2[3][3], aux[3][3];

	subT1[0][0] = _lmn1[0]; subT1[0][1] = _lmn2[0]; subT1[0][2] = _lmn3[0];
	subT1[1][0] = _lmn1[1]; subT1[1][1] = _lmn2[1]; subT1[1][2] = _lmn3[1];
	subT1[2][0] = _lmn1[2]; subT1[2][1] = _lmn2[2]; subT1[2][2] = _lmn3[2];

	subT2[0][0] = _LMN1[0]; subT2[0][1] = _LMN2[0]; subT2[0][2] = _LMN3[0];
	subT2[1][0] = _LMN1[1]; subT2[1][1] = _LMN2[1]; subT2[1][2] = _LMN3[1];
	subT2[2][0] = _LMN1[2]; subT2[2][1] = _LMN2[2]; subT2[2][2] = _LMN3[2];

	_inv(subT2, aux);
	_m_prod(subT1, aux, _T);
	_inv(_T, _iT);
	qDebug() << "LMN3 = ["<<_LMN3[0] <<"," <<_LMN3[1] <<"," <<_LMN3[2]<<"]" ;
	qDebug() << "lmn3 = ["<<_lmn3[0] <<"," <<_lmn3[1] <<"," <<_lmn3[2]<<"]" ;
	qDebug() << "T1 = ["<<_T[0][0] <<"," <<_T[0][1] <<"," <<_T[0][2] <<"," <<_T[1][0] <<"," <<_T[1][1] <<"," <<_T[1][2] <<"," <<_T[2][0] <<"," <<_T[2][1] <<"," <<_T[2][2] <<"]" ;
	//qDebug() << "iT = ["<<_iT[0][0] <<"," <<_iT[0][1] <<"," <<_iT[0][2] <<"," <<_iT[1][0] <<"," <<_iT[1][1] <<"," <<_iT[1][2] <<"," <<_iT[2][0] <<"," <<_iT[2][1] <<"," <<_iT[2][2] <<"]";
	
}

/*
 * Horizontal coordinates (ac, alt) obtained from equatorial ones and time (ar, dec, t).
 *
 * If the third reference object is not established, it calculates it by calling the 
 * proper function.
 */
void Calibrate::getHCoords(double ar, double dec, double t, double *ac, double *alt){
	double HVC[3];
	double EVC[3];
	_setEVC(ar, dec, t, EVC);

	if(!_isSetR3){
		autoRef_3();
	}

	for(int i=0; i<3; i++){
		HVC[i] = 0.0; }
	for(int i=0; i<3; i++){	
		for(int j=0; j<3; j++){
			HVC[i] += _T[i][j] * EVC[j];
		}
	}	

	qDebug() << "clmnforgoto=["<<HVC[0] <<"," <<HVC[1] <<"," <<HVC[2]<<"]";

	(*ac) = atan2(HVC[1], HVC[0]);
        //(*alt) = atan2(HVC[2]*sin(*ac),HVC[1]);
        (*alt) = asin(HVC[2]);
}

/*
 * Equatorial coordinates (ar, dec) obtained from horizontal ones and time (ac, alt, t).
 * 
 * If the third reference object is not established, it calculates it by calling the 
 * proper function.
 */
void Calibrate::getECoords(double ac, double alt, double t, double *ar, double *dec){
	double HVC[3];
	double EVC[3];
	_setHVC(ac, alt, HVC);

	if(!_isSetR3){
		autoRef_3();
	}

	for(int i=0; i<3; i++)
		EVC[i] = 0.0;
	for(int i=0; i<3; i++)
		for(int j=0; j<3; j++)
				EVC[i] += _iT[i][j] * HVC[j];

	(*ar) = atan2(EVC[1], EVC[0]) + (_k*(t-_t0));
	(*dec) = asin(EVC[2]);
}
