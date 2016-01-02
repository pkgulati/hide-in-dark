

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

#define DIR_RIGHT   0
#define DIR_UP      1
#define DIR_LEFT    2
#define DIR_DOWN    3


struct torch {
	point 	p;
	int     dir;
	int 	radius;
	double 	angle;
	int 	color;
	int 	steps;
	int 	mustturn;
	int     player;
	int 	score;
	int wrongsteps;
};

#define MAX_TORCH 3
#define MAX_DIAMONDS 5

point diamonds[MAX_DIAMONDS];

torch t[MAX_TORCH];
torch me;

int pi =  3.14159265;
int width = 7;
int ohalf = 3;
int boardwidth  = 540;
int boardheight = 480;
int endgame = false;
int maxx = 128;
int maxy = 96;
int board[128][96];
int min_up = 10;
int max_down = 458;
int min_left = 10;
int max_right = 500;


void initialisedata()
{
    // 640 * 480

	for (int i = 0; i < maxx; i++)
	{
		for (int j=0; j < maxy; j++)
		{
			board[i][j] = -1;
		}
	}

	for (i = 0; i < MAX_TORCH; i++)
	{
		t[i].radius   = 40;
		t[i].dir      = DIR_RIGHT;
		if (i == 1 || i == 3)
		{
			t[i].p.x  = 50*width+ohalf;
		}
		else
		{
			t[i].p.x  = 4*width+ohalf;
		}
		t[i].p.y      = (4*i+5)*width+ohalf;
		t[i].angle    = t[i].dir * 90;
		t[i].player   = i+1;
		t[i].steps    = 0;
		t[i].wrongsteps = 0;
		t[i].mustturn = 0;
		t[i].score    = 0;
	}
	t[0].color = BLUE;
	t[1].color = CYAN;
	t[2].color = RED;
	t[3].color = GREEN;
	t[4].color = MAGENTA;
	me.p.x      = 40*width+ohalf;
	me.p.y      = 40*width+ohalf;
	me.angle    = 90;
	me.radius   = 40;
	me.dir      = DIR_UP;
	me.player   = 0;
	me.steps    = 0;
	me.color = YELLOW;
	me.score ++;
	me.mustturn = 0;
	me.wrongsteps = 0;
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

    // set the background color
	setbkcolor(BLACK);
    // set the foreground color
	setcolor(WHITE);
    // draw a white color border with rectangle
	rectangle(0,0,getmaxx(),getmaxy());

	return 1;
}


void drawrect(point& p1, point& p2)
{
     rectangle(p1.x, p1.y, p2.x, p2.y);
}

void showbox(torch& tr)
{
      setcolor(tr.color);
      setfillstyle(SOLID_FILL,tr.color);
      bar(tr.p.x-ohalf,tr.p.y-ohalf,tr.p.x+ohalf,tr.p.y+ohalf);
}
void showhead(torch& tr)
{
      setcolor(BLACK);
      setfillstyle(SOLID_FILL,BLACK);
      switch(tr.dir)
      {
	case DIR_UP:
		bar(tr.p.x-1,tr.p.y-2,tr.p.x+1,tr.p.y-4);
		break;
	case DIR_DOWN:
		bar(tr.p.x-1,tr.p.y+2,tr.p.x+1,tr.p.y+4);
		break;
	case DIR_LEFT:
		bar(tr.p.x-2,tr.p.y-1,tr.p.x-4,tr.p.y+1);
		break;
	case DIR_RIGHT:
		bar(tr.p.x+2,tr.p.y-1,tr.p.x+4,tr.p.y+1);
		break;
      }
}

void drawtorch(torch& tr)
{
	showbox(tr);
	showhead(tr);
}

void adjustpos(torch& tr)
{
    int x = tr.p.x / width;
    tr.p.x = width*x + ohalf;
    int y = tr.p.y / width;
    tr.p.y = width*y + ohalf;
}

void turnright(torch& tr)
{
  tr.dir += 3;
  tr.dir  = tr.dir%4;
  tr.angle    = tr.dir * 90;
}

void turnleft(torch& tr)
{
  tr.dir += 1;
  tr.dir  = tr.dir%4;
  tr.angle    = tr.dir * 90;
}

void turnrightleft(torch& tr)
{
  if (rand()%2 == 0)
     tr.dir += 1;
  else
     tr.dir += 3;
  tr.dir  = tr.dir%4;
  tr.angle    = tr.dir * 90;
}

