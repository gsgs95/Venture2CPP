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
	
	// Dangling Pointer ���� ������ ���� �ڽ��� �ּҰ��� ���ѱ�� ������
	unique_ptr<A> SPA = make_unique<A>();
	// unique_ptr<A> SPB = SPA; ERROR
	// �뵵 : Singleton Pattern ���� ���


	shared_ptr<A> SPA2 = make_shared<A>();
	shared_ptr<A> SPA3 = SPA2;

	SPA2 = nullptr;
	SPA3 = nullptr;

	// �ش� �Ҵ�� �ּҸ� ����Ű�� ��� �����Ͱ� �������
	// �ش� �޸𸮸� �ڵ����� ����


	// ���� ���� ������, ������ ���������� ����� �뵵.
	// �����Ҷ����� ���ſ� ����Ʈ �����͵��� ����ϸ� ���ſ� ���� ���������� ������� ������ ������
	weak_ptr<A> WP = SPA3;
	weak_ptr<A> WP2 = SPA;

	


	return 0;
}