#ifndef _MENU_H_
#define _MENU_H_

#include "global.h"

int initmenu(void);
int initmenu1(void);	// calling menu for winning song
int initmenu2(void);	// calling menu for losing song
int loadmenu(void);
int loading(void);
int menukeys(void);
int menudraw(void);
int menudraw1(void);	// calling menudraw for 2nd case
extern int menuitem;
#endif
