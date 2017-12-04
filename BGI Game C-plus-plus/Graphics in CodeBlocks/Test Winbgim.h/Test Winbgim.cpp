 /*	Test thu vien winbgim.h	*/

#include <winbgim.h>

main(int argc, char *argv[])
{
	initwindow(300, 300);					// init window graphics
	setbkcolor(1);							// set background
   	cleardevice();
	setcolor(14);							// set text color
	outtextxy(50,100,"Graphics in CodeBlocks");// print text in window graphics
	while(!kbhit()) delay(1);				// pause screen
}
