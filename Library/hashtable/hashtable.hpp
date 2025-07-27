#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

/* ************************************************************************** */

#include <random>

/* ************************************************************************** */

#include "../container/dictionary.hpp"

/* ************************************************************************** */

namespace lasd { //acoeff + key + bcoeff %prime %tablesize

/* ************************************************************************** */

template <typename Data>
class Hashable {
  //tool class: quali sono i dati di cui è noto l'hash? <Data>=int,float,double
  //operator(x) -> x applica il calcolo mod
public:

  unsigned long operator()(const Data&)const noexcept; // (concrete function should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class HashTable : virtual public ResizableContainer,
                  virtual public DictionaryContainer<Data>{
                  // Must extend ResizableContainer,
                  //             DictionaryContainer<Data>

private:

  // ...

protected:

  using DictionaryContainer<Data>::size;

  unsigned long foff=0; // First offset
  unsigned long loff=0; // Second offset

  unsigned long tableSize=32;
  unsigned long primenum=4051;
  static const Hashable<Data> enchash;

public:

  // Default constructor
  HashTable();

  // Copy constructor
  HashTable(const HashTable<Data>&);

  // Move constructor
  HashTable(HashTable<Data>&&)noexcept;

  // Destructor
  virtual ~HashTable()=default;

  /* ************************************************************************ */

  // Copy assignment
  HashTable<Data>& operator=(const HashTable&); // Copy assignment of abstract types should not be possible.

  // Move assignment
  HashTable<Data>& operator=(HashTable&&)noexcept; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTable&)const noexcept=delete; // Comparison of abstract hashtable is possible but not required.
  bool operator!=(const HashTable&)const noexcept=delete; // Comparison of abstract hashtable is possible but not required.

protected:

  // Auxiliary member functions

  // hash di primo livello
  unsigned long HashKey(unsigned long key) const noexcept;

  unsigned long randomHash(const int&);

};

/* ************************************************************************** */

}

#include "hashtable.cpp"

#endif
