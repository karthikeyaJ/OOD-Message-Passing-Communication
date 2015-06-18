/////////////////////////////////////////////////////////////////////////////
// Receiver.cpp - It receives the message                                  //
//                and sends ack to appropriate server                      //
// Ver 1.1                                                                 //
// Venkata Karthikeya, CSE#687 - Object Oriented Design, Spring 2015       //
//-------------------------------------------------------------------------//
// Venkata Karthikeya (c) copyright 2015                                   //
// All rights granted provided this copyright notice is retained           //
//-------------------------------------------------------------------------//
// Application: OOD Projects     #4                                       //
// Platform:    Visual Studio 2013, Dell, Win 8.1 pro                      //
//ll///////////////////////////////////////////////////////////////////////////

#include "Receiver.h"
#include <iostream>
#include "../Sender/Sender.h"

// uses base64.h and cpp files to decode the received message and returns new message
std::string ClientHandler::decoder1(std::string msg)
{
	Base64 decoder;
	std::vector<char> decodedData = decoder.decode(msg);
	std::string newdata(decodedData.begin(), decodedData.end());
	return newdata;
}




//----< Client Handler thread starts running this function >-----------------
void ClientHandler::operator()(Socket& socket_)
{
	    Receiver r; std::string msg;
		headermessages hm; int count = 0; Display d;
		do
		{
			msg = socket_.recvString();
			msg = decoder1(msg);
			std::size_t found1; std::string data;
			found1 = msg.find("CLIENTPORT");
			if (found1 != std::string::npos)
				clientport = stoi(msg.substr(found1 + 13, 4));
			found1 = msg.find("MYPORT");
			if (found1 != std::string::npos)
				mylistenport = stoi(msg.substr(found1 + 9, 4));
			found1 = msg.find("$Ack$");
			if (found1 != std::string::npos)
			{
				int k = msg.size();
				data = (msg.substr(found1 + 6, k));
				std::string print="\n\n\n ################################################# \n Printing the acknowledgement sent from other peer\n "+ msg+"\n ################################################# \n\n";
				d.display(print);
				::Sleep(10);
			}
			if (msg == "stop")
			{
				r.setStatus1();
				std::thread sendrThread(&Receiver::startSending, std::ref(r), mylistenport, clientport);
				sendrThread.join();
				break;
			}
			if (msg == "")
				break;
			hm.constructheaders(msg);  
			std::size_t found = msg.find("\n\n");
			if (found != std::string::npos)
				readstring = readstring + msg.substr(found + 2);
			count = count + 1;
		} while (msg != "quit");
		q_.enQ(std::to_string(hm.get_thread_count()));
		q_.enQ(readstring);
		q_.enQ(hm.getfilename());
		q_.enQ(std::to_string(hm.getclientport()));
		q_.enQ(std::to_string(hm.getMyPort()));
	    readstring = "";
}


// Sends the acknowledgement 
void Receiver::startSending(int serv,int client)
{
	Display d;
	d.display("  Message # =====================> sender started on server side \n");
	Sender s2(100, "file_upload_successful", serv, client, 1);
	SocketSystem ss2;
	SocketConnecter si2;
	serverport_ = serv;
	clientport_ = client;
	while (!si2.connect("localhost", clientport_))
	{
		Verbose::show("client waiting to connect");
		::Sleep(100);
	}
	headermessages h(clientport_, serverport_, "RMsg.txt$", 1);
	string header = h.createheader();
	std::string send_ = "$Ack$ : Acknowledgment=File successfully created at other peer";
	std::string mssg = header + send_;
	Base64 encoder;
	std::vector<char> encodedData(mssg.begin(), mssg.end());
	q_.enQ(encoder.encode(encodedData));
	mssg = q_.deQ();
	si2.sendString(mssg);
	mssg = "";
	Verbose::show("\n  client calling send shutdown\n");
	si2.shutDownSend();

}

// starts the receiver using the port number
void Receiver::start(int port)
{
	try
	{
		Verbose v(true);
		sl = new SocketListener(port, Socket::IP6); //socket listens for the client
		ClientHandler cp(q_);                       // if message arrives,it need to be decoded and enqued
		sl->start(cp);                              // so that this fucntion can deque and create received file
		std::string msg;
		std::string name_file;
		int i = 1;
		std::string no_of_threads=q_.deQ();
		std::string temp_count;
		int j = std::stoi(no_of_threads);
		do
		{
			if (i != 1)
			temp_count = q_.deQ();
			msg = q_.deQ();
			name_file = q_.deQ();
			clientport_ = stoi(q_.deQ());
			serverport_ = stoi(q_.deQ());
			std::ofstream file;
			if (name_file == "")
			name_file = "receivedMsg";
			file.open("./download/" + name_file, ios::out | ios::app | ios::binary); // creates a file with same filename with same message
			::Sleep(10);
			file << msg;
			file.flush();
			i = i + 1;
		} while (true);
		Verbose::show("press key to exit: ", always);
		std::cout.flush();
		std::cin.get();
		::Sleep(1000000);
	}
	catch (std::exception& ex)
	{
		Verbose::show("  Exception caught:", always);
		Verbose::show(std::string("\n  ") + ex.what() + "\n\n");
	}
}


#ifdef RECEIVER_TEST
#include "Receiver.h"
int main(int argc, char* argv[])
{
	Display d;
	d.display("starting clients and servers");
	if (argc < 2)
	{
		d.display("\n Options entered are invalid,check readme file\n");
		return 0;
	}
	int rcvPort = std::stoi(argv[2]);

	Receiver r;	
	std::thread receive(&Receiver::start, std::ref(r), rcvPort);
	receive.join();

}
#endif