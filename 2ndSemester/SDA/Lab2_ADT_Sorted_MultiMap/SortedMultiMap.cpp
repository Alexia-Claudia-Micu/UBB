#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

nod* null_nod(){
    nod *null_nod = new nod;
    null_nod->next = NULL; null_nod->info = NULL_TELEM;
    return null_nod;
}

SLL* null_sll(){
    SLL *null_sll = new SLL;
    null_sll->number_of_values = 0;
    null_sll->next = NULL;
    null_sll->key = NULL_TVALUE;
    null_sll->first_pair = null_nod();
    null_sll->first_pair->next = null_nod();
    return null_sll;
}

// Complexity of search: O(n) + O(nrValues) = O(n)
vector<TValue> SortedMultiMap::removeKey(TKey key) {
    vector<TValue> vectorOfRemovedValues;
    vectorOfRemovedValues = this->search(key);
    for(int i = 0; i < vectorOfRemovedValues.size(); i++)
        this->remove(key, vectorOfRemovedValues.at(i));
    return vectorOfRemovedValues;
}

SortedMultiMap::SortedMultiMap(Relation r){
    this->relation = r;
    this->length = 0;
    this->head = null_sll();
    this->head->next = null_sll();
    this->head->number_of_values = 0;
}

// O(2*nrKeys + nrValues) -> O(n)
void SortedMultiMap::add(TKey new_key, TValue new_value) {
    if(!this->search(new_key).empty()){
        int i = 0;
        SLL *key_iterator = this->head;
        if(key_iterator->key != new_key)
            for( i = 0; i < this->length && key_iterator->key != new_key; i++) // Worst case: O(nrKeys); Best case: O(1)
                key_iterator = key_iterator->next;
        nod *nod_iterator = key_iterator->first_pair;
        nod *prev = nod_iterator;
        if(!this->relation(new_value, nod_iterator->info.second)) // Worst case: O(nrValues); Best case: O(1)
            for( i = 0; i < key_iterator->number_of_values && !this->relation(new_value, nod_iterator->next->info.second); i++) {
                prev = nod_iterator;
                nod_iterator = nod_iterator->next;
            }
        nod *nod_to_add = new nod;
        nod_to_add->next = nod_iterator;
        nod_to_add->info = TElem (new_key, new_value);
        if(this->relation(new_value, key_iterator->first_pair->info.second))
            key_iterator->first_pair = nod_to_add;
        else
            prev->next = nod_to_add;
        key_iterator->number_of_values ++;
    }
    else{
        SLL *key_iterator = this->head;
        SLL *prev = key_iterator;
        int i;
        if(!this->relation(new_key, key_iterator->key) && this->length != 0) // Worst case: O(nrKeys); Best case: O(1)
            for(i = 0; i < this->length && !this->relation(new_key, key_iterator->key); i++) {
                prev = key_iterator;
                key_iterator = key_iterator->next;
            }
        SLL *key_to_add = null_sll();
        key_to_add->next = key_iterator;
        key_to_add->number_of_values = 1;
        key_to_add->key = new_key;
        nod *nod_to_add = new nod;
        nod_to_add->info = TElem (new_key, new_value);
        nod_to_add->next = null_nod();
        key_to_add->first_pair = nod_to_add;
        if(this->relation(new_key, this->head->key) || this->length == 0)
            this->head = key_to_add;
        else
            prev->next = key_to_add;
        this->length ++;
    }

    /*
    if(this->length == 0 || (this->relation(c, this->head->key) && c != this->head->key)){
        this->length ++;
        nod *nod_to_add = new nod;
        nod_to_add->next = null_nod(); nod_to_add->info.first = c; nod_to_add->info.second = v;
        SLL *elem_to_add = new SLL;
        elem_to_add->number_of_values = 1;
        elem_to_add->key = c;
        elem_to_add->first_pair = *nod_to_add;
        elem_to_add->next = this->head;
        this->head = elem_to_add;
        return;
    }
    int i;
    SLL* list_iterator = this->head;
    for(i = 0; i < this->length && (!this->relation(c, list_iterator->key) && list_iterator->key != c); i++)
        list_iterator = list_iterator->next;
    if (list_iterator->key == c)
    {
        nod* nod_iterator = &list_iterator->first_pair;
        for( i = 0; i < list_iterator->number_of_values - 1 && !this->relation(v, nod_iterator->info.second); i++)
            nod_iterator = nod_iterator->next;
        nod *nod_to_add = new nod;
        nod_to_add->info.first = c; nod_to_add->info.second = v;
        nod_to_add->next = nod_iterator->next;
        nod_iterator->next = nod_to_add;
        list_iterator->number_of_values ++;
    } else{
        SLL *element_to_add = new SLL;
        element_to_add->number_of_values = 1;
        element_to_add->key = c;
        SLL list_iterator2 = *this->head;
        if(list_iterator2.key != list_iterator->key)
            while(list_iterator2.next != list_iterator)
                list_iterator2 = *list_iterator2.next;
        list_iterator2.next = element_to_add;
        element_to_add->next = list_iterator->next;
        nod *nod_to_add = new nod;
        nod_to_add->next = null_nod();
        nod_to_add->info.second = v; nod_to_add->info.first = c;
        element_to_add->first_pair = *nod_to_add;
        this->length ++;
    }*/
}

