#pragma once
#include <windows.h>
#include <queue>
#include <mutex>
#include <iostream>
#include <thread>
#include <string>

class StreamT
{
	std::mutex state;
	std::queue<char> data;
public:
	StreamT();
	StreamT(StreamT& stream);
	~StreamT();
	char pop(); // return data
	void push(char data); // adds data
	void lock(); 
	void unlock();
};

class EventT
{
private:
	std::mutex state; // shows acces
	bool happened;
public:
	EventT() : happened(false) {};
	~EventT() {};
	void setEvent() { 
	  std::lock_guard<std::mutex> mutex(state); 
	  happened = true; 
	} // evet happened
	void resetEvent() { 
	  std::lock_guard<std::mutex> mutex(state); 
	  happened = false; 
	} // not happened
	bool getState() { 
	  std::lock_guard<std::mutex> mutex(state); 
	  return happened; 
	}
};

class InputT
{
	int count;
	std::thread thread;
	
public:
	Reader() : counter(0) {};
	void run(Data& data, std::mutex& out, Event& exitEvent);
	void operator() (Data& data, std::mutex &out, Event& exitEvent);
	void join();
	void printStats(int i);
	
};
