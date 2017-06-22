// #include "WProgram.h" // Arduino < 1.0
#include <Arduino.h> //Arduino >= 1.0
#include "OSP.h"

//int steps;
int dir1, step1, dir2, step2; 
int stepx;
int stepy;
int low;
int high;
int x_rev_set = 0;
int y_rev_set = 0;
float valx;
float valy;
float _pgrad_x;
float _pgrad_y;
//bool blind;
//int diff_x;
//int diff_y;
int stepx_new;
int stepy_new;
float degsH;
float degsV;
float degsH_new;
float degsV_new;
//int slow=50;
//int xcount;
//int ycount;


OSP::OSP(){
    stopper=0;
}

void OSP::setMotorsPins(int step1, int dir1, int enable1, int step2, int dir2, int enable2, int ledPin, int ddir1, int ddir2, int motor1, int motor2, int sensor1, int sensor2)
{

	pinMode(step1, OUTPUT); // pinMode(pulPin, OUTPUT); 
  pinMode(dir1, OUTPUT); // pinMode(dirPin, OUTPUT);
  pinMode(enable1, OUTPUT); // pinMode(enblPin, OUTPUT);
  pinMode(step2, OUTPUT); // pinMode(pulPin1, OUTPUT);
  pinMode(dir2, OUTPUT);//   pinMode(dirPin1, OUTPUT);
  pinMode(enable2, OUTPUT); //   pinMode(enblPin1, OUTPUT);
  pinMode(ledPin, OUTPUT); // pinMode(ledPin, OUTPUT);
  pinMode(sensor1, INPUT); // pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT); // pinMode(sensor2, INPUT);
  
  digitalWrite(step1, LOW); // digitalWrite(pulPin, LOW);
   digitalWrite(step2, LOW); // digitalWrite(pulPin1, LOW);
  digitalWrite(ledPin, LOW); // digitalWrite(ledPin, LOW);
  digitalWrite(enable1, LOW); // digitalWrite(enblPin, LOW);
  digitalWrite(enable2, LOW); // digitalWrite(enblPin1, LOW);
  delayMicroseconds(50); 
  digitalWrite(dir1, HIGH); //   digitalWrite(dirPin, LOW);
digitalWrite(dir2, HIGH); // digitalWrite(dirPin1, LOW);

  
  //Serial.begin(9600);
  Serial.println("Setting up Motor pins..done");
  
  digitalWrite(enable1, HIGH); // digitalWrite(enblPin, HIGH);
  delay(100);
  digitalWrite(enable1, LOW); // digitalWrite(enblPin, LOW);
   digitalWrite(enable2, HIGH); // digitalWrite(enblPin1, HIGH);
  delay(100);
  digitalWrite(enable2, LOW); // digitalWrite(enblPin1, LOW);

 
  motor1 = 10;//number of steps
  motor2 = 20;//number of steps

  ddir1=1;//dir 1 for CW 0 for CCW
  ddir2=1;//dir 1 for CW 0 for CCW
        delay(1000);
}


//#######################################
void OSP::init()
{
  low = 0;
  high = 3200;//Motor driver switch setting;

  _pgrad_x=(float)((float)(high-low)/360);
  _pgrad_y=(float)((float)(high-low)/180);

  stepx=0;
  stepy=0;
  low = 0;
high = 0;
x_rev_set = 0;
y_rev_set = 0;
valx = 0;
valy = 0;
_pgrad_x = 0;
_pgrad_y = 0;
stepx_new = 0;
stepy_new = 0;
degsH = 0;
degsV = 0;
degsH_new = 0;
degsV_new = 0;
  
  //Serial.println(_pgrad_x);
  }

//####################################
  int OSP::getPX() //Steps per revolution on X axis
  {
        return x_rev_set = 3200;//Change this as per the switch setting on the driver
    }
