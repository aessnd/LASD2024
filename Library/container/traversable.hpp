
#ifndef TRAVERSABLE_HPP
#define TRAVERSABLE_HPP

/* ************************************************************************** */

#include <functional>

/* ************************************************************************** */

#include "testable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class TraversableContainer : virtual public TestableContainer<Data>{
  // Must extend TestableContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~TraversableContainer()=default;

  /* ************************************************************************ */

  // Copy assignment
  TraversableContainer& operator=(const TraversableContainer&)=delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  TraversableContainer& operator=(TraversableContainer&&)noexcept=delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const TraversableContainer&)const noexcept=delete; // Comparison of abstract types might be possible.
  bool operator!=(const TraversableContainer&)const noexcept=delete; // Comparison of abstract types might be possible.

  /* ************************************************************************ */

  // Specific member function (##DA DEFINIRE##)

  using TraverseFun = std::function<void(const Data &)>;

  virtual void Traverse(const TraverseFun)const=0;

  template <typename Accumulator>
  using FoldFun = std::function<Accumulator(const Data &,const Accumulator &)>;

  template <typename Accumulator>
  Accumulator Fold(FoldFun<Accumulator>,const Accumulator&)const;

  /* ************************************************************************ */

  // Specific member function (inherited from TestableContainer)

  virtual bool Exists(const Data&)const noexcept override; // Override TestableContainer member

};

/* ************************************************************************** */

template <typename Data>
class PreOrderTraversableContainer : virtual public TraversableContainer<Data> {
  // Must extend TraversableContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~PreOrderTraversableContainer()=default;

  /* ************************************************************************ */

  // Copy assignment
  PreOrderTraversableContainer& operator=(const PreOrderTraversableContainer&)=delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  PreOrderTraversableContainer& operator=(PreOrderTraversableContainer&&)noexcept=delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const PreOrderTraversableContainer&) const noexcept=delete; // Comparison of abstract types might be possible.
  bool operator!=(const PreOrderTraversableContainer&) const noexcept=delete; // Comparison of abstract types might be possible.

  /* ************************************************************************ */

  // Specific member function

  using typename TraversableContainer<Data>::TraverseFun;

  virtual void PreOrderTraverse(const TraverseFun)const =0;

  template <typename Accumulator>
  using FoldFun = typename TraversableContainer<Data>::FoldFun<Accumulator>;

  template <typename Accumulator>
  Accumulator PreOrderFold(FoldFun<Accumulator>,const Accumulator&)const;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  virtual void Traverse(const TraverseFun)const override=0; // Override TraversableContainer member

};

/* ************************************************************************** */

template <typename Data>
class PostOrderTraversableContainer : virtual public TraversableContainer<Data>{
  // Must extend TraversableContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~PostOrderTraversableContainer()=default;

  /* ************************************************************************ */

  // Copy assignment
  PostOrderTraversableContainer& operator=(const PostOrderTraversableContainer&)=delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  PostOrderTraversableContainer& operator=(PostOrderTraversableContainer&&)noexcept=delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const PostOrderTraversableContainer&)const noexcept=delete; // Comparison of abstract types might be possible.
  bool operator!=(const PostOrderTraversableContainer&)const noexcept=delete; // Comparison of abstract types might be possible.

  /* ************************************************************************ */

  // Specific member function

  using typename TraversableContainer<Data>::TraverseFun;

  virtual void PostOrderTraverse(const TraverseFun)const=0;

  template <typename Accumulator>
  using FoldFun = typename TraversableContainer<Data>::FoldFun<Accumulator>;

  template <typename Accumulator>
  Accumulator PostOrderFold(FoldFun<Accumulator>,const Accumulator&)const;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  virtual void Traverse(const TraverseFun) const=0; // Override TraversableContainer member

};

/* ************************************************************************** */

template <typename Data>
class InOrderTraversableContainer : virtual public TraversableContainer<Data> {
  // Must extend TraversableContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~InOrderTraversableContainer()=default;

  /* ************************************************************************ */

  // Copy assignment
  InOrderTraversableContainer& operator=(const InOrderTraversableContainer&)=delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  InOrderTraversableContainer& operator=(InOrderTraversableContainer&&)noexcept=delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const InOrderTraversableContainer&)const noexcept=delete; // Comparison of abstract types might be possible.
  bool operator!=(const InOrderTraversableContainer&)const noexcept=delete; // Comparison of abstract types might be possible.

  /* ************************************************************************ */

  // Specific member function

  using typename TraversableContainer<Data>::TraverseFun;

  virtual void InOrderTraverse(const TraverseFun)const =0;

  template <typename Accumulator>
  using FoldFun = typename TraversableContainer<Data>::FoldFun<Accumulator>;

  template <typename Accumulator>
  Accumulator InOrderFold(FoldFun<Accumulator>,const Accumulator&)const ;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  virtual void Traverse(const TraverseFun)const =0; // Override TraversableContainer member

};

/* ************************************************************************** */

template <typename Data>
class BreadthTraversableContainer : virtual public TraversableContainer<Data>{
  // Must extend TraversableContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~BreadthTraversableContainer()=default;

  /* ************************************************************************ */

  // Copy assignment
  BreadthTraversableContainer& operator=(const BreadthTraversableContainer<Data>&)=delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  BreadthTraversableContainer& operator=(BreadthTraversableContainer<Data>&&)noexcept=delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BreadthTraversableContainer<Data>&) const noexcept=delete; // Comparison of abstract types might be possible.
  bool operator!=(const BreadthTraversableContainer<Data>&) const noexcept=delete; // Comparison of abstract types might be possible.

  /* ************************************************************************ */

  // Specific member function

  using typename TraversableContainer<Data>::TraverseFun;

  virtual void BreadthTraverse(const TraverseFun)const =0;

  template <typename Accumulator>
  using FoldFun = typename TraversableContainer<Data>::FoldFun<Accumulator>;

  template <typename Accumulator>
  Accumulator BreadthFold(FoldFun<Accumulator>,const Accumulator&)const;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  virtual void Traverse(const TraverseFun) const override=0; // Override TraversableContainer member

};

/* ************************************************************************** */

}

#include "traversable.cpp"

#endif
