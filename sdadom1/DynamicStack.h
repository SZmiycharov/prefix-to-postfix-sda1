/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Stanislav Zmiycharov
* @idnumber 61883
* @task 1
* @compiler GCC
*
*/

#include <assert.h>
#include <exception>

template <typename T>
class DynamicStack {
	class Container {
	public:
		T Data;
		Container* pNext;
		Container(T Data, Container* pNext = NULL);
	};

public:
	DynamicStack();
	~DynamicStack();
	DynamicStack(DynamicStack const & obj);
	DynamicStack& operator=(DynamicStack const & obj);

	T& Peek();
	void Push(const T & Element);
	bool Pop();
	void RemoveAll();
	int GetLength();

private:
	void Init();
	void Destroy();
	void CopyFrom(DynamicStack const &obj);

	Container* pTop;
	size_t Used;
};

template <typename T>
DynamicStack<T>::Container::Container(T Data, Container* pNext)
{
	this->Data = Data;
	this->pNext = pNext;
}

template <typename T>
DynamicStack<T>::DynamicStack()
{
	Init();
}

template <typename T>
DynamicStack<T>::DynamicStack(DynamicStack const & obj)
{
	Init();
	CopyFrom(obj);
}

template <typename T>
DynamicStack<T>::~DynamicStack()
{
	Destroy();
}

template <typename T>
DynamicStack<T>& DynamicStack<T>::operator=(DynamicStack<T> const & obj)
{
	if (this != &obj)
	{
		Destroy();
		CopyFrom(obj);
	}

	return *this;
}

template <typename T>
void DynamicStack<T>::Init()
{
	pTop = 0;
	Used = 0;
}

template <typename T>
void DynamicStack<T>::Destroy()
{
	Container* p;

	while (pTop)
	{
		p = pTop;
		pTop = pTop->pNext;
		delete p;
	}

	Init();
}

template <typename T>
void DynamicStack<T>::CopyFrom(DynamicStack const& obj)
{
	if (obj.Used == 0)
	{
		return;
	}
		
	Container<T> *ours, *theirs;

	try
	{
		pTop = new Container(obj.pTop->Data);

		ours = pTop;
		theirs = obj.pTop->pNext;

		while (theirs)
		{
			ours->pNext = new Container(theirs->Data);
			ours = ours->pNext;
			theirs = theirs->pNext;
		}

		Used = obj.Used;
	}
	catch (const std::bad_alloc&)
	{
		Destroy();	
		fprintf(stderr, "Exception thrown on failure allocating memory\n");
		return -1;
	}
}

template<typename T>
T& DynamicStack<T>::Peek()
{
	assert(Used != 0);

	return pTop->Data;
}

template <typename T>
void DynamicStack<T>::Push(const T & Element)
{
	pTop = new Container(Element, pTop);

	Used++;
}

template<typename T>
bool DynamicStack<T>::Pop()
{
	if (Used == 0)
	{
		return false;
	}
		
	Container* pOld = pTop;
	pTop = pTop->pNext;
	delete pOld;

	Used--;

	return true;
}

template <typename T>
void DynamicStack<T>::RemoveAll()
{
	Destroy();
}

template <typename T>
int DynamicStack<T>::GetLength()
{
	return Used;
}