
#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/linear.hpp"
#include "../container/dictionary.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class List : virtual public ClearableContainer,
             virtual public LinearContainer<Data>,
             virtual public DictionaryContainer<Data>{
  // Must extend ClearableContainer,
  //             LinearContainer<Data>,
  //             DictionaryContainer<Data>

private:

  // ...

protected:

  using Container::size;
  
  struct Node {

    // Data
    Data element;
    struct Node* next=nullptr;

    /* ********************************************************************** */

    // Specific constructors
    Node()=default;

    /* ********************************************************************** */

    // Copy constructor
    Node(const Data&);
    Node(const Node&);

    // Move constructor
    Node(Data&&)noexcept;
    Node(Node&&)noexcept;

    /* ********************************************************************** */

    // Destructor
    ~Node()=default;

    /* ********************************************************************** */

    // Comparison operators

    // Comparison between 2 pointers? Not needed..
    // ...

    /* ********************************************************************** */

    // Specific member functions

    // ...

  };

  Node* head=nullptr;

public:

  // Default constructor
  List()=default;

  /* ************************************************************************ */

  // Specific constructor
  List(const TraversableContainer<Data>&); // A list obtained from a TraversableContainer
  List(MappableContainer<Data>&&)noexcept;// A list obtained from a MappableContainer


  /* ************************************************************************ */

  // Copy constructor
  List(const List<Data>&);

  // Move constructor
  List(List<Data>&&)noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~List();

  /* ************************************************************************ */

  // Copy assignment
  List& operator=(const List<Data>&);

  // Move assignment
  List& operator=(List<Data>&&)noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const List<Data>&) const noexcept;
  bool operator!=(const List<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  void InsertAtFront(const Data&); // Copy of the value
  void InsertAtFront(Data&&) noexcept; // Move of the value
  void RemoveFromFront(); // (must throw std::length_error when empty)
  Data FrontNRemove(); // (must throw std::length_error when empty)

  void InsertAtBack(const Data&); // Copy of the value
  void InsertAtBack(Data&&)noexcept; // Move of the value

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override; // Override ClearableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  bool Insert(const Data&); // Copy of the value
  bool Insert(Data&&)noexcept; // Move of the value
  bool Remove(const Data&);

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  const Data& operator[](const unsigned long)const override; // Override (NonMutable) LinearContainer member (must throw std::out_of_range when out of range)
  Data& operator[](const unsigned long)override; // Override (Mutable) LinearContainer member (must throw std::out_of_range when out of range)

  const Data& Front()const override; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  Data& Front()override; // Override (Mutable) LinearContainer member (must throw std::length_error when empty)

  const Data& Back()const override; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  Data& Back()override; // Override (Mutable) LinearContainer member (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  using typename TraversableContainer<Data>::TraverseFun;

  void Traverse(const TraverseFun)const override; // Override TraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

  void PreOrderTraverse(const TraverseFun)const override; // Override PreOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

  void PostOrderTraverse(const TraverseFun)const override; // Override PostOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFun;

  void Map(const MapFun)override; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  void PreOrderMap(const MapFun)override; // Override PreOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  void PostOrderMap(const MapFun)override; // Override PostOrderMappableContainer member

protected:

  // Auxiliary functions, if necessary!

  /*Overloading delle funzioni PostOrder.
  
    Il nodo che verrà passato a tali funzioni,
    sarà la testa della lista e ricorsivamente,
    daranno il risultato aspettatosi.*/
  void PostOrderTraverse(const TraverseFun,Node*)const;

  void PostOrderMap(const MapFun,Node*);

};

/* ************************************************************************** */

}

#include "list.cpp"

#endif
