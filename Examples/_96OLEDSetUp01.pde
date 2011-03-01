//////////////////////////////////////////////////////////////////////
// 4D Systems OLED Display Template | GOLDELOX-SGC Processor
// Paul J Karlik | Cubtastic71@gmail.com | www.byte-mechanic.com
// 
// 10.09.09 - Working framework for Video and Image Processing
//
//////////////////////////////////////////////////////////////////////

#include <oled.h>
#include <string.h>

// Int an Define the Base Vars and Params ////////////////////////////

#define DIGI_A        13
#define DIGI_B        12
#define DIGI_C        11

 OLED myOLED = OLED(7,8,2500,57600);

// Set Up Function ///////////////////////////////////////////////////

void setup(){
  Serial.begin(57600);
  myOLED.Init();
  myOLED.Clear();
}

// Main Program Loop  ////////////////////////////////////////////////

void loop(){
  
  delay(100);
  
}
