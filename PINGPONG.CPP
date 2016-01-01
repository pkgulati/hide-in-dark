/*
http://www.botskool.com/tutorials/c-tutorials/ping-pong-game-c-language
*/

#include <graphics.h>
#include <dos.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>


struct bat
{
 int length;
 int width;
 int xcoordinate;
 int new_ycoordinate;
 int old_ycoordinate;
}batA, batB; // Create Two Bats For Each User.

struct ball
{
 int radius;
 int speedx;
 int speedy;
 int old_xcenter;
 int old_ycenter;
 int new_xcenter;
 int new_ycenter;
}ball1;

struct score
{
  int score_A;
  int score_B;
}score_game;


void initialize () // Initialize the game.

{
  int gdriver = DETECT, gmode;
  char tempstring [10]; //This String holds score in char format temporarily
  time_t t;// Used to generate random number from system time.
  closegraph ();
  initgraph(&gdriver, &gmode, "c:\\tc\\bgi"); // Intializes Graphics

  //Initialise Bat A
  batA.length = 40;
  batA.width = 2;
  batA.xcoordinate = 20;
  batA.new_ycoordinate = 237;
  batA.old_ycoordinate = 237;

  // Intialise Bat B
  batB.length = 40;
  batB.width = 2;
  batB.xcoordinate = 620;
  batB.new_ycoordinate = 237;
  batB.old_ycoordinate = 237;

   // Intialise Ball
   ball1.radius = 3;
   ball1.speedx = 2;
   srand((int) time(&t)); // Seed rand a random number
   ball1.speedy = rand ()%1;// Sets speed from 0 to 2 depending upon remainder.
   if (rand() % 2 == 0)
     {
       ball1.speedx = - ball1.speedx; // Generate Random X direction.
       ball1.speedy = - ball1.speedy; // Generate Random Y direction.
      }
    ball1.old_xcenter = 320;
    ball1.old_ycenter = 250;
    ball1.new_xcenter = 320;
    ball1.new_ycenter = 250;

   // Set Background to white
   setbkcolor (BLACK);

   // Draw Ball at Initial Position
   setfillstyle (1,15);
   fillellipse (ball1.new_xcenter,ball1.new_ycenter,ball1.radius,ball1.radius);

   // Draw Bats at Intial Position
   bar (batA.xcoordinate,batA.new_ycoordinate,batA.xcoordinate+batA.width,batA.new_ycoordinate+batA.length);
   bar (batB.xcoordinate,batB.new_ycoordinate,batB.xcoordinate+batB.width,batB.new_ycoordinate+batB.length);

   // Display Score
   //textcolor ();
   sprintf (tempstring,"A - %d",score_game.score_A);
   outtextxy (10,450,tempstring);
   sprintf (tempstring,"B - %d",score_game.score_B);
   outtextxy (590,450,tempstring);
   outtextxy (40,472,"Remove This Line by Learn Coding It yourself at www.cencyclopedia.com");
}

void movebat (char input)

