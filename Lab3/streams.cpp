#include "streams.h"

StreamT::StreamT()
{
}

StreamT::StreamT(StreamT & stream) :
	messages(messages)
{
}

StreamT::~StreamT()
{
}

int StreamT::pop()
{
	std::lock_guard<std::mutex> mutex(state);

	if (messages.empty())
		return -1;

	int stream = messages.front();
	messages.pop();

	return stream;
}

void StreamT::push(char input)
{
	std::lock_guard<std::mutex> mutex(state);
	messages.push(input);
}

void StreamT::lock()
{
	state.lock();
}

void StreamT::unlock()
{
	state.unlock();
}

void InputT::operator() (StreamT & data, std::mutex& out, Event& exitEvent)
{
	char currentData = 'e';
	while (!exitEvent.getState())
	{
		currentData = data.getStreamT();

		if (currentData != 'e')
		{
			out.lock();
			std::cout << "ID:" << std::this_thread::get_id() << " get " << currentData << std::endl;
			out.unlock();
			count++;
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		}
	}
}

void InputT::run(StreamT & data, std::mutex &out, Event& exitEvent)
{
	thread = std::thread(std::ref(*this), std::ref(data), std::ref(out), std::ref(exitEvent));
}


void InputT::join()
{
	thread.join();
}

void InputT::print(char c)
{
	std::cout << "Thread " << c << " called " << count << " times" << std::endl;
}
