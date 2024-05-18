#pragma once

#include "SortedMultiMap.h"


class SMMIterator{
	friend class SortedMultiMap;
private:
	//DO NOT CHANGE THIS PART
	const SortedMultiMap& map;
	SMMIterator(const SortedMultiMap& map);

	SLL current_key;
    nod current_value;
    int key_index;
    int value_index;

public:
	void first();
	void next();
	bool valid() const;
   	TElem getCurrent() const;
};

