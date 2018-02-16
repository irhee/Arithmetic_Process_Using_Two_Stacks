#include <iostream>
#include <string>
#include <stack>

using namespace std;

template <class A_Type> class implement_queue
{
public:
	implement_queue() { }
	~implement_queue() { }
	A_Type front() {
		if (deStack.empty())
		{
			int S = enStack.size();
			for (int i = 0; i < S; i++)
			{
				deStack.push(enStack.front());
				enStack.pop();
			}
		}
		return deStack.front();
	}
	void enQueue(A_Type newString) {
		enStack.push(newString);
	}
	void deQueue() {
		if (deStack.empty())
		{
			int S = enStack.size();
			for (int i = 0; i < S; i++)
			{
				deStack.push(enStack.front());
				enStack.pop();
			}
		}
		deStack.pop();
	}
	int size() {
		int ret = deStack.size() + enStack.size();
		return ret;
	}
	bool empty() {
		bool ret = false;
		if (deStack.empty() && enStack.empty())
		{
			ret = true;
		}
		return ret;
	}
private:
	stack<A_Type> enStack;
	stack<A_Type> deStack;
};
int main()
{
	implement_queue <string> newQueue;
	newQueue.enQueue("hello");
	cout << "newQueue has \"" << newQueue.front() << "\"" << endl;
	newQueue.enQueue("this works!");
	newQueue.enQueue("10");
	newQueue.enQueue("20");
	newQueue.enQueue("30");
	cout << "size of newQueue is " << newQueue.size() << endl;
	int S = newQueue.size();
	for (int i = 0; i < S; i++)
	{
		cout << newQueue.front() << endl;
		newQueue.deQueue();
	}
	if (newQueue.empty())
	{
		cout << "now newQueue is empty" << endl;
	}
	else
	{
		cout << "now newQueue is not empty" << endl;
	}

    return 0;
}

