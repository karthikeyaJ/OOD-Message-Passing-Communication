#ifndef DISPLAY_H
#define DISPLAY_H
///////////////////////////////////////////////////////////////////////
//  Display.h   -  Display Package for Files/Directories display     //
//  Author:		   Venkata Karthikeya Jangal, Syracuse University    //
//				   vjangal@syr.edu                       			 //	
///////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
This module is designed to display the string that contains
file/directory name to be displayed on the console.
*
*  Build Command:
*  --------------
*  devenv Display.sln /rebuild debug
*
*  Public Interface:
*  =================
* void display(std::string);
* void display_int(int);
*
* Maintenance History:
* ====================
* ver 1.0 : 12 April 15
* - first release
*/

#include<iostream>
#include<string>
#include<vector>

class Display
{
public:
	void display(std::string);
	void display_int(int);

};


#endif
