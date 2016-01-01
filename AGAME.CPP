

#include <bios.h>
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

// BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN,
// LIGHTGRAY, DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN,
// LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE and BLINK
#define true 1
#define false 0

struct point {
	int 	x;
	int 	y;
};

char dtext[200];

#define DIR_UP      1
#define DIR_DOWN    3
#define DIR_RIGHT   0
#define DIR_LEFT    2

int min_up =20;
int max_down = 460;
int min_left = 50;
int max_right = 600;

struct torch {
	point 	p;
	int     dir;
	int 	radius;
	double 	angle;
	int 	color;
	int 	steps;
	int player;
};

#define MAX_TORCH 5

torch t[MAX_TORCH];
torch me;

int pi =  3.14159265;

// it can be different on each monitor's resolution
int maxwidth = 640;
int maxheight = 480;
int endgame = false;

void initialisetorchs()
{
    // 640 * 480
	for (int i = 0; i < MAX_TORCH; i++)
	{
		t[i].p.x      = 100+rand()%200;
		t[i].p.y      = 100+rand()%400;
		t[i].radius   = 50;
		t[i].dir      = rand()%3;
		t[i].angle    = t[i].dir * 90;
		t[i].player   = i+1;
	}
	me.p.x      = maxwidth/2;
	me.p.y      = maxheight/2;
	me.angle    = 90;
	me.radius   = 60;
	me.dir      = DIR_UP;
	me.player   = 0;
};

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

	maxwidth =  getmaxx() + 1;
	maxheight = getmaxy() + 1;

    // set the background color
	setbkcolor(BLACK);
    // set the foreground color
	setcolor(WHITE);
    // draw a white color border with rectangle
	rectangle(0,0,getmaxx(),getmaxy());
	return 1;
}

point pointatangle(int x, int y, int radius, double angle)
{
	point ret;
	//double slope = atan(angle);
	//ret.x = x  + radius / sqrt(1 + slope * slope);
	//ret.y = y  + radius * slope / sqrt(1 + slope * slope);
	ret.x = x + radius * cos(angle);
	ret.y = y + radius * sin(angle);
	//sprintf(dtext,"%f %f ", angle, cos(angle));
	//outtext(dtext);

	return ret;

}

void drawrect(point& p1, point& p2)
{
	rectangle(p1.x, p1.y, p2.x, p2.y);
}


void
mypieslice(int x, int y, int sangle, int eangle, int radius)
{
	sangle = sangle % 360;
	eangle = eangle % 360;

	setcolor(YELLOW);
	struct arccoordstype arcinfo;
	arc(x, y,sangle, eangle, radius);
	getarccoords(&arcinfo);
	//setfillstyle(2,CYAN);
	line(x,y,arcinfo.xstart, arcinfo.ystart);
	line(x,y,arcinfo.xend, arcinfo.yend);
	floodfill((arcinfo.xstart+arcinfo.xend)/2, (arcinfo.ystart+arcinfo.yend)/2,YELLOW);
	//circle((arcinfo.xstart+arcinfo.xend)/2, (arcinfo.ystart+arcinfo.yend)/2,25);
	int x1 = (arcinfo.xstart+arcinfo.xend)/2;
	int y1 = (arcinfo.ystart+arcinfo.yend)/2;
	int x2 = (x1 + 5*x)/6;
	int y2 = (y1 + 5*y)/6;
	floodfill(x2,y2,YELLOW);
	//circle(x2,y2,6);

}

double pdist(point& f, point& p1, point& p2)
{
	double d1 = abs( (p2.y-p1.y)*f.x - (p2.x - p1.x)*f.y + p2.x * p1.y - p2.y * p1.x);
	double d2 =  sqrt((p2.y - p1.y) * (p2.y - p1.y) + (p2.x - p1.x) * (p2.x - p1.x));
	return d1/d2;
}

void drawtorch(torch& tr)
{
	setcolor(WHITE);
		   // red circle at torch centre
	//moveto(t[i].p.x,t[i].p.y);
	if (tr.player == 0)
	{
		setcolor(YELLOW);
		setfillstyle(SOLID_FILL,YELLOW);
	}
	else
	{
		setcolor(CYAN);
		setfillstyle(SOLID_FILL,CYAN);

	}
	circle(tr.p.x,tr.p.y,4);
	// start torch light
	moveto(tr.p.x,tr.p.y);
	struct arccoordstype arcinfo;
	mypieslice(tr.p.x, tr.p.y,tr.angle - 15, tr.angle+15, tr.radius);
}

