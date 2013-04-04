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

int speedo(float speed){
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

int firstperson(){
  /* Speed Barchart */
  orthosetup();
glTranslatef(xres-120, 10, 0);
    glBindTexture(GL_TEXTURE_2D, texture[14]);
    glBegin(GL_QUADS);
      glTexCoord2f(0.0f,0.0f);	glVertex2f(300,0);
      glTexCoord2f(0.0f,1.0f);	glVertex2f(300,300);
      glTexCoord2f(1.0f,1.0f);	glVertex2f(-xres,300);
      glTexCoord2f(1.0f,0.0f);	glVertex2f(-xres,0);
    glEnd();
  orthoreset();
  return 1;
}

int fpscount(){
  char fpstxt[5];
  sprintf(fpstxt,"%i",(int)get_fps());

  glEnable(GL_BLEND);
    fontprint(10, 10, fpstxt, 1,0.5,0);
  glDisable(GL_BLEND);

  return 1;
}

int radar(int range){
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
if(!tushar)
{
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glBindTexture(GL_TEXTURE_2D, texture[13]);
    glBegin(GL_QUADS);
      glTexCoord2f(ax,dy);	glVertex2f(-50,-50);
      glTexCoord2f(bx,cy);	glVertex2f( 50,-50);
      glTexCoord2f(cx,by);	glVertex2f( 50, 50);
      glTexCoord2f(dx,ay);	glVertex2f(-50, 50);
    glEnd();
    glDisable(GL_BLEND);
}
if(tushar)
{
glBlendFunc(GL_ONE, GL_ONE);
    glEnable(GL_BLEND);
    glBindTexture(GL_TEXTURE_2D, texture[13]);
    glBegin(GL_QUADS);
      glTexCoord2f(ax,dy);	glVertex2f(xres/2-50,-500-50);
      glTexCoord2f(bx,cy);	glVertex2f(xres/2+50,-500-50);
      glTexCoord2f(cx,by);	glVertex2f(xres/2+50, -500+50);
      glTexCoord2f(dx,ay);	glVertex2f(xres/2-50,-500+50);
    glEnd();
    glDisable(GL_BLEND);
}
    glColor4fv(white);
    glBegin(GL_LINES);
      glVertex2d(0, cos(degtorad*-player.rot)*-5);
      glVertex2d(sin(degtorad*-player.rot)* 5, cos(degtorad*-player.rot)* 5);
    glEnd();

  orthoreset();
  return 1;
}
int end()
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


int timer(){
     int   timenow = SDL_GetTicks();
   float elapsed;
   int   minutes    = 0;
   int   seconds    = 0;
   int   hundredths = 0;
   char  minsec[5];
   char  hunsec[5];
   
   elapsed    = (float)(timenow - timestart) / 1000;
  minutes    = (int)  (elapsed)             / 60;
  seconds    = (int)  (elapsed)             % 60;
   hundredths = (int)  (elapsed * 100 + 0.5) % 100;
   if((seconds>=40)&&(dist<82000))
	{
	printf("You Lose\n");
	dist=0;
	end();		
	return 1;
	}
if((dist>=82000)&&(seconds>=40))
{
	printf("You win\n");
	dist=0;
	end1();
	return 1;
}
if(player.vel>=0)
	dist+=player.vel*12;
else
dist-=player.vel*12;
//printf("Lol %d\n",dist);
   if(hundredths < 10)
     sprintf(hunsec,"0%d",hundredths);
   else
     sprintf(hunsec,"%d",hundredths);
   
   if (minutes < 10 && seconds < 10)
     sprintf(minsec,"0%d:0%d",minutes,seconds);
   else if(minutes < 10 && seconds >= 10)
     sprintf(minsec,"0%d:%d",minutes,seconds);  
   else if(minutes >= 10 && seconds < 10)
     sprintf(minsec,"%d:0%d",minutes,seconds);
   else
     sprintf(minsec,"%d:%d",minutes,seconds);
   
   glEnable(GL_BLEND);
     fontprint(xres - (7*20), yres-32, minsec, 1,1,1);
     fontprint(xres - (2*20)+5, yres-18, hunsec, 1,0.5,1);
   glDisable(GL_BLEND);

  return 1;
}

int drawhud(){
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
