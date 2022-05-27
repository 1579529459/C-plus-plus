#include <iostream>
using namespace std;

template<class T>
//缺陷：该智能指针可以使用，遗憾的是多个unique_ptr的对象之间不能共享资源
class Unique_ptr
{
public:
	T* _ptr;
public:
	Unique_ptr(T* ptr)
		:_ptr(ptr)
	{}
	~Unique_ptr()
	{
		if (_ptr)
		{
			delete _ptr;
		}
	}
	// 具有指针类似行为
	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}
	// 防止被拷贝--禁止调用拷贝构造&赋值运算符重载	
	Unique_ptr(const Unique_ptr<T>&) = delete;
	Unique_ptr& operator=(const Unique_ptr<T>&) = delete;

};
