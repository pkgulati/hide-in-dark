#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <bios.h>
#include <dos.h>
#include <graphics.h>
#include <time.h>

#define PI 3.141592654
#define ON 1
#define OFF 0
#define TRUE 1
#define FALSE 0

int leave=0,moves=10,crswiz=9,filled=1,bcol=2,cwiz,grid,wizx[8],wizy[8];
int lcol=14,angle=269,cirx[15],ciry[15],gone[8],curn=0,turn=0;
int gridx1[16],gridx2[16],gridx3[16],gridx4[16],col[8],done,filledpeople=1;
int gridy1[16],gridy2[16],gridy3[16],gridy4[16],curx,cury,temp10,thismany;
int bkcol,cmode,maxx,maxy,hmaxx,hmaxy,nexscr,actscr=1,inc,three_d=1;
int oldx,oldy,wizatt[7],wizdef[7],players,temp[7],moving,order[88];
int intpoints[10],curs[8],changed,num[8],polypoints[8],already,ballz[120];
int playhit,deady,fightadd1,fightadd2,dead,nomore,winnerbloke,owner[80];
int ang,fullscr[8],board[125],creatures,cx[80],cy[80],type[80],fillpeople=1;
int circx,circy,circsize,sides=18,zooming,finding;
int placex[8],placey[8],oldzoom,dirx[4],diry[4],actioncam,oldmoving[2];

float major=3.2,minor,t[8],acr,dwn,x,y,zoom=300,temped,psadangle[361];
float points[8],wiz[400],angchange=6,radang,adder,addx,addy,difx,dify;

char *name1[10],*name2[10],*name3[10],*name4[10],*name5[10],*name6[10],*name7[10],*name8[10];

void program(void),keypresses(void),update(void),point_workout(void);
void display(void),left(void),right(void),up(void),down(void),wizpos(void);
void change_turn(void),cursor(void),move(void),wiz3d(void),movingg(void);
void changeview(void),update_board(void),newpos(void),casting(void);
void collision(void),menu(void),death(void),howmany(void),centre(void);
void winner(void),start_thing(void),directions(void),start(void);
void collision_detect(void),status(void),zbufs(void),viewchange(void);
void newang(void),re_calc(void),circ_points(void),circ(void),find(void);

int main(void)
{
   int gdriver = EGA, gmode = EGAHI, errorcode;

   initgraph(&gdriver, &gmode, "c:\\TC\\BGI");
   errorcode = graphresult();
   if (errorcode != grOk)
   {
      printf("Either:-\n\n  1) You do not have a 64k or above EGA card, or\n");
      printf("  2) There are important files missing. Please re-install in this instance.\n");
      exit(1);
   }

   *name1="Thomas";
   col[0]=3;

   *name2="Jay";
   col[1]=4;

   *name3="Perky";
   col[2]=5;

   *name4="Neil Smelly";
   col[3]=6;

   *name5="Jimbo";
   col[4]=7;

   *name6="Tigger";
   col[5]=8;

   *name7="Neil Attrill";
   col[6]=9;

   *name8="Bernard";
   col[7]=10;

   program();

   if(leave==1)
     printf("ESC pressed . . .\n");

   getch();
   closegraph();
   return 0;
}

void program(void)
{
  menu();
  start();

  do
    {
     update();
     point_workout();
     display();
     keypresses();
    } while(leave==OFF);
}

void update(void)
{
  if(angle<0)
    angle=angle+360;

  if(angle>360)
    angle=angle-360;

  x = acr + hmaxx;
  y = dwn + hmaxy;

  crswiz = 9;
  for(temp[0]=0;temp[0]<players;temp[0]++)
    if(curx == wizx[temp[0]] && cury == wizy[temp[0]])
      {
       crswiz = temp[0];
       temp[0] = players;
      }
}

void menu(void)
{
  printf("Speed? ");
  scanf("%f",&adder);
  printf("\nPlayers? ");

  scanf("%d",&players);
}

void point_workout(void)
{
  zbufs();
  cursor();
}

