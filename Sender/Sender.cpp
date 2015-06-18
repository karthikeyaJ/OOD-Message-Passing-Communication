/////////////////////////////////////////////////////////////////////////////
// Sender.cpp - It build the message and sends it to appropriate server    //
// Ver 1.1                                                                 //
// Venkata Karthikeya, CSE#687 - Object Oriented Design, Spring 2015       //
//-------------------------------------------------------------------------//
// Venkata Karthikeya (c) copyright 2015                                   //
// All rights granted provided this copyright notice is retained           //
//-------------------------------------------------------------------------//
// Application: OOD Projects     #4                                        //
// Platform:    Visual Studio 2013, Dell, Win 8.1 pro                      //
/////////////////////////////////////////////////////////////////////////////


#include "Sender.h"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
//#include "../Header/Header.h"
//#include "../Encoder/Base64.h"
using namespace FileSystem;


using namespace ApplicationHelpers;

//----< test stub starts here >----------------------------------------------

struct Cosmetic
{
	~Cosmetic()
	{
		Display d;
		d.display("\n  press key to exit: ");
		std::cin.get();
		d.display( "\n\n");
	}
} aGlobalForCosmeticAction;

//Convert to int to string
std::string Sender::ToString(int i)
{
	std::ostringstream conv;
	conv << i;
	return conv.str();
}

//encodes the message using Base64.h and cpp files and returns encoded message
std::string Sender::encoder1(std::string msg)
{
	Base64 encoder;
	std::vector<char> encodedData(msg.begin(), msg.end());
	std::string newdata(encoder.encode(encodedData));
	return newdata;
}



// Start of run function which waits for the data which is enqued and sends using sendString function by dequing
void Sender::run()
{
//	Display d;
	std::string msg;
	while (q_.size() == 0)
	{
		::Sleep(100);
	}
	while (msg != "stop")
	{
		msg = q_.deQ();
		si.sendString(msg);
	}
}

// Function called by main(). It starts a new thread for every sending client
void Sender::starting(int port)
{
	std::thread enqueThread(&Sender::connectServer2, this,port);
	enqueThread.join();
	
}

// Connects to the port number given by starting fucntion written above
void Sender::connectServer2(int port)
{
	try
	{
		    title("Creating Sending Socket for this peer", '=');
			Verbose v(true);
			std::thread senderThread(&Sender::run, this);
			senderThread.detach();
			while (!si.connect("localhost", port))
			{
				Verbose::show("client waiting to connect");
				::Sleep(100);
			}
			std::string msg; 
			size_t buffer_size = 512;	  //number of blocks -->set int = 512//---reading blocks
			std::ifstream inputFile;
			inputFile.open("./upload/" + file_, ios::binary);  //open file to upload
			if (!inputFile){
				cerr << "Error: File not found" << endl;
				exit(1);
			}
			std::cout << "\n Sharing File from folder : ./upload/" << file_ << " to the other Peer\n";
			std::vector<char> myBuffer(512);     //buffer length
			std::ostream_iterator<char> osIt(std::cout);
			file_ = file_ + "$";
			headermessages h(port1_, port2_, file_, thread_count); //creating header messages for easiness of receiver
			string header = h.createheader();
			while (inputFile)
			{
				inputFile.read(&myBuffer.front(), buffer_size);
				if (!inputFile)
					myBuffer.resize(static_cast<int>(inputFile.gcount()));    //
				for (size_t k = 0; k < myBuffer.size(); k++)
					msg = msg + myBuffer[k];
				msg = header + msg;                               //attaching header to message 
				q_.enQ(encoder1(msg));                            //encoding message and enquing it
				msg = "";
				::Sleep(10 * id()); // sleep time increases with each addition Sender
			}
			q_.enQ(encoder1("stop"));
			msg = "";
		}
		catch (std::exception& ex)
		{
			Verbose::show("  Exception caught:", always);
			Verbose::show(std::string("\n  ") + ex.what() + "\n\n");
		}
	}


//----< demonstration >------------------------------------------------------

 #ifdef SENDER_TEST
#include "../Receiver/Receiver.h"
#include "Sender.h"
int main(int argc, char* argv[])
{
	Display d;
	d.display("starting clients and servers");
	if (argc < 6)
	{
		d.display("\n Options entered are invalid,check readme file\n");
		return 0;
	}
	std::string type = argv[1];
	int rcvPort = std::stoi(argv[2]);
	int sndPort = std::stoi(argv[3]);
	std::string filename = argv[5];
	Receiver r;
	Sender s(100, filename, rcvPort, sndPort, 1);
	std::thread send(&Sender::starting, std::ref(s), sndPort);
	//std::thread receive(&Receiver::start, std::ref(r), rcvPort);
	send.join();
	//receive.join();
	Socket s_;
	SocketSystem ss;
	SocketConnecter si;
	while (!si.connect("localhost", sndPort))
	{
		Verbose::show("client waiting to connect");
		::Sleep(100);
	}
	std::string value = "My name is karthikeya";
	si.sendString(value);
	Verbose::show("\n  client calling send shutdown\n");
	si.shutDownSend();


}
#endif
