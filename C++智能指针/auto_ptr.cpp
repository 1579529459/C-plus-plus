#include <iostream>
using namespace std;
template<class T>
class Auto_ptr
{
public:
	T* _ptr;
public:
	Auto_ptr(T* ptr) 
		:_ptr(ptr)
	{}
	Auto_ptr(const Auto_ptr& tmp)	
	{
		
		_ptr = tmp._ptr;
		tmp._ptr == nullptr;
	}
	Auto_ptr& operator=(const Auto_ptr& tmp)
	{
		//防止自己给自己 只有一个对象的时候会有野指针
		if (_ptr != tmp._ptr)
		{
			//先释放自己 再管理新的;
			if (_ptr) delete _ptr;

			_ptr = tmp._ptr;
			tmp._ptr == nullptr;
		}
		return *this;
	}
	// 让类对象具有指针类似的行为
	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}
	~Auto_ptr()
	{
		if (_ptr) delete _ptr;
	}
};