#include <iostream>
#include <string>
#include <vector>

class Animal
{
public:
	virtual void sound() = 0;
	void info()
	{
		std::cout << "동물은 숨을 쉽니다.\n";
	}

};

class Dog : public Animal
{
private:
	std::string name;
public:
	Dog(std::string s) : name(s) {};
	void sound() { std::cout << "멍멍\n"; }
	void name_print() { std::cout << name << std::endl; }
	void only_dog() { std::cout << "이건 개 클래스\n"; }
};


class Cat : public Animal
{
private:
	std::string name;
public:
	Cat(std::string s) : name(s) {};
	void sound() { std::cout << "냐옹\n"; }
	void name_print() { std::cout << name << std::endl; }
	void data() { std::cout << this << std::endl; }
	void only_cat() { std::cout << "이건 고양이 클래스\n"; }
};

int main()
{
	std::vector<Animal*> v;
	v.emplace_back(new Cat("나비"));
	v.emplace_back(new Dog("멍멍이"));

	Cat* cat; Dog* dog;
	for (size_t idx = 0; idx < v.size(); idx++)
	{
		if (cat = dynamic_cast<Cat*>(v[idx]))
		{
			cat->name_print();
			cat->sound();
			cat->only_cat();
		}
		else
		{
			dog = dynamic_cast<Dog*>(v[idx]);
			dog->name_print();
			dog->sound();
			dog->only_dog();
		}
	}
	delete cat;
	delete dog;

	return 0;
}