#include "pch.h"
#include "EventDispatcher.h"

CREATE_EVENT(TestEvent, int)
CREATE_EVENT(ChickenNugget, float)

void damnit(int){}
void damnit2(float){}

int main()
{
	try
	{
		jpd::EventDispatcher Dispatcher;
		Dispatcher.RegisterEvent<TestEvent>(damnit);
		Dispatcher.RegisterEvent<ChickenNugget>(damnit2);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "fk u caleb" << std::endl;
	}
}