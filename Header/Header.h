#ifndef AAA_HEADER
#define AAA_HEADER

/////////////////////////////////////////////////////////////////
// Header.cpp - Demonstration of header messages in            //
//   reciever from Sender                                      //
//                                                             //
// venkata karthikeya jangal, CSE687 - OOD Project -4, Spring 2015 //
/////////////////////////////////////////////////////////////////
/*
* This Header expects to read lines of header like IP,Port,Content length
*
* Background:For HTTP like protocols the Reciever should expect
* lines in the header and bytes in the body, if there is one,
* specified by a header line something like:
*    content_length : 1024
* where 1024 is a stand-in for whatever you want your block
* size to be.
*
*/
/*
*
* Maintanence History:
* ver 1.0 - 08-Mar 2014
* - OOD Project 4

*/

//#include "../Sockets/Sockets.h"
//#include "../Threads/Threads.h"
//#include "../Threads/Locks.h"
//#include "../BlockingQueue/BlockingQueue.h"

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;


class Iheaders
{
public:
  virtual std::string createheader() = 0;
  virtual std::string getfilename() = 0;
  virtual void constructheaders(string msg) = 0;
};

class headermessages : public Iheaders
{
  
public:
  headermessages(){}
  headermessages(int cp, int mp,string fn,int tc):clientlistenerport(cp),mylistenerport(mp),filename(fn),thread_count(tc) {}

  std::string createheader()
  {
    std::string header1;
    header1 = "CLIENTPORT : " + to_string(clientlistenerport) + "\nMYPORT : " + to_string(mylistenerport) + "\nFILENAME : " + filename + "\nTHREAD_COUNTS : " + to_string(thread_count) + "\n\n";
    return header1;
  }

  void constructheaders(string msg)
  {
    std::size_t found;

    found = msg.find("CLIENTPORT");
    if (found != std::string::npos)
      clientlistenerport = stoi(msg.substr(found + 13, 4));

    found = msg.find("MYPORT");
    if (found != std::string::npos)
      mylistenerport = stoi(msg.substr(found + 9, 4));

    found = msg.find("FILENAME");
    size_t found1 = msg.find("$");
    if (found != std::string::npos)
      filename = msg.substr(found + 11, ((found1 - found) - 11));

    found = msg.find("THREAD_COUNTS");
    if (found != std::string::npos)
      thread_count = std::stoi(msg.substr(found + 15, 4));

  }
  
  std::string getfilename()
  {
    return filename;
  }


  int get_thread_count()
  {
    return thread_count;
  }

  int getclientport()
  {
    return mylistenerport;
  }
  int getMyPort()
  {
	  return clientlistenerport;
  }

 private:
  int clientlistenerport;
  int mylistenerport;
  string filename;
  int thread_count;
  string msg_;
};
#endif