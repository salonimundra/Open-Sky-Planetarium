//MOST IMPORTANT INSTALL QT CREATOR LATEST VERSION ELSE CODE WOULD NOT COMPILE NEITHER ONLINE NOR OFFLINE(BE IT COMMAND LINE OR ANY SOFTWARE
//INSTALLATION OF QT CREATOR TAKES TIME BE PATIENT ..!!

/*This file contains all the conversions that would be needed to communicate
 with the device and stellatium and passing and feedback of cordinates(only their conversion )
i.e what format is accepted and what not . For the ease of readability the code has been properly indented and also has comments __Yudhisther Bhargava*/
//HEADER FILES
#include<iostream>
/*regular expression as alot many times regular expressions are handled so before going through the code please be thorough with the regular expression conversions
(not much detail basic would do) also go through the functions of regex class and also how splitting takes place using regex and how they are evaluated and compared with strings*/
#include<regex>

/*basic knowledge of string and its functions*/
#include<cstring>

/*Alot of functions are used like round absolute etc so please be thorough with the
  knowledge of cmath(math.h) before attempting the code*/
#include<cmath>


#include<QString>
/*Since strings cannot be directly returned and also stellarium is qt based software so we need to avoid pointers
 as much as possible and use qt objets and also qt makes cding bit easy so before the code please attempt classes of qt  and understand the functions */
#include<QString>

/*The QList class allows us to return the list of elements and also store strings after spliiting them .This feature is needed at alot of places
 so please read it before hand to avoid hastles and errors*/
#include<QList>

/*Time class used in c++ contains functions for manipulation of time */
#include<ctime>
//ctime

/*Regular Expression can also be used from Qt and c++ it depends on coder which seems easy to him */
#include<QRegExp>


#include "Coords.hpp"
/*the file taht contains declaration of all functions defined by us*/
//qt reg expr
#include<QDebug>

#include<QTime>

using namespace std;
//class declaration
//class class_Coords{

    //Constructor

    Coords::Coords()
    {

    }

    //Desrtuctor
    Coords::~Coords()
    {
    }


/*This function takes input as float type and coverts radian
 to hour time format and returns float value*/

float Coords::rad_2_hour(float rads)
{
    float h;

    h = round( (rads * 180)/(15 * M_PI));

    if (h > 24.0)
        h = h - 24.0;

    if (h < 0.0)
        h = 24.0 + h;

    return h;
}


/*This function takes input as character array which gets converted to string and then finally to
 Qstring which is converted to degree format from radian string and returns a double value */

double Coords:: radStr_2_deg(QString qstr)
{
    bool b;
    b=1;
    //float r;
   float r;

       //std :: string str(rad);
     //QString qstr = QString::fromStdString(str);

     //r= strtof(str);
    //double r = ::atof(r.c_str());

     //r = QString( qstr).toFloat(&ok);
     r=qstr.toFloat();
   //regex e("'^(-?)[0-9]{1}\\.[0-9]{4,8}'");
   //b = regex_match(str,e);
     /*cpp version */
    QRegExp e("[+-]([0-9]*[.])?[0-9]+");
    b=e.exactMatch(qstr);
    //cout << r<< endl;
    //cout << b <<endl;
   if(b==1)
     {
        if(r<0)
            r=(2*M_PI)-abs(r);
        //cout << r<< endl;
        //return (r * 180) /M_PI;
     }
   //else
     //  return NULL;
   return (r * 180) /M_PI;
}


/*This function takes input as a float value that represents radian and
 converts it wo radian string and returns as a qstring object */


QString Coords::rad_2_radStr(float rad)
{
    //int i=0;
    //int j=0;
    //int k=0;
    //char res[20];

    //ftoa(rad,res,6);
    QString b = QString::number(rad);

    if(rad <0.0)
    {
        //string str(res);
        //QString qstr = QString::fromAscii(str);

        //QString qstr = QString::fromStdString(str);

        return b;


        //return &res
    }else
        {

        /*while(res[i]!= NULL)
          {
            j++;
        }
        j=j+1;
        res[j]=res[0];
        res[0]='+';*/
        QString qstr ;
        qstr.append("+");
        qstr.append(b);
        //0QString qstr = QString::fromAscii(str);
         //QString qstr = QString::fromStdString(str);*/
            //b.append()

         return qstr;
        //return &res;
}

}


