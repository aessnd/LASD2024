
#ifndef QUEUEVEC_HPP
#define QUEUEVEC_HPP

/* ************************************************************************** */

#include "../queue.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class QueueVec : virtual public Queue<Data>,
                 virtual public Vector<Data>{
  // Must extend Queue<Data>,
  //             Vector<Data>

private:

  /*Utile valore booleano per rappresentare
    la ciclicità della queue*/
  bool wraparound=false;

protected:

  using Vector<Data>::elements;

  /*LIFO= Last In, First Out
  -Traccia inserimento in coda : rear
  -Traccia de-coda in testa: front*/
  signed long front=0;
  signed long rear=-1;

  using Container::size;
  

public:


  // Default constructor
  QueueVec();

  /* ************************************************************************ */

  // Specific constructor
  QueueVec(const TraversableContainer<Data>&); // A stack obtained from a TraversableContainer
  QueueVec(MappableContainer<Data>&&)noexcept; // A stack obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  QueueVec(const QueueVec<Data>&);

  // Move constructor
  QueueVec(QueueVec<Data>&&)noexcept;

  /* ************************************************************************ */

  // Destructor
  ~QueueVec()=default;

  /* ************************************************************************ */

  // Copy assignment
  QueueVec<Data>& operator=(const QueueVec<Data>&);

  // Move assignment
  QueueVec<Data>& operator=(QueueVec<Data>&&)noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const QueueVec<Data>&)const noexcept;
  bool operator!=(const QueueVec<Data>&)const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Queue)

  const Data& Head() const override; // Override Queue member (non-mutable version; must throw std::length_error when empty)
  Data& Head() override; // Override Queue member (mutable version; must throw std::length_error when empty)
  void Dequeue() override; // Override Queue member (must throw std::length_error when empty)
  Data HeadNDequeue() override; // Override Queue member (must throw std::length_error when empty)
  void Enqueue(const Data&) override; // Override Queue member (copy of the value)
  void Enqueue(Data&&) noexcept override; // Override Queue member (move of the value)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  bool Empty()const noexcept override; // Override Container member

  unsigned long Size()const noexcept override; // Override Container member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override; // Override ClearableContainer member

protected:

  // Auxiliary functions, if necessary!
  
  void Expand();
  void Reduce();
  void SwapVectors(unsigned long);

};

/* ************************************************************************** */

}

#include "queuevec.cpp"

#endif