void display(void)
{
  char *currentplayer[10];
  int cur;

  setactivepage(nexscr);
  cleardevice();
  setcolor(15);

  setbkcolor(bkcol);

  setfillstyle(SOLID_FILL,bcol);
  if(filled==1)
    fillpoly(4,intpoints);
  else
    drawpoly(5,intpoints);


  if(moving != 1)
    {
     setfillstyle(SOLID_FILL,15);
     setcolor(col[turn]);
     fillpoly(4,curs);
    }

  setcolor(lcol);
  if(grid==1)
    {
     for(temp[0]=0;temp[0]!=16;temp[0]++)
       {
	temp[1] = 15 - temp[0];
	line(gridx1[temp[0]], gridy1[temp[0]],gridx3[temp[1]], gridy3[temp[1]]);
	line(gridx2[temp[0]], gridy2[temp[0]],gridx4[temp[1]], gridy4[temp[1]]);
       }
    }

  for(temp[2]=0;temp[2]<players;temp[2]++)
    {
     if(gone[order[temp[2]]] != 1)
       {
	cwiz=order[temp[2]];
	wiz3d();
	setcolor(col[order[temp[2]]]);
	setfillstyle(SOLID_FILL,col[order[temp[2]]]);

	if(filledpeople==1)
	  {
	   for(temp[6]=4;temp[6]<num[cwiz]*4+1;temp[6]=temp[6]+4)
	     {
	      cur=(temp[6]/4)-1;
	      /*circx=cirx[cur];
	      circy=ciry[cur];
	      circsize=(cwiz*50)+temp[6];
	      circ();*/

	      fillellipse(cirx[cur],ciry[cur],wiz[(cwiz*50)+ temp[6]] * zoom, (wiz[(cwiz*50)+ temp[6]] * zoom)/48 * 35);
	     }
	  }
	else
	  {
	   for(temp[6]=4;temp[6]<num[cwiz]*4+1;temp[6]=temp[6]+4)
	     {
	      cur=(temp[6]/4)-1;
	      circle(cirx[cur],ciry[cur],wiz[(cwiz*50)+ temp[6]] * zoom);
	     }
	  }

	for(temp[6]=1;temp[6]<(ballz[cwiz*15]+1)*2;temp[6]=temp[6]+2)
	  line(cirx[ballz[temp[6]]],ciry[ballz[temp[6]]],cirx[ballz[temp[6]+1]],ciry[ballz[temp[6]+1]]);
       }
    }

  setcolor(15);
  setfillstyle(SOLID_FILL,12);
  fillpoly(4,polypoints);
  settextstyle(GOTHIC_FONT, HORIZ_DIR, 3);

  if(turn==0)
    *currentplayer=*name1;

  if(turn==1)
    *currentplayer=*name2;

  if(turn==2)
    *currentplayer=*name3;

  if(turn==3)
    *currentplayer=*name4;

  if(turn==4)
    *currentplayer=*name5;

  if(turn==5)
    *currentplayer=*name6;

  if(turn==6)
    *currentplayer=*name7;

  if(turn==7)
    *currentplayer=*name8;

  setcolor(16);
  outtextxy(6,1,*currentplayer);
  setcolor(15);
  outtextxy(5, 0, *currentplayer);

  settextstyle(GOTHIC_FONT,HORIZ_DIR,4);
  if(cmode==0)
    outtextxy(5,maxy-30,"Rotate /  Scale");

  if(cmode==1)
    outtextxy(5,maxy-30,"Cursor Movement");

  if(cmode==2)
    outtextxy(5,maxy-30,"Wizard Movement");

  if(actscr==1 && actioncam == TRUE)
    {
     setcolor(12);
     outtextxy(maxx-160,1,"Action Cam");
    }

  setcolor(15);
  line(0,0,0,maxy);
  line(0,maxy,maxx,maxy);
  line(maxx,maxy,maxx,0);
  line(maxx,0,0,0);

  setvisualpage(nexscr);

  temp[0]=actscr;
  actscr=nexscr;
  nexscr=temp[0];
}

