#include "global.h"
#include "font.h"
#include "ortho.h"
#include "timing.h"
#include "global.h"
#include "init.h"
#include "audio.h"
#include "menu.h"
#include "game.h"
#include "fifo.h"
#include "font.h"
#include "messages.h"

// Heads up display (HUD) file supporting user interface

/* Color Arrays */
float white[]  = {1.0,1.0,1.0,1.0};
float black[]  = {0.0,0.0,0.0,1.0};

float red[]    = {1.0,0.0,0.0,1.0};
float green[]  = {0.0,1.0,0.0,1.0};
float blue[]   = {0.0,0.0,1.0,1.0};
float yellow[] = {1.0,1.0,0.0,1.0};

float dred[]   = {0.5,0.0,0.0,1.0};
float dgreen[] = {0.0,0.5,0.0,1.0};
float dblue[]  = {0.0,0.0,0.5,1.0};
float dyellow[] = {0.5,0.5,0.0,1.0};

int speedo(float speed)			// For showing speed like a bar
{
  float spdperc;
  char  spdtxt[5];

  sprintf(spdtxt,"%i",(int)speed);
  spdperc = speed/180;

  /* Speed Barchart */
  orthosetup();
    glTranslatef(xres-120 ,10, 0);
    glBindTexture(GL_TEXTURE_2D, texture[11]);
    glBegin(GL_QUADS);
      glTexCoord2f(0.0f,        0.0f);	glVertex2f(0,0);
      glTexCoord2f(1.0f*spdperc,0.0f);	glVertex2f(100*spdperc,0);
      glTexCoord2f(1.0f*spdperc,1.0f);	glVertex2f(100*spdperc,20);
      glTexCoord2f(0.0f,        1.0f);	glVertex2f(0,20);
    glEnd();
  orthoreset();
  
  /* Print the Speed as Text */
  glEnable(GL_BLEND);
    fontprint(xres-130, 35, spdtxt, 1,1,  0);
    fontprint(xres-60,  40,"km/h",  1,0.5,0);
  glDisable(GL_BLEND);
  return 1;
}

int firstperson() 		// For first person view
{
  /* First person Cockpit view */
  orthosetup();
glTranslatef(xres-120, 10, 0);
    glBindTexture(GL_TEXTURE_2D, texture[14]);
    glBegin(GL_QUADS);
      glTexCoord2f(0.0f,0.0f);	glVertex2f(300,-10);
      glTexCoord2f(0.0f,1.0f);	glVertex2f(300,800);
      glTexCoord2f(1.0f,1.0f);	glVertex2f(-xres,800);
      glTexCoord2f(1.0f,0.0f);	glVertex2f(-xres,-10);
    glEnd();
  orthoreset();
  return 1;
}

int fpscount()				// Counting frame per seconds
{
  char fpstxt[5];
  sprintf(fpstxt,"%i",(int)get_fps());

  glEnable(GL_BLEND);
    fontprint(10, 10, fpstxt, 1,0.5,0);
  glDisable(GL_BLEND);

  return 1;
}


int radar(int range)				// Radar display
{
  float x,y;
  float ax,bx,cx,dx;
  float ay,by,cy,dy;

  x  = -player.x / XSCALE;
  y  = -player.z / ZSCALE;
  
  ax = dx = (x-range)/64;
  bx = cx = (x+range)/64;  
  ay = by = (y-range)/64;
  cy = dy = (y+range)/64;

  orthosetup();
    glTranslatef(60, yres-60, 0);
    glColor4f( 0.0f, 1.0f, 0.0f, 0.5f );
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

if(!tushar)						// in case of 3rd person setting up the location of radar in right uppermost place
{
    glEnable(GL_BLEND);
    glBindTexture(GL_TEXTURE_2D, texture[13]);
    glBegin(GL_QUADS);
      glTexCoord2f(ax,dy);	glVertex2f(-50,-50);
      glTexCoord2f(bx,cy);	glVertex2f( 50,-50);
      glTexCoord2f(cx,by);	glVertex2f( 50, 50);
      glTexCoord2f(dx,ay);	glVertex2f(-50, 50);
    glEnd();
    glDisable(GL_BLEND);
	glColor4fv(white);
    glBegin(GL_LINES);
      glVertex2d(0, cos(degtorad*-player.rot)*-5);
      glVertex2d(sin(degtorad*-player.rot)* 5, cos(degtorad*-player.rot)* 5);
    glEnd();
}

if(tushar)				// Setting up radar at appropriate place in first person view
{
	
    glEnable(GL_BLEND);
    glBindTexture(GL_TEXTURE_2D, texture[13]);
    glBegin(GL_QUADS);
      glTexCoord2f(ax,dy);	glVertex2f(xres/2-150,-575-100);
      glTexCoord2f(bx,cy);	glVertex2f(xres/2+100,-570-100);
      glTexCoord2f(cx,by);	glVertex2f(xres/2+100, -570+100);
      glTexCoord2f(dx,ay);	glVertex2f(xres/2-150,-570+100);
    glEnd();
    glDisable(GL_BLEND);
	glColor4fv(white);
      glBegin(GL_LINES);
      glVertex2d(xres/2, -570+cos(degtorad*-player.rot)*-5);
      glVertex2d(xres/2+sin(degtorad*-player.rot)* 5, -570+cos(degtorad*-player.rot)* 5);
    glEnd();
}
    

  orthoreset();
  return 1;

}

