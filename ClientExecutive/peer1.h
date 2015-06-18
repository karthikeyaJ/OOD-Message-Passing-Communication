#ifndef PEER1_H
#define PEER1_H
/////////////////////////////////////////////////////////////////////////////
// Peer1.h             - Process the command line arguments                //
//                       and pass it sender or receiver                    //
// Ver 1.1                                                                 //
// Venkata Karthikeya, CSE#687 - Object Oriented Design, Spring 2015       //
//-------------------------------------------------------------------------//
// Karthikeya (c) copyright 2015                                           //
// All rights granted provided this copyright notice is retained           //
//-------------------------------------------------------------------------//
// Platform:    Dell     , Win Pro 8.1, Visual Studio 2013                 //
/////////////////////////////////////////////////////////////////////////////
/*
*  Package Operations:
*  -------------------
*  This package process the command line and divide peer ports to send to a Sender package:
*
*  Required Files:
*  ---------------
*sockets.h,AppHelpers.h,FileSystem.h,Receiver.h
*Sender.h,Display.h
*
*  Build Command:
*  --------------
*  devenv Sockets.sln /rebuild debug
*
*  Maintenance History:
*  --------------------
*  ver 1.1 : 10 Aril 15
*  - minor modification to comments, above
*  ver 1.0 : 5 april 15
*  - first release
*/

#include "../sockets/sockets.h"
#include "../ApplicationHelpers/AppHelpers.h"
#include <iostream>
#include <thread>
#include <mutex>
#include "../FileSystemDemo/FileSystem.h"
#include "../Receiver/Receiver.h"
#include "../Sender/Sender.h"
#include <thread>
#include "../Display/Display.h"
using namespace ApplicationHelpers;




class Peer1
{
public:
	void Client(int endpoint1,int endpoint2, std::string filename);
	void Server(int endpoint1,int endpoint2);
	int getPort1(){ return port1; }
	int getPort2(){ return port2; }

private:
	int port1;
	int port2;
};

#endif




