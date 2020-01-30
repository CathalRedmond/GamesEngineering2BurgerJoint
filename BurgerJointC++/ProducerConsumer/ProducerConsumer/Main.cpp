#include <thread>
#include <iostream>
#include <queue>
#include <mutex>

class Burger
{
public:
	Burger()
	{
		m_id = m_idCount;
		m_idCount++;
	}
	int getId()
	{
		return m_id;
	}
	int m_id;
	static int m_idCount;
};

int Burger::m_idCount = 0;

std::mutex mutex;
std::condition_variable condition;
std::queue<Burger> queue;
bool finished = false;
int maxProduced = 10;
int producedCount = 0;

void producer(int numberOfBurgers) 
{
	for (int index = 0; index < numberOfBurgers; index++)
	{
		if (producedCount <= maxProduced)
		{
			std::lock_guard<std::mutex> lockGuard(mutex);
			queue.push(Burger());
			producedCount++;
			std::cout << "Producing Burger " << index << std::endl;
			condition.notify_all();
		}
		else
		{
			std::cout << "Shoot System Full" << std::endl;
		}
	}
	std::lock_guard<std::mutex> lockGuard(mutex);
	finished = true;
	condition.notify_all();
}

void consumer() 
{
	while (true) 
	{
		std::unique_lock<std::mutex> lockGuard(mutex);
		condition.wait(lockGuard, [] { return finished || !queue.empty(); });
		while (!queue.empty()) 
		{
			producedCount--;
			std::cout << "Eating Burger" << queue.front().getId() << std::endl;
			queue.pop();
		}
		if (finished) break;
	}
}

int main()
{
	std::thread producerThread(producer, 50);
	std::thread consumerThread(consumer);
	producerThread.join();
	consumerThread.join();
	std::cout << "FINISHED" << std::endl;
	system("Pause");
}