void changeposition(torch& tr)
{
	switch(tr.dir)
	{
		case DIR_UP:
		{
			if (tr.p.y <= min_up)
			{
				tr.dir = DIR_DOWN;
			}
			else
			{
				tr.p.y -= 1;
			}
			break;
		}
		case DIR_DOWN:
		{
			if (tr.p.y >= max_down)
			{
				tr.dir = DIR_UP;
			}
			else
			{
				tr.p.y += 1;
			}
			break;
		}
		case DIR_RIGHT:
		{
			if (tr.p.x >= max_right)
			{
				tr.dir = DIR_LEFT;
			}
			else
			{
				tr.p.x += 1;
			}

			break;
		}
		case DIR_LEFT :
		{

			if (tr.p.x <= min_left)
			{
				tr.dir = DIR_RIGHT;
			}
			else
			{
				tr.p.x -= 1;
			}


			break;
		}
	}
	return;
}

void moveme(torch& tr)
{
	switch(tr.dir)
	{
		case DIR_UP:
		{
			if (tr.p.y <= min_up)
			{
			}
			else
			{
				tr.p.y -= 2;
			}
			break;
		}
		case DIR_DOWN:
		{
			if (tr.p.y >= max_down)
			{
			}
			else
			{
				tr.p.y += 2;
			}
			break;
		}
		case DIR_RIGHT:
		{
			if (tr.p.x >= max_right)
			{
			}
			else
			{
				tr.p.x += 2;
			}

			break;
		}
		case DIR_LEFT :
		{

			if (tr.p.x <= min_left)
			{
			}
			else
			{
				tr.p.x -= 2;
			}


			break;
		}
	}
	return;
}

void handlekeypress() {
	char ch = getch();
	switch (ch)
	{
		case 72: // upward
		{
			me.dir = DIR_UP;
			me.angle = 90;
			break;
		}
		case 75: // left
		{
			me.dir = DIR_LEFT;
			me.angle = 180;
			break;
		}
		case 77: // right
       	{
			me.dir = DIR_RIGHT;
			me.angle = 0;
			break;
       	}
       	case 80: // down
	    {

	    	me.dir = DIR_DOWN;
	    	me.angle = 270;
	    	break;
	    }
	    case 27:
	    case 65:
	    {
	    	endgame = true;
	    	break;
	    }
	    default:
	    {
	    	break;
	    }

	}
	return;
}


void main()
{
	if(InitGraphics() == -1)
		return;

	initialisetorchs();

	while(1)
	{
		delay(20);

		clearviewport();

		setcolor(WHITE);

		if (kbhit())
		{
			handlekeypress();
		}
		if (endgame == true)
		{
			break;
		}

		for (int i = 0; i < MAX_TORCH; i++)
		{
			drawtorch(t[i]);
		}
		moveme(me);
		drawtorch(me);

		for (i = 0; i < MAX_TORCH; i++)
		{
			//t[i].angle = t[i].angle + 1;
			if (t[i].angle >= 360)
				t[i].angle -= 360;
			changeposition(t[i]);
			if (t[i].p.x > maxwidth/4 &&
			    t[i].p.x < 3*maxwidth/4 &&
			    t[i].p.y > maxheight/4 &&
			    t[i].p.y < 3*maxheight/4 &&
			    rand() % 200 < 2)
			{
			    t[i].dir = rand()%3;
			}
			t[i].angle    = t[i].dir * 90;
		}
		changeposition(me);
	}
}


/*
Names	Value	Means  Fill With...
EMPTY_FILL	0	Background color
SOLID_FILL	1	Solid fill
LINE_FILL	2	---
LTSLASH_FILL	3	///
SLASH_FILL	4	///, thick lines
BKSLASH_FILL	5	\\\, thick lines
LTBKSLASH_FILL	6	 \\\
HATCH_FILL	7	Light hatch
XHATCH_FILL	8	Heavy crosshatch
INTERLEAVE_FILL	9	Interleaving lines
WIDE_DOT_FILL	10	Widely spaced dots
CLOSE_DOT_FILL	11	Closely spaced dots
USER_FILL	12	User-defined fill pattern
*/

/*
bar(50, 50, 590, 430);
setfillstyle(SOLID_FILL,RED);
putpixel(random(439)+101,  random(279)+101,random(16));
*/

