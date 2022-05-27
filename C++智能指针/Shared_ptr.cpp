#include <iostream>
#include <mutex>
using namespace std;
//

//template<class T>
//class Free//delete
//{
//public:
//	void opreatorp()(T*& ptr)
//	{
//		if (ptr)
//		{
//			free(ptr);
//			ptr == nullptr;
//		}
//	}
//};
template<class T>
class DelRef
{
public:
	void operator()(T*& ptr)
	{
		if (ptr)
		{
			delete ptr;
			ptr = nullptr;
		}
	}
};
template<class T>
class Default//delete
{
public:
	void operator()(T*& ptr)
	{
		if (ptr)
		{
			delete ptr;
			ptr == nullptr;
		}
	}
};
template<class T>
class Free
{
public:
	void operator()(T*& ptr)
	{
		if (ptr)
		{
			free(ptr);
			ptr = nullptr;
		}
	}
};

class FClose
{
public:
	void operator()(FILE*& pf)
	{
		if (pf)
		{
			fclose(pf);
			pf = nullptr;
		}
	}
};


template<class T,class D = Default<T>>
class Shared_ptr
{
public:
	T* _ptr;
	int* re_count;
	mutex* _mutex;
public:
	Shared_ptr(T* ptr)
		:_ptr(ptr)
	{
		_mutex = new mutex;
		re_count = new int(1);
	}

	Shared_ptr(const Shared_ptr& tmp)//拷贝构造
	{
		_ptr = tmp._ptr;
		_mutex = tmp._mutex;
		re_count = tmp.re_count;
		++(*re_count);
		
	}
	Shared_ptr& operator=(const Shared_ptr& tmp)
	{
		if (&tmp != this)
		{
			Release();

			re_count = tmp.re_count;
			_ptr = tmp._ptr;
			_mutex = tmp._mutex;
			// 加锁或者使用加1的原子操作
			_mutex->lock();
			++(*re_count);
			_mutex->unlock();
		}
		return *this;
	}
	T& operator*() { return  *_ptr; }
	T* operator->() { return  _ptr; }
	T* get() { return _ptr; }
	int UseCount(){ return *re_count; }

//
//
	void Release()
	{
		bool flag = false;
		// 加锁或者使用加1的原子操作
		_mutex->lock();
		if (--(*re_count) == 0 && _ptr)
		{
			D de;
			de(_ptr);
			delete re_count;
			flag = true;
		}
		_mutex->unlock();
		if (flag) delete _mutex;
	}
	////缺陷：可能会到导致循环引用，如果出现了循环引用，采用weak_ptr配合解决
};
//
int main()
{
	Shared_ptr<int> sp1(new int(10));
	Shared_ptr<int> sp2(sp1);
	*sp2 = 20;
	cout << sp1.UseCount() << endl;
	cout << sp2.UseCount() << endl;
	Shared_ptr<int> sp3(new int(10));
	sp2 = sp3;
	cout << sp1.UseCount() << endl;
	cout << sp2.UseCount() << endl;
	cout << sp3.UseCount() << endl;
	sp1 = sp3;
	cout << sp1.UseCount() << endl;
	cout << sp2.UseCount() << endl;
	cout << sp3.UseCount() << endl;

	return 0;
}
