//////////////////////////////////////////////////////////////////////
// 4D Systems OLED Display Template | GOLDELOX-SGC Processor
// Paul J Karlik | Cubtastic71@gmail.com | www.byte-mechanic.com
// 
// 10.09.09 - Working framework for Video and Image Processing
//
//////////////////////////////////////////////////////////////////////

#include <Oled.h>
#include <string.h>

// Int an Define the Base Vars and Params ////////////////////////////

#define DIGI_A        3
#define DIGI_B        12
#define DIGI_C        11

OLED myOLED(7,8,2500,57600);

int color=0;
int tick = 3;

int ax =random(1,50);
int ay =random(1,10);
int ag = 1;
int af =3;

int bx =random(50,90);
int by =random(30,60);
int bg = 3;
int bf =2;

int xdelay;

int latch=0;

// Set Up Function ///////////////////////////////////////////////////

void setup(){
  
  Serial.begin(57600);
  pinMode(10, OUTPUT);
  digitalWrite(10,HIGH);
  myOLED.Init();
  myOLED.Clear();
  
}

// Main Program Loop  ////////////////////////////////////////////////

void loop(){
 
    if(digitalRead(DIGI_B)!=1){
     delayMicroseconds(1);
     myOLED.Clear();
    }

    if(digitalRead(DIGI_C)!=0){
     tick++; 
      if (tick>5){tick=0;}
      delay(10);
    }

    if(digitalRead(DIGI_A)!=0){
      xdelay=200;
    }else{
      xdelay=0; 
    } 
    
    switch(tick){
      case 0:
           color = myOLED.get16bitRGB(random(255),random(255),random(255));
           break;
      case 1:
           color = myOLED.get16bitRGB(0,0,random(255));
           break;
      case 2:
           color = myOLED.get16bitRGB(0,random(255),0);
           break;
      case 3:
           color = myOLED.get16bitRGB(random(255),0,0);
           break;    
      case 4:
           color = myOLED.get16bitRGB(255,255,random(255));
           break;
      case 5:
           color = myOLED.get16bitRGB(random(155),255,random(155));
           break;           
      default:
           color = myOLED.get16bitRGB(random(255),random(255),random(255));
    }
    

 
 ax+=ag;
 if(ax>91){ax=90;ag=random(3)+1;ag*=-1;}
 if(ax<8){ax=9;ag=random(2)+1;}
  
 ay+=af;
 if(ay>60){ay=61;af=random(2)+1;af*=-1;}
 if(ay<8){ay=9;af=random(3)+1;}

 bx+=bg;
 if(bx>91){bx=90;bg=random(2)+1;bg*=-1;}
 if(bx<8){bx=9;bg=random(3)+1;}
 
 by+=bf;
 if(by>61){by=60;bf=random(2)+1;bf*=-1;}
 if(by<8){by=9;bf=random(3)+1;}
 

 myOLED.DrawLine(ax, ay, bx, by, color );
 myOLED.DrawLine(96-ax, ay, 96-bx, by, color );
 
 delay(xdelay);

}
