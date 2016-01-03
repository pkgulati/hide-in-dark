/*
This program is written by Komal Gulati
for project in Delhi Public School Bangalore
For any queries please contact komalgulati1@gmail.com
*/

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

// macros used in program

#define true 	1
#define false 	0

// to make it slow increase delay interval
// depending upon your computer
// default 100 to 300
#define DELAY_INTERVAL 	 400
#define NUM_PLAYERS	 3

// directions are clockwise increasing
// so that if we want to use for cos or sin methods
// we can form angle using this
#define DIR_RIGHT   0
#define DIR_UP      1
#define DIR_LEFT    2
#define DIR_DOWN    3

struct player {
    int     x;
    int     y;
    int     dir;
    int     color;
    int     steps;
    int     owner;
    int     score;
    int     wrongsteps;
};

player plist[NUM_PLAYERS];


int width = 7;
int ohalf = 3;
int boardwidth  = 540;
int boardheight = 480;
int endgame = false;

// 70 x 60 board
int board[70][60];
int maxx = 69;
int maxy = 59;

// scoreboard x start and y end
int sx;
int sy;

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

    for (i = 0; i < NUM_PLAYERS; i++)
    {
        // i = 0 for me
	if (i==0)
        {
            plist[i].dir = DIR_UP;
	    plist[i].x   = maxx-4;
	    plist[i].y   = maxy-4;
        }
        else
	{
            plist[i].dir =  rand()%4;
	    plist[i].x   =  rand()%maxx;
	    plist[i].y   =  rand()%maxy;
        }


        plist[i].owner       = i;
        plist[i].steps       = 0;
        plist[i].wrongsteps = 0;

        plist[i].score        = 0;
        switch(i)
	{
            case 0:
                plist[i].color = YELLOW;
                break;
            case 1:
                plist[i].color = GREEN;
		break;
            case 2:
                plist[i].color = RED;
                break;
            case 3:
                plist[i].color = BLUE;
                break;
	    case 4:
                plist[i].color = CYAN;
                break;
        }
    }
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
    return 1;
}

int px(player& pl)
{
    return pl.x * width + 4;
}
int py(player& pl)
{
    return pl.y * width + 4;
}

int ax(player& pl)
{
    return pl.x*width+1;
}
int ay(player& pl)
{
    return pl.y*width+1;
}
int dx(player& pl)
{
    return pl.x*width + width;
}
int dy(player& pl)
{
    return pl.y*width+width;
}


void showbox(player& pl)
{
      setcolor(pl.color);
      setfillstyle(SOLID_FILL,pl.color);
      bar(ax(pl), ay(pl), dx(pl), dy(pl));
}
void showhead(player& pl)
{
      setcolor(BLACK);
      setfillstyle(SOLID_FILL,BLACK);
      switch(pl.dir)
      {
	case DIR_UP:
	     bar(px(pl)-1,py(pl)-2,px(pl)+1,py(pl)-3);
	break;
    case DIR_DOWN:
	bar(px(pl)-1,py(pl)+2,px(pl)+1,py(pl)+3);
	break;
    case DIR_LEFT:
	bar(px(pl)-2,py(pl)-1,px(pl)-3,py(pl)+1);
	break;
    case DIR_RIGHT:
	bar(px(pl)+2,py(pl)-1,px(pl)+3,py(pl)+1);
	break;
      }
}

void drawplayer(player& pl)
{
    setcolor(YELLOW);
    //circle(px(pl), py(pl), 3);
    showbox(pl);
    showhead(pl);
}

void turnright(player& pl)
{
  if (pl.dir == 0)
    pl.dir = 3;
  else
    pl.dir--;
 }

void turnleft(player& pl)
{
 if (pl.dir == 3)
    pl.dir = 0;
  else
    pl.dir++;
}

void turnrightleft(player& pl)
{

  if (rand()%2 == 0)
     turnleft(pl);
  else
     turnright(pl);
}

void turnanyside(player& pl)
{
  pl.dir += rand()%3;
  pl.dir  = pl.dir%4;
}


void moveit(player& pl)
{
    switch(pl.dir)
    {
        case DIR_UP:
	{
	    pl.y--;
	    break;
        }
        case DIR_DOWN:
        {
            pl.y++;
            break;
	}
	case DIR_RIGHT:
        {
            pl.x++;
            break;
	}
	case DIR_LEFT :
	{
	    pl.x--;
	    break;
	}
    }
    pl.steps++;
    return;
}