void keypresses(void)
{
  int key;

  oldx = wizx[turn];
  oldy = wizy[turn];

  if(bioskey(1)!=OFF)
    {
     do
       {
	key=bioskey(0);
       }
     while(bioskey(1)!=OFF);

     if (key==283)
       leave=1;

     if (key==19252)
       left();

     if (key==18231)
       {
	up();
	left();
       }

     if (key==18488)
       up();

     if (key==18745)
       {
	up();
	right();
       }

     if (key==19766)
       right();

     if (key==20787)
       {
	down();
	right();
       }

     if (key==20530)
       down();

     if (key==20273)
       {
	down();
	left();
       }

     if (key==21294)
       {
	changed=0;

	if(cmode==1)
	  {
	   cmode=0;
	   changed=1;
	  }

	if(cmode==0 && changed!=1)
	  cmode=1;
       }

     if (key==8807)
       {
	changed=0;

	if(grid==1)
	  {
	   grid=0;
	   changed=1;
	  }

	if(grid==0 && changed!=1)
	  grid=1;
       }

     if (key==19509 && moving == OFF)
       move();

     if (key==21040 && moving == OFF)
       change_turn();

     if (key==21040 && moving == ON)
       done=moves;

     if (key==14122)
       status();

     if (key==13615)
       viewchange();

     if(key==8550 || key==8518)
       if(filled==TRUE)
	 {
	  filled=FALSE;
	  fillpeople=FALSE;
	  filledpeople=FALSE;
	 }
       else
	 {
	  filled=TRUE;
	  fillpeople=TRUE;
	  filledpeople=TRUE;
	 }

      if(key == 7745 || key == 7777)
	{
	 if(actioncam==FALSE)
	   actioncam=TRUE;
	 else
	   actioncam=FALSE;

	 changeview();
	}

      /*printf("%d",key);
      getch();*/
     }
}

void cursor(void)
{
   curs[0] = (points[0] - ((curx - 5) * t[0])) - (cury + 5) * t[2];
   curs[1] = (points[1] - ((curx - 5) * t[1])) - (cury + 5) * t[3];
   curs[2] = (points[0] - ((curx + 5) * t[0])) - (cury + 5) * t[2];
   curs[3] = (points[1] - ((curx + 5) * t[1])) - (cury + 5) * t[3];
   curs[4] = (points[0] - ((curx + 5) * t[0])) - (cury - 5) * t[2];
   curs[5] = (points[1] - ((curx + 5) * t[1])) - (cury - 5) * t[3];
   curs[6] = (points[0] - ((curx - 5) * t[0])) - (cury - 5) * t[2];
   curs[7] = (points[1] - ((curx - 5) * t[1])) - (cury - 5) * t[3];
}

void wiz3d(void)
{
   temp[1] = 0;
   for(temp[0]=0;temp[0]<(num[cwiz])*4;temp[0]=temp[0]+4)
     {
      cirx[temp[1]] = points[0] - ((wizx[cwiz] + wiz[(cwiz*50) + temp[0] + 1]) * t[0]) - ((wizy[cwiz] + wiz[(cwiz*50) + temp[0] + 2]) * t[2]);
      ciry[temp[1]] = points[1] - ((wizx[cwiz] + wiz[(cwiz*50) + temp[0] + 1]) * t[1]) - ((wizy[cwiz] + wiz[(cwiz*50) + temp[0] + 2]) * t[3]);

      if(three_d==1)
	ciry[temp[1]]=ciry[temp[1]] - ((wiz[(cwiz*50) + temp[0] + 3]) * zoom);

      temp[1] = temp[1] + 1;
     }
}

void zbufs(void)
{
  int zbuf[8],zbuf2[8],max,flag,cur,used;

  for(temp[0]=0;temp[0]<players;temp[0]++)
    zbuf[temp[0]]=points[1]-(wizx[temp[0]]*t[1])-(wizy[temp[0]]*t[3]);

  for(temp[0]=0;temp[0]<players;temp[0]++)
    zbuf2[temp[0]]=zbuf[temp[0]];

  max=players;
  for(temp[2]=0;temp[2]<players-1;temp[2]++)
    {
     max--;
     flag=0;
     for(temp[0]=0;temp[0]<max;temp[0]++)
       if(zbuf[temp[0]]>zbuf[temp[0]+1])
	 {
	  temp[1]=zbuf[temp[0]];
	  zbuf[temp[0]]=zbuf[temp[0]+1];
	  zbuf[temp[0]+1]=temp[1];
	  flag=1;
	 }
     if(flag==0)
       break;
    }

  for(temp[0]=0;temp[0]<8;temp[0]++)
    order[temp[0]]=9;

  cur=0;
  for(temp[0]=0;temp[0]<players;temp[0]++)
    {
     used=0;

     for(temp[2]=0;temp[2]<8;temp[2]++)
       if(temp[0]==order[temp[2]])
	 used=1;

     if(zbuf[cur]==zbuf2[temp[0]] && used==0)
       {
	order[cur]=temp[0];

	temp[0]=-1;

	if(cur==players)
	  temp[0]=players;
	else
	  cur++;
       }
    }
}