//#######################################

    int OSP::getPY() //Steps per revolution on Y axis
  {
        return y_rev_set = 3200;//Change this as per the switch setting on the driver
    }
    
  //#####################################  
	bool OSP::movx(bool dir, int step1, int dir1) //Move on X axis // ovx(bool dir, int pulPin, int dirPin)
  {
    int bytes_recv = 0;        
    char comm[5]="nost";
 
    comm[bytes_recv++] = Serial.read();
    //Serial.print("value of comm is ");
    //Serial.println(comm);
    while(strcmp(comm, "stop")!=0 || stopper)
  {
    //Serial.println("movx");
    //Serial.println(pulPin);
    if(dir==1)
    {
      
      if(stepx>=3200)
      {
     stepx=3200;
      }
        /*digitalWrite(dirPin, HIGH);
        digitalWrite(pulPin, HIGH);
        digitalWrite(pulPin, LOW); */
        else
        {
        digitalWrite(dir1, HIGH);
        digitalWrite(step1, HIGH);
        delay(10); 
        digitalWrite(step1, LOW);
        delay(10);
        
        stepx++;
        }
        
       //Serial.println(stepx);

    }
    else
    {
      if(stepx<=0)
      {
        stepx = 0;
        }
        else {
          /*digitalWrite(dirPin, LOW);
          digitalWrite(pulPin, HIGH);
          digitalWrite(pulPin, LOW);*/ 
          
           digitalWrite(dir1, LOW);
          digitalWrite(step1, HIGH);
           delay(10); 
           digitalWrite(step1, LOW);
          delay(10);

          stepx--;
          
        }
             
        //Serial.println(stepx);
     }
   //delay(50);
   while(Serial.available() > 0)
      comm[bytes_recv++] = Serial.read();
                //Serial.println(comm);
                //Serial.println("inside second while");
    //Safeguard...
    //Serial.println(stepx);
    if(bytes_recv>4)
    {
      break;
      
    }
   
}


  return true;
    }

    //#####################################  
  bool OSP::movy(bool dir,  int step2, int dir2) //Move on Y axis 
  // bool OSP::movy(bool dir,  int pulPin1, int dirPin1)
  {
     // Serial.print("stepx of axes ");    Serial.println(stepx);
    int bytes_recv = 0;        
    char comm[5]="nost";
 
    comm[bytes_recv++] = Serial.read();
    //Serial.print("value of comm is ");
    //Serial.println(comm);
    while(strcmp(comm, "stop")!=0)
  {
    if(dir==0)
    {
      if(stepy>=3200/4)
      {
     stepy=3200/4;
      }
      else
      {
    digitalWrite(dir2, LOW); // digitalWrite(dirPin1, HIGH);
    digitalWrite(step2, HIGH); // digitalWrite(pulPin1, HIGH); 
    delay(10);
    digitalWrite(step2, LOW);  // digitalWrite(pulPin1, LOW);
    delay(10); 
    stepy++; 
      }
    //Serial.println(stepy);

    }
    else
    {
      if(stepy<=0)
      {
        stepy=0;
      //Serial.println("stop");

        }
        else
        {
          digitalWrite(dir2, HIGH); // digitalWrite(dirPin1, LOW);
          digitalWrite(step2, HIGH); // digitalWrite(pulPin1, HIGH);
          delay(10); 
          digitalWrite(step2, LOW);  // digitalWrite(pulPin1, LOW);
          delay(10); 
          stepy--; 
        }
      //Serial.println(stepy);

      }

 
   //delay(50);
   while(Serial.available() > 0)
      comm[bytes_recv++] = Serial.read();
                //Serial.println(comm);
                //Serial.println("inside second while");
    //Safeguard...
    //Serial.println(stepy);
    if(bytes_recv>4)
    {
      break;
      //
    }
   
}

      
  return true;
    }

    //560 to 2420 << 590 2190
//#################################

float OSP::getX()
{
  /**
       * Returns current position on X axis
       * 
       * \return X position as radians to stellarium
       */

       //Serial.println(stepx);
  float valx;
  //valx = map(stepx, 0, 3200, 0, 360);
  valx = stepx*(float)(360.00/3200.00);
  valx = (float)(M_PI/180)*valx;
    //vlax = _deg2rad(valx);

  return valx;
}

float OSP::getY()
{
   /**
       * Returns current position on Y axis
       * 
       * \return Y position as radians to stellarium
       */
        //Serial.println(stepy);

  float valy;

  valy = stepy*(float)(360.00/3200.00);
//  valy = map(stepy, 0, 3200/2, 0, 180);
  valy = (float)(M_PI/180)*valy;
//  //vlay=_deg2rad(valy);

  return valy;
}

