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
		//��ֹ�Լ����Լ� ֻ��һ�������ʱ�����Ұָ��
		if (_ptr != tmp._ptr)
		{
			//���ͷ��Լ� �ٹ����µ�;
			if (_ptr) delete _ptr;

			_ptr = tmp._ptr;
			tmp._ptr == nullptr;
		}
		return *this;
	}
	// ����������ָ�����Ƶ���Ϊ
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