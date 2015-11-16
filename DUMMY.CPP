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

struct torch {
        int x;
	int y;
	int xdir;
	int ydir;
	int rad;
	int angle;
	int color;
	int steps;
};

torch tr[4];

struct {
    int x;
    int y;
    int xdir;
    int ydir;
    int rad;
    int angle;
}
me;

int InitGraphics() {
    int grd, grm;
    int gresult;
    // Detect the graphics driver and mode
    detectgraph( & grd, & grm);
    // initialize the graphics mode with initgraph
    initgraph( & grd, & grm, "c:\\TC\\BGI");

    gresult = graphresult();
    if (gresult != grOk) {
        printf(grapherrormsg(gresult));
	getch();
        return -1;
    }

    // set the background color
    setbkcolor(BLACK);
    // set the foreground color
    setcolor(WHITE);
    // draw a white color border with rectangle
    rectangle(0, 0, getmaxx(), getmaxy());
    return 1;
}

void main() {
    int i, x, y, w;
    int left, top, right, bottom;
    int margin;
    int xradius, yradius;
    int cx, cy;

    int numt = 4;


    if (InitGraphics() == -1)
	return;

    int xmax = getmaxx();
    int ymax = getmaxy();

    for (i = 0; i < numt; i++) {
	tr[i].x = 100 + i * 60;
	tr[i].y = 100 + i * 80;
	tr[i].rad = 30;
	tr[i].steps = 0;
    }
    tr[0].color = YELLOW;
    tr[1].color = BLUE;
    tr[2].color = WHITE;
    tr[3].color = BLUE;

    tr[0].xdir = 1;
    tr[1].xdir = 0;
    tr[2].xdir = -1;
    tr[3].xdir = 0;

    tr[0].ydir = 0;
    tr[1].ydir = -1;
    tr[2].ydir = 0;
    tr[3].ydir = 1;

    me.x = 500;
    me.y = 400;
    me.xdir = 1;
    me.ydir = 0;

    //rectangle(me.x, me.y, me.x + 5, me.y + 5);

    int endgame = 0;
    int step = 2;
    int idle = 0;
    i = 100;
    int xdir = 1;
    int ydir = 0;
    int j = 100;
    while (1) {
	// erase torch
	// erase me
	// if key move me
	// move torch
	// draw torch and me

	// erase
	setcolor(BLACK);
	for (i = 0; i < numt; i++) {
	    circle(tr[i].x, tr[i].y, tr[i].rad);
	    tr[i].steps++;
	}
	rectangle(me.x, me.y, me.x + 5, me.y + 5);
	// erase complete

	idle++;

	if (kbhit()) {
	    idle = 0;
	    char ch = getch();
	    switch (ch) {
	    case 72: // upward
		me.xdir = 0;
		me.ydir = -1;
		break;
	    case 75: // left
		me.xdir = -1;
		me.ydir = 0;
		break;
	    case 77: // right
		me.xdir = 1;
		me.ydir = 0;
		break;
	    case 80: // down
		me.xdir = 0;
		me.ydir = 1;
		break;
	    case 27:
		endgame = 1;
		break;
	    }
	}
	if (endgame)
	    break;

	setcolor(WHITE);

	me.x = me.x + me.xdir;
	me.y = me.y + me.ydir;

	rectangle(me.x, me.y, me.x + 5, me.y + 5);

	for (i = 0; i < numt; i++) {
	    if (tr[i].steps > 50) {
		int r = rand() % 10;
		switch (r) {
		case 1: //left
		    tr[i].xdir = -1;
		    tr[i].ydir = 0;
		    tr[i].steps = 0;
		    break;
		case 2: // right
		    tr[i].xdir = 1;
		    tr[i].ydir = 0;
		    tr[i].steps = 0;
		    break;
		case 3: // up
		    tr[i].xdir = 0;
		    tr[i].ydir = -1;
		    tr[i].steps = 0;
		    break;
		case 4: // down
		    tr[i].xdir = 0;
		    tr[i].ydir = 1;
		    tr[i].steps = 0;
		    break;
		}
	    }

	    tr[i].x = tr[i].x + tr[i].xdir;
	    tr[i].y = tr[i].y + tr[i].ydir;

	    if (tr[i].xdir) {
		if (tr[i].x > xmax - 30)
		    tr[i].xdir = -1;
		if (tr[i].x < 30)
		    tr[i].xdir = 1;
	    }

	    if (tr[i].ydir) {
		if (tr[i].y > ymax - 30)
		    tr[i].ydir = -1;
		if (tr[i].y < 30)
		    tr[i].ydir = 1;
	    }

	    setfillstyle(SOLID_FILL, BLUE);

	    circle(tr[i].x, tr[i].y, tr[i].rad);

	    if (0 && idle) {
		if (idle > 5000)
		    delay(20);
		else if (idle > 500)
		    delay(10);
		else if (idle > 50)
		    delay(5);
	    }
	    delay(10);

	}
    }

    getch();
    closegraph();
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

