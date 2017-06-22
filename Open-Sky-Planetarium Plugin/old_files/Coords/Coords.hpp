#ifndef COORDS_HPP
#define COORDS_HPP

#include<regex>
#include<QString>
#include<QList>
#include<cstring>
#include<cmath>
#include<ctime>
#include<iostream>
#include<QRegularExpression>
#include<QRegExp>
#include<QDebug>
#include<QTime>
class Coords
{
public:
    Coords();
    ~Coords();

    ///////////////////////////////////////////////////////////////////////////

    float rad_2_hour(float rads);
    double  radStr_2_deg(QString qstr);
    QString rad_2_radStr(float rad);
    QString radStr_2_degStr(QString r );
    QString degStr_2_radStr(QString d);
    QString deg_2_degStr( float deg);
    QList<int> rad_2_stellarium_protocol(float ra,float dec);
    QList<float>  eCoords2str(float ra, float dec,float mtime);
    QList<float> grad_min_sec(float degs);
    QList<int> hour_min_sec(float hours);
    QList<QString> hour_2_hourStr( float hours);
    QList<QString> toJ2000(float ra,float dec,float mtime);
    float hourStr_2_rad( QString h);
    float degStr_2_rad( QString d);
    void reverse(char *str, int len);
    void ftoa(float n, char *res, int afterpoint);
    int intToStr(int x, char str[], int d);

};

#endif // COORDS_H
