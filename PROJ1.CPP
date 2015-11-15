#include <graphics.h>
#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <string.h>
#include <alloc.h>
#include <bios.h>
#include <math.h>

int InitGraphics()
{
      int grd, grm;
      int gresult;
      // Detect the graphics driver and mode
      detectgraph(&grd,&grm);
      // initialize the graphics mode with initgraph
      initgraph(&grd, &grm, "c:\\TC\\BGI");

      gresult = graphresult();
      if(gresult != grOk)
      {
	    printf(grapherrormsg(gresult));
	    getch();
	    return -1;
      }

      // set the background color
      setbkcolor(BLACK);
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


      printf("ok\n");
      getch();

      if(InitGraphics() == -1)
	    return;


	    int xmax =  getmaxx();
	    int ymax = getmaxy();

      int xpos = rand() % xmax;
      int ypos = rand() % ymax;
      int color = rand() % 12;
      putpixel(xpos, ypos, color);

      i = 100;
      int xdir = 1;
      int ydir = 0;
      int j =100;
      while (1)
      {

	   if (kbhit()) {
	     break;
	   }
	   delay(10);
	   setcolor(BLACK);
	   circle(i,j,20);
	   setcolor(WHITE);

	   int r = rand() % 300;
	   switch(r){

	      case 1:   //left
		  xdir = -1;
		  ydir = 0;
		  break;
	      case 2:  // right
		  xdir = 1;
		  ydir = 0;
		  break;
	       case 3:   // up
		  xdir = 0;
		  ydir = -1;
		  break;
	       case 4:   // down
		  xdir = 0;
		  ydir = 1;
		  break;
	   }

	   if (xdir == 0 && ydir == 0)
	      xdir = 1;

	   if (xdir) {
	       if (i > xmax - 30)
			xdir = -1;
		if (i < 30)
			xdir = 1;
	   }

	   if (ydir) {
	       if (j > ymax - 30)
			ydir = -1;
		if (j < 30)
			ydir = 1;
	   }


	   i += xdir;
	   j += ydir;
	   circle(i, j, 20);
      }

      // fill an ellipse will BLUE color SOLID
      // setfillstyle(SOLID_FILL, BLUE);
      // fillellipse(cx, cy, xradius, yradius);
      // outtextxy(cx - 95, cy - yradius + 20, "fillellipse 0-360 deg");
      // fill a sector (pie) with close dot fill
      // setfillstyle(CLOSE_DOT_FILL, GREEN);
      // sector(cx, cy, 0, 270, xradius - 30, yradius - 40);
      // outtextxy(cx - 30, cy - 50, "sector 0-270 deg");
      // setcolor(YELLOW);
      // moveto(cx + 5, cy + 5);
      // linerel(xradius - 30, 0);
      // ellipse(cx + 5, cy + 5, 270, 0, xradius - 30, yradius - 40);
      // circle(right, top, 25);
      // Draw pie slice
      // setfillstyle(SOLID_FILL, GREEN);
      // pieslice(right, top, 0, 90, 25);
      // Draw arc
      // arc(right, top, 0, 90, 35);


      getch();
      closegraph();
}