void turnanyside(torch& tr)
{
  tr.dir += rand()%3;
  tr.dir  = tr.dir%4;
  tr.angle    = tr.dir * 90;
  adjustpos(tr);
}


void moveit(torch& tr)
{
	switch(tr.dir)
	{
		case DIR_UP:
		{
			tr.p.y--;
			break;
		}
		case DIR_DOWN:
		{
			tr.p.y++;
			break;
		}
		case DIR_RIGHT:
		{
			tr.p.x ++;
			break;
		}
		case DIR_LEFT :
		{
			tr.p.x--;
			break;
		}
	}
	tr.steps++;
	return;
}

int adjustdir(torch& tr)
{
  switch(tr.dir)
  {
     case DIR_UP:
     {
	if (tr.p.y <= min_up)
	{
	   turnrightleft(tr);
	   tr.p.y = min_up;
	   tr.mustturn = rand()%10 * width;
	   return true;
	}
	break;
     }
     case DIR_DOWN:
     {
	if (tr.p.y >= max_down)
	{
	   turnrightleft(tr);
	   tr.p.y = max_down;
	   tr.mustturn = rand()%10 * width;
	   return true;
	}
	break;
     }
     case DIR_RIGHT:
     {
	  if (tr.p.x >= max_right)
	  {
	      turnrightleft(tr);
	      tr.mustturn = rand()%10 * width;
	      tr.p.x = max_right;
	      return true;
	  }
	  break;
     }
     case DIR_LEFT :
     {
	if (tr.p.x <= min_left)
	{
	     turnrightleft(tr);
	     tr.mustturn = rand()%10 * width;
	     tr.p.x = min_left;
	     return true;
	}
	break;
     }
  }
  return false;
}


