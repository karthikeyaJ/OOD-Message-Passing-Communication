///////////////////////////////////////////////////////////////////////
//  Display.cpp -  Display Package for string or int messages        //
//  Author:		   Venkata karthikeya, Syracuse University		     //
//				   vjangal@syr.edu	                  				 //	
///////////////////////////////////////////////////////////////////////


#include<iostream>
#include "Display.h"

// Displays string type of data
void Display::display(std::string data)
{
	std::cout <<"\n"<< data;
}

//Displays int type of data
void Display::display_int(int data)
{
	std::cout <<"\n"<< data;
}

#ifdef TEST_DISPLAY

int main(int argc, char* argv[])
{
	std::string data1="Hi this is test for the display class";
	Display d;
	d.display(data1);

}

#endif