int end()		// For setting different display when a person looses or wins then corresponding function end and end1 are called
{
	sayan=1;
	menukeys();    
        menudraw1();
	return 1;
}

int end1()		
{
	sayan=2;
	menukeys();    
        menudraw1();
	return 1;
}

int timer()		// Timer implementation along with distance , winning strategy , different colouring mode , penalty mode , more precise timer near end
{
   int   timenow = SDL_GetTicks();
   float elapsed;
   int   minutes    = 0;
   int   seconds    = 0;
   int   hundredths = 0;
   char  minsec[5];
   char  hunsec[5];
   char  st[30];			// For showing distance left
   char ts[100];			// For showing offtrack vehicle
   
  elapsed    = (float)(timenow - timestart) / 1000;
  minutes    = (int)  (elapsed)             / 60;
  seconds    = (int)  (elapsed)             % 60;
  hundredths = (int)  (elapsed * 100 + 0.5) % 100;

if(flag)			// For reinitializing stuff like velocity when escape button is pressed
{
	flag=0;
	timestart=timenow;
	minutes=seconds=hundredths=0;
	player.vel=0;
}

if((seconds>=40)&&(dist<82000))		// Loosing condition
{
	printf("You Lose\n");
	dist=0;
	end();		
	return 1;
}

if(dist>=82000)				// Winning condition
{
	printf("You win\n");
	dist=0;
	end1();
	return 1;
}

if(player.vel>=0)			// Calculating distance
	dist+=player.vel*12;
else
	dist-=player.vel*12;

if(player.y>=60)				// Condition for showing that vehicle is going offtrack
{
	sprintf(ts,"Vehicle Off Track !!!");
	glEnable(GL_BLEND);
        fontprint(xres-(30*20)-300,yres-150,ts,1,1,1);
        glDisable(GL_BLEND);
	glColor4fv(blue);
	if(player.vel>=0)			// Penalty for going offside
		dist-=player.vel*24;
	else
		dist+=player.vel*24;
}

if(player.y<60)
glColor4fv(white);

dist1=82000-dist;				// Distance left for winning
sprintf(st,"Distance Left : %d m",dist1/100);
if(hundredths < 10)
   sprintf(hunsec,"0%d",hundredths);
else
   sprintf(hunsec,"%d",hundredths);   
   if (minutes < 10 && seconds < 10)
     sprintf(minsec,"0%d:%d",minutes,40-seconds);
   else if(minutes < 10 && seconds >= 10)
     sprintf(minsec,"0%d:%d",minutes,40-seconds);  
   else if(minutes >= 10 && seconds < 10)
     sprintf(minsec,"%d:0%d",minutes,40-seconds);
   else
     sprintf(minsec,"%d:%d",minutes,40-seconds);

if(seconds>=30)			// For red and white flashback
{
	if(seconds%2)
		glColor4fv(red);
	else
		glColor4fv(white);
}

   glEnable(GL_BLEND);
     fontprint(xres - (7*20), yres-32, minsec, 1,1,1);
     fontprint(xres - (2*20)+5, yres-18, hunsec, 1,0.5,1);
     fontprint(xres-(30*20)-300,yres-50,st,1,1,1);
   glDisable(GL_BLEND);

  return 1;
}

int drawhud()			// Drawing out HUD 
{
  int speed;
  
  if(player.vel < 0)
    speed = -player.vel*36;
  else
    speed =  player.vel*36;

if(tushar)
 firstperson();

 speedo(speed);
 
  if(showfps)
    fpscount();

  radar(10);

  timer();

  return 1;
}
