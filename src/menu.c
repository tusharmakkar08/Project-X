// Game Menu 
#include "global.h"
#include "menu.h"
#include "main.h"
#include "font.h"
#include "textures.h"
#include "audio.h"
#include "ortho.h"
#include <time.h>
#define MENU_ITEMS	6			// No of items in the menu
#define RES_ITEMS	3
int tushar=1; 			// Tushar initialized to 1 to make first person view the default view of the game
char *menulist[20];
int   menuitem = 0;
char  res[9];

int loadmenu(void)			// loading the menu
{
  menu = 1;
  loadtexture("all","loading.jpg",	1,0,10);		// loading textures
  loadtexture("all","font.png",		4,0,0);
  loadtexture("all","fontoutline.png",	4,0,12);
if(!sayan)						// if sayan==0 default screen will come
{
  loadtexture("all","menu.jpg",		4,0,1);
initmenu();
}
else if(sayan==1)				// losing screen
{
loadtexture("all","lose.jpg",4,0,1);
initmenu1();
}
else if(sayan==2)				// winning screen
{
loadtexture("all","win.jpg",4,0,1);
initmenu2();
}  
  
  return 1;
}

int initmenu(void)			// playing default menu sound
{
  playmusic("data/music/sensation.mp3");  
  return 1;
}

int initmenu1(void)				// playing loosing menu sound
{
  playmusic("data/music/Lose.mp3"); 
  return 1;
}

int initmenu2(void)				// playing winning menu sound
{
  playmusic("data/music/Win.mp3"); 
  return 1;
}

int menudraw1(void) 	// Different menu draw functions for different cases
{
  int x;
  loadmenu();
  menulist[0] = "Start game";
  
  menulist[1] = course[loadc].name; 
  if(fullscreen == 1)
    menulist[2] = "Fullscreen";
  else
    menulist[2] = "Windowed";  

  menulist[5] = "Exit Game";

menulist[3]="First Person";

menulist[4]="Third person";
  
  orthosetup();
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glBegin(GL_QUADS);
      glTexCoord2f(0.0f,1.0f); glVertex2i(0,   0   );
      glTexCoord2f(0.0f,0.0f); glVertex2i(0,   yres);
      glTexCoord2f(1.0f,0.0f); glVertex2i(xres,yres);
      glTexCoord2f(1.0f,1.0f); glVertex2i(xres,0   );
    glEnd();
  orthoreset();

  glEnable(GL_BLEND);


    fontprint(xres/2-80, yres-130 - (25*menuitem), "o",0,0.5,0);
    glColor3f(1.0f, 1.0f, 0.0f);
    fontprint(xres/2-78, yres-128 - (25*menuitem), "o",0,0.5,0);

    glColor3f(0.0f, 0.0f, 1.0f);
    for(x=0; x<MENU_ITEMS; x++)
      fontprint(xres/2 - 60, yres-130 - (25*x), menulist[x],0,0.5,0);

    glColor3f(1.0f, 1.0f, 1.0f);
    for(x=0; x<MENU_ITEMS; x++)
      fontprint(xres/2 - 58, yres-128 - (25*x), menulist[x],0,0.5,0);

  glDisable(GL_BLEND);

  SDL_GL_SwapBuffers();
  SDL_Delay(10); /* Menu doesnt need high framerate */
  return 1;
}