// O(nrKeys) + Theta(nrValues) -> O(nrKey + nrValues) -> O(2*n) -> O(n)
vector<TValue> SortedMultiMap::search(TKey c) const {
    SLL list_iterator = *this->head;
    for(int i = 0; i < this->length - 1 && list_iterator.key != c; i++) // Worst case: O(nrKeys); Best case: O(1)
        list_iterator = *list_iterator.next;
    vector<TValue> result;
    if (list_iterator.key == c) {
        nod nod_iterator = *list_iterator.first_pair;
        result.push_back(list_iterator.first_pair->info.second);
        for (int i = 0; i < list_iterator.number_of_values - 1; i++) // Theta(nrValues)
        {
            nod_iterator = *nod_iterator.next;
            result.push_back(nod_iterator.info.second);
        }
    }
	return result;
}

// O(2*nrKeys + nrValues) -> O(n)
bool SortedMultiMap::remove(TKey c, TValue v) {
    int i;
    SLL *list_iterator = this->head;
    if(this->head->first_pair->info.second == v && this->head->key == c)
    {
        if(this->head->number_of_values == 1) {
            this->head = this->head->next;
            this->length --;
            return true;
        }
        this->head->number_of_values --;
        this->head->first_pair = this->head->first_pair->next;
        return true;
    }
    for( i = 0; i < this->length - 1 && !this->relation(c, list_iterator->key); i++) // Worst case: O(nrKeys); Best case: O(1)
        list_iterator = list_iterator->next;
    if(list_iterator->key == c)
    {
        nod *nod_iterator = list_iterator->first_pair;
        if( nod_iterator->info.second == v) {
            list_iterator->first_pair = list_iterator->first_pair->next;
            list_iterator->number_of_values --;
            if(list_iterator->number_of_values == 0)
            {
                if(this->length == 1) {
                    this->length = 0;
                    this->head = null_sll();
                    return true;
                }
                SLL *list_iterator2 = this->head;
                while (list_iterator2->next != list_iterator) // Worst case: O(nrKeys); Best case: O(1)
                    list_iterator2 = list_iterator2->next;
                list_iterator2->next = list_iterator->next;
                this->length --;
            }
            return true;
        }
        for( i = 0; i < list_iterator->number_of_values - 1 && nod_iterator->next->info.second != v; i++) { // Worst case: O(nrValues); Best case: O(1)
            nod_iterator = nod_iterator->next;
        }
        if(nod_iterator->next->info.second == v)
        {
            nod_iterator->next = nod_iterator->next->next;
            list_iterator->number_of_values --;
            return true;
        }
    }
    return false;
}


// Theta(nrKeys)
int SortedMultiMap::size() const {
    int size = this->head->number_of_values;
    SLL list_iterator = *this->head;
    for(int i = 0; i < this->length - 1 ; i ++){
        list_iterator = *list_iterator.next;
        size += list_iterator.number_of_values;
    }
    return size;
}

bool SortedMultiMap::isEmpty() const {
    return this->length == 0;
}

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

SortedMultiMap::~SortedMultiMap() {
	//TODO - Implementation
}