{
  switch (input)
     {
       case 'A' :
                  if (batA.new_ycoordinate > 0) // Move only when bat is not touching the top so it doesnt jump out of screen.
                    {
                      batA.old_ycoordinate = batA.new_ycoordinate;
                      batA.new_ycoordinate --;
                      setfillstyle (1,0); // Remove last postion.
                      bar (batA.xcoordinate,batA.old_ycoordinate,batA.xcoordinate+batA.width,batA.old_ycoordinate+batA.length);
                      setfillstyle (1,15); // Display New postion.
                      bar (batA.xcoordinate,batA.new_ycoordinate,batA.xcoordinate+batA.width,batA.new_ycoordinate+batA.length);
                     }
                   break;

       case 'Z' :
                  if (batA.new_ycoordinate+batA.length < 430) // Make sure bat doesnot go below the screen.
                    {
                      batA.old_ycoordinate = batA.new_ycoordinate;
                      batA.new_ycoordinate ++;
                      setfillstyle (1,0); // Remove last postion.
                      bar (batA.xcoordinate,batA.old_ycoordinate,batA.xcoordinate+batA.width,batA.old_ycoordinate+batA.length);
                      setfillstyle (1,15); // Display New postion.
                      bar (batA.xcoordinate,batA.new_ycoordinate,batA.xcoordinate+batA.width,batA.new_ycoordinate+batA.length);
                    }
                  break;
       case 'J' :
                  if (batB.new_ycoordinate > 0) // Move only when bat is not touching the top so it doesnt jump out of screen.
                     {
                      batB.old_ycoordinate = batB.new_ycoordinate;
                      batB.new_ycoordinate --;
                      setfillstyle (1,0); // Remove last postion.
                      bar (batB.xcoordinate,batB.old_ycoordinate,batB.xcoordinate+batB.width,batB.old_ycoordinate+batB.length);
                      setfillstyle (1,15); // Display New postion.
                      bar (batB.xcoordinate,batB.new_ycoordinate,batB.xcoordinate+batB.width,batB.new_ycoordinate+batB.length);
                     }
                  break;

        case 'M' :
                  if (batB.new_ycoordinate+batB.length < 430) // Make sure bat doesnot go below the screen.
                    {
                      batB.old_ycoordinate = batB.new_ycoordinate;
                      batB.new_ycoordinate ++;
                      setfillstyle (1,0); // Remove last postion.
                      bar (batB.xcoordinate,batB.old_ycoordinate,batB.xcoordinate+batB.width,batB.old_ycoordinate+batB.length);
                      setfillstyle (1,15); // Display New postion.
                      bar (batB.xcoordinate,batB.new_ycoordinate,batB.xcoordinate+batB.width,batB.new_ycoordinate+batB.length);
                    }
                   break;
         }

}

void moveball ()

{
   ball1.old_xcenter = ball1.new_xcenter;
   ball1.old_ycenter = ball1.new_ycenter;
   ball1.new_xcenter = ball1.new_xcenter + ball1.speedx;
   ball1.new_ycenter = ball1.new_ycenter + ball1.speedy;
   setcolor (0);
   setfillstyle (1,0); // Remove last postion.
   fillellipse (ball1.old_xcenter,ball1.old_ycenter,ball1.radius,ball1.radius);
   setfillstyle (1,15); // Display New postion.
   fillellipse (ball1.new_xcenter,ball1.new_ycenter,ball1.radius,ball1.radius);
   if ( ball1.new_ycenter - ball1.radius < 0 ) ball1.speedy = -ball1.speedy; // Reflect From Top
   if ( ball1.new_ycenter + ball1.radius > 430 ) ball1.speedy = -ball1.speedy; // Reflect From Bottom
}

void physics ()

{
  char tempstring [10];
  if ( ball1.new_xcenter - ball1.radius <= 20)
     {
         if (ball1.new_ycenter > batA.new_ycoordinate && ball1.new_ycenter < batA.new_ycoordinate+batA.length)
            {
               ball1.speedx = - ball1.speedx;
               ball1.speedy = rand () % 2;// Sets speed from 0 to 2 depending upon remainder.
               if (rand() % 2 == 0) ball1.speedy = - ball1.speedy; // Generate Random Y direction.
             }
          else // Reintialize entire game with new score
             {
               score_game.score_B ++;
               initialize ();
             }
          return;
      }

  if ( ball1.new_xcenter +  ball1.radius > 620)

      {
         if (ball1.new_ycenter > batB.new_ycoordinate && ball1.new_ycenter < batB.new_ycoordinate+batB.length)
          {
            ball1.speedx = - ball1.speedx;
            ball1.speedy = rand ()%2;// Sets speed from 0 to 2 depending upon remainder.
            if (rand() % 2 == 0) ball1.speedy = - ball1.speedy; // Generate Random Y direction.
           }
         else // Reintialize game with new score
          {
           score_game.score_A ++;
           initialize ();
          }
           return;
       }
}

void play ()

{
  while (inportb (0X60) != 16) // Check wether key press is Q if so exit loop
     {
       delay (10); // Reduce game speed to human playable level
       if (inportb (0X60) == 30)  movebat ('A');
       if (inportb (0X60) == 44)  movebat ('Z');
       if (inportb (0X60) == 36)  movebat ('J');
       if (inportb (0X60) == 50)  movebat ('M');
       moveball ();
       physics ();
      }
}


int main ()

{
  score_game.score_A = 0;// Intialise score in Main This Time
  score_game.score_B = 0;// It improves Efficiency
  initialize ();
  play (); // Game Engine
  closegraph (); // Close Graphics
  return 0;
}
