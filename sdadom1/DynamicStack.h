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
			T Value;
			Container* pNext;
			Container(T Value, Container* pNext = NULL);
	};

public:
	DynamicStack();
	~DynamicStack();
	DynamicStack(DynamicStack const & obj);
	DynamicStack& operator=(DynamicStack const & obj);

	T& Top();
	void Push(const T & Element);
	void Pop();
	int GetLength();

private:
	void RemoveAll();
	void CopyFrom(DynamicStack const &obj);

	Container* pTop;
	size_t Used;
};

template <typename T>
DynamicStack<T>::Container::Container(T Value, Container* pNext)
{
	this->Value = Value;
	this->pNext = pNext;
}

template <typename T>
DynamicStack<T>::DynamicStack()
{
	pTop = 0;
	Used = 0;
}

template <typename T>
DynamicStack<T>::~DynamicStack()
{
	RemoveAll();
}

template <typename T>
DynamicStack<T>::DynamicStack(DynamicStack const & obj)
{
	pTop = 0;
	Used = 0;
	CopyFrom(obj);
}

template <typename T>
DynamicStack<T>& DynamicStack<T>::operator=(DynamicStack<T> const & obj)
{
	if (this != &obj)
	{
		RemoveAll();
		CopyFrom(obj);
	}

	return *this;
}

template<typename T>
T& DynamicStack<T>::Top()
{
	assert(Used > 0);

	return pTop->Value;
}

template <typename T>
void DynamicStack<T>::Push(const T & Element)
{
	pTop = new Container(Element, pTop);

	++Used;
}

template<typename T>
void DynamicStack<T>::Pop()
{
	assert(Used > 0);

	Container* pOld = pTop;
	pTop = pTop->pNext;
	delete pOld;

	--Used;
}

template <typename T>
int DynamicStack<T>::GetLength()
{
	return Used;
}

template <typename T>
void DynamicStack<T>::RemoveAll()
{
	Container* p;

	while (pTop)
	{
		p = pTop;
		pTop = pTop->pNext;
		delete p;
	}

	pTop = 0;
	Used = 0;
}

template <typename T>
void DynamicStack<T>::CopyFrom(DynamicStack const& obj)
{
	if (obj.Used == 0)
	{
		return;
	}
		
	try
	{
		pTop = new Container(obj.pTop->Value);

		while (obj.pTop->pNext)
		{
			pTop->pNext = new Container(obj.pTop->pNext->Value);
			pTop = pTop->pNext;
			obj.pTop->pNext = obj.pTop->pNext->pNext;
		}

		Used = obj.Used;
	}
	catch (const std::bad_alloc&)
	{
		RemoveAll();	
		fprintf(stderr, "Exception thrown on failure allocating memory\n");
		throw;
	}
}