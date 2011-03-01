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

#define DIGI_A        13
#define DIGI_B        12
#define DIGI_C        11

int colorX = 100;
int tick = 0;
int temp = 0;
int del = 1200;
int latch = 1;
int button[3]={DIGI_C,DIGI_B,DIGI_A};

OLED myOLED(7,8,2500,57600);


// Set Up Function ///////////////////////////////////////////////////

void setup(){
  
  Serial.begin(57600);
  pinMode(10, OUTPUT);
  digitalWrite(10,HIGH);
  myOLED.Init();
  myOLED.Clear();
  
  myOLED.SaveBitChar(0,0,108,254,254,124,56,16,0);
  myOLED.SaveBitChar(1,240,252,254,231,194,66,102,63);
  myOLED.SaveBitChar(2,7,31,63,115,33,33,51,126);
  myOLED.SaveBitChar(3,35,168,232,104,8,80,240,224);
  myOLED.SaveBitChar(4,98,10,11,10,8,5,7,3);  
  
}

// Main Program Loop  ////////////////////////////////////////////////

void loop(){
 
tick++;
if(tick>del){
colorX = myOLED.get16bitRGB(random(255),random(255),random(255));

  if (random(300)>270){
    int tempx= random(3,78);
    int tempy =random(3,46);
    myOLED.DisplayBitChar(2,tempx,tempy,colorX);
    //myOLED.DisplayBitChar(1,tempx+8,tempy,colorX);
    //myOLED.DisplayBitChar(4,tempx,tempy+8,colorX);
    //myOLED.DisplayBitChar(3,tempx+8,tempy+8,colorX);
  }


  if(digitalRead(button[1])==HIGH){
    latch=1;
  }
  if(digitalRead(button[0])==HIGH){
    latch=2;
  }
    if(digitalRead(button[2])==HIGH){
    latch=3;
  }
  

temp++;
if (temp>2){
  temp=0;
  
switch (latch) {
   case 1:
   myOLED.CopyPast(0,0,1,1,47,31);
   myOLED.CopyPast(49,0,48,1,47,31);
   myOLED.CopyPast(0,33,1,32,47,31);
   myOLED.CopyPast(49,33,48,32,47,31);
   break;
   case 2:
   myOLED.CopyPast(0,0,1,0,47,64);
   myOLED.CopyPast(49,0,48,0,47,64);
   break;
   case 3:
   myOLED.CopyPast(0,0,0,1,96,31);
   myOLED.CopyPast(0,33,0,32,96,31);
   break;
}
}

}


 
}
