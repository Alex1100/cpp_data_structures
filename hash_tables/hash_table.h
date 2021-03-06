// hash_table.h
#pragma once

#include <typeinfo>
#include <sstream>
#include <math.h>
#include <string>
#include <iostream>

using namespace std;

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "node.h"
#include "linked_list.h"


template <class T, class E, class Y>
class HashTable {
private:
  LinkedList<T, E, Y> *storage;
  int front, rear, size, storage_limit;
  const int hash_salt = {11021992};
  void expand();
  void shrink();
public:
  HashTable(int initial_size = 10) {
    front = 0;
    rear = initial_size - 1;
    size = 0;
    storage_limit = initial_size;
    storage = new LinkedList<T, E, Y>[storage_limit];
  }
  ~HashTable(){
    delete []storage;
  }
  int get_size();
  int get_storage_limit();
  int hash(T key);
  void insert(T key, E val, Y weight = 0.0, Y heuristic = 0.0);
  node<T, E, Y> *remove(T key);
  LinkedList<T, E, Y> *get_bucket(int hash_key_index);
  bool is_int(T key);
  bool contains(T key);
  node<T, E, Y> *get_entry(T key);
  LinkedList<T, E, Y> *get_storage();
};

#include "hash_table_impl.h"

#endif
