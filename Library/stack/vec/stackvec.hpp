
#ifndef STACKVEC_HPP
#define STACKVEC_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class StackVec : virtual public Stack<Data>,
                 virtual public Vector<Data>{
  // Must extend Stack<Data>,
  //             Vector<Data>

private:

  // ...

protected:

  unsigned long front=0;
  using Vector<Data>::elements; 
  using Container::size;

  // ...

public:

  // Default constructor
  StackVec();

  /* ************************************************************************ */

  // Specific constructor
  StackVec(const TraversableContainer<Data>&); // A stack obtained from a TraversableContainer
  StackVec(MappableContainer<Data>&&)noexcept; // A stack obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  StackVec(const StackVec<Data>&);

  // Move constructor
  StackVec(StackVec<Data>&&)noexcept;

  /* ************************************************************************ */

  // Destructor
  ~StackVec()=default;

  /* ************************************************************************ */

  // Copy assignment
  StackVec& operator=(const StackVec<Data>&);

  // Move assignment
  StackVec& operator=(StackVec<Data>&&)noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const StackVec<Data>&) const noexcept;
  bool operator!=(const StackVec<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)

  const Data& Top() const override; // Override Stack member (non-mutable version; must throw std::length_error when empty)
  Data& Top() override; // Override Stack member (non-mutable version; must throw std::length_error when empty)
  void Pop() override; // Override Stack member (must throw std::length_error when empty)
  Data TopNPop() override; // Override Stack member (must throw std::length_error when empty)
  void Push(const Data&) override; // Override Stack member (copy of the value)
  void Push(Data&&)noexcept override; // Override Stack member (move of the value)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  bool inline Empty() const noexcept override; // Override Container member

  unsigned long inline Size() const noexcept override; // Override Container member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override; // Override ClearableContainer member

protected:

  // Auxiliary functions, if necessary!
  void Reduce();
  void Expand();

};

/* ************************************************************************** */

}

#include "stackvec.cpp"

#endif
