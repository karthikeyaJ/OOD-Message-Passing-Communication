#ifndef RECEIVER_H
#define RECEIVER_H
/////////////////////////////////////////////////////////////////////////////
// Receiver.h  - Receives the string from connected port                   //
// Ver 1.1                                                                 //
// Venkata Karthikeya, CSE#687 - Object Oriented Design, Spring 2015       //
//-------------------------------------------------------------------------//
// Jim Fawcett (c) copyright 2015                                          //
// All rights granted provided this copyright notice is retained           //
//-------------------------------------------------------------------------//
// Application:  Project #4,                                               //
// Platform:    Dell, Win Pro 8.1, Visual Studio 2013                      //
/////////////////////////////////////////////////////////////////////////////
/*
*  Package Operations:
*  -------------------
*  This package helps to receive binary or string
*  from other peer present at different port
*  - receiveing byte buffers
*  - receiving strings
*  It has a client handler class which handles the receive string
*  does build header messages using header.h file and enq
*  so that receiver can deq and create a file with same message into the downloads folder
*
*  Public Interface:
*  =================
* void startSending(int serv, int client);
* bool testStringHandling(Socket& socket_);
* bool testBufferHandling(Socket& socket_);
* int getClientPort(){ return clientport; }
* std::string decoder1(std::string msg);
*
*  Required Files:
*  ---------------
* Sockets.h
* BlockingQueue.h
* AppHelpers.h
* FileSystem.h
* Base64.h
* Header.h
* Display.h
*
*  Build Command:
*  --------------
*  devenv Receiver.sln /rebuild debug
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
using namespace ApplicationHelpers;
#include <string>
#include <iostream>
#include "../Display/Display.h"

class ClientHandler
{
public:
	ClientHandler();
	ClientHandler(BlockingQueue<std::string>& q) : q_(q) {}
	void operator()(Socket& socket_);
	bool testStringHandling(Socket& socket_);
	bool testBufferHandling(Socket& socket_);
	int getClientPort(){ return clientport; }
	std::string decoder1(std::string msg);

private:
	std::string msg;
	Socket s_;
	BlockingQueue<std::string>& q_;
	std::string ipaddress;
	std::string portnum;
	std::string readstring = "";
	int contentlength;
	int tag = 0;
	int clientport;
	int mylistenport;
};



class Receiver
{
public:
	Receiver(){}
	void start(int port);
	void readMsg();
	enum IpVer { IP4, IP6 };
	Socket& getSocket(){ return s_; }
	void startSending(int serv, int client);
	bool getStatus1(){ return status1; }
	void setStatus1(){ status1 = true; }
	int getClientPort(){ return clientport_; }
	int getServerPort(){ return serverport_; }
	void setClientPort(int port){ clientport_ = port; }
	void setServerPort(int port){ serverport_ = port; }

private:
	BlockingQueue<std::string> q_; 
	SocketSystem ss;
	SocketListener* sl;// (size_t port, IpVer ipv = IP6);
	bool status1=false;
	std::string msg;
	Socket s_;
	std::string ipaddress;
	int clientport_;
	int serverport_;
	std::string portnum;
	std::string filename_;
	std::string readstring = "";
	int contentlength;
	int tag = 0;
};


#endif