#include "Oled.h"

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "WProgram.h"


OLED::OLED(uint8_t pinPower, uint8_t pinReset, uint8_t baudRate, uint8_t startUpTimer){

  _pinReset = pinReset;
  _pinPower = pinPower;
  _baudRate = baudRate;
  _startUpTimer = startUpTimer;
   
  pinMode(_pinPower, OUTPUT);
  pinMode(_pinReset, OUTPUT);
  digitalWrite(_pinPower, HIGH);
  //pinMode(_pinReset, OUTPUT);

}

void OLED::write(uint8_t value) {
  Serial.print(value, BYTE);
}

char GetResponse()
{
	byte incomingByte = OLED_ACK;
	while (!Serial.available()) { delayMicroseconds(150); }
	incomingByte = Serial.read();
	return incomingByte;
}

uint8_t OLED::Init()
{
	ResetDisplay();  
	delay(OLED_INITDELAYMS);
	Serial.write(OLED_DETECT_BAUDRATE); 
	GetResponse(); 
}

// YAPAN.org's small utilities for Arduino //
unsigned int OLED::get16bitRGB(uint8_t red, uint8_t green, uint8_t blue) 
{
  uint8_t r = red >> 3;  						// red: 0-31
  uint8_t g = green >> 2;  						// green: 0-63
  uint8_t b = blue >> 3; 						// blue: 0-31

  unsigned int bitRGB = (r << 11) + (g << 5) + b;
  return bitRGB;
}

uint8_t OLED::Clear()
{
	Serial.write(OLED_CLEAR);
    GetResponse();
}

uint8_t OLED::ResetDisplay()
{
	digitalWrite(OLED_RESETPIN, LOW);
	delay(10);                  
	digitalWrite(OLED_RESETPIN, HIGH);
	delay(10);             
}

uint8_t OLED::PutPixel(uint8_t x, uint8_t y, unsigned int color)
{
	Serial.write(OLED_PUTPIXEL);
	Serial.write(x);						// X
	Serial.write(y);						// Y

	// Color
	Serial.write(color >> 8);				// MSB			
	Serial.write(color & 0xFF);				// LSB

    GetResponse();
}

uint8_t OLED::PenSize(uint8_t size) {
  Serial.write(OLED_SETPEN);
  Serial.write(size);
   
  GetResponse();
}

uint8_t OLED::DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, unsigned int color)
{

	Serial.write(OLED_LINE);

	Serial.write(x1);						// X1
	Serial.write(y1);						// Y1
	Serial.write(x2);						// X2
	Serial.write(y2);						// Y2

	// Color
	Serial.write(color >> 8);				// MSB			
	Serial.write(color & 0xFF);			// LSB

    GetResponse();

}

uint8_t OLED::DrawRectangle(uint8_t x, uint8_t y, uint8_t width, uint8_t height, unsigned int color)
{

	Serial.write(OLED_RECTANGLE); 

	Serial.write(x);						// X1
	Serial.write(y);						// Y1
	Serial.write(x+width);					// X2
	Serial.write(y+height);					// Y1

	// Color
	Serial.write(color >> 8);				// MSB			
	Serial.write(color & 0xFF);				// LSB				
	
	GetResponse();
}

uint8_t OLED::DrawCircle(uint8_t x, uint8_t y, uint8_t radius, unsigned int color)
{
    
    Serial.write(OLED_CIRCLE);

	Serial.write(x);						// X
	Serial.write(y);						// Y
	Serial.write(radius);					// Radius

	// Color
	Serial.write(color >> 8);				// MSB			
	Serial.write(color & 0xFF);				// LSB

    GetResponse();

}

uint8_t OLED::SetFontSize(uint8_t FontType)
{
    
    Serial.write(OLED_SETFONTSIZE);
    Serial.write(FontType);
    
    GetResponse();
}

uint8_t OLED::DrawText(uint8_t column, uint8_t row, uint8_t font_size, char *mytext, unsigned int color)
{

	Serial.write(0x73);						// Formated Text
        
    // Adjust to center of the screen (26 Columns at font size 0)
    int newCol = 13 - (strlen(mytext)/2);
   
    Serial.write(column); 					// Column    
	Serial.write(row); 						// Row
			
	Serial.write(font_size); 				// Font Size
	
	// Color
	Serial.write(color >> 8);				// MSB			
	Serial.write(color & 0xFF);				// LSB

	for (int i=0 ; i<strlen(mytext) ; i++)
	{
		Serial.print(mytext[i]); 			// character to write
	}
	
	Serial.print(0x00, BYTE); 				// string terminator (always 0x00)

    GetResponse();

}


uint8_t OLED::DrawSingleChar(uint8_t column, uint8_t row, uint8_t font_size, uint8_t MyChar, unsigned int color)
{

	Serial.write(OLED_TEXTFORMATED);
	
    Serial.write(MyChar);
    Serial.write(column);
    Serial.write(row);
        
	// Color
	Serial.write(color >> 8);				// MSB			
	Serial.write(color & 0xFF);				// LSB

    GetResponse();

}

uint8_t OLED::CopyPast(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t width, uint8_t height)
{

	Serial.write(OLED_COPYPASTE);

	Serial.write(x1);						// X1
	Serial.write(y1);						// Y1
	Serial.write(x2);						// X2
	Serial.write(y2);						// Y2

	Serial.write(width);					// Box Width	
	Serial.write(height);					// Box Height

    GetResponse();

}

uint8_t OLED::SaveBitChar(uint8_t slot, uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4, uint8_t data5, uint8_t data6, uint8_t data7, uint8_t data8  )
{

	Serial.write(OLED_SAVE_CHAR);

	Serial.write(slot);						// Char Slot
	Serial.write(data1);					// Data 1
	Serial.write(data2);					// Data 2
	Serial.write(data3);					// Data 3
	Serial.write(data4);					// Data 4
	Serial.write(data5);					// Data 5
	Serial.write(data6);					// Data 6
	Serial.write(data7);					// Data 7
	Serial.write(data8);					// Data 8

    GetResponse();

}


uint8_t OLED::DisplayBitChar(uint8_t slot, uint8_t x, uint8_t y, unsigned int color)
{

	Serial.print(OLED_DISPLAY_CHAR, BYTE);

	Serial.write(slot);						// Char Slot
	Serial.write(x);						// X
	Serial.write(y);						// Y
	
	// Color
	Serial.write(color >> 8);				// MSB			
	Serial.write(color & 0xFF);				// LSB

    GetResponse();

}








