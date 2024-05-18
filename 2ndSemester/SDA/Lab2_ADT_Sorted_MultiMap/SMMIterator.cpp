#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <exception>

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
    this->current_key = *this->map.head;
    this->current_value = *this->current_key.first_pair;
    key_index = 0;
    value_index = 0;
}

void SMMIterator::first(){
    this->current_key = *this->map.head;
    this->current_value = *this->current_key.first_pair;
    key_index = 0;
    value_index = 0;
}

void SMMIterator::next(){
//    if(this->current_value.next == NULL)
//        throw exception();
    if(!this->valid())
        throw exception();
	if(this->value_index + 1< this->current_key.number_of_values) {
        this->current_value = *this->current_value.next;
        this->value_index ++;
    }
    else if (this->key_index < this->map.length) {
        this->current_key = *this->current_key.next;
        this->current_value = *this->current_key.first_pair;
        this->key_index ++;
        this->value_index = 0;
    }
}

bool SMMIterator::valid() const{
	if(this->key_index >= this->map.length)
        return false;
	return true;
}

TElem SMMIterator::getCurrent() const{
    if(!this->valid())
        throw exception();
	TElem result;
    result.first = this->current_key.key;
    result.second  = this->current_value.info.second;
	return result;
}


