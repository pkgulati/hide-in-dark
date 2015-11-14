#include <graphics.h>
#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
 
int InitGraphics()
{
      int grd, grm;
      int gresult;
      // Detect the graphics driver and mode
      detectgraph(&grd,&grm);
      // initialize the graphics mode with initgraph
      initgraph(&grd, &grm, "");
 
      gresult = graphresult();
      if(gresult != grOk)
      {
            printf(grapherrormsg(gresult));
            getch();
            return -1;
      }
 
      // set the background color
      setbkcolor(RED);
      // set the foreground color
      setcolor(WHITE);
      // draw a white color border with rectangle
      rectangle(0,0,getmaxx(),getmaxy());
      return 1;
}
 
void main()
{
      int i, x, y, w;
      int left,top,right,bottom;
      int margin;
      int xradius, yradius;
      int cx, cy;
 
      if(InitGraphics() == -1)
            return;
 
      margin = 100; // 100 pixel margin
      left = margin;
      top = margin;
      bottom = getmaxy() - margin;
      right = getmaxx() - margin;
      xradius = (right - left) / 2;
      yradius = (bottom - top) / 2;
      cx = (left + right) / 2;
      cy = (top + bottom) / 2;
 
 
      // fill an ellipse will BLUE color SOLID
      setfillstyle(SOLID_FILL, BLUE);
      fillellipse(cx, cy, xradius, yradius);
      outtextxy(cx - 95, cy - yradius + 20, "fillellipse 0-360 deg");
 
      // fill a sector (pie) with close dot fill
      setfillstyle(CLOSE_DOT_FILL, GREEN);
      sector(cx, cy, 0, 270, xradius - 30, yradius - 40);
      outtextxy(cx - 30, cy - 50, "sector 0-270 deg");
 
      // draw an elipitical arc and have two ends of arc joined with center point by two lines
      setcolor(YELLOW);
      moveto(cx + 5, cy + 5);
      linerel(xradius - 30, 0);
      moveto(cx + 5, cy + 5);
      linerel(0,yradius - 40);
      ellipse(cx + 5, cy + 5, 270, 0, xradius - 30, yradius - 40);
      outtextxy(cx + 20, cy + 30, "Ellipse 270-360 deg");
 
      setcolor(WHITE);
 
      // Draw circles
      circle(left, top, 25);
      circle(right, top, 25);
      circle(left, bottom, 25);
      circle(right, bottom, 25);
 
      // Draw pie slice
      setfillstyle(SOLID_FILL, GREEN);
      pieslice(right, top, 0, 90, 25);
      pieslice(left, top, 90, 180, 25);
      pieslice(left, bottom, 180, 270, 25);
      pieslice(right, bottom, 270, 360, 25);
 
      // Draw arc
      arc(right, top, 0, 90, 35);
      arc(left, top, 90, 180, 35);
      arc(left, bottom, 180, 270, 35);
      arc(right, bottom, 270, 360, 35);
 
 
      getch();
      closegraph();
}
 