void handlekeypress() {
   char ch = getch();
   switch (ch)
   {
	 case 72: // upward
	 {
	     me.dir = DIR_UP;
	     me.angle = 90;
	     adjustpos(me);
	     break;
	 }
	 case 75: // left
	 {
		me.dir = DIR_LEFT;
		me.angle = 180;
		adjustpos(me);
		break;
	 }
	case 77: // right
	{
	     me.dir = DIR_RIGHT;
	     me.angle = 0;
	     adjustpos(me);
	     break;
	}
	case 80: // down
	{
	    me.dir = DIR_DOWN;
	    me.angle = 270;
	    adjustpos(me);
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

void showdebug(char *ch)
{
	setfillstyle(1,RED);
	setcolor(WHITE);
	bar(20,450,20+500, 480);
	outtextxy(25,452, ch);
}

void showscore()
{
	setfillstyle(1,me.color);
	setcolor(BLACK);
	char stext[50];
	sprintf(stext, "%d ", me.score);
	bar(550,220,550+100,220+30);
	outtextxy(555,230, stext);

	for (int i = 0; i < MAX_TORCH; i++)
	{

		setfillstyle(1,t[i].color);
		setcolor(WHITE);

		char stext[50];
		sprintf(stext, "%d ", t[i].score);
		bar(550,250+30*i,550+100,250+30*i+30);
		outtextxy(555,260+30*i, stext);
	}
}

void setboard()
{
	for (int i = 0; i < maxx; i++)
	{
		for (int j = 0; j < maxy; j++)
		{
			board[i][j] = -1;
		}
	}
}

void updatescore(torch& tr)
{
	int x = tr.p.x % width;
	int y = tr.p.y % width;
	if (x == ohalf && y == ohalf)
	{
		int i = tr.p.x / width;
		int j = tr.p.y / width;
		if (board[i][j] != -1)
		{
		   if (board[i][j] != tr.player)
		   {
		       // square does not belong to player
		       if (tr.player == 0)
		       {
			   me.score = me.score -2;
			   t[board[i][j]-1].score++;
		       }
		       else
		       {
			   tr.score--;
			   if (board[i][j] == 0)
				me.score = me.score + 1;
			   else
				t[board[i][j]-1].score++;
		       }
		       // change owner of sqaure
		       board[i][j]=tr.player;
		       tr.wrongsteps++;
		    }
		    else
		    {
			// square belongs to same player
			tr.wrongsteps++;
		    }

		}
		else
		{
		   board[i][j]=tr.player;
		   tr.score++;
		   tr.wrongsteps =0;
		}

	}
}

int ahead(torch& tr)
{
	if (tr.p.x % width != ohalf ||
	   tr.p.y % width != ohalf)
	{
		return true;
	}
	int x = tr.p.x;
	int y = tr.p.y;
	switch(tr.dir)
	{
		case DIR_UP:
		     y = y+width;
		     break;
		case DIR_DOWN:
			y =y-width ;
			break;
		case DIR_RIGHT:
			x = x + width;
			break;
		case DIR_LEFT :
			x = x - width;
			break;
	}
	int i = x / width;
	int j = y / width;
	if (board[i][j] == -1)
		return true;
	return false;
}

int right(torch &tr)
{
	if (tr.p.x % width != ohalf ||
	   tr.p.y % width != ohalf)
	{
		return true;
	}

	int x = tr.p.x;
	int y = tr.p.y;
	switch(tr.dir)
	{
		case DIR_UP:
		     x = x+ width;
		     break;
		case DIR_DOWN:
			 x = x -width;
			break;
		case DIR_RIGHT:
			y = y+ width;
			break;
		case DIR_LEFT :
			y = y-width;
			break;
	}
	int i = x / width;
	int j = y / width;
	if (board[i][j] == -1)
		return true;
	return false;
}

int left(torch &tr)
{
	if (tr.p.x % width != ohalf ||
	   tr.p.y % width != ohalf)
	{
		return true;
	}

	int x = tr.p.x;
	int y = tr.p.y;
	switch(tr.dir)
	{
		case DIR_UP:
		     x = x - width;
		     break;
		case DIR_DOWN:
		       x = x + width;
			break;
		case DIR_RIGHT:
			y = y-width;
			break;
		case DIR_LEFT :
			y = y+width;
			break;
	}

	int i = x / width;
	int j = y / width;
	if (board[i][j] == -1)
		return true;

	return false;
}

void choose(torch& tr)
{
	if (tr.p.x % width != ohalf ||
	   tr.p.y % width != ohalf)
	{
		return;
	}
	if (tr.wrongsteps <= 21 &&
	    tr.steps <= 21)
	{
		return;
	}

	int r = rand()%30;
    switch(r)
    {
	case 0:
			if (right(tr))
			{
				turnright(tr);
				tr.steps = 0;
			}
			else if (left(tr))
			{
				turnleft(tr);
			tr.steps = 0;
			}
			break;
	case 1:
		if (left(tr))
		{
				turnleft(tr);
				tr.steps = 0;
			}
			else if (right(tr))
			{
				turnright(tr);
				tr.steps = 0;
		}
		break;
    }

    if (ahead(tr))
    {
	return;
    }
    else if (r%2 == 0)
    {
		if (left(tr))
		{
			turnleft(tr);
			tr.steps = 0;
		}
		else if (right(tr))
		{
			turnright(tr);
			tr.steps = 0;
	    }
	}
	else
   	{
		if (right(tr))
		{
				turnright(tr);
				tr.steps = 0;
		}
		else if (left(tr))
		{
			turnleft(tr);
  			tr.steps = 0;
	    }
	}

    if (r==0)
    {
   		turnleft(tr);
   		tr.steps = 0;
   	}
   	else if (r==1)
   	{
   		turnright(tr);
   		tr.steps = 0;
   	}

}


void main()
{
	if(InitGraphics() == -1)
		return;

	rectangle(0,0,boardwidth, boardheight);

	initialisedata();

	clearviewport();

	rectangle(0, 0, boardwidth-1, boardheight-1);
	while(!endgame)
	{
		drawtorch(me);
		for (int i = 0; i < MAX_TORCH; i++)
		{
			drawtorch(t[i]);
		}
		showscore();
		delay(20);
		showbox(me);
		for (i = 0; i < MAX_TORCH; i++)
		{
		   showbox(t[i]);
		}
		if (kbhit())
		{
			handlekeypress();
		}
		if (endgame)
			break;
		for (i = 0; i < MAX_TORCH; i++)
		{
			choose(t[i]);
		}
		adjustdir(me);
		moveit(me);
		for (i = 0; i < MAX_TORCH; i++)
		{
		    adjustdir(t[i]);
		    moveit(t[i]);
		}
		updatescore(me);
		for (i = 0; i < MAX_TORCH; i++)
		{
			updatescore(t[i]);
		}

	}


}

