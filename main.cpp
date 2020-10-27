#include <stdio.h>
#include "mbed.h"
#include "rgb_lcd.h"
#include "Adafruit_SSD1306.h"
#include "Segment16.h"

// #if DEVICE_SPI_ASYNCH
// #error defined
// #else
// #error NOT DEFINED
// #endif

using namespace Segment16Display;

static I2C i2c(I2C_SDA , I2C_SCL);
rgb_lcd lcd(i2c);

BusIn enc(D4, D5, D6, D7);

// an SPI sub-class that provides a constructed default
class SPIPreInit : public SPI
{
   public:
      SPIPreInit(PinName mosi, PinName miso, PinName clk) : SPI(mosi,miso,clk)
      {
         format(8,3);
         frequency(5000000);
      };
};
DigitalOut spiDc(D9);
DigitalOut spiReset(D8);
DigitalOut spiCs(D10);
DigitalOut pin(PC_10);
SPIPreInit oledSpi(D11,D12,D13);

void spiDoneCallback( int argument ){
   spiCs = 1;    
   pin = 0;
}


class My_SSD1306_Spi : public Adafruit_SSD1306_Spi
{
   public:
   	My_SSD1306_Spi(SPI &spi, PinName DC, PinName RST, PinName CS, uint8_t rawHieght = 32, uint8_t rawWidth = 128) :
         Adafruit_SSD1306_Spi(spi, DC, RST, CS, rawHieght, rawWidth) {}

   protected: 
	void sendDisplayBuffer()
	{
		cs = 1;
		dc = 1;
		cs = 0;

		oledSpi.transfer<char>((const char*)buffer.data(), (int)buffer.size(), NULL, 0, 
			spiDoneCallback,
			SPI_EVENT_COMPLETE);
		// for(uint16_t i=0, q=buffer.size(); i<q; i++)
		// 	mspi.write(buffer[i]);

		// if(height() == 32)
		// {
		// 	for(uint16_t i=0, q=buffer.size(); i<q; i++)
		// 		mspi.write(0);
		// }

		// cs = 1;
	};
};

//Adafruit_SSD1306_Spi oled(oledSpi, D9, D8, D10, 64, 128);
My_SSD1306_Spi oled(oledSpi, D9, D8, D10, 64, 128);
Segment16 seg1(oled, 0, 10, 32, 44);
Segment16 seg2(oled, 32, 10, 32, 44);
Segment16 seg3(oled, 64, 10, 32, 44);
Segment16 seg4(oled, 96, 10, 32, 44);

int main(int argc, char ** argv)
{
   uint8_t value;
               // 0    1    2    3    4    5    6    7
   char hex[] = {'0', '1', '7', '6', '3', '2', '4', '5',
               // 8    9    A    B    C    D    E    F
                 'F', 'E', '8', '9', 'C', 'D', 'B', 'A'};

   printf("Starting...\r\n");
   enc.mode(PullUp);
   i2c.frequency(67600);
   lcd.begin(16,2);
   lcd.home();
   lcd.print("Position");

   ThisThread::sleep_for(1500);

   oled.fillScreen(0);
   oled.printf("%ux%u OLED Display\r\n", oled.width(), oled.height());
   oled.display();

   pin = 0;

   while(1)
   {
      lcd.setCursor(0, 1);
      value = (~enc.read())&0x0f;
      lcd.print(hex[value]);
      lcd.print(' ');
      lcd.print(value, HEX);

      seg1.SetCharacter(hex[value]);
      pin = 1;
      oled.display();
      ThisThread::sleep_for(1500);

      /*
      oled.fillScreen(0);
      oled.setTextCursor(0, 0);
      oled.printf("%ux%u OLED Display\r\n", oled.width(), oled.height());
      oled.display();

      ThisThread::sleep_for(1500);
      oled.fillScreen(1);
      oled.display();
      */

      // ThisThread::sleep_for(1500);
      // oled.fillScreen(0);
      // oled.drawFastHLine(0, 0, 128, 1);
      // oled.drawFastHLine(0, 63, 128, 1);
      // oled.drawFastVLine(0, 0, 64, 1);
      // oled.drawFastVLine(127, 0, 64, 1);
      // DrawSegment(xOffset, yOffset);
      // xOffset += 32;
      // DrawSegment(xOffset, yOffset);
      // xOffset += 32;
      // DrawSegment(xOffset, yOffset);
      // xOffset += 32;
      // DrawSegment(xOffset, yOffset);
      // oled.display();
      // seg1.AllOn();
      // seg2.AllOn();
      // seg3.AllOn();
      // seg4.AllOn();
      // oled.display();

   }

   return 0;
}

