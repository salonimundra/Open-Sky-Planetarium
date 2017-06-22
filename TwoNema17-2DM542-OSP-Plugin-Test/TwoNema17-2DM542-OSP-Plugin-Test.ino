#include <stdio.h>
#include <string.h>
#include <math.h>
//#include "CoordsLib.h"
#include "OSP.h"
// step dir enable 
// 10 11 12 7 8 9 
// Declarations for stepper motor 1 (at the base)
#define dir1 11
#define step1 10
//int ms1_1=10;
//int ms1_2=11;
//int ms1_3=12;
#define enable1 12

// Declarations for stepper motor 2 (at the top holding the laser)
#define dir2 8 
#define step2 7 
//int ms2_1=7;
//int ms2_2=8;
//int ms2_3=9;
#define enable2 9
//int ResolutionPin = 12;

#define ledPin 13 //  LED pin

#define ddir1 0
#define ddir2 0
#define motor1 0
#define motor2 0

#define sensor1 A2
#define sensor2 A3 

/* 
#define pulPin 10 // step of stepper motor 
#define dirPin  11 // direction of stepper motor 
#define pulPin1 3
#define dirPin1 4
#define enblPin1 5

#define ledPin 13
#define ddir1 0
#define ddir2 0
#define motor1 0
#define motor2 0

#define sensor1 7
#define sensor2 8

*/

/**
 * Output pin to control the laser pointer
 */
int laserPin = 6;


/**
 * Library for control the device: stepper motors, sensors, current position..
 */
OSP Axes = OSP();

//Axes.pulPin =10;
//Axes.dirPin = 11;
//Axes.enblPin = 12;
//Axes.pulPin1 = 3;
//Axes.dirPin1 = 4;
//Axes.enblPin1 = 5;
//Axes.ledPin = 13;
//Axes.ddir1;
//Axes.ddir2;
//
//Axes.motor1;
//Axes.motor2;

/**
 * Initializes the serial port and sets pins to control the device
 */
 String m_data,sac_data,salt_data;
 void(* resetFunc) (void) = 0;
void setup(){
	Serial.begin(9600);
        //myservo.attach(9,500,2100);///ATTACH servo
	//Serial.println("init");
	
  pinMode(laserPin, OUTPUT);
  //pinMode(ResolutionPin, OUTPUT);
  //digitalWrite(ResolutionPin,HIGH);
	laserOff();

  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);

  Axes.setMotorsPins(dir1, step1, enable1, dir2, step2, enable2, ledPin, ddir1, ddir2, motor1, motor2, sensor1,sensor2);
	
	//Axes.setMotorsPins(pulPin, dirPin, enblPin, pulPin1, dirPin1, enblPin1, ledPin, ddir1, ddir2, motor1, motor2, sensor1,sensor2);
 
	}

/**
 * Turn the laser On
 */
void laserOn(int intensity){
analogWrite(laserPin, intensity);
}

/**
 * Turn the laser Off
 */
void laserOff(){
	digitalWrite(laserPin, LOW);
}

void getAcAlt(){
  char bytes[40];
  //char *m,*sac,*salt;
  //String m_data,sac_data,salt_data;
  int nbytes = 0;
  bool recv=false;
  while(!recv){
    //Serial.println(recv);
  while(nbytes < 17){
    //Serial.println("Inside nbytes");Serial.println(nbytes);
    if(Serial.available() > 0){
      bytes[nbytes] = Serial.read();
      nbytes++;
    }
    //Serial.println(bytes);
    recv=true;
  }
  }

 

  ///*################################
  //     movem_-4.5434_-2.5254
 //Serial.println(bytes);

String data= String(bytes);
data.trim();
int len=data.length();
//Serial.println(data);
//Serial.println(len);
//data.remove(17,len-11);
//Serial.println("-----------");
//Serial.println(data);
//delay(20);
m_data=data;
sac_data=data;
salt_data=data;

m_data.remove(1,len-1);
//Serial.println(m_data);

sac_data.remove(0,2);
len=sac_data.length();
//Serial.println(len);
sac_data.remove(7,len-7);


len=salt_data.length();
//Serial.println(len);

salt_data=salt_data.substring(10,17);


}


void loop(){
  float ac, alt;
  char comm[5];
  char dir;
  int bytes_recv = 0;
  bool mov_end;
  int ret;                                                      //Added to check val of PX
  comm[4]='\0';
  while(bytes_recv < 4){
    //Waiting for a command...
    if (Serial.available() > 0)
      comm[bytes_recv++] = Serial.read();
      
  }
  if(strcmp(comm, "move")==0){
   //delay(10); 
    //Serial.println("float");
    Serial.println("float");
    getAcAlt();
        Serial.println("done_move");
   Axes.goToRads(sac_data.toFloat(),salt_data.toFloat());
  }
  if(strcmp(comm, "movl")==0){
    mov_end=Axes.movx(false,step1,dir1); // mov_end=Axes.movx(false,pulPin,dirPin);
    if(mov_end)
    Serial.println("done_movl");
  }	
  else if(strcmp(comm, "movr")==0){
    mov_end=Axes.movx(true,step1,dir1); // mov_end=Axes.movx(true,pulPin,dirPin);
      if(mov_end)
        Serial.println("done_movr");
  }    
  else if(strcmp(comm, "movu")==0){
    mov_end=Axes.movy(false,step2,dir2); // mov_end=Axes.movy(false,pulPin1,dirPin1);
    if(mov_end)
      Serial.println("done_movu");
  }
  else if(strcmp(comm, "movd")==0){
    mov_end=Axes.movy(true,step2,dir2); // mov_end=Axes.movy(true,pulPin1,dirPin1);
    if(mov_end)//==false)
      Serial.println("done_movd");
  }
  else if(strcmp(comm, "init")==0){
    Axes.init();
    Serial.println("done_init");
  }else if(strcmp(comm, "laon")==0){
    laserOn(50);
    Serial.println("done_laon");
  }else if(strcmp(comm, "loff")==0){
    laserOff();		
    Serial.println("done_loff");
  }else if(strcmp(comm, "post")==0){
    ac=Axes.getX();
    alt=Axes.getY();
    Serial.print("t_");
    Serial.print(ac,6);
    Serial.print("_");
    Serial.println(alt,6);
  }else if(strcmp(comm,"stop")==0){
   //TODO: IF not detected inside the movx function create a function to stop movement 
   Axes.stopper=1;
  }
  else if(strcmp(comm,"rest")==0){
   resetFunc();  
   }
  else if(strcmp(comm,"moff")==0){
    digitalWrite(A0, HIGH);
    delay(100);
    digitalWrite(A1, HIGH);
    delay(100);
    Serial.println("done_motor_off");
    
  }
  else if(strcmp(comm,"moon")==0){
    digitalWrite(A0, LOW);
    delay(100);
    digitalWrite(A1, LOW);
    delay(100);
    Serial.println("done_motor_on");
  }
  else if(strcmp(comm,"lase")==0){
    Serial.println("done_lase");
    char bytes[40];
    int nbytes = 0;
  bool recv=false;
  while(!recv){
    //Serial.println(recv);
  while(nbytes < 4){
    //Serial.println("Inside nbytes");Serial.println(nbytes);
    if(Serial.available() > 0){
      bytes[nbytes] = Serial.read();
      nbytes++;
    }
    //Serial.println(bytes);
    recv=true;
  }
  }
  String data= String(bytes);
  int intensity=data.toInt();
  laserOn(intensity);
  }
  else{ 
  //Serial.println(comm);
  }
}