int adjustdir(player& pl)
{
  if (pl.y <= 0 && pl.dir == DIR_UP)
  {
     if (pl.x <= 0)
     {
	  pl.dir = rand()%2 ? DIR_RIGHT : DIR_DOWN;
     }
     else if (pl.x >= maxx)
     {
	 pl.dir = rand()%2 ? DIR_LEFT : DIR_DOWN;
     }
     else
     {
	 switch(rand()%3)
	 {
	   case 0: pl.dir = DIR_RIGHT; break;
	   case 1: pl.dir = DIR_LEFT; break;
	   case 2: pl.dir = DIR_DOWN; break;
	 }
     }
  }
  else if (pl.x <= 0 && pl.dir == DIR_LEFT)
  {
     if (pl.y <= 0)
     {
	 pl.dir = rand()%2 ? DIR_DOWN : DIR_RIGHT;
     }
     else if (pl.y >= maxy)
     {
	 pl.dir = rand()%2 ? DIR_UP : DIR_RIGHT;
     }
     else
     {
	 switch(rand()%3)
	 {
	   case 0: pl.dir = DIR_RIGHT; break;
	   case 1: pl.dir = DIR_UP; break;
	   case 2: pl.dir = DIR_DOWN; break;
	 }
     }
  }
  else if (pl.y >= maxy && pl.dir == DIR_DOWN)
  {
     if (pl.x <= 0)
     {
	 pl.dir = rand()%2 ? DIR_UP : DIR_RIGHT;
     }
     else if (pl.x >= maxx)
     {
	 pl.dir = rand()%2 ? DIR_UP : DIR_LEFT;
     }
     else
     {
	 switch(rand()%3)
	 {
	   case 0: pl.dir = DIR_RIGHT; break;
	   case 1: pl.dir = DIR_UP; break;
	   case 2: pl.dir = DIR_LEFT; break;
	 }
     }
  }
  else if (pl.x >= maxx && pl.dir == DIR_RIGHT)
  {
     if (pl.y <= 0)
     {
	 pl.dir = rand()%2 ? DIR_DOWN : DIR_LEFT;
     }
     else if (pl.y >= maxy)
     {
	 pl.dir = rand()%2 ? DIR_UP : DIR_LEFT;
     }
     else
     {
	 switch(rand()%3)
	 {
	   case 0: pl.dir = DIR_DOWN; break;
	   case 1: pl.dir = DIR_UP; break;
	   case 2: pl.dir = DIR_LEFT; break;
	 }
      }
  }

  return true;
}


