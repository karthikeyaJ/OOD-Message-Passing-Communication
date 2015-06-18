/////////////////////////////////////////////////////////////////////////////
//Peer2.cpp - Process the command line arguments                           //
//            and pass it sender or receiver                               //
// Ver 1.1                                                                 //
// Venkata Karthikeya, CSE#687 - Object Oriented Design, Spring 2015       //
//-------------------------------------------------------------------------//
// Venkata Karthikeya (c) copyright 2015                                   //
// All rights granted provided this copyright notice is retained           //
//-------------------------------------------------------------------------//
// Application: OOD Projects     #4                                        //
// Platform:    Visual Studio 2013, Dell, Win 8.1 pro                      //
/////////////////////////////////////////////////////////////////////////////
/*
*  Package Operations:
*  -------------------
*  Acts as server or client based on the inputs:
*  - Starts sender or receiver threads
*  - passing ports
*
*
*  Build Command:
*  --------------
*  devenv Peer1.sln /rebuild debug
*
*  Maintenance History:
*  --------------------
*  ver 1.0 : 15 April 15
*  - first release
*/
#include "Peer2.h"

// Acts as a client i.e, sends to the acting server with sendport and starts its own listener for receiving acknowledgement
void Peer2::Client(int sndPort, int rcvPort, std::string filename)
{
	Receiver r;
	Sender s(100, filename, rcvPort, sndPort, 1);
	try
	{
		std::mutex mtx;
		mtx.lock();
		Display d;
		d.display("\n %%%%%%%%%%%%%%%%%%%%%%CLIENTTTTTTTTTTTTT%%%%%%%%%%%%%%%%%%%%");

		d.display("\n %%%%%%%%%%%%%%%%%%%%%%Entered Parameters are%%%%%%%%%%%%%%%%%%%%");
		d.display("\n Entered file name is      :" + filename);
		d.display("\n Entered receiving peer port number:" + std::to_string(rcvPort));
		d.display("\n Entered sending peer port number:" + std::to_string(sndPort));
		d.display("\n %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% \n");
		mtx.unlock();
		std::thread send(&Sender::starting, std::ref(s), sndPort); // start of new thread for sending
		std::thread receive(&Receiver::start, std::ref(r), rcvPort); // start of new thread for receiving
		send.join();
		receive.join();
		::Sleep(1000);
	}
	catch (std::exception& ex)
	{
		Verbose::show("  Exception caught:", always);
		Verbose::show(std::string("\n  ") + ex.what() + "\n\n");
	}

}


// Acts as a server i.e, receives from acting client with listening port which starts its own listener for receiving message
void Peer2::Server(int endpoint1, int endpoint2)
{
	Display d;
    d.display("\n\n**********************I AM Server [PEER 1]******************************\n\n");
	try
	{
		d.display("\n %%%%%%%%%%%%%%%%%%%%%%Entered Parameters are%%%%%%%%%%%%%%%%%%%%");
		d.display("\n Entered server port number:" + std::to_string(endpoint1));
		d.display("\n %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% \n");
		Receiver r;
		std::thread receiverThread(&Receiver::start, std::ref(r), endpoint1);
		receiverThread.join();
		d.display("\n ################ Exiting Server Executing Function ############ \n ");
	}
	catch (std::exception& ex)
	{
		Verbose::show("  Exception caught:", always);
		Verbose::show(std::string("\n  ") + ex.what() + "\n\n");
	}
}


int main(int argc, char* argv[])
{
	Display d;
	Peer2 p;
	if (argc < 4)
	{
		d.display("\n Options entered are invalid,check readme file\n");
		return 0;
	}
	std::string type = argv[1];
	int endpoint1 = std::stoi(argv[2]); //send port for client or receive port for server
	int endpoint2 = std::stoi(argv[3]); //receive port for client or dummy port for server
	std::string filename = argv[4];

	if (type == "client")              //if type is client,act as client i.e sending message
	{
		p.Client(endpoint1, endpoint2, filename);
	}
	else if (type == "server")         //if type is server,acts as server ie., receive message
	{
		p.Server(endpoint1, endpoint2);
	}
	else
		d.display("\n Please Check your inputs carefully \n");
	return 1;
}