int menudraw(void)
{
  int x;
  
  menulist[0] = "Start Game";
  
  menulist[1] = course[loadc].name;
  
  if(fullscreen == 1)
    menulist[2] = "Fullscreen";
  else
    menulist[2] = "Windowed";  
  menulist[5] = "Exit Game";
menulist[4]="Third Person";
menulist[3]="First person";
  
  orthosetup();
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glBegin(GL_QUADS);
      glTexCoord2f(0.0f,1.0f); glVertex2i(0,   0   );
      glTexCoord2f(0.0f,0.0f); glVertex2i(0,   yres);
      glTexCoord2f(1.0f,0.0f); glVertex2i(xres,yres);
      glTexCoord2f(1.0f,1.0f); glVertex2i(xres,0   );
    glEnd();
  orthoreset();

  glEnable(GL_BLEND);
    glColor3f(1.0f, 1.0f, 1.0f);
    fontprint(xres/2-(4.5*20), yres-80, "Project X",0,1,1);
    glColor3f(1.0f,0.0f,0.0f);
    fontprint(xres/2-(4.5*20)+2, yres-78, "Project X",0,1,1);

    fontprint(xres/2-80, yres-130 - (25*menuitem), "o",0,0.5,0);
    glColor3f(1.0f, 1.0f, 0.0f);
    fontprint(xres/2-78, yres-128 - (25*menuitem), "o",0,0.5,0);

    glColor3f(0.0f, 0.0f, 1.0f);
    for(x=0; x<MENU_ITEMS; x++){
     fontprint(xres/2 - 60, yres-130 - (25*x), menulist[x],0,0.5,0);
}
    glColor3f(1.0f, 1.0f, 1.0f);
    for(x=0; x<MENU_ITEMS; x++)
      fontprint(xres/2 - 58, yres-128 - (25*x), menulist[x],0,0.5,0);

  glDisable(GL_BLEND);

  SDL_GL_SwapBuffers();
  SDL_Delay(10); /* Menu doesnt need high framerate */
  return 1;
}

int menukeys(void) 		// Impact for pressing keys during menu 
{
  /* Key Handling */
  while (SDL_PollEvent(&event)){
    events();
    switch(event.type){
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym){
          case SDLK_RETURN:
	  case SDLK_SPACE:
	    switch(menuitem){
	      case 0:
	        menu = 2;
		newgame = 1;
		break;
	      case 5:
	        killgame(1);
		break;
		case 4:tushar=0;			// for first person and third person view
		break;
		case 3:
		tushar=1;
		break;
	      default:
	        break;
	    }
	    break;
	  case SDLK_LEFT:
	    switch(menuitem){
	      case 1:
	        if(loadc == 0)
	          loadc = COURSES-1;
	        else
	          loadc--;
		  playsound("data/sounds/menu.wav",0);
	        break;
		
	      case 2:
		SDL_WM_ToggleFullScreen(surface);
	        fullscreen = 0;
		playsound("data/sounds/menu.wav",0);
	        break;
	      default:
	        break;
	    }
	    break;
	  case SDLK_RIGHT:
	    switch(menuitem){
	      case 1:
	        if(loadc == COURSES-1)
	          loadc = 0;
	        else
	          loadc++;
		playsound("data/sounds/menu.wav",0);
	        break;
	      case 2:
	        fullscreen = 0;
	        SDL_WM_ToggleFullScreen(surface);
		playsound("data/sounds/menu.wav",0);
	        break;
	      default:
	        break;
	    }
	    break;
	  case SDLK_UP:
	    if(menuitem == 0)
              menuitem = MENU_ITEMS-1;
	    else
	      menuitem--;
	    playsound("data/sounds/menu.wav",0);
	    break;
	  case SDLK_DOWN:
	    if(menuitem == MENU_ITEMS-1)
              menuitem = 0;
	    else
	      menuitem++;
    	    playsound("data/sounds/menu.wav",0);
	    break;
	  case SDLK_q:
	    killgame(1);
	    break;	
          default:
            break;
        }
      break;
      case SDL_QUIT:
	done = 1;
	break;
      default:
	break;
    }
  }
if(loadc==1)
{
mint=1;
}
 
  return 1;
}

int loading(void)
{

  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  
  orthosetup();
    glBindTexture(GL_TEXTURE_2D, texture[10]);
    glBegin(GL_QUADS);
      glTexCoord2f(0.0f,1.0f); glVertex2i(0,   0   );
      glTexCoord2f(0.0f,0.0f); glVertex2i(0,   yres);
      glTexCoord2f(1.0f,0.0f); glVertex2i(xres,yres);
      glTexCoord2f(1.0f,1.0f); glVertex2i(xres,0   );
    glEnd();
  orthoreset();
  
  SDL_GL_SwapBuffers();
  return 1;
}