void handlekeypress() {
   char ch = getch();
   switch (ch)
   {
     case 72: // upward
     {
	 plist[0].dir = DIR_UP;
	 break;
     }
     case 75: // left
     {
	plist[0].dir = DIR_LEFT;

	break;
     }
    case 77: // right
    {
	 plist[0].dir = DIR_RIGHT;

	 break;
    }
    case 80: // down
    {
	plist[0].dir = DIR_DOWN;

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

void updatescore(player& pl)
{
	int i = pl.x;
	int j = pl.y;
	if (board[i][j] != -1)
	{
	   if (board[i][j] == pl.owner)
	   {
		// my square nothing to do
	   }
	   else
	   {
	       // square does not belong to owner
	       if (pl.owner == 0)
		  plist[0].score = plist[0].score -2;
	       else
		  pl.score--;
	       plist[board[i][j]].score++;
	       // change owner of sqaure
	       board[i][j]=pl.owner;
	       pl.wrongsteps++;
	    }
	}
	else
	{
	   board[i][j]=pl.owner;
	   pl.score++;
	   pl.wrongsteps =0;
	}


}

int isaheadempty(player& pl)
{
    int x = pl.x;
    int y = pl.y;
    switch(pl.dir)
    {
	case DIR_UP:
	     if (y > 0 && board[x][y-1]==-1)
		return true;
	     break;
	case DIR_DOWN:
	     if (y < maxx  && board[x][y+1]==-1)
		return true;
	    break;
	case DIR_RIGHT:
	     if (x < maxx && board[x+1][y]==-1)
		return true;
	    break;
	case DIR_LEFT :
	     if (x > 0 && board[x-1][y]==-1)
		return true;
	    break;
    }
    return false;
}

int isrightempty(player& pl)
{
    int x = pl.x;
    int y = pl.y;
    switch(pl.dir)
    {
	case DIR_LEFT:
	     if (y > 0 && board[x][y-1]==-1)
		return true;
	     break;
	case DIR_RIGHT:
	     if (y < maxy  && board[x][y+1]==-1)
		return true;
	    break;
	case DIR_UP:
	     if (x < maxx && board[x+1][y]==-1)
		return true;
	    break;
	case DIR_DOWN :
	     if (x > 0 && board[x-1][y]==-1)
		return true;
	    break;
    }
    return false;
}


int isleftempty(player& pl)
{
    int x = pl.x;
    int y = pl.y;
    switch(pl.dir)
    {
	case DIR_RIGHT:
	     if (y > 0 && board[x][y-1]==-1)
		return true;
	     break;
	case DIR_LEFT:
	     if (y < maxx && board[x][y+1]==-1)
		return true;
	    break;
	case DIR_DOWN:
	     if (x < maxx && board[x+1][y]==-1)
		return true;
	    break;
	case DIR_UP :
	     if (x > 0 && board[x-1][y]==-1)
		return true;
	    break;
    }
    return false;
}

void decidemove2(player& pl)
{

}

void decidemove(player& pl)
{
    if (pl.wrongsteps <= 3 &&
	pl.steps <= 3)
    {
	return;
    }

    int r = rand()%30;
    switch(r)
    {
    case 0:
	    if (isrightempty(pl))
	    {
		turnright(pl);
		pl.steps = 0;
	    }
	    else if (isleftempty(pl))
	    {
		turnleft(pl);
	    pl.steps = 0;
	    }
	    break;
    case 1:
	if (isleftempty(pl))
	{
		turnleft(pl);
		pl.steps = 0;
	    }
	    else if (isrightempty(pl))
	    {
		turnright(pl);
		pl.steps = 0;
	}
	break;
    }

    if (isaheadempty(pl))
    {
	return;
    }
    else if (r%2 == 0)
    {
	if (isleftempty(pl))
	{
	    turnleft(pl);
	    pl.steps = 0;
	}
	else if (isrightempty(pl))
	{
	    turnright(pl);
	    pl.steps = 0;
	}
    }
    else
    {
	if (isrightempty(pl))
	{
	    turnright(pl);
	    pl.steps = 0;
	}
	else if (isleftempty(pl))
	{
	    turnleft(pl);
	    pl.steps = 0;
	}
    }

    if (r==0)
    {
	turnleft(pl);
	pl.steps = 0;
    }
    else if (r==1)
    {
	turnright(pl);
	pl.steps = 0;
    }
}


void showscoreboard()
{
   char stext[80];

   setcolor(WHITE);
   rectangle(sx+1,0,639,sy);

   setfillstyle(1, BLUE);
   bar(sx+2,3,638,50);
   setcolor(WHITE);
   outtextxy(sx+20,15,"SCOREBOARD");
   outtextxy(sx+5,35,"MY COLOR YELLOW");

   setfillstyle(1, YELLOW);
   bar(sx+2,50,638,79);
   setcolor(BLACK);
   sprintf(stext, "ME     =  %d ", plist[0].score);
   outtextxy(sx+10,60, stext);

   for (int i = 1; i < NUM_PLAYERS; i++)
   {
	int tx = 50+30*i;
	setfillstyle(1, plist[i].color);
	bar(sx+2,tx,638,tx+30);
	setcolor(WHITE);
	sprintf(stext, "PLAYER%d = %d ", i, plist[i].score);
	outtextxy(sx+10,tx+10, stext);
   }
   /*
   int tx = 300;
   setfillstyle(1, BLACK);
   bar(sx+2,tx,638,tx+30);
   setcolor(WHITE);
   sprintf(stext, "W %d A %d R %d L %d", plist[i].wrongsteps,
	isaheadempty(plist[1]),
	isrightempty(plist[1]),
	isleftempty (plist[1]) );
   outtextxy(sx+1,tx+10, stext);
   */

  }


void main()
{
    if(InitGraphics() == -1)
	return;


    initialisedata();

    clearviewport();
    rectangle(0,0,(maxx+1)*width+2, (maxy+1)*width+2);
    sx = (maxx+1)*width+6;
    sy = (maxy+1)*width+2;

    int loop = 0;
    while(!endgame)
    {
	loop++;
	for (int i = 0; i < NUM_PLAYERS; i++)
	{
	    drawplayer(plist[i]);
	}
	showscoreboard();
	delay(DELAY_INTERVAL);
	for (i = 0; i < NUM_PLAYERS; i++)
	{
	   showbox(plist[i]);
	}
	if (kbhit())
	{
	    handlekeypress();
	}

	if (endgame)
	    break;

	// 1 to n is computer plaer, 0 is me
	for (i = 1; i < NUM_PLAYERS; i++)
	{
	    decidemove(plist[i]);
	}

	for (i = 0; i < NUM_PLAYERS; i++)
	{
	    adjustdir(plist[i]);
	    moveit(plist[i]);
	}
	for (i = 0; i < NUM_PLAYERS; i++)
	{
	      updatescore(plist[i]);
	}

    }


}

