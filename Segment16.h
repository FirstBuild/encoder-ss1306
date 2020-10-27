/*
 * Segment16.h
 *
 * A 16-segment LED analog for SSD1306 displays.
 * 
 * Author: Rob Bultman
 * License: MIT
 */

#ifndef SEGMENT_16_H
#define SEGMENT_16_H

#include "Adafruit_SSD1306.h"

namespace Segment16Display
{

   typedef struct Vertex
   {
      uint8_t x;
      uint8_t y;
   } Vertex;

   class Segment16 
   {
      public:
         Segment16(
               Adafruit_SSD1306_Spi &oledRef, 
               uint8_t xOff, 
               uint8_t yOff, 
               uint8_t w, 
               uint8_t h
               );
         void AllOn();
         void AllOff();
         void SetCharacter(char c);

      private:
         void DrawHorizLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t color);
         void DrawVertLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t color);
         void DrawDiagLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t color);
         void DrawSegment();
         void ClearDisplay();

      private:
         Adafruit_SSD1306_Spi &oled;
         uint8_t xOffset;
         uint8_t yOffset;
         uint8_t width;
         uint8_t height;
         uint8_t characterOffsetX;
         uint8_t characterOffsetY;
         uint8_t characterWidth;
         uint8_t characterHeight;
         uint8_t slant;
         Vertex vertexA;
         Vertex vertexB;
         Vertex vertexC;
         Vertex vertexD;
         Vertex vertexE;
         Vertex vertexF;
         Vertex vertexG;
         Vertex vertexH;
         Vertex vertexI;
   };
}

#endif // SEGMENT_16_H

