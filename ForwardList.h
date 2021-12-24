#pragma once
#include <list>

template<typename T>
class ForwardList
{
public:
	template<typename T>
	class ListNode
	{
	public:
		ListNode  *_next;
		T _value;

		ListNode(T value = T(), ListNode *next = nullptr)
		{
			this->_value = value;
			this->_next = next;
		}
		ListNode &operator=(const ListNode &) = delete;
	};

private:
	size_t _size;
	ListNode<T> *_head;
	ListNode<T> *_last;

public:

	ForwardList();
	ForwardList(const ForwardList<T> &forwardList);
	ForwardList(ForwardList<T> &&forwardList) noexcept;
	~ForwardList();
	void pop_front();
	void clear();
	ListNode<T> *insert_after(ListNode<T> * where, const T& value);
	void push_back(const T& value);
	void push_front(const T& value);
	void remove(const T& value);
	ListNode<T> *first() const
	{
		if (_head == nullptr)
			throw std::runtime_error("Empty list");
		return _head;
	}
	ListNode<T> * last() const
	{
		if (_head == nullptr)
			throw std::runtime_error("Empty list");
		return _last;
	}
	T &get(int position);
	bool empty() const noexcept;
	void reverse() noexcept;
	size_t size() const;

	template<typename TT>
	friend bool operator==(const ForwardList<TT>& left, const ForwardList<TT>& right);

	template<typename TT>
	friend bool operator!=(const ForwardList<TT>& left, const ForwardList<TT>& right);

	template<typename TT>
	friend bool operator+=(const ForwardList<TT>& left, const ForwardList<TT>& right);
};

template<typename T>
ForwardList<T>::ListNode<T> *ForwardList<T>::insert_after(ListNode<T> * where, const T& value)
{
	ListNode<T>* nn = new ListNode<T>(value);
	++_size;
	if (where == nullptr)
	{
		nn->_next = _head;
		_head = nn;
	}
	else
	{
		nn->_next = where->_next;
		where->_next = nn;
	}
	if (where == _last)
		_last = where->_next;
	return where->_next;
};


template<typename T>
ForwardList<T>::ForwardList()
{
	_size = 0;
	_head = nullptr;
	_last = nullptr;
}

template<typename T>
inline ForwardList<T>::ForwardList(const ForwardList<T> & forwardList)
{
	if (forwardList._head == nullptr)
		this->_head = nullptr;
	else
	{
		_head = new ListNode<T>(forwardList._head->_value);
		++_size;
		ListNode<T> *last = this->_head;
		ListNode<T> *current = forwardList._head->_next;
		while (current != nullptr)
		{
			last->_next = new ListNode<T>(current->_value);
			last = last->_next;
			current = current->_next;
			++_size;
		}
		_last = last;
		this->reverse();
	}
}

template<typename T>
inline ForwardList<T>::ForwardList(ForwardList<T> &&forwardList) noexcept
{
	_size = forwardList->_size;
	_head = forwardList->_head;
	_last = forwardList->_last;
	forwardList->_head = nullptr;
	forwardList->_last = nullptr;
}

template<typename T>
inline ForwardList<T>::~ForwardList()
{
	clear();
}

template<typename T>
inline void ForwardList<T>::pop_front()
{
	ListNode<T> *temp = _head;
	_head = _head->_next;
	delete temp;
	--_size;
}

template<typename T>
inline void ForwardList<T>::clear()
{
	while (_size)
	{
		pop_front();
	}
}

template<typename T>
inline void ForwardList<T>::push_back(const T & value)
{
	insert_after(_last, _value);
	/*_last = insert_after(_last, value);
	if (_head == nullptr)
		_head = _last;*/
}

template<typename T>
inline void ForwardList<T>::push_front(const T & value)
{
	insert_after()
	/*_head = new ListNode<T>(value, _head);
	if (_last == nullptr)
		_last = _head;
	++_size;*/
}

template<typename T>
inline void ForwardList<T>::remove(const T & value)
{
	ListNode<T> *current = this->_head;
	if (current == nullptr)
		return;
	while (current->_next != nullptr && current->_next->_value != value)
		current = current->_next;
	if (_head == current && current->_next == nullptr)
	{
		delete current;
		_head = nullptr;
		--_size;
		return;
	}
	if (_head != current && current->_next == nullptr)
	{
		return;
	}
	ListNode<T> *toDelete = current->_next;
	current->_next = toDelete->_next;
	delete toDelete;
	--_size;
}

template<typename T>
inline T &ForwardList<T>::get(int position)
{
	int counter = 0;

	ListNode<T> *current = this->_head;

	while (current != nullptr)
	{
		if (counter == position)
		{
			break;
		}
		current = current->_next;
		counter++;
	}
	return current->_value;
}

template<typename T>
inline bool ForwardList<T>::empty() const noexcept
{
	return _head == nullptr;
}

template<typename T>
inline void ForwardList<T>::reverse() noexcept
{
	ListNode<T> *currentNext = this->_head->_next;
	ListNode<T> *currentPrew = this->_head;
	_head->_next = nullptr;
	while (currentNext != nullptr)
	{
		ListNode<T> *tmp = currentNext->_next;
		currentNext->_next = currentPrew;
		currentPrew = currentNext;
		currentNext = tmp;
	}
	std::swap(_last, _head);
}

template<typename T>
inline size_t ForwardList<T>::size() const
{
	return _size;
}

template<typename T2>
bool operator==(const ForwardList<T2>& left, const ForwardList<T2>& right)
{
	auto pLeft = left.first();
	auto pRight = right.first();

	while (pLeft && pRight)
	{
		if (pLeft->_value != pRight->_value)
			return false;
		pLeft = pLeft->_next;
		pRight = pRight->_next;
	}

	return pLeft == pRight;
}

template<typename T2>
bool operator +=( ForwardList<T2>& list1, ForwardList<T2>& list2)
{
	list1.last->_next = list2.first;
	list1.last = list2.last;
	list2.first = nullptr;
	list2.last = nullptr;
}

template<typename T2>
bool operator!= (const ForwardList<T2>& left,
	const ForwardList<T2>& right)
{
	return !(left == right);
}