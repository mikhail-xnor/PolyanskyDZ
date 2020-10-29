#pragma once

template <class ValueType>
class list;

template <typename ValueType>
class iterator;

template <class ValueType>
class element
{
	friend class list<ValueType>;
	friend class iterator<ValueType>;
	ValueType elem;
	element* top;
	element* bot;
};


template <class ValueType>
class list
{
	element<ValueType>* front_ptr;
	element<ValueType>* back_ptr;
public:
	
	typedef const iterator<ValueType> const_iterator;
	typedef iterator<ValueType> iterator;
	
	list();
	~list();
	list(const list<ValueType>&);
	list<ValueType>& operator=(const list<ValueType>&);

	void erase(iterator&);
	void push_back(ValueType);
	void push_front(ValueType);
	bool empty() const;
	ValueType pop_back();
	ValueType pop_front();
	
	ValueType back(); 
	iterator find(ValueType select); //if not found return null ptr
	
	
	const_iterator begin() const;
	const_iterator end() const;

	iterator begin();
	iterator end();
};


template <typename ValueType>
class iterator
{
	friend class list<ValueType>;
	mutable element<ValueType>* ptr;
public:
	iterator() : ptr(nullptr) {};
	iterator(element<ValueType>* elem) : ptr(elem) {}
	const iterator& operator=(const iterator& it) const
	{
		ptr = it.ptr;
		return *this;
	}
	iterator& operator=(const iterator& it)
	{
		ptr = it.ptr;
		return *this;
	}
	ValueType operator*() const
	{ 
		if (!ptr->bot)
			throw std::exception("Out of range!");
		return ptr->elem;
	}
	ValueType& operator*() 
	{ 
		if (!ptr->bot)
			throw std::exception("Out of range!");
		return ptr->elem;
	}
	const iterator operator++() const {
		if (!ptr->bot)
			throw std::exception("Out of range!");
		else
			ptr = ptr->bot;
		return *this;
	}
	iterator operator++() {
		if (!ptr->bot)
			throw std::exception("Out of range!");
		else
			ptr = ptr->bot;
		return *this;
	}
	const iterator operator--() const {
		if (!ptr->top)
			throw std::exception("Out of range!");
		else
			ptr = ptr->top;
		return *this;
	}
	iterator operator--() {
		if (!ptr->top)
			throw std::exception("Out of range!");
		else
			ptr = ptr->top;
		return *this;
	}
	bool operator==(const iterator& b) const
	{
		return ptr == b.ptr;
	}
	bool operator!=(const iterator& b) const
	{
		return ptr != b.ptr;
	}

};



#include "methods_class_list.inl"