/*This function takes a character array input and converts it from radian string format
 to degreestring format (takes a character array as input(radian str and returns a qstring
 object i.e the degree string output)*/


QString Coords::radStr_2_degStr(QString r )//hdhdjfj
{

    QString qstr  = deg_2_degStr(radStr_2_deg(r));
    //QString qstr = QString::fromAscii(s);
    //QString qstr = QString::fromStdString(s);
        return qstr;
}


/*This function takes a character array input and converts it from degree string format
 to radian string format (takes a character array as input(degree str and returns a qstring
 object i.e the radian string output)*/

QString Coords::degStr_2_radStr(QString d)//452212
{
    //string str(d);
    //QString qstr = QString::fromAscii(str);

    //QString qstr1 = QString::fromStdString(str);
    QString qstr =rad_2_radStr(degStr_2_rad(d));
    //QString qstr = QString::fromAscii(s);
   // QString qstr = QString::fromUtf8(content.c_s());
    //QString qstr = QString::fromStdString(s);
    return qstr;
}


/*The function takes a float input that represnts degree value and converts it to string and
 returns as a QString object that represents the degree string (degree converted to string
format from float*/


QString Coords::deg_2_degStr( float deg)
{
    float ndeg,nmins,secs,mins;
    //char a[3];
    //QString r,s,t,u;
    ndeg = floor(float(deg));
    //QString r = QString::number(ndeg);

    nmins = (deg - ndeg) * 60;

    mins = floor(float(nmins));
    //cout << mins << endl;
    //QString b = QString::number(nmins)
    secs = round( (nmins - mins) * 60 );
    //a[2]=secs;
    //cout << secs <<endl;

   // string str(a);
    //QString qstr= QString::fromAscii(str);
    //QString directory = QString("%1 %2 %3").arg(ndeg,mins,secs);
            QString str =QString::number( ndeg ) + " " +  QString::number( mins ) + " " +QString::number( secs );
    //QString qstr = QString::fromStdString(str);
    return str;

}


/* The function transforms coordinates from radians to the "Stellarium Telescope Protocol" format
 returns a list of right ascension and declination in stellerium compatible format
 in an integer list after receiving corrdinates in float format  */



QList<int> Coords::rad_2_stellarium_protocol(float ra,float dec)
{
    float ra_h,dec_d;
    QList<int> integerList;
    ra_h = rad_2_hour(ra);
    dec_d = (dec * 180) / M_PI;
    //QDebug
   // ra_h=int(ra_h*(2147483648/12.0))
     integerList.append(int(ra_h*(2147483648/12.0)));
     integerList.append( int(dec_d*(1073741824/90.0)));
     return integerList;
}

/*The function transforms the values obtained from "Stellarium Telescope Protocol", to a list with each
  value in string format i.e takes ra dec and mtime converts and stores them to a float qlist
  and returns */


QList<float>  Coords::eCoords2str(float ra, float dec,float mtime)
{
    float ra_h,dec_d,time_s;
    QList<float> ls;
    ra_h = ra*12.0/2147483648;
    dec_d = dec*90.0/1073741824;
    time_s = floor(mtime / 1000000);
    ls.append(ra_h);
    ls.append(dec_d);
    ls.append(time_s);
    return ls;
}




/*This function converts from degree in in float format to a list that
 seperates degree ,minute and seconds and returns them in a list (qlist<float>)
 float ->QList<float>*/

QList<float> Coords::grad_min_sec(float degs)
{
    QList<float> ls;
    int d,s,m;
    float degs_m;
    bool to_neg;
    to_neg = 0;
    if(degs < 0)
       { degs = fabs(degs);
        to_neg =1;
    }
    d = floor(degs);

    degs_m = (degs - d)*60.0;
    m = floor(degs_m);

    s = (degs_m - m)*60.0;
    if(s >= 59.99)
        {s = 0;
        m += 1;}
    if( m >= 60.0)
        {m = 60.0-m;
        d += 1;
    }
    if(to_neg)
        d = -d;


   ls.append(d);
   ls.append(m);
   ls.append(s);
    return ls;
}


