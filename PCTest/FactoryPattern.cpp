#include <iostream>

using namespace std;

// Factory Pattern
class Object
{
public:
	Object() {}
	virtual ~Object() {}
};

class Item : public Object
{
public:
	Item() {}
	virtual ~Item() {}
};

class Factory
{
public:
	Factory() {}
	virtual ~Factory() {}

	Object* Make()
	{
		return new Item;
	}
};

int main()
{
	return 0;
}