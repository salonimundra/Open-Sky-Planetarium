// #include "WProgram.h" // Arduino < 1.0
#include <Arduino.h> //Arduino >= 1.0
#include "AxesLib.h"
#include <Servo.h>

Servo myservo, Xservo, Yservo;
int steps;
int stepx;
int stepy;
int low;
int high;
int x_rev_set = 0;
int y_rev_set = 0;
float valx;
float valy;
int _pgrad_x;
int _pgrad_y;
bool blind;
int diff_x;
int diff_y;
int stepx_new;
int stepy_new;
int slow=50;
int xcount;
int ycount;

AxesLib::AxesLib(){
    stopper=0;
}

void AxesLib::setMotorsPins(int Pin1, int Pin2){

	
	pinMode(Pin1, OUTPUT);
	pinMode(Pin2, OUTPUT);
	

        Xservo.attach(9);//,500,2100);///ATTACH servo
        Yservo.attach(10);//,500,2100);///ATTACH servo
        delay(1000);
}


//#######################################
void AxesLib::init()
{
  low = 560;//590;
  high = 2420;//2190;
  _pgrad_x=((high-low)/170)/5;
  _pgrad_y=((high-low)/170)/5;
  for (stepx=1490;stepx>low;stepx=stepx-5)
  {
    //Serial.println("in init");
    stepy=stepx;
    Xservo.writeMicroseconds(stepx); 
    Yservo.writeMicroseconds(stepy); 
    delay(20);
    }
  
  }

//####################################
  int AxesLib::getPX() //Steps per revolution on X axis
  {
    return x_rev_set = (high-low)/5;
    }
//#######################################

    int AxesLib::getPY() //Steps per revolution on Y axis
  {
    return y_rev_set = (high-low)/5;//(2190-590)/5;
    }
    
  //#####################################  
	bool AxesLib::movx(bool dir) //Move on X axis
  {
    int bytes_recv = 0;        
    char comm[5]="nost";
 
    comm[bytes_recv++] = Serial.read();
    //Serial.print("value of comm is ");
    //Serial.println(comm);
    while(strcmp(comm, "stop")!=0 || stopper)
  {
    if(stepx>high)
      stepx=high;
    if(stepx<low)
      stepx=low;
    //Serial.println("inside button ");
    //Serial.println(stepx);
   Xservo.writeMicroseconds(stepx); 
   if(dir==false)
   {
   stepx=stepx+5;
   delay(100); 
 }
   if(dir==true)
   {
   stepx=stepx-5;
 delay(100);
 
 }
   //delay(5);
   while(Serial.available() > 0)
      comm[bytes_recv++] = Serial.read();
                //Serial.println(comm);
                //Serial.println("inside second while");
    //Safeguard...
    if(bytes_recv>4)
      break;
   
}


  return true;
    }

    //#####################################  
  bool AxesLib::movy(bool dir) //Move on Y axis
  {
     // Serial.print("stepx of axes ");    Serial.println(stepx);
    int bytes_recv = 0;        
    char comm[5]="nost";
 
    comm[bytes_recv++] = Serial.read();
    //Serial.print("value of comm is ");
    //Serial.println(comm);
    while(strcmp(comm, "stop")!=0)
  {
    if(stepy>high)
      stepy=high;
    if(stepy<low)
      stepy=low;
    //Serial.println("inside button ");
    //Serial.println(stepy);
   Yservo.writeMicroseconds(stepy); 
   if(dir==false)
   {
   stepy=stepy+5;
   delay(100); 
 }
   if(dir==true)
   {
   stepy=stepy-5;
 delay(100);
 
 }
   //delay(5);
   while(Serial.available() > 0)
      comm[bytes_recv++] = Serial.read();
                //Serial.println(comm);
                //Serial.println("inside second while");
    //Safeguard...
    if(bytes_recv>4)
      break;
   
}

      
  return true;
    }

    //560 to 2420 << 590 2190
//#################################
    float AxesLib::getX()
{
  float valx;
  valx = map(stepx, 560, 2420, 0, 170);
  valx = (valx/180)*M_PI;
  return valx;
}

float AxesLib::getY()
{
  float valy;
  valy = map(stepy, 560, 2420, 0, 170);
  valy = (valy/180)*M_PI;
  return valy;
}

int AxesLib::getPx()
{
  return (stepx-560)/5;
}

int AxesLib::getPy()
{
  return (stepy-560)/5;
}


int AxesLib::_rad2deg(float rad){
  return lrint( (float) (rad * 180.0)/M_PI );
}

float AxesLib::_deg2rad(float deg){
  return (float) (deg * M_PI)/ 180.0;
}

/*
void AxesLib::goToRads(float rx, float ry){
  float degsH = (360.0 - _rad2deg(rx));
  if(degsH >= 360.0)
    degsH = degsH - 360.0;
  
  _moveTo((float) degsH*_pgrad_x, (float) _rad2deg(ry)*_pgrad_y);
}*/

//################################################

