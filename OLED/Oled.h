/*
	Oled.h - Oled Display library for Arduino & 4d Systems Serial OLEDs
	Copyright(c) 2010 Paul Karlik 
	Original Source Copyright(c)2007 Oscar Gonzalez

	Licensed under the MIT license: 
	http://www.opensource.org/licenses/mit-license.php
	
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
	THE SOFTWARE.
	
	16bitColor from RGB by YAPAN.org's small utilities for Arduino
	http://www.opensource.org/licenses/bsd-license.php
*/

#ifndef Oled_h
#define Oled_h

#include <inttypes.h>

#define OLED_BAUDRATE			57600
#define OLED_RESETPIN			8  
#define OLED_INITDELAYMS		1000

#define	OLED_DETECT_BAUDRATE	0x55

#define	OLED_CLEAR				0x45
#define	OLED_BKGCOLOR			0x42
#define	OLED_COPYPASTE			0x63

#define OLED_SAVE_CHAR			0x41
#define OLED_DISPLAY_CHAR		0x44

#define	OLED_LINE				0x4C
#define	OLED_CIRCLE				0x43
#define	OLED_CIRCLEFILL			0x69
#define	OLED_PUTPIXEL			0x50
#define	OLED_READPIXEL			0x52
#define	OLED_RECTANGLE			0x72
#define OLED_SETPEN				0x70
#define	OLED_SETFONTSIZE		0x46
#define	OLED_FONT5X7			0x01
#define	OLED_FONT8X8			0x02
#define	OLED_FONT8X12			0x03
#define	OLED_TEXTFORMATED		0x54

#define	OLED_COMMAND_CONTROL	0x59
#define	OLED_COMMAND_DISPLAY	0x01
#define	OLED_COMMAND_CONTRAST	0x02
#define	OLED_COMMAND_POWER		0x03

#define OLED_ACK				0x06
#define OLED_NAK 				0x15

class OLED
{

  public:
    OLED(uint8_t pinPower, uint8_t pinReset, uint8_t baudRate, uint8_t startUpTimer);

    uint8_t Init();   
    unsigned int get16bitRGB(uint8_t red, uint8_t green, uint8_t blue);
  
    
    uint8_t ResetDisplay();
	uint8_t Clear();
	uint8_t PutPixel(uint8_t x, uint8_t y, unsigned int color);
	uint8_t PenSize(uint8_t size);
	uint8_t DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, unsigned int color);
	uint8_t DrawRectangle(uint8_t x, uint8_t y, uint8_t width, uint8_t height, unsigned int color);
	uint8_t DrawCircle(uint8_t x, uint8_t y, uint8_t radius, unsigned int color);
	uint8_t SetFontSize(uint8_t FontType);
	uint8_t DrawText(uint8_t column, uint8_t row, uint8_t font_size, char *mytext, unsigned int color);
	uint8_t DrawSingleChar(uint8_t column, uint8_t row, uint8_t font_size, uint8_t MyChar, unsigned int color);
	uint8_t CopyPast(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t width, uint8_t height);
	uint8_t SaveBitChar(uint8_t slot, uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4, uint8_t data5, uint8_t data6, uint8_t data7, uint8_t data8);
	uint8_t DisplayBitChar(uint8_t slot, uint8_t x, uint8_t y, unsigned int color);
	
  private:
	uint8_t _pinReset;
	uint8_t _pinPower;
	uint8_t _baudRate;
	uint8_t _startUpTimer;
	
    void write(uint8_t value);
	  
};

#endif

