#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include "Segment16.h"
#include "Segment16Font.h"

#ifndef PI
#define PI 3.14159265
#endif

namespace Segment16Display
{

   void Segment16::DrawHorizLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t color)
   {
      oled.drawLine(x1, y1-1, x2, y2-1, color);
      oled.drawLine(x1, y1, x2, y2, color);
      oled.drawLine(x1, y1+1, x2, y2+1, color);
   }

   void Segment16::DrawVertLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t color)
   {
      oled.drawLine(x1-1, y1, x2-1, y2, color);
      oled.drawLine(x1, y1, x2, y2, color);
      oled.drawLine(x1+1, y1, x2+1, y2, color);
   }

   void Segment16::DrawDiagLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t color)
   {
      int slope;
      if (x2 < x1)
      {
         std::swap(x1, x2);
         std::swap(y1, y2);
      }
      slope = (y2 - y1)/(x2 - x1);
      if (slope < 0)
      {
         oled.drawLine(x1+1, y1, x2, y2-1, color);
         oled.drawLine(x1, y1, x2, y2, color);
         oled.drawLine(x1, y1+1, x2-1, y2, color);
      }
      else
      {
         oled.drawLine(x1, y1-1, x2-1, y2, color);
         oled.drawLine(x1, y1, x2, y2, color);
         oled.drawLine(x1+1, y1, x2, y2+1, color);
      }
   }

   /*
    * Vertices
    * A B C
    * D E F
    * G H I
    */

   void Segment16::SetCharacter(char c)
   {
      uint16_t pattern;

      if (c < FONT_FIRST_CHARACTER || c > FONT_LAST_CHARACTER)
      {
         return;
      }

      ClearDisplay();

      pattern = fontTable[c - FONT_FIRST_CHARACTER];

      if (pattern & SegmentMaskA) DrawHorizLine(vertexA.x, vertexA.y, vertexB.x, vertexB.y, 1);
      if (pattern & SegmentMaskB) DrawHorizLine(vertexB.x, vertexB.y, vertexC.x, vertexC.y, 1);
      if (pattern & SegmentMaskH) DrawVertLine(vertexA.x, vertexA.y, vertexD.x, vertexD.y, 1);
      if (pattern & SegmentMaskG) DrawVertLine(vertexD.x, vertexD.y,vertexG.x, vertexG.y, 1);
      if (pattern & SegmentMaskC) DrawVertLine(vertexC.x, vertexC.y, vertexF.x, vertexF.y, 1);
      if (pattern & SegmentMaskD) DrawVertLine(vertexF.x, vertexF.y, vertexI.x, vertexI.y, 1);
      if (pattern & SegmentMaskF) DrawHorizLine(vertexG.x, vertexG.y, vertexH.x, vertexH.y, 1);
      if (pattern & SegmentMaskE) DrawHorizLine(vertexH.x, vertexH.y, vertexI.x, vertexI.y, 1);
      if (pattern & SegmentMaskU) DrawHorizLine(vertexD.x, vertexD.y, vertexE.x, vertexE.y, 1);
      if (pattern & SegmentMaskP) DrawHorizLine(vertexE.x, vertexE.y, vertexF.x, vertexF.y, 1);
      if (pattern & SegmentMaskM) DrawVertLine(vertexB.x, vertexB.y, vertexE.x, vertexE.y, 1);
      if (pattern & SegmentMaskS) DrawVertLine(vertexE.x, vertexE.y, vertexH.x, vertexH.y, 1);
      if (pattern & SegmentMaskK) DrawDiagLine(vertexA.x, vertexA.y, vertexE.x, vertexE.y, 1);
      if (pattern & SegmentMaskN) DrawDiagLine(vertexE.x, vertexE.y, vertexC.x, vertexC.y, 1);
      if (pattern & SegmentMaskT) DrawDiagLine(vertexG.x, vertexG.y, vertexE.x, vertexE.y, 1);
      if (pattern & SegmentMaskR) DrawDiagLine(vertexE.x, vertexE.y, vertexI.x, vertexI.y, 1);
   }

   void Segment16::DrawSegment()
   {
      ClearDisplay();
      // segment A
      DrawHorizLine(vertexA.x, vertexA.y, vertexB.x, vertexB.y, 1);
      // segment B
      DrawHorizLine(vertexB.x, vertexB.y, vertexC.x, vertexC.y, 1);
      // segment H
      DrawVertLine(vertexA.x, vertexA.y, vertexD.x, vertexD.y, 1);
      // segment G
      DrawVertLine(vertexD.x, vertexD.y,vertexG.x, vertexG.y, 1);
      // segment C
      DrawVertLine(vertexC.x, vertexC.y, vertexF.x, vertexF.y, 1);
      // segment D
      DrawVertLine(vertexF.x, vertexF.y, vertexI.x, vertexI.y, 1);
      // segment F
      DrawHorizLine(vertexG.x, vertexG.y, vertexH.x, vertexH.y, 1);
      // segment E
      DrawHorizLine(vertexH.x, vertexH.y, vertexI.x, vertexI.y, 1);
      // segment U
      DrawHorizLine(vertexD.x, vertexD.y, vertexE.x, vertexE.y, 1);
      // segment P
      DrawHorizLine(vertexE.x, vertexE.y, vertexF.x, vertexF.y, 1);

      // segment M
      DrawVertLine(vertexB.x, vertexB.y, vertexE.x, vertexE.y, 1);
      // segment S
      DrawVertLine(vertexE.x, vertexE.y, vertexH.x, vertexH.y, 1);
      // segment K
      DrawDiagLine(vertexA.x, vertexA.y, vertexE.x, vertexE.y, 1);
      // segment N
      DrawDiagLine(vertexE.x, vertexE.y, vertexC.x, vertexC.y, 1);
      // segment u
      DrawDiagLine(vertexG.x, vertexG.y, vertexE.x, vertexE.y, 1);
      // segment R
      DrawDiagLine(vertexE.x, vertexE.y, vertexI.x, vertexI.y, 1);

      // lower left dp
      oled.fillRect(
            width - 3 + xOffset, 
            characterOffsetY + characterHeight - 3 + yOffset, 
            3, 3, 1);
      // upper right dp
      oled.fillRect(
            1 + xOffset, 
            characterOffsetY + 1 + yOffset, 
            3, 3, 1);

      // oled.drawLine(xOffset, yOffset, xOffset + width - 1, yOffset, 1);
      // oled.drawLine(xOffset + width - 1, yOffset, xOffset + width - 1, yOffset + height, 1);
      // oled.drawLine(xOffset, yOffset, xOffset, yOffset + height, 1);
      // oled.drawLine(xOffset, yOffset + height, xOffset + width - 1, yOffset + height, 1);
   }

   void Segment16::AllOn()
   {
      DrawSegment();
   }

   void Segment16::ClearDisplay()
   {
      oled.fillRect(xOffset, yOffset, width, height, 0);
   }

   void Segment16::AllOff()
   {
      ClearDisplay();
      oled.display();
   }

   Segment16::Segment16(
         Adafruit_SSD1306_Spi &oledRef, 
         uint8_t xOff, 
         uint8_t yOff, 
         uint8_t w, 
         uint8_t h
         ):oled(oledRef), xOffset(xOff), yOffset(yOff), width(w), height(h)
   {
      characterWidth = (uint8_t)((float)width * 0.4/0.787);
      characterHeight = (uint8_t)((float)height * 0.795/1.091);
      slant = characterHeight * tan(12.0 * PI / 180.0);
      characterOffsetX = (width - characterWidth - slant)/2;
      characterOffsetY = (height - characterHeight)/2;
      vertexA.x = characterOffsetX + slant + xOffset;
      vertexA.y = characterOffsetY + yOffset;
      vertexB.x = characterOffsetX + slant + (characterWidth/2) + xOffset;
      vertexB.y = characterOffsetY + yOffset;
      vertexC.x = characterOffsetX + slant + characterWidth + xOffset;
      vertexC.y = characterOffsetY + yOffset;
      vertexD.x = characterOffsetX + (slant/2) + xOffset;
      vertexD.y = characterOffsetY + (characterHeight/2) + yOffset;
      vertexE.x = characterOffsetX + (slant/2) + (characterWidth/2) + xOffset;
      vertexE.y = characterOffsetY + (characterHeight/2) + yOffset;
      vertexF.x = characterOffsetX + (slant/2) + characterWidth + xOffset;
      vertexF.y = characterOffsetY + (characterHeight/2) + yOffset;
      vertexG.x = characterOffsetX + xOffset;
      vertexG.y = characterOffsetY + characterHeight + yOffset;
      vertexH.x = characterOffsetX + (characterWidth/2) + xOffset;
      vertexH.y = characterOffsetY + characterHeight + yOffset;
      vertexI.x = characterOffsetX + characterWidth + xOffset;
      vertexI.y = characterOffsetY + characterHeight + yOffset;

      printf("Character Width:    %d\r\n", characterWidth);
      printf("Character Height:   %d\r\n", characterHeight);
      printf("Character X Offset: %d\r\n", characterOffsetX);
      printf("Character Y Offset: %d\r\n", characterOffsetY);
      printf("Slant:              %d\r\n", slant);
   };

}
