#include <iostream>
using namespace std;

template<class T>
//ȱ�ݣ�������ָ�����ʹ�ã��ź����Ƕ��unique_ptr�Ķ���֮�䲻�ܹ�����Դ
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
	// ����ָ��������Ϊ
	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}
	// ��ֹ������--��ֹ���ÿ�������&��ֵ���������	
	Unique_ptr(const Unique_ptr<T>&) = delete;
	Unique_ptr& operator=(const Unique_ptr<T>&) = delete;

};
