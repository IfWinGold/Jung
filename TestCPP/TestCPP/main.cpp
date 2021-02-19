#include<iostream>

using namespace std;

void main()
{
	class Test1
	{
	public:
		Test1()
		{
			cout << "부모 클래스 생성"<<this << endl;
		}
		void Start()
		{
			cout << "test! " <<this<< endl;
		}
	};

	class Test2 : public Test1
	{
	public:	
		Test2()
		{
			cout << "자식 클래스 생성" <<this<<endl;
		}
		void Start2()
		{
			cout << "Test2" <<this<<endl;
		}
	};
	Test1 test1;
	test1.Start();
	Test2 test; 
	test.Start();
	test.Start2();
}