int OSP::getPx()
{
  /**
       * Return the number of steps per revolution of the Y axis
       *
       * \return Steps per revolution
       */

    return stepx;
  
}

int OSP::getPy()
{
    return stepy;
}


float OSP::_rad2deg(float rad){
//    return lrint( (float) (180.00/M_PI)*rad);
    return  (float) (180.00/M_PI)*rad;

}

float OSP::_deg2rad(float deg){
    return (float) (M_PI/180.00)*deg;
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
void OSP::goToRads(float x_rad, float y_rad)//give this input for debugging> movem_-4.5434_-2.5254
{
  
  float degsH = _rad2deg(x_rad);
  float degsV = _rad2deg(y_rad);

//if((degsH_new==degsH)
//if(degsV_new==degsV))
//if((degsH_new>degsH)
//{
//  }
//if(degsV_new>degsV))
//if((degsH_new<degsH)
//if(degsV_new<degsV))
//{
//}
//else if((degsH_new>degsH)||(degsV_new>degsV))
//
//{
//  degsH = degsH_new;
//  degsV = degsV_new;
  //Serial.println(degsH);
  //Serial.println(degsV);
_moveTo(degsH,degsV);
//  }

  //degsH = degsH+180;
  //degsV = 180-degsV;

  
}
//##################################################
void OSP::_moveTo(float x, float y, char* method)
{
  //stepx_new = map(abs(x), 0, 360, low, high);
  //stepy_new = map(abs(y), 0, 180, low, high);
 

  stepx_new = (3200*x)/360;//map to counts
  stepy_new = (3200*y)/360;//map to counts

//  if(((stepx-stepx_new)==0)||((stepy-stepy_new)==0))
//  {
//    stepx=0;
//    stepy=0;
//  }
//  else
//  {
//    stepx=stepx_new-stepx;
//    stepy=stepy_new-stepy;
    //}

//if((stepx_new>stepx)||(stepy_new>stepy))
//{
//  Serial.println("Forward");
//      stepx=stepx_new-stepx;
//      stepy=stepy_new-stepy;
//  }
//  else
//  {  Serial.println("Reverse");
//
//      stepx=stepx-stepx_new;
//      stepy=stepy-stepy_new;
//    }

stepx=stepx_new-stepx;
stepy=stepy_new-stepy;

 
  //Serial.println(stepx);
  //Serial.println(stepy);
  
 //_moveXY(stepx, stepy);
 //Serial.println("done_move");


    //Serial.println("done_move");


  
  //Serial.println(low);
  //Serial.println(high);
  //Serial.println(stepx_new);
  //Serial.println(stepy_new);

      //_moveDDA(stepx_new, stepy_new);
   _moveXY(stepx, stepy,true);
    stepx=stepx_new;
stepy=stepy_new;
//   //_moveEqua(stepx_new, stepy_new);
//   stepx=stepx_new;
//   stepy=stepy_new;  
}
//##################################################
void OSP::_moveXY(int x, int y, bool nodelay)
{
 

  if(y>3200/4) y = 3200/4; // This is to limit the Tilt Motor to 90 degree
  
  for(int count=0;count<abs(x);count++)
  {
    if(x<0)
    {
      digitalWrite(11, LOW); //       digitalWrite(11, LOW);
    }
    else
    {
      digitalWrite(11, HIGH); // digitalWrite(11, HIGH);
    }
    
    digitalWrite(10, HIGH); // digitalWrite(10, HIGH);
    delay(10); 
    digitalWrite(10, LOW);  // digitalWrite(10, LOW);
    //Serial.println(pulPin);
 
    delay(10);
    }

    for(int count=0;count<abs(y);count++)
  {
    if(y<0)
    {
      digitalWrite(8, HIGH);// digitalWrite(4, LOW);
    }
    else
    {
      digitalWrite(8, LOW); // digitalWrite(4, HIGH);
    }
    
    digitalWrite(7, HIGH); //  digitalWrite(3, HIGH);
    delay(10); 
    digitalWrite(7, LOW); // digitalWrite(3, LOW);
    delay(10);
    }

  }

void OSP::_moveEqua(int x, int y)
  {
    
  }

