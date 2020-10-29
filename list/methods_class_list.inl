#include "class_list.h"
template <class ValueType>
inline list<ValueType>::list()
{
	front_ptr = new element<ValueType>;
	back_ptr = front_ptr;
	front_ptr->bot = nullptr;
	front_ptr->top = nullptr;
}

template<class ValueType>
inline list<ValueType>::~list()
{
	while (back_ptr)
	{
		element<ValueType> *temp = back_ptr;
		back_ptr = back_ptr->top;
		delete temp;
	}
}

template<class ValueType>
inline list<ValueType>::list(const list<ValueType> &main_list)
{
	front_ptr = new element<ValueType>;
	back_ptr = front_ptr;
	front_ptr->bot = nullptr;
	front_ptr->top = nullptr;
	element<ValueType> *el = main_list.front_ptr;
	while (el->bot)
	{
		push_back(el->elem);
		el = el->bot;
	}
}

template<class ValueType>
inline list<ValueType>& list<ValueType>::operator=(const list<ValueType> &main_list)
{
	front_ptr = new element<ValueType>;
	back_ptr = front_ptr;
	front_ptr->bot = nullptr;
	front_ptr->top = nullptr;
	element<ValueType> *el = main_list.front_ptr;
	while (el->bot)
	{
		push_back(el->elem);
		el = el->bot;
	}
	return *this;
}

template<class ValueType>
inline void list<ValueType>::erase(iterator &it_cur)
{
	if (empty())
		throw std::exception("Out of range!");
	it_cur.ptr->bot->top = it_cur.ptr->top;
	if (it_cur.ptr->top)
		it_cur.ptr->top->bot = it_cur.ptr->bot;
	else
		front_ptr = it_cur.ptr->bot;
	element<ValueType> *temp = it_cur.ptr;
	it_cur.ptr = it_cur.ptr->bot;
	delete temp;
}

template<class ValueType>
inline void list<ValueType>::push_back(ValueType count)
{
	element<ValueType> *temp = new element<ValueType>;
	temp->top = back_ptr->top;	
	temp->bot = back_ptr;
	temp->elem = count;
	back_ptr->top = temp;
	if (back_ptr == front_ptr)
		front_ptr = temp;
	else
		temp->top->bot = temp;
}

template<class ValueType>
inline void list<ValueType>::push_front(ValueType count)
{
	element<ValueType> *temp = new element;
	temp->bot = front_ptr;
	temp->top = front_ptr->top; // можно заменить на nullptr
	temp->elem = count;
	front_ptr->top = temp;
	front_ptr = temp;
}

template<class ValueType>
inline bool list<ValueType>::empty() const
{
	return !front_ptr->bot;
}

template<class ValueType>
inline ValueType list<ValueType>::pop_back()
{
	if (empty())
		throw std::exception("Out of range!");
	ValueType el = back_ptr->top->elem;
	element<ValueType> *temp = back_ptr->top;
	back_ptr->top = back_ptr->top->top;
	if (!back_ptr->top)
		front_ptr = back_ptr;
	else
		back_ptr->top->bot = back_ptr;
	delete temp;
 	return el;
}

template<class ValueType>
inline ValueType list<ValueType>::pop_front()
{
	if (empty())
		throw std::exception("Out of range!");
	ValueType el = front_ptr->elem;
	element<ValueType> *temp = front_ptr;
	front_ptr = front_ptr->bot;
	front_ptr->top = temp->top; // можно заменить на nullptr
	delete temp;
	return el;
}

template<class ValueType>
inline ValueType list<ValueType>::back()
{
	if (empty())
		throw std::exception("Out of range!");
	return back_ptr->top->elem;
}

template<class ValueType>
inline typename iterator<ValueType> list<ValueType>::find(ValueType select)
{
	for (list<ValueType>::iterator it = begin(); it != end(); ++it)
		if (*it == select)
			return it;
	return nullptr;
}

template<class ValueType>
inline typename const iterator<ValueType> list<ValueType>::begin() const 
{
	return iterator(front_ptr);
}

template<class ValueType>
inline typename const iterator<ValueType> list<ValueType>::end() const
{
	return iterator(back_ptr);
}

template<class ValueType>
inline typename iterator<ValueType> list<ValueType>::begin()
{
	return iterator(front_ptr);
}

template<class ValueType>
inline typename iterator<ValueType> list<ValueType>::end()
{
	return iterator(back_ptr);
}