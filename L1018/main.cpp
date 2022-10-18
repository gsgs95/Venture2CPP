#include <iostream>

using namespace std;

class A
{
public:
	A()
	{
		cout << "A()" << endl;
	}
	~A()
	{
		cout << "~A()" << endl;
	}
};

A* Make()
{
	return new A();
}

int main()
{
	//A* PA = Make();

	//A* PA = Make();
	//A* PB = PA;
	//cout << PA << endl;
	// delete PA;
	// delete PB; // ERROR : Dangling Pointer!
	
	// Dangling Pointer 문제 방지를 위해 자신의 주소값을 못넘기는 포인터
	unique_ptr<A> SPA = make_unique<A>();
	// unique_ptr<A> SPB = SPA; ERROR
	// 용도 : Singleton Pattern 에서 사용


	shared_ptr<A> SPA2 = make_shared<A>();
	shared_ptr<A> SPA3 = SPA2;

	SPA2 = nullptr;
	SPA3 = nullptr;

	// 해당 할당된 주소를 가리키는 모든 포인터가 사라지면
	// 해당 메모리를 자동해제 해줌


	// 값만 보는 포인터, 잠깐잠깐 참조용으로 사용할 용도.
	// 참조할때마다 무거운 스마트 포인터들을 사용하면 무거워 져서 참조용으로 만들어진 가벼운 포인터
	weak_ptr<A> WP = SPA3;
	weak_ptr<A> WP2 = SPA;

	


	return 0;
}