void left(void)
{
   changed=0;

   if(cmode == 0)
     {
      angle = angle + adder;
      changed = 1;
      centre();
     }

   if(cmode == 1 && changed != 1 && curn != 1 && curx > 14)
     {
      curx = curx - 10;
      changed = 1;
     }

   if(cmode == 2 && wizx[turn] > 9 && changed != 1)
     {
      wizx[turn] = wizx[turn] - 10;
      centre();
      done++;
     }
}

void right(void)
{
   changed=0;

   if(cmode == 0)
     {
      angle = angle - adder;
      changed = 1;
      centre();
     }

   if(cmode == 1 && changed != 1 && curn != 1 && curx < 136)
     {
      curx = curx + 10;
      changed = 1;
     }

   if(cmode == 2 && wizx[turn] <140 && changed != 1)
     {
      wizx[turn] = wizx[turn] + 10;
      centre();
      done++;
     }
}

void up(void)
{
   changed=0;

   if(cmode == 0 && zoom < 1000)
     {
      zoom = zoom + (2*adder);
      changed = 1;
      re_calc();
      centre();
     }

   if(cmode == 1 && changed != 1 && curn != 1 && cury < 136)
     {
      cury = cury + 10;
      changed = 1;
     }

   if(cmode == 2 && wizy[turn] < 140 && changed != 1)
     {
      wizy[turn] = wizy[turn] + 10;
      centre();
      done++;
     }
}

void down(void)
{
   changed=0;

   if(cmode == 0 && zoom > 30)
     {
      zoom = zoom - (2*adder);
      changed = 1;
      re_calc();
      centre();
     }

   if(cmode == 1 && changed != 1 && curn != 1 && cury > 14)
     {
      cury = cury - 10;
      changed = 1;
     }

   if(cmode == 2 && wizy[turn] > 9 && changed != 1)
     {
      wizy[turn] = wizy[turn] - 10;
      centre();
      done++;
     }
}

void start(void)
{
  FILE *fptr,*fopen();
  char *fname[12] = {"wizard.dat"};

  for(cwiz=0;cwiz<8;cwiz++)
    {
     fptr=fopen("wizard.dat", "r");

     fscanf(fptr,"%f,",&wiz[cwiz*50]);

     for(temp[0]=1;temp[0]<(wiz[0]*4)+1;temp[0]++)
       fscanf(fptr,"%f,",&wiz[(cwiz*50)+temp[0]]);

     for(temp[0]=0;temp[0]<8;temp[0]++)
       num[cwiz]=wiz[cwiz*50];

     fscanf(fptr,"%d,",&ballz[(cwiz*15)]);

     for(temp[0]=1;temp[0]<(ballz[cwiz*15]+1)*2;temp[0]++)
       fscanf(fptr,"%d,",&ballz[(cwiz*15)]+temp[0]);

     fclose(fptr);
    }

  maxx=getmaxx();
  maxy=getmaxy();
  hmaxx=maxx/2;
  hmaxy=maxy/2;
  minor=(1/angchange)*major;

  settextstyle(GOTHIC_FONT,HORIZ_DIR,4);

  randomize();
  for(temp[0]=0;temp[0]<players;temp[0]++)
    {
     wizatt[temp[0]]= 1 + rand()%5;

     wizdef[temp[0]]= 1 + rand()%5;

     if(temp[0] > 0)
       if(wizatt[temp[0]]==wizatt[temp[0]-1] && wizdef[temp[0]]==wizdef[temp[0]-1])
	 temp[0]--;

     setcolor(rand()%16);
     outtextxy(maxx-(rand()%maxx),maxy-(rand()%maxy),"PLEASE WAIT");
    }

  if(players == 2)
    {
     wizx[0] = 75;
     wizy[0] = 125;
     wizx[1] = 75;
     wizy[1] = 25;
    }

  if(players == 3)
    {
     wizx[0] = 75;
     wizy[0] = 125;
     wizx[1] = 135;
     wizy[1] = 25;
     wizx[2] = 15;
     wizy[2] = 25;
    }

  if(players == 4)
    {
     wizx[0] = 15;
     wizy[0] = 135;
     wizx[1] = 135;
     wizy[1] = 135;
     wizx[2] = 135;
     wizy[2] = 15;
     wizx[3] = 15;
     wizy[3] = 15;
    }

  if(players == 5)
    {
     wizx[0] = 75;
     wizy[0] = 135;
     wizx[1] = 135;
     wizy[1] = 95;
     wizx[2] = 105;
     wizy[2] = 25;
     wizx[3] = 45;
     wizy[3] = 25;
     wizx[4] = 15;
     wizy[4] = 95;
    }

  if(players == 6)
    {
     wizx[0] = 75;
     wizy[0] = 145;
     wizx[1] = 145;
     wizy[1] = 125;
     wizx[2] = 145;
     wizy[2] = 25;
     wizx[3] = 75;
     wizy[3] = 5;
     wizx[4] = 5;
     wizy[4] = 25;
     wizx[5] = 5;
     wizy[5] = 125;
    }

  if(players == 7)
    {
     wizx[0] = 75;
     wizy[0] = 145;
     wizx[1] = 135;
     wizy[1] = 135;
     wizx[2] = 145;
     wizy[2] = 45;
     wizx[4] = 45;
     wizy[4] = 5;
     wizx[3] = 105;
     wizy[3] = 5;
     wizx[5] = 5;
     wizy[5] = 45;
     wizx[6] = 15;
     wizy[6] = 135;
    }

  if(players==8)
    {
     wizx[0] = 75;
     wizy[0] = 145;
     wizx[1] = 145;
     wizy[1] = 145;
     wizx[2] = 145;
     wizy[2] = 75;
     wizx[3] = 145;
     wizy[3] = 5;
     wizx[4] = 75;
     wizy[4] = 5;
     wizx[5] = 5;
     wizy[5] = 5;
     wizx[6] = 5;
     wizy[6] = 75;
     wizx[7] = 5;
     wizy[7] = 145;
    }

  creatures=players;

  for(temp[0]=0;temp[0]<players;temp[0]++)
    {
     type[temp[0]]=temp[0]+1;
     owner[temp[0]]=temp[0]+1;
    }

  polypoints[0]=0;
  polypoints[1]=0;
  polypoints[2]=0;
  polypoints[3]=30;
  polypoints[4]=210;
  polypoints[5]=30;
  polypoints[6]=210;
  polypoints[7]=0;

  fullscr[0]=0;
  fullscr[1]=0;
  fullscr[2]=maxx;
  fullscr[3]=0;
  fullscr[4]=maxx;
  fullscr[5]=maxy;
  fullscr[6]=0;
  fullscr[7]=maxy;

  //update_board();

  oldzoom=zoom;
  zoom=100;
  update();
  re_calc();
  newang();

  filledpeople=OFF;
  start_thing();
  filledpeople=fillpeople;

  turn=9;
  change_turn();
}

void start_thing(void)
{
   moving=1;

   for(temp[0]=0;temp[0]<6;temp[0]++)
     for(temp[1]=0;temp[1]<players;temp[1]++)
       wiz[(temp[1]*50)+(temp[0]*4)]++;

   for(temp[4]=0;temp[4]<10;temp[4]++)
     {
      for(temp[5]=0;temp[5]<6;temp[5]++)
	for(temp[6]=0;temp[6]<players;temp[6]++)
	  wiz[(temp[6]*50)+(temp[5]*4)] = wiz[(temp[6]*50)+(temp[5]*4)] - 0.1;

      if(actioncam == TRUE && zoom <oldzoom)
	zoom=zoom+20;
      else
	if(actioncam == FALSE)
	  zoom=100;

      //re_calc();
      newang();
      update();
      point_workout();
      display();
     }
  moving=0;
}

void move(void)
{
   int leaver;

   if(crswiz == turn)
     {
      done = 0;
      leaver = 0;
      moving = 1;
      cmode = 2;

      do
	{
	 keypresses();
	 collision_detect();

	 if(leave==TRUE)
	   break;

	 display();

	 if(done >= moves || leave == TRUE)
	   leaver = 1;
	}
      while(leaver==0);

      collision_detect();
      cmode = 1;
      moving = FALSE;
      change_turn();
     }
}

void change_turn(void)
{
   int alive,oldturn;

   zooming=ON;

   oldturn=turn;

   alive=FALSE;

   do
     {
      turn = turn + 1;
      if(turn > players - 1)
	turn = 0;
      if(gone[turn] == FALSE)
	alive=TRUE;
     }
   while (alive == FALSE);

   curx = wizx[turn];
   cury = wizy[turn];

   if(oldturn != turn)
     find();
}

