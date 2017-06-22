#include <stdio.h>
#include <string.h>
#include <math.h>
//#include "CoordsLib.h"
#include "AxesLib.h"
#include <Servo.h>

/**
 * Output pin for the STEP on X axis of the stepper controller (horizontal)
 */
int servoPin1 =9;

/**
 * Output pin for the STEP on Y axis of the stepper controller (vertical)
 */
int servoPin2 = 10;

/**
 * Output pin to control the laser pointer
 */
int laserPin = 8;

/**
 * Library for control the device: stepper motors, sensors, current position..
 */
AxesLib	Axes = AxesLib();

/**
 * Initializes the serial port and sets pins to control the device
 */
 String m_data,sac_data,salt_data;
void setup(){
	Serial.begin(9600);
        //myservo.attach(9,500,2100);///ATTACH servo
	//Serial.println("init");
	
	pinMode(laserPin, OUTPUT);
	laserOff();
	
	Axes.setMotorsPins(servoPin1, servoPin2);
 
	}

/**
 * Turn the laser On
 */
void laserOn(){
	digitalWrite(laserPin, HIGH);
}

/**
 * Turn the laser Off
 */
void laserOff(){
	digitalWrite(laserPin, LOW);
}

/*
 * Get a float value from the serial port, and send the '_OK_' ack string.
 * The value must conains six decimals, in a string with 9 bytes, including sign and decimal dot.
 * Examples: '-0.036526', '+5.238388'
 *
 * \return float.
 */
/*float serialGetFloat(){
	char bytes[9], sign;
	int nbytes = 0;
	float fex;
	bool recv = false;
	
	bytes[8] = '\0';
	Serial.println("float");
  //Serial.flush();
	while(!recv){
		if (Serial.available() > 0) {
			sign = Serial.read();//Float with eight representation bytes (including dot and sign)
			while(nbytes < 8)
				if(Serial.available() > 0){
					bytes[nbytes] = Serial.read();
					nbytes++;
				}
			fex = strtod(bytes, NULL);
			if(sign=='-')
				fex = 0.0 - fex;
			recv = true;
		}
	}
	//Serial.println("_OK_");
	return fex;
}*/
void getAcAlt(){
  char bytes[20];
  //char *m,*sac,*salt;
  //String m_data,sac_data,salt_data;
  int nbytes = 0;
  bool recv=false;
  while(!recv){
    //Serial.println(recv);
  while(nbytes < 13){
    //Serial.println("Inside nbytes");Serial.println(nbytes);
    if(Serial.available() > 0){
      bytes[nbytes] = Serial.read();
      nbytes++;
    }
    recv=true;
  }
  }

 

  ///*################################
  //m_-4.54_-2.52
 //Serial.println(bytes);

String data= String(bytes);
data.trim();
int len=data.length();
//Serial.println(data);
//Serial.println(len);
data.remove(13,len-11);
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
sac_data.remove(5,len-5);

//Serial.println(sac_data);

len=salt_data.length();
//Serial.println(len);
salt_data.remove(0,len-5);
//Serial.println(salt_data);
//###############################*/
 /*
  char* strarr;
  strarr=strtok(bytes,"_");
  int scount=0;
  while(strarr != NULL ){
    //Serial.println(strarr);
     switch(scount){
       case 1:
         Serial.println(strarr);//strcpy(m,strarr);
       case 2:
         Serial.println(strarr);//strcpy(sac,strarr);
       case 3:
         Serial.println(strarr);//strcpy(salt,strarr);
     }
     strarr=strtok(NULL,"_");
     scount++;
  }  
  //delay(1000);
  //Serial.println(sac);//Serial.println(sac);
  //Serial.println("salt = ");Serial.println(salt);*/
}


/**
 * Main loop..
 *
 * Obtains and executes the commands received by the serial port
 * 
 * Avaliable commands:
 * 
 *-	'init' () -> (float px, float py)	Initializes the device and returns the steps by revolution obtained
 *- 'time' (float t)  -> ()		Sets initial observation time
 *- 'set1' (float ar, float dec, float t, float ac, float alt) -> ()	Sets the first reference object
 *-	'set2' (float ar, float dec, float t, float ac, float alt) -> ()	Sets the second reference object
 *-	'set3' (float ar, float dec, float t, float ac, float alt) -> ()	Sets the third reference object (usually not used..)
 *-	'goto' (float ar, float dec, float t) -> (float ar, float dec)(float ac, float alt)		Points the device towards the received equatorial coordinates
 *-	'move' () -> (float px, float py)(float ar, float dec)(float ac, float alt)		Points the device towards the received horizontal coordinates
 *-	'movx' (char dir) -> (float ar, float dec)(float ac, float alt)		Starts the accelerated horizontal movement towards the indicated direction
 *-	'movy' (char dir)	Starts the accelerated vertical movement towards the indicated direction
 *-	'stop' () -> ()		Stops the movements initiated by movx or movy commands
 *-	'laon' () -> ()		Turn the laser On
 *-	'loff' () -> ()		Turn the laser Off
 */
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
   delay(10); 
    Serial.println("float");
    getAcAlt();
   Axes.goToRads(sac_data.toFloat(),salt_data.toFloat());
   delay(10);
    Serial.println("done_move");
  }
  if(strcmp(comm, "movl")==0){
    mov_end=Axes.movx(false);
    if(mov_end)
    Serial.println("done_movl");
  }	
  else if(strcmp(comm, "movr")==0){
    mov_end=Axes.movx(true);
      if(mov_end)
        Serial.println("done_movr");
  }    
  else if(strcmp(comm, "movu")==0){
    mov_end=Axes.movy(false);
    if(mov_end)
      Serial.println("done_movu");
  }
  else if(strcmp(comm, "movd")==0){
    mov_end=Axes.movy(true);
    if(mov_end)//==false)
      Serial.println("done_movd");
  }
  else if(strcmp(comm, "init")==0){
    Axes.init();
    Serial.println("done_init");
  }else if(strcmp(comm, "laon")==0){
    laserOn();
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
  }else{ 
  //iniSerial.println(comm);
  }
}

