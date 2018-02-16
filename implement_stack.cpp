#include <iostream>
#include <string>
#include <queue>

using namespace std;

template <class A_Type> class implement_stack
{
public:
	implement_stack() { }
	~implement_stack() { }
	A_Type top() {
		return top_type;
	}
	void push(A_Type newString) {
		fQueue.push(newString);
		top_type = newString;
	}
	void pop() {
		int S = fQueue.size() - 2;
		for (int i = 0; i < S; i++)
		{
			lQueue.push(fQueue.front());
			fQueue.pop();
		}
		if (!fQueue.empty())
		{
			top_type = fQueue.front();
			lQueue.push(fQueue.front());
			fQueue.pop();
			if (!fQueue.empty())
			{
				fQueue.pop();
			}
		}
		fQueue.swap(lQueue);
	}
	int size() {
		int ret = fQueue.size() + lQueue.size();
		return ret;
	}
	bool empty() {
		bool ret = false;
		if (fQueue.empty() && lQueue.empty())
		{
			ret = true;
		}
		return ret;
	}
private:
	queue<A_Type> fQueue;
	queue<A_Type> lQueue;
	A_Type top_type;
};
int main()
{
	implement_stack <string> newStack;
	newStack.push("hello");
	cout << "newStack has \"" << newStack.top() << "\"" << endl;
	newStack.push("this works!");
	newStack.push("10");
	newStack.push("20");
	newStack.push("30");
	cout << "size of newStack is " << newStack.size() << endl;
	int S = newStack.size();
	for (int i = 0; i < S; i++)
	{
		cout << newStack.top() << endl;
		newStack.pop();
	}
	if (newStack.empty())
	{
		cout << "now newStack is empty" << endl;
	}
	else
	{
		cout << "now newStack is not empty" << endl;
	}

	return 0;
}