void collision_detect(void)
{
   for(temp[0]=0;temp[0]<players;temp[0]++)
     if(wizx[turn] == wizx[temp[0]] && wizy[turn] == wizy[temp[0]] && temp[0] != turn && gone[temp[0]] != 1)
       {
	playhit = temp[0];
	temp[0] = players;
	collision();
       }
}

void collision(void)
{
   sound(110);
   delay(10);
   nosound();
   wizx[turn] = oldx;
   wizy[turn] = oldy;
   deady = 0;

   randomize();
   fightadd1 = random(15);
   fightadd2 = random(15);

   if(wizatt[turn] + fightadd1 > 2+ wizdef[playhit] + fightadd2)
     {
      dead=playhit;
      deady=1;
     }

   if(wizatt[turn] + fightadd1 > wizdef[playhit] + fightadd2)
     {
      wizdef[playhit]--;
      if(wizdef[playhit]==0)
	{
	 dead=playhit;
	 deady=1;
	}
     }


   if(deady==1)
     {
      filledpeople=OFF;
      death();
      filledpeople=fillpeople;
      gone[playhit]=1;

      wizx[turn]=wizx[playhit];
      wizy[turn]=wizy[playhit];

      wizx[playhit]=999;
      wizy[playhit]=999;
     }

   done = moves;
   nomore = 0;

   for(temp[0]=0;temp[0]<players;temp[0]++)
     {
      if(gone[temp[0]] == 1)
	nomore++;

      if(gone[temp[0]] == 0)
	winnerbloke=temp[0];
     }

   if(nomore == players - 1)
     winner();
}

void status(void)
{
  int third;
  third=maxy/3;

  if(crswiz!=9)
    {

  setactivepage(nexscr);
  cleardevice();

  setfillstyle(SOLID_FILL,1);
  fillpoly(4,fullscr);

  settextstyle(GOTHIC_FONT, HORIZ_DIR, 4);
  outtextxy(150,third,"Attack:");
  outtextxy(150,third*2,"Defense:");

  if(wizatt[crswiz]==1)
    outtextxy(250,third,"1");

  if(wizatt[crswiz]==2)
    outtextxy(250,third,"2");

  if(wizatt[crswiz]==3)
    outtextxy(250,third,"3");

  if(wizatt[crswiz]==4)
    outtextxy(250,third,"4");

  if(wizatt[crswiz]==5)
    outtextxy(250,third,"5");

  if(wizdef[crswiz]==1)
    outtextxy(270,third*2,"1");

  if(wizdef[crswiz]==2)
    outtextxy(270,third*2,"2");

  if(wizdef[crswiz]==3)
    outtextxy(270,third*2,"3");

  if(wizdef[crswiz]==4)
    outtextxy(270,third*2,"4");

  if(wizdef[crswiz]==5)
    outtextxy(270,third*2,"5");

  setcolor(14);
  outtextxy(maxx-200,maxy-40,"Press A Key");

  setvisualpage(nexscr);
  getch();

  temp[0]=actscr;
  actscr=nexscr;
  nexscr=temp[0];
  }
}

void winner(void)
{
  char *winner[10];

  update();
  point_workout();
  display();
  update();
  point_workout();
  display();

  leave=TRUE;

  intpoints[0]=hmaxx-69;
  intpoints[1]=hmaxy-21;

  intpoints[2]=hmaxx-69;
  intpoints[3]=hmaxy+21;

  intpoints[4]=hmaxx+69;
  intpoints[5]=hmaxy+21;

  intpoints[6]=hmaxx+69;
  intpoints[7]=hmaxy-21;

  randomize();

  if(winnerbloke==0)
    *winner=*name1;

  if(winnerbloke==1)
    *winner=*name2;

  if(winnerbloke==2)
    *winner=*name3;

  if(winnerbloke==3)
    *winner=*name4;

  if(winnerbloke==4)
    *winner=*name5;

  if(winnerbloke==5)
    *winner=*name6;

  if(winnerbloke==6)
    *winner=*name7;

  if(winnerbloke==7)
    *winner=*name8;

  do
    {
     setvisualpage(actscr);
     setactivepage(actscr);

     setcolor(rand() % 15);
     settextstyle(GOTHIC_FONT,HORIZ_DIR,3);
     outtextxy(rand() % maxx,rand() % maxy,*winner);

     setactivepage(nexscr);

     outtextxy(rand() % maxx,rand() % maxy,*winner);

     setcolor(0);
     settextstyle(GOTHIC_FONT,HORIZ_DIR,4);
     setfillstyle(SOLID_FILL,11);
     fillpoly(4,intpoints);
     outtextxy(hmaxx-64,hmaxy-16,"WINNER");

     setvisualpage(nexscr);

     nexscr=temp[0];
     nexscr=actscr;
     actscr=temp[0];
    }
  while (bioskey(1)==0);
}