/* This function takes a float argument that represents hours and converts
it to a list of integers that contain hours min and seconds and return it
tranformation float -> QList<int>*/

QList<int> Coords::hour_min_sec(float hours)
{
    int h,m,s;
    QList<int> ls;
    float hours_m;
    h=floor(hours);
    hours_m=(hours-h)*60;
    m = floor(hours_m);

    s = (hours_m - m)*60.0;


    if( s >= 59.99)
    {s = 0;
        m += 1;
    }
    if( m >= 60)

       { m = 60-m;
        h += 1;
    }
    ls.append(h);
    ls.append(m);
    ls.append(s);
    return ls;
}



/* The function float input and first breaks it to hour min and second and stores in an
integer Qlist and then  typecasts each to string and stores in QList<string> and
returns a list of string converting hour in float format to hour in string format*/


QList<QString> Coords::hour_2_hourStr( float hours)
{
    QList<int> ls;
    ls=hour_min_sec(hours);
    QList<QString> ls1;
    //QString s = QString::number(i);
   // ls1.append(to_string(ls[0]));
    //ls1.append(to_string(ls[1]));
    //ls1.append(to_string(ls[2]));
    ls1.append(QString::number(ls[0]));
    ls1.append(QString::number(ls[1]));
    ls1.append(QString::number(ls[2]));
    return ls1;
}


/* Transforms coordinates from radians to J2000 string format ("HhMmSSs/GºM'SS'' at Fecha")

param ra Right ascension (float)
param dec Declination (float)
param mtime Timestamp in microseconds (float)
return Equiatorial coordinates in J2000 string format*/


QList<QString> Coords::toJ2000(float ra,float dec,float mtime)
{
    QList<QString> ss;
    //QString t1;
    QList<int> ls1;
    QList<float> ls2;
    float ra_h,dec_d;
    //float t;
    //time_t time_s;
    ra_h = ra*(12.0/2147483648);
 // cout << ra_h <<endl;
    ls1=hour_min_sec(ra_h);
   // for(int b:ls1)
     //   cout <<b << endl;
   // cout << ls1<< endl;
    dec_d = dec*(90.0/1073741824);
    //cout << dec_d <<endl;
    ls2 = grad_min_sec(dec_d);
    //for(float a:ls2)
      //  cout << a << endl;
    //cout << ls2 <<endl;
  //t= floor(mtime );
   QTime t(0,0,floor(mtime));
     //float f = (float)t;
    //time_t t;
    // string b;
   // b=f.ctime();
   // time(&t);
    //time_t p;
    //p=t;
    //b=ctime(p);
    //b=QTime::toString(t);
    //std::string str = b.toStdString();
    //ss.append(to_string(ls1[0]));
   // ss.append(to_string(ls1[1]));
    //ss.append(to_string(ls1[2]));
    //ss.append(to_string(ls2[0]));
    //ss.append(to_string(ls2[1]));
    //ss.append(to_string(ls2[2]));*/
    ss.append(QString::number(ls1[0]));
    ss.append(QString::number(ls1[1]));
    ss.append(QString::number(ls1[2]));
    ss.append(QString::number(ls2[0]));
    ss.append(QString::number(ls2[1]));
    ss.append(QString::number(ls2[2]));
    ss.append(t.toString());
    return ss;
    //return ls2;
}


/* The function coverts from hours in string format to radians
in float format and returns  float variable
*/



