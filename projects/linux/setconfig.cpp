//AUTHOR:	DAN CRISP
//DATE:		Nov. 18, 2016
//DESC:		setconfig.cpp
/*
For making an executable which will set-up configurations on ReA linux machines

NOTE:
	Don't forget to compile this code with -1X11 -|Xrandr to link the libraries
	Currently copy/pasted from stackoverflow.com/questions/13706078/xrandr-related-c-programming
	Plan on expanding when I have time to get back to it
*/

#include<iostream>
#include<cstdlib>
#include<X11/Xlib.h>
#include<X11/extensions/Xrandr.h>

int main()
{
	using namespace std;
	
	Display *dpy;
	XRRScreenResources *screen;
	XRRCrtcInfo *crtc_info;

	dpy = XOpenDisplay(":0");
	screen = XRRGetScreenResources (dpy, DefaultRootWindo(dpy));
	//0 to ge the first monitor
	crtc_info = XRRGetCrtcInfo (dpy, screen, screen->crtcs[0]);
	
	// Now crtc_info->width contains width, and crtc_info-> the x position
	
	
	return 0;
}
