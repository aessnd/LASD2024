
#ifndef ITERATOR_HPP
#define ITERATOR_HPP

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Iterator {

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~Iterator()=default;

  /* ************************************************************************ */

  // Copy assignment
  Iterator& operator=(const Iterator<Data>&)=delete; // Copy assignment of abstract is not possible.

  // Move assignment
  Iterator& operator=(Iterator<Data>&&)noexcept=delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Iterator<Data>&)const noexcept=delete; // Comparison of abstract types is not possible.
  bool operator!=(const Iterator<Data>&)const noexcept=delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual const Data& operator*() const=0; // (non-mutable version; concrete function must throw std::out_of_range when terminated)

  virtual bool Terminated() const noexcept=0; // (concrete function should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class MutableIterator : virtual public Iterator<Data> {
  // Must extend Iterator<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~MutableIterator()=default;

  /* ************************************************************************ */

  // Copy assignment
  MutableIterator& operator=(const MutableIterator<Data>&)=delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  MutableIterator& operator=(MutableIterator<Data>&&)noexcept=delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const MutableIterator<Data>&)const noexcept=delete; // Comparison of abstract types is not possible.
  bool operator!=(const MutableIterator<Data>&)const noexcept=delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual Data& operator*() =0; // (mutable version; concrete function must throw std::out_of_range when terminated)

};

/* ************************************************************************** */

template <typename Data>
class ForwardIterator : virtual public Iterator<Data>{
  // Must extend Iterator<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~ForwardIterator()=default;

  /* ************************************************************************ */

  // Copy assignment
  ForwardIterator& operator=(const ForwardIterator<Data>&)=delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  ForwardIterator& operator=(ForwardIterator<Data>&&)noexcept=delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const ForwardIterator<Data>&)const noexcept=delete; // Comparison of abstract types is not possible.
  bool operator!=(const ForwardIterator<Data>&)const noexcept=delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual ForwardIterator& operator++()=0; // (concrete function must throw std::out_of_range when terminated)

};

/* ************************************************************************** */

template <typename Data>
class ResettableIterator : virtual public Iterator<Data> {
  // Must extend Iterator<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~ResettableIterator()=default;

  /* ************************************************************************ */

  // Copy assignment
  ResettableIterator& operator=(const ResettableIterator<Data>&)=delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  ResettableIterator& operator=(ResettableIterator<Data>&&)noexcept=delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const ResettableIterator<Data>&) const noexcept=delete; // Comparison of abstract types is not possible.
  bool operator!=(const ResettableIterator<Data>&) const noexcept=delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual void Reset()noexcept=0; // (concrete function should not throw exceptions)

};

/* ************************************************************************** */

}

#endif