void viewchange(void)
{
  changed=0;

  if(three_d==1)
    {
     three_d=0;
     changed=1;
     minor=(major/((maxx/4)*3))*maxy;
    }

  if(three_d==0 && changed != 1)
   {
    three_d=1;
    minor=(1/angchange)*major;
   }

  newang();
}

void death(void)
{
   for(temp[3]=0;temp[3]<6;temp[3]++)
     {
      for(temp[4]=0;temp[4]<9;temp[4]++)
	wiz[(playhit*50)+(temp[4]*4)]=wiz[(playhit*50)+(temp[4]*4)]+.09;

      update();
      display();
      sound(temp[3]*100);
     }

   for(temp[3]=0;temp[3]<4;temp[3]++)
     {
      for(temp[4]=0;temp[4]<9;temp[4]++)
	wiz[(playhit*50)+(temp[4]*4)]=wiz[(playhit*50)+(temp[4]*4)]-.18;

      update();
      display();
      sound(temp[3]*100);
     }

   for(temp[3]=0;temp[3]<3;temp[3]++)
     {
      for(temp[4]=0;temp[4]<9;temp[4]++)
	wiz[(playhit*50)+(temp[4]*3)]=wiz[(playhit*50)+(temp[4]*3)]+.5;

      update();
      display();
      sound(temp[3]*100);
     }
   nosound();
}

/*void update_board(void)
{
  for(temp[0]=0;temp[0]<players;temp[0]++)
    board[wizx[temp[0]]+(((wizy[temp[0]]-5)/10)+1)]=temp[0]+1;

  for(temp[0]=0;temp[0]<creatures-players;temp[0]++)
    board[cx[temp[0]]+(((cy[temp[0]]-5)/10)+1)]=type[temp[0]];
}*/

void howmany(void)
{
  thismany=0;

  for(temp[0]=0;temp[0]<40;temp[0]++)
    if(owner[temp[0]]==cwiz+1)
      thismany++;
}

void newang(void)
{
  for(temp[0]=0;temp[0]<8;temp[0]=temp[0]+2)
    {
     ang=angle+((temp[0]/2)*90);

     if(ang > 360)
       ang=ang-360;

     points[temp[0]]=x-(major*zoom*psadangle[ang]);

     ang=ang+90;

     if(ang > 360)
       ang=ang-360;

     points[temp[0]+1]=y-(minor*zoom*psadangle[ang]);

     intpoints[temp[0]]=points[temp[0]];
     intpoints[temp[0]+1]=points[temp[0]+1];
    }

  intpoints[8]=intpoints[0];
  intpoints[9]=intpoints[1];

  t[0] = (points[0]-points[2]) / 150;
  t[1] = (points[1]-points[3]) / 150;

  t[2] = (points[2]-points[4]) / 150;
  t[3] = (points[3]-points[5]) / 150;

  t[4] = (points[4]-points[6]) / 150;
  t[5] = (points[5]-points[7]) / 150;

  t[6] = (points[6]-points[0]) / 150;
  t[7] = (points[7]-points[1]) / 150;

  for(temp[0]=0;temp[0]<16;temp[0]++)
    {
     temp[1]=temp[0]*10;

     gridx1[temp[0]] = points[0] - (t[0] * temp[1]);
     gridy1[temp[0]] = points[1] - (t[1] * temp[1]);

     gridx2[temp[0]] = points[2] - (t[2] * temp[1]);
     gridy2[temp[0]] = points[3] - (t[3] * temp[1]);

     gridx3[temp[0]] = points[4] - (t[4] * temp[1]);
     gridy3[temp[0]] = points[5] - (t[5] * temp[1]);

     gridx4[temp[0]] = points[6] - (t[6] * temp[1]);
     gridy4[temp[0]] = points[7] - (t[7] * temp[1]);
    }
}