//######################################
void AxesLib::goToRads(float x_rad, float y_rad)
{
//    float degsH = (360.0 - _rad2deg(valx));
//  if(degsH >= 360.0)
//    degsH = degsH - 360.0;
//  
//  _moveTo((float) degsH*_pgrad_x, (float) _rad2deg(valy)*_pgrad_y);
 // _moveTo(_rad2deg(valx),_rad2deg(valy));

float degsH = _rad2deg(x_rad);
float degsV = _rad2deg(y_rad);
//Serial.println("radians received to gotoRads");
//Serial.print(x_rad);Serial.print(" ");Serial.println(y_rad);

//Serial.println("degrees received to gotoRads");
//Serial.println(degsH);Serial.println(" ");Serial.println(degsV);
if ((degsH > 170 && degsH < 180)||(degsH > 350 && degsH < 360))
{
//Serial.println("Warning.. Device is in blind zone");
blind = true;
}
else
blind = false;

//if ((degsH > 180) && blind==false)
//{
//degsH = degsH-180;
//degsV = 180-degsV;
//}

if ((x_rad < 0) && blind==false)
{
degsH = degsH+180;
degsV = 180-degsV;
}
//
//Serial.println("degrees conveyed to moveXY");
//Serial.println(degsH);Serial.print(" ");Serial.println(degsV);
_moveTo(degsH,degsV);

}
//##################################################
void AxesLib::_moveTo(int x, int y, char* method)
{
  //Serial.println(x);
  //Serial.println(y);
  /*
  if(strcmp(method, "DDA")==0)
    _moveDDA(x, y);
  else if(strcmp(method, "XY")==0) */

  stepx_new = map(x, 0, 170, low, high);
  stepy_new = map(y, 0, 170, low, high);

  
    //_moveDDA(stepx_new, stepy_new);
   //_moveXY(stepx_new, stepy_new);
   _moveEqua(stepx_new, stepy_new);
   stepx=stepx_new;
   stepy=stepy_new;
}
//##################################################
void AxesLib::_moveXY(int x, int y, bool nodelay){

  float xdeg;
  float ydeg;
//  Serial.println(x);
//  Serial.println(y);
//  xdeg = _rad2deg(x);
//  Serial.println("xdeg, ydeg");
//  Serial.println(xdeg, ydeg);
//  ydeg = _rad2deg(y);

  //stepx = map(x, 0, 170, low, high);
  Xservo.writeMicroseconds(x);
   //Serial.println("steps for x");
  //Serial.println(stepx);
  //stepy = map(y, 0, 170, low, high);
  Yservo.writeMicroseconds(y);
    //Serial.println("steps for y");
  //Serial.println(stepy);
  
}

//################################################  m_+0.13_+0.82
void AxesLib::_moveDDA(int x, int y){

   int xcount;
    int ycount;
    slow = 100;

//    Serial.println(x);
//Serial.println(y);
//Serial.println(stepx);
// Serial.println(stepy);
    if(x>stepx)
    {
      //Serial.println("case1");
      for(xcount=stepx;xcount<x;xcount=xcount+5)
      {Xservo.writeMicroseconds(xcount);
      //Serial.println(xcount);
      delay(slow);}
      }

      if(x<stepx)
    {
      //Serial.println("case2");
      for(xcount=stepx;xcount>x;xcount=xcount-5)
      {Xservo.writeMicroseconds(xcount);
      //Serial.println(xcount);
      delay(slow);}
      }

      if(y>stepy)
    {
      //Serial.println("case3");
      for(ycount=stepy;ycount<y;ycount=ycount+5)
      {Yservo.writeMicroseconds(ycount);
      //Serial.println(ycount);
      delay(slow);}
      }

      if(y<stepy)
    {
      //Serial.println("case4");
      for(ycount=stepy;ycount>y;ycount=ycount-5)
      {Yservo.writeMicroseconds(ycount);
      //Serial.println(ycount);
      delay(slow);}
      }
  
  }

  void AxesLib::_moveEqua(int x, int y)
  {

    float y_mov=0;
    int x_mov=0;
    int slow = 10;
    float slope=(((float)stepy-(float)y)/((float)stepx-(float)x));
    //Serial.println(slope);

 if(x>stepx)
    {
      //Serial.println("case1");
      for(x_mov=stepx;x_mov<=x;x_mov++)
      {
        y_mov = slope*(x_mov-stepx)+stepy;
        Xservo.writeMicroseconds(x_mov);
        Yservo.writeMicroseconds(y_mov);
        
//        Serial.println("----");
//        Serial.println(x_mov);
//        Serial.println(y_mov);
//        Serial.println("----");
//
//        Serial.println("#######");
//        Serial.println(x);
//        Serial.println(y);
//        Serial.println(stepx);
//        Serial.println(stepy);
//        Serial.println("######");
        
        delay(slow);}
      }

//m_+0.13_+0.82
      if(x<stepx)
    {
      //Serial.println("case2");
      for(x_mov=stepx;x_mov>=x;x_mov--)
      {
        
        y_mov = slope*(x_mov-stepx)+stepy;
        Xservo.writeMicroseconds(x_mov);
        Yservo.writeMicroseconds(y_mov);

        
//        Serial.println("----");
//        Serial.println(x_mov);
//        Serial.println(y_mov);
//        Serial.println("----");
//        
//        Serial.println("#######");
//        Serial.println(x);
//        Serial.println(y);
//        Serial.println("######");
        
      delay(slow);}
      }
  }

