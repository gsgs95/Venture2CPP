#include <iostream>
using namespace std;

class Parent
{

public:
	Parent()
	{
		cout << "Parent()" << endl;
	}
	virtual ~Parent()
	{
		cout << "~Parent()" << endl;
	}

	 virtual void Do()
	{
		cout << "Parent Do()" << endl;
	}

};

class Child1 : public Parent
{
public:
	Child1()
	{
		cout << "Child1()" << endl;

	}
	~Child1()
	{
		cout << "~Child1()" << endl;

	}

	void Do() override
	{
		cout << "Child1 Do()" << endl;
		Parent::Do();
	}
};

class Child2 : public Parent
{
public:
	Child2()
	{
		cout << "Child2()" << endl;

	}
	~Child2()
	{
		cout << "~Child2()" << endl;

	}

	void Do() override
	{
		cout << "Child2 Do()" << endl;
	}
};


int main()
{
	Parent* C = new Child1();
	//C->Do();
	//dynamic_cast<Child1*>(C)->Do();
	C->Do();
	if (dynamic_cast<Parent*>(C))
	{
		dynamic_cast<Parent*>(C)->Do();
	}

	delete C;

	return 0;
}