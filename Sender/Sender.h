#ifndef SENDER_H
#define SENDER_H
/////////////////////////////////////////////////////////////////////////////
// Sender.h  - Sends the string to connected port                          //
// Ver 1.1                                                                 //
// Venkata Karthikeya, CSE#687 - Object Oriented Design, Spring 2015       //
//-------------------------------------------------------------------------//
// Jim Fawcett (c) copyright 2015                                          //
// All rights granted provided this copyright notice is retained           //
//-------------------------------------------------------------------------//
// Application:  Project #4,                                               //
// Platform:    Dell 2720, Win Pro 8.1, Visual Studio 2013                 //
/////////////////////////////////////////////////////////////////////////////
/*
*  Package Operations:
*  -------------------
*  This package helps to send binary or string 
*  to other peer present at different port
*  - passing byte buffers
*  - passing strings
*  Public Interface:
*  =================
*   void connectServer2(int port);
*	void starting(int port); 
*	void run();
*	void run2();
*
*  Required Files:
*  ---------------
*  ClientTest.cpp, ServerTest.cpp
*  Sockets.h, Sockets.cpp, AppHelpers.h, AppHelpers.cpp
*
*  Build Command:
*  --------------
*  devenv Sender.sln /rebuild debug
*
*  Maintenance History:
*  --------------------
*  ver 1.1 : 15 Apl 15
*  - minor modification to comments, above
*  ver 1.0 : 15 Apl 15
*  - first release
*/

#include "../Sockets/Sockets.h"
#include "../BlockingQueue/BlockingQueue/BlockingQueue.h"
#include "../ApplicationHelpers/AppHelpers.h"
#include "../FileSystemDemo/FileSystem.h"
#include "../Encoder/Base64.h"
#include "../Header/Header.h"
#include "../Display/Display.h"

#include <iostream>

using namespace ApplicationHelpers;



class Sender
{
public:
	Sender(int numMsgs, std::string file, int port1, int port2, int n_o_threads, int numTestLines = 0) : numMsgs_(numMsgs), file_(file), port1_(port1), port2_(port2), thread_count(n_o_threads), numTestLines_(numTestLines) { myCount = ++count; }
	int id() { return myCount; }
	std::string ToString(int i);
	void connectServer2(int port);
	std::string encoder1(std::string msg);
	void starting(int port); 
	void run();
	void run2();

private:
	Socket s_;
	SocketSystem ss;
	SocketConnecter si;
	BlockingQueue<std::string> q_;
	int count;
	int myCount;
	int numMsgs_;
	int numTestLines_;
	std::string file_;
	int port1_;
	int port2_;
	int thread_count;
};

#endif







