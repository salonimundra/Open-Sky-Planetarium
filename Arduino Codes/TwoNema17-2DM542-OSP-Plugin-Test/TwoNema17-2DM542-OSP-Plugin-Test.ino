#include <stdio.h>
#include <string.h>
#include <math.h>
#include "OSP.h"

/** 
 * Declarations for stepper motor 1 (at the base)
 * All the pins below are connected to digital pins of Arduino Nano.
 */
 
#define dir1 11 
#define step1 12 
#define enable1 10 

#define relay1 2
#define relay2 4
#define relay3 5
#define relay4 6

/**
 * Declarations for stepper motor 2 (at top holding LASER)
 */
#define dir2 8 
#define step2 9 
#define enable2 7 

/**
 * Digital pin to control the LASER 
 * This pin is connected to gate (G) of IRF540
 */
int laserPin = 3;

 
/**
 * Library for control the device. 
 */
OSP Axes = OSP();
String m_data, sac_data, salt_data; // to store LASER coorinates 

void setup(){
	Serial.begin(9600);	
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  pinMode(relay3,OUTPUT);
  pinMode(relay4,OUTPUT);
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  pinMode(laserPin, OUTPUT);
	laserOff();
  Axes.setMotorsPins(dir1, step1, enable1, dir2, step2, enable2);
	Axes.delayValue = 10; // to adjust motor speed as Coarse and Fine 
 
	}
 

/**
 * Turn LASER on at given intensity 
 */
void laserOn(int intensity){
  analogWrite(laserPin, intensity);
  }

/**
 * Turn LASER Off
 */
void laserOff(){
	digitalWrite(laserPin, LOW);
}


void getAcAlt(){
  char bytes[40];
  int nbytes = 0;
  bool recv=false;
  while(!recv){
  while(nbytes < 17){
    if(Serial.available() > 0){
      bytes[nbytes] = Serial.read();
      nbytes++;
    }
    recv=true;
  }
  }

 
/**
 * As LASER coordinates, we receive string like movem_-4.5434_-2.5254.
 * This string is chunked to extract ac and alt values. 
 */

  String data= String(bytes);
  data.trim();
  int len=data.length();
  m_data=data;
  sac_data=data;
  salt_data=data;
  m_data.remove(1,len-1);
  sac_data.remove(0,2);
  len=sac_data.length();
  sac_data.remove(7,len-7);
  len=salt_data.length();
  salt_data=salt_data.substring(10,17);    
}


void loop(){
  float ac, alt;
  char comm[5];
  int bytes_recv = 0;
  bool mov_end;                                                     
  comm[4]='\0';
  while(bytes_recv < 4){
    //Waiting for a command from serial monitor 
    if (Serial.available() > 0)
      comm[bytes_recv++] = Serial.read();
      
  }
  if(strcmp(comm, "move")==0){
    Serial.println("float");
    getAcAlt();
    Serial.println("done_move");
    Axes.goToRads(sac_data.toFloat(),salt_data.toFloat());
  }
  
  if(strcmp(comm, "movl")==0){
    mov_end=Axes.movx(false,step1,dir1); 
    if(mov_end)
      Serial.println("done_movl");
  }	
  
  else if(strcmp(comm, "movr")==0){
    mov_end=Axes.movx(true,step1,dir1); 
    if(mov_end)
      Serial.println("done_movr");
  } 
     
  else if(strcmp(comm, "movu")==0){
    mov_end=Axes.movy(false,step2,dir2); 
    if(mov_end)
      Serial.println("done_movu");
  }
  
  else if(strcmp(comm, "movd")==0){
    mov_end=Axes.movy(true,step2,dir2); 
    if(mov_end)
      Serial.println("done_movd");
  }
  
  else if(strcmp(comm, "init")==0){
    delay(1000);
    digitalWrite(relay1,LOW);
    digitalWrite(relay2,LOW);
    digitalWrite(relay3,LOW);
    digitalWrite(relay4,LOW);
    Axes.init();
    Serial.println("done_init");
  }
  
  else if(strcmp(comm, "laon")==0){
    laserOn(50);
    Serial.println("done_laon");
  }
  
  else if(strcmp(comm, "loff")==0){
    laserOff();		
    Serial.println("done_loff");
  }
  else if(strcmp(comm, "post")==0){
    ac=Axes.getX();
    alt=Axes.getY();
    Serial.print("t_");
    Serial.print(ac,6);
    Serial.print("_");
    Serial.println(alt,6);
  }
  
  else if(strcmp(comm,"stop")==0){
   Axes.stopper=1;
  }
     
  else if(strcmp(comm,"coad")==0){
    Axes.delayValue = 3; 
    Serial.println("done_high_speed"); 
  }
  
  else if(strcmp(comm,"fiad")==0){
    Axes.delayValue = 10; 
    Serial.println("done_low_speed");
  }
  else if(strcmp(comm,"clos")==0){
    digitalWrite(relay1, HIGH);
    digitalWrite(relay2, HIGH);
    digitalWrite(relay3, HIGH);
    digitalWrite(relay4, HIGH);
    laserOff(); 
    Serial.println("done_close");
    
  }
  else if(strcmp(comm,"lase")==0){
    Serial.println("done_lase");
    char bytes[40];
    int nbytes = 0;
    bool recv=false;
    while(!recv){
      while(nbytes < 4){
        if(Serial.available() > 0){
          bytes[nbytes] = Serial.read();
          nbytes++;
    }
      recv=true;
  }
  }
  String data= String(bytes);
  int intensity=data.toInt();
  laserOn(intensity);
  }
  
  else{ 
  }
}

