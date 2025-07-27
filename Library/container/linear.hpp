
#ifndef LINEAR_HPP
#define LINEAR_HPP

/* ************************************************************************** */

#include "mappable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class LinearContainer : virtual public PreOrderMappableContainer<Data>, 
                        virtual public PostOrderMappableContainer<Data>{
  // Must extend PreOrderMappableContainer<Data>,
  //             PostOrderMappableContainer<Data>

private:

  // ...

protected:

  using Container::size;

public:

  // Destructor
  virtual ~LinearContainer()=default;

  /* ************************************************************************ */

  // Copy assignment
  LinearContainer& operator=(const LinearContainer&)=delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  LinearContainer& operator=(LinearContainer&&)noexcept=delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const LinearContainer&)const noexcept; // Comparison of abstract types is possible.
  bool operator!=(const LinearContainer&)const noexcept; // Comparison of abstract types is possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual const Data& operator[](const unsigned long) const=0; // (non-mutable version; concrete function must throw std::out_of_range when out of range)
  virtual Data& operator[](const unsigned long)=0; // (mutable version; concrete function must throw std::out_of_range when out of range)

  virtual const Data& Front()const; // (non-mutable version; concrete function must throw std::length_error when empty)
  virtual Data& Front(); // (mutable version; concrete function must throw std::length_error when empty)

  virtual const Data& Back()const; // (non-mutable version; concrete function must throw std::length_error when empty)
  virtual Data& Back(); // (mutable version; concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  using typename TraversableContainer<Data>::TraverseFun;

  virtual void Traverse(const TraverseFun)const override; // Override TraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

  virtual void PreOrderTraverse(const TraverseFun) const override; // Override PreOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

  virtual void PostOrderTraverse(const TraverseFun) const override; // Override PostOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFun;

  virtual void Map(const MapFun) override; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  virtual void PreOrderMap(const MapFun) override; // Override PreOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  virtual void PostOrderMap(const MapFun) override; // Override PostOrderMappableContainer member

};

/* ************************************************************************** */

template <typename Data>
class SortableLinearContainer: virtual public LinearContainer<Data> {
  // Must extend LinearContainer<Data>

private:

  // ...

protected:

  using Container::size;

public:

  // Destructor
  virtual ~SortableLinearContainer() =default;

  /* ************************************************************************ */

  // Copy assignment
  SortableLinearContainer& operator=(const SortableLinearContainer&)=delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  SortableLinearContainer& operator=(SortableLinearContainer&&)noexcept=delete; // Move assignment of abstract types is not be possible.

  /* ************************************************************************ */

  /*Ai fini del progetto, si è deciso di non implementare
  gli operatori di confronto di SortableContainer, in quanto,
  nella gerarchia di classi seguente..

                    (LinearContainer)
                   /                 \
      (SortableLinearContainer)    (Vector)
                   \                 /
                     (SortableVector)

  ..SortableVector trova ambiguità nell'utilizzo
  dell'operatore di confronto (bisogna che specifichi
  se utilizza l'operatore di confronto di SortableLC o
  di Vector).

  Nel caso, con il progredire nello sviluppo delle librerie,
  se si terrà necessario, adeguerò al meglio tale ambiguità. 
  */

  // Comparison operators
  //bool operator==(const SortableLinearContainer&) const noexcept; // Comparison of abstract types is possible.
  //bool operator!=(const SortableLinearContainer&) const noexcept; // Comparison of abstract types is possible.

  /* ************************************************************************ */

  // Specific member function

  virtual void Sort() noexcept=0;

protected:

  // Auxiliary member functions

  // ...

};

/* ************************************************************************** */

}

#include "linear.cpp"

#endif