void re_calc(void)
{
  float radangle;

  for(temp[7]=0;temp[7]<361;temp[7]++)
    {
     radangle=(temp[7]*PI)/180;

     psadangle[temp[7]]=sin(radangle);
    }
}

void circ(void)
{
  int cur,circle[720];

  cur=0;
  for(temp[0]=0;temp[0]<360;temp[0]=temp[0]+adder)
    {
     circle[cur]=circx-(circsize*psadangle[temp[0]]);

     ang=temp[0]+90;

     if(ang > 360)
       ang=ang-360;

     circle[cur+1]=circy-(circsize*psadangle[temp[0]]);
     cur=cur+2;
    }

  fillpoly(sides,circle);
}

void find(void)
{
  float dist,percent,multadder;

  if(actioncam == FALSE || leave == TRUE)
    return;

  update();

  oldmoving[0]=moving;

  finding=TRUE;
  moving=TRUE;

  wizpos();

  difx=hmaxx-placex[turn];
  dify=hmaxy-placey[turn];

  dist=sqrt((difx*difx)+(dify*dify));

  multadder=8*adder;

  if(dist < 150)
    {
     moving=oldmoving[0];
     return;
    }
  percent=(multadder/dist)*100;

  addx=(difx/100)*percent;
  addy=(dify/100)*percent;

  oldzoom=zoom;

  for(temped=0;temped<dist;temped=temped+multadder)
    {
     acr=acr+addx;
     dwn=dwn+addy;

     if(zooming==ON)
       {
	if(temped>(dist/2) && zoom<oldzoom)
	  zoom=zoom+(multadder/2);
	else
	  if(zoom>10)
	    zoom=zoom-(multadder/2);
	re_calc();
       }

     update();
     newang();

     display();

     if(leave==TRUE)
       break;
    }
  finding=FALSE;
  moving=oldmoving[0];
}

void centre(void)
{
  if(actioncam == FALSE || leave == TRUE)
     goto end;

  wizpos();

  difx=hmaxx-placex[turn];
  dify=hmaxy-placey[turn];

  acr=acr+difx;
  dwn=dwn+dify;

  update();

  end:;
  newang();
}

void wizpos(void)
{
   for(cwiz=0;cwiz<players;cwiz++)
     {
      placex[cwiz]=points[0]-(wizx[cwiz]*t[0])-(wizy[cwiz]*t[2]);
      placey[cwiz]=points[1]-(wizx[cwiz]*t[1])-(wizy[cwiz]*t[3]);
     }
}

void directions(void)
{
   int dirs[8];

   dirs[0]=points[0]-(0*t[0])-(75*t[2]);
   dirs[2]=points[0]-(75*t[0])-(0*t[2]);
   dirs[4]=points[0]-(75*t[0])-(150*t[2]);
   dirs[6]=points[0]-(150*t[0])-(75*t[2]);

   dirs[1]=points[1]-(0*t[1])-(75*t[3]);
   dirs[3]=points[1]-(75*t[1])-(0*t[3]);
   dirs[5]=points[1]-(75*t[1])-(150*t[3]);
   dirs[7]=points[1]-(150*t[1])-(75*t[3]);

   for(temp[7]=0;temp[7]<4;temp[7]++)
     {
      dirx[temp[7]]=dirs[temp[7]];

      if(dirx[temp[7]] >= maxx-50)
	dirx[temp[7]] = maxx-50;

      if(dirx[temp[7]] <= 50)
	dirx[temp[7]] = 50;
     }

   for(temp[7]=0;temp[7]<4;temp[7]++)
     {
      diry[temp[7]]=dirs[temp[7]+1];

      if(diry[temp[7]] >= maxy-30)
	diry[temp[7]] = maxy-30;

      if(diry[temp[7]] <= 30)
	diry[temp[7]] = 30;
     }
}

void changeview(void)
{
   int zoomadd;

   oldmoving[1]=moving;
   moving=TRUE;

   if(actioncam == TRUE)
     zoomadd = 20;

   if(actioncam == FALSE)
     {
      zoomadd = -20;
      acr=0;
      dwn=0;
      update();
     }

   for(temp[3]=0;temp[3]<10;temp[3]++)
     {
      zoom=zoom+zoomadd;
      re_calc();
      newang();
      display();
     }

   if(actioncam == TRUE)
     find();

   moving=oldmoving[1];
}
