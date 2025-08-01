
#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

/* ************************************************************************** */

#include "mappable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class DictionaryContainer : virtual public TestableContainer<Data> {
  // Must extend TestableContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~DictionaryContainer()=default;

  /* ************************************************************************ */

  // Copy assignment
  DictionaryContainer& operator=(const DictionaryContainer&)=delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  DictionaryContainer& operator=(DictionaryContainer&&)noexcept=delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const DictionaryContainer&)const noexcept=delete; // Comparison of abstract types is not possible.
  bool operator!=(const DictionaryContainer&)const noexcept=delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual bool Insert(const Data&)=0; // Copy of the value
  virtual bool Insert(Data&&)=0; // Move of the value
  virtual bool Remove(const Data&)=0;

  bool InsertAll(const TraversableContainer<Data>&); // Copy of the value; From TraversableContainer; True if all are inserted
  bool InsertAll(MappableContainer<Data>&&)noexcept; // Move of the value; From MappableContainer; True if all are inserted
  bool RemoveAll(const TraversableContainer<Data>&); // From TraversableContainer; True if all are removed

  bool InsertSome(const TraversableContainer<Data>&); // Copy of the value; From TraversableContainer; True if some is inserted
  bool InsertSome(MappableContainer<Data>&&)noexcept; // Move of the value; From MappableContainer; True if some is inserted
  bool RemoveSome(const TraversableContainer<Data>&); // From TraversableContainer; True if some is removed

};

/* ************************************************************************** */

}

#include "dictionary.cpp"

#endif