float Coords::hourStr_2_rad( QString h)//awsredrfgyhjkl
//once
{
    //QtList<float> ls;
    string k;
    k=h.toStdString();
    float h_h,h_m,h_s,nh;
    bool b;
    //QStringList list
    //char *pch;
    QList<QString> list;
   // regex e("^[0-9]{,3}h[0-9]{,3}m[0-9]{,3}s$");
    //b = regex_match(k,e);
    //b=e.exactMatch(h)

    QRegExp e("[0-9]{,3}h[0-9]{,3}m[0-9]{,3}s");

    b=e.exactMatch(h);
    //cout <<b << endl;
           if(b==1)
   {
    QString query;
    std::replace( h.begin(), h.end(), 'h', '.');
    std::replace( h.begin(), h.end(), 'm', '.');
    std::replace( h.begin(), h.end(), 's', '.');
    //QString qstr = QString::fromStdString(h);
    //qDebug() << QString(h)<<endl;
    //list = h.split(QRegExp("[.]"));
    list = h.split('.');
  //r  qDebug()<< list<< endl;
    h_h=list[0].toFloat();
    h_m=list[1].toFloat();
    h_s=list[2].toFloat();
   //qDebug()<<QLis
    nh = (h_h+(h_m/60)+(h_s/(pow(60,2))));
    nh= ((nh * 15 * M_PI) / 180);
    //setprecision(9) << nh << endl;
    //cout << nh;
    return nh;
    }
           else
               return 0;
    //QRegExp rx(".");
    //QList<QString>query = h.split('rx');
    /*h_h = float(query[0].toFloat());
    h_m = float(query[1].toFloat);
    h_s = float(query[2].toFloat());
    nh = (h_h+(h_m/60)+(h_s/(60**2)))
    nh= round((nh * 15 * M_PI) / 180, 6)

    return nh;*/

}

/*This function converts from degree string to radians in float
 format i.e takes an expression compares with regular expression and returns accordingly
 a float value that represents radian value*/

float Coords::degStr_2_rad( QString d)//regex
    {
        bool b1, b2;
        string g;
        g=d.toStdString();
         QStringList list;
        float d_deg;
        float d_min;
        float d_sec;
        float d_ndeg;
        //qDebug() << QString(d)<<endl;
        //QRegExp e1("^-?[0-9]{,3}(º|ᵒ)[0-9]{,3}\'[0-9]{,3}([\']{2}|)$");
        QRegExp e1("[+-]([0-9]{,3}(º|ᵒ)][0-9]{,3}\'[0-9]{,3}([\']{2}|))");
       b1= e1.exactMatch(d);
       //qDebug() << QString(d)<<endl;
     //  cout << b1 << endl;
      // QRegExp e2("^-?[0-9]{,3}\.[0-9]{,6}(º|ᵒ)$");
        QRegExp e2("[+-]([0-9]{,3}*[.])?([0-9]{,6}(º|ᵒ))");
      b2 = e2.exactMatch(d);
      //qDebug() << QString(d)<<endl;
      //cout << b2 << endl;
      if(b1==1)

      {
          //string sValue = "36";
          std::replace( d.begin(), d.end(), '\xB0','.');
          std::replace( d.begin(), d.end(), '\'','.');
          //QString qstr = QString::fromStdString(d);
          //list = d.split(QRegExp("\."));
          list = d.split('.');
          d_deg = list[0].toFloat();
          d_min = list[1].toFloat();
          d_sec = list[2].toFloat();
          if(d_deg<0)
          {
              d_min = 0 - d_min;
              d_sec = 0 - d_sec;
          }

          d_ndeg = (d_deg+(d_min/60)+(d_sec/pow(60,2)));

      }
      else if(b2==1)
      {
          std::replace( d.begin(), d.end(), '\xB0', '.');
          //QString qstr = QString::fromStdString(d);
          list = d.split('.');
          d_ndeg = list[0].toFloat();
          if(d_ndeg<0)
          {
               d_ndeg = 360 - abs(d_ndeg);


          }

      }

    return ((d_ndeg *M_PI) / 180);


    }
/*reverse function is to reverse the characters */

void Coords::reverse(char *str, int len)
{
    int i=0, j=len-1, temp;
    while (i<j)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++; j--;
    }
}

/*to convert to strings*/

int Coords::intToStr(int x, char str[], int d)
{
    int i = 0;
    while (x)
    {
        str[i++] = (x%10) + '0';
        x = x/10;
    }


    while (i < d)
        str[i++] = '0';

    reverse(str, i);
    str[i] = '\0';
    return i;
}
void Coords::ftoa(float n, char *res, int afterpoint)
{

    int ipart = (int)n;

    float fpart = n - (float)ipart;


    int i = intToStr(ipart, res, 0);


    if (afterpoint != 0)
    {

        fpart = fpart * pow(10, afterpoint);

        intToStr((int)fpart, res + i + 1, afterpoint);
    }
}



//};




