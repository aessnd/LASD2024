
#ifndef STACKLST_HPP
#define STACKLST_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class StackLst : virtual public Stack<Data>,
                 virtual public List<Data> {
  // Must extend Stack<Data>,
  //             List<Data>

private:

  // ...

protected:

  using List<Data>::List;
  
  // ...

public:

  // Default constructor
  StackLst();

  /* ************************************************************************ */

  // Specific constructor
  StackLst(const TraversableContainer<Data>&); // A stack obtained from a TraversableContainer
  StackLst(MappableContainer<Data>&&)noexcept; // A stack obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  StackLst(const StackLst<Data>& cpy);

  // Move constructor
  StackLst(StackLst<Data>&& mve)noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~StackLst()=default;

  /* ************************************************************************ */

  // Copy assignment
  StackLst& operator=(const StackLst<Data>&);

  // Move assignment
  StackLst& operator=(StackLst<Data>&&)noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const StackLst<Data>&)const noexcept;
  bool inline operator!=(const StackLst<Data>&)const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)

  const Data& Top() const override; // Override Stack member (non-mutable version; must throw std::length_error when empty)
  Data& Top() override; // Override Stack member (non-mutable version; must throw std::length_error when empty)
  void Pop()override; // Override Stack member (must throw std::length_error when empty)
  Data TopNPop() override; // Override Stack member (must throw std::length_error when empty)
  void Push(const Data&)override; // Override Stack member (copy of the value)
  void Push(Data&&)noexcept override; // Override Stack member (move of the value)

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  using List<Data>::Clear;

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "stacklst.cpp"

#endif
