
#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/mappable.hpp"

#include "../iterator/iterator.hpp"

#include "../stack/vec/stackvec.hpp"
// #include "../stack/lst/stacklst.hpp"
#include "../queue/vec/queuevec.hpp"
// #include "../queue/lst/queuelst.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTree : virtual public PreOrderTraversableContainer<Data>,
                   virtual public PostOrderTraversableContainer<Data>,
                   virtual public InOrderTraversableContainer<Data>,
                   virtual public BreadthTraversableContainer<Data>{
  // Must extend PreOrderTraversableContainer<Data>,
  //             PostOrderTraversableContainer<Data>,
  //             InOrderTraversableContainer<Data>,
  //             BreadthTraversableContainer<Data>

private:

  // ...

protected:

  using Container::size;

public:

  struct Node {

  protected:

    // Comparison operators
    bool operator==(const Node&) const noexcept; // Comparison of abstract types is possible, but is not visible.
    bool inline operator!=(const Node&) const noexcept; // Comparison of abstract types is possible, but is not visible.

  public:

    friend class BinaryTree<Data>;

    /* ********************************************************************** */

    // Destructor
    virtual ~Node()=default;

    /* ********************************************************************** */

    // Copy assignment
    Node& operator=(const Node&)=delete; // Copy assignment of abstract types is not possible.

    // Move assignment
    Node& operator=(Node&&)noexcept=delete; // Move assignment of abstract types is not possible.

    /* ********************************************************************** */

    // Specific member functions

    virtual const Data& Element()const noexcept=0; // Immutable access to the element (concrete function should not throw exceptions)

    virtual bool IsLeaf() const noexcept; // (concrete function should not throw exceptions)
    virtual bool HasLeftChild() const noexcept=0; // (concrete function should not throw exceptions)
    virtual bool HasRightChild() const noexcept=0; // (concrete function should not throw exceptions)

    virtual const Node& LeftChild() const=0; // (concrete function must throw std::out_of_range when not existent)
    virtual const Node& RightChild() const=0; // (concrete function must throw std::out_of_range when not existent)

  };

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTree()=default;

  /* ************************************************************************ */

  // Copy assignment
  BinaryTree& operator=(const BinaryTree<Data>&)=delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  BinaryTree& operator=(BinaryTree<Data>&&)noexcept=delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTree<Data>&) const noexcept; // Comparison of abstract binary tree is possible.
  bool operator!=(const BinaryTree<Data>&) const noexcept; // Comparison of abstract binary tree is possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual const Node& Root() const =0; // (concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  using typename TraversableContainer<Data>::TraverseFun;

  virtual void Traverse(const TraverseFun) const override; // Override TraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

  virtual void PreOrderTraverse(const TraverseFun) const override; // Override PreOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

  virtual void PostOrderTraverse(const TraverseFun) const override; // Override PostOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from InOrderTraversableContainer)

  virtual void InOrderTraverse(const TraverseFun) const override; // Override InOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthTraversableContainer)

  virtual void BreadthTraverse(const TraverseFun) const override; // Override BreadthTraversableContainer member

protected:

  // Auxiliary functions, if necessary!
  void PreOrderTraverse(const TraverseFun,const Node*)const;

  void PostOrderTraverse(const TraverseFun,const Node*)const;

  void InOrderTraverse(const TraverseFun,const Node*)const;

  void BreadthTraverse(const TraverseFun,const Node*)const;

};

/* ************************************************************************** */

template <typename Data>
class MutableBinaryTree : virtual public ClearableContainer,
                          virtual public BinaryTree<Data>,
                          virtual public PreOrderMappableContainer<Data>,
                          virtual public PostOrderMappableContainer<Data>,
                          virtual public InOrderMappableContainer<Data>,
                          virtual public BreadthMappableContainer<Data>{
  // Must extend ClearableContainer,
  //             BinaryTree<Data>,
  //             PreOrderMappableContainer<Data>,
  //             PostOrderMappableContainer<Data>,
  //             InOrderMappableContainer<Data>,
  //             BreadthMappableContainer<Data>

private:

  // ...

protected:

  using Container::size;

public:

  struct MutableNode : public BinaryTree<Data>::Node{
    // Must extend Node

    friend class MutableBinaryTree<Data>;

    /* ********************************************************************** */

    // Destructor
    virtual ~MutableNode()=default;

    /* ********************************************************************** */

    // Copy assignment
    MutableNode& operator=(const MutableNode&)=delete; // Copy assignment of abstract types is not possible.

    // Move assignment
    MutableNode& operator=(MutableNode&&)noexcept=delete; // Move assignment of abstract types is not possible.

    /* ********************************************************************** */

    // Specific member functions

    virtual Data& Element() noexcept=0; // Mutable access to the element (concrete function should not throw exceptions)

    virtual MutableNode& LeftChild() =0; // (concrete function must throw std::out_of_range when not existent)
    virtual MutableNode& RightChild() =0; // (concrete function must throw std::out_of_range when not existent)

  };


  /* ************************************************************************ */

  // Destructor
  virtual ~MutableBinaryTree()=default;

  /* ************************************************************************ */

  // Copy assignment
  virtual MutableBinaryTree& operator=(const MutableBinaryTree<Data>&)=delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  virtual MutableBinaryTree& operator=(MutableBinaryTree<Data>&&)noexcept=delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual MutableNode& Root() =0; // (concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFun;

  virtual void Map(const MapFun)override; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  virtual void PreOrderMap(const MapFun)override; // Override PreOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  virtual void PostOrderMap(const MapFun)override; // Override PostOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from InOrderMappableContainer)

  virtual void InOrderMap(const MapFun)override; // Override InOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthMappableContainer)

  virtual void BreadthMap(const MapFun)override; // Override BreadthMappableContainer member

protected:
  
  // Auxiliary functions, if necessary!
  void PreOrderMap(const MapFun,MutableNode*);

  void PostOrderMap(const MapFun,MutableNode*);

  void InOrderMap(const MapFun,MutableNode*);

  void BreadthMap(const MapFun,MutableNode*);

};

/* ************************************************************************** */

template <typename Data>
class BTPreOrderIterator : virtual public ForwardIterator<Data>,
                           virtual public ResettableIterator<Data> {
  // Must extend ForwardIterator<Data>,
  //             ResettableIterator<Data>

private:

  // ...

protected:

  const typename BinaryTree<Data>::Node* root = nullptr;
  const typename BinaryTree<Data>::Node* cursor=nullptr;
  StackVec<const typename BinaryTree<Data>::Node*> stk;

public:

  // Specific constructors
  BTPreOrderIterator(const BinaryTree<Data>&); // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTPreOrderIterator(const BTPreOrderIterator<Data>&);

  // Move constructor
  BTPreOrderIterator(BTPreOrderIterator<Data>&&)noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPreOrderIterator()=default;

  /* ************************************************************************ */

  // Copy assignment
  BTPreOrderIterator& operator=(const BTPreOrderIterator<Data>&);

  // Move assignment
  BTPreOrderIterator& operator=(BTPreOrderIterator<Data>&&)noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTPreOrderIterator<Data>&) const noexcept;
  bool operator!=(const BTPreOrderIterator<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  const Data& operator*() const override; // (throw std::out_of_range when terminated)

  bool Terminated() const noexcept override; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  BTPreOrderIterator& operator++() override; // (throw std::out_of_range when terminated)

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  void Reset() noexcept override; // (should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class BTPreOrderMutableIterator : virtual public MutableIterator<Data>,
                                  virtual public BTPreOrderIterator<Data> {
  // Must extend MutableIterator<Data>,
  //             BTPreOrderIterator<Data>

private:

  // ...

protected:

  /*typename MutableBinaryTree<Data>::MutableNode* root=nullptr;
  typename MutableBinaryTree<Data>::MutableNode* cursor=nullptr;
  StackVec<typename MutableBinaryTree<Data>::MutableNode*> stk;*/

public:

  // Specific constructors
  BTPreOrderMutableIterator(MutableBinaryTree<Data>&); // An iterator over a given mutable binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTPreOrderMutableIterator(const BTPreOrderMutableIterator<Data>&);

  // Move constructor
  BTPreOrderMutableIterator(BTPreOrderMutableIterator<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPreOrderMutableIterator()=default;

  /* ************************************************************************ */

  // Copy assignment
  BTPreOrderMutableIterator& operator=(const BTPreOrderMutableIterator<Data>&);

  // Move assignment
  BTPreOrderMutableIterator& operator=(BTPreOrderMutableIterator<Data>&&)noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTPreOrderMutableIterator<Data>&) const noexcept;
  bool operator!=(const BTPreOrderMutableIterator<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  Data& operator*() override; // (throw std::out_of_range when terminated)

};

/* ************************************************************************** */

template <typename Data>
class BTPostOrderIterator : virtual public ForwardIterator<Data>,
                            virtual public ResettableIterator<Data>{
  // Must extend ForwardIterator<Data>,
  //             ResettableIterator<Data>

private:

  // ...

protected:

  const typename BinaryTree<Data>::Node* root=nullptr;
  const typename BinaryTree<Data>::Node* cursor=nullptr;
  StackVec<const typename BinaryTree<Data>::Node*> stk;

  // Auxiliary functions
  const typename BinaryTree<Data>::Node* DeepNode(const typename BinaryTree<Data>::Node* deep){
    if(deep!=nullptr){
      //Finchè ha figlio sinistro, memorizza il nodo
      while(deep->HasLeftChild()){
        stk.Push(deep);
        deep=&deep->LeftChild();
      }

      //Se non ha figli sinistri, ma ha figlio destro, richiama la funzione sul
      //figlio destro
      if(deep->HasRightChild())
      {
        stk.Push(deep);
        deep=DeepNode(&deep->RightChild());
      }
    }
    return deep;
    /*if(deep!=nullptr)
    {
      while(deep->HasLeftChild())
      {
        stk.Push(deep);
        deep=&deep->LeftChild();
        if(deep->HasRightChild() && !(deep->HasLeftChild()))
        {
          stk.Push(deep);
          deep=&deep->RightChild();
        }
      }
      if(deep->HasRightChild())
      {
        stk.Push(deep);
        cursor=DeepNode(&cursor->RightChild());
      }
    }
    return deep;*/
  }

public:

  // Specific constructors
  BTPostOrderIterator(const BinaryTree<Data>&); // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTPostOrderIterator(const BTPostOrderIterator<Data>&);

  // Move constructor
  BTPostOrderIterator(BTPostOrderIterator<Data>&&)noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPostOrderIterator()=default;

  /* ************************************************************************ */

  // Copy assignment
  BTPostOrderIterator& operator=(const BTPostOrderIterator<Data>&);

  // Move assignment
  BTPostOrderIterator& operator=(BTPostOrderIterator<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTPostOrderIterator<Data>&) const noexcept;
  bool operator!=(const BTPostOrderIterator<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  const Data& operator*() const override; // (throw std::out_of_range when terminated)

  bool Terminated() const noexcept override; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  BTPostOrderIterator& operator++() override; // (throw std::out_of_range when terminated)

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  void Reset() noexcept override; // (should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class BTPostOrderMutableIterator : virtual public MutableIterator<Data>,
                                   virtual public BTPostOrderIterator<Data>{
  // Must extend MutableIterator<Data>,
  //             BTPostOrderIterator<Data>

private:

  // ...

protected:

  /*typename MutableBinaryTree<Data>::MutableNode* root=nullptr;
  typename MutableBinaryTree<Data>::MutableNode* cursor=nullptr;
  StackVec<typename MutableBinaryTree<Data>::MutableNode*> stk;*/

public:

  // Specific constructors
  BTPostOrderMutableIterator(MutableBinaryTree<Data>&); // An iterator over a given mutable binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTPostOrderMutableIterator(const BTPostOrderMutableIterator<Data>&);

  // Move constructor
  BTPostOrderMutableIterator(BTPostOrderMutableIterator<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPostOrderMutableIterator()=default;

  /* ************************************************************************ */

  // Copy assignment
  BTPostOrderMutableIterator& operator=(const BTPostOrderMutableIterator<Data>&);

  // Move assignment
  BTPostOrderMutableIterator& operator=(BTPostOrderMutableIterator<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTPostOrderMutableIterator<Data>&) const noexcept;
  bool operator!=(const BTPostOrderMutableIterator<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  Data& operator*() override; // (throw std::out_of_range when terminated)

};

/* ************************************************************************** */

template <typename Data>
class BTInOrderIterator : virtual public ForwardIterator<Data>,
                          virtual public ResettableIterator<Data>{
  // Must extend ForwardIterator<Data>,
  //             ResettableIterator<Data>

private:

  // ...

protected:

  const typename BinaryTree<Data>::Node* root=nullptr;
  const typename BinaryTree<Data>::Node* cursor=nullptr;
  StackVec<const typename BinaryTree<Data>::Node*> stk;

  const typename BinaryTree<Data>::Node* DeepNode(const typename BinaryTree<Data>::Node* deep){
    
    //Finchè ha figlio sinistro, memorizza il nodo
    //N.B, con operator++, non si creano rivisite su un nodo, in quandto
    // deep->HasLeftChild() permette al ciclo di terminare prima di 
    // Moemorizzare un nodo che non ha figli sinistri
    while (deep != nullptr && (deep->HasLeftChild())) {
        stk.Push(deep);
        deep = &deep->LeftChild();
    }
    return deep;
  }

 

public:

  // Specific constructors
  BTInOrderIterator(const BinaryTree<Data>&); // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTInOrderIterator(const BTInOrderIterator<Data>&);

  // Move constructor
  BTInOrderIterator(BTInOrderIterator<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BTInOrderIterator()=default;

  /* ************************************************************************ */

  // Copy assignment
  BTInOrderIterator& operator=(const BTInOrderIterator<Data>&);

  // Move assignment
  BTInOrderIterator& operator=(BTInOrderIterator<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTInOrderIterator<Data>&) const noexcept;
  bool operator!=(const BTInOrderIterator<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  const Data& operator*() const override; // (throw std::out_of_range when terminated)

  bool Terminated() const noexcept override; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  BTInOrderIterator& operator++() override; // (throw std::out_of_range when terminated)

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  void Reset() noexcept override; // (should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class BTInOrderMutableIterator : virtual public MutableIterator<Data>,
                                 virtual public BTInOrderIterator<Data> {
  // Must extend MutableIterator<Data>,
  //             BTInOrderIterator<Data>

private:

  // ...

protected:

  typename MutableBinaryTree<Data>::MutableNode* root=nullptr;
  typename MutableBinaryTree<Data>::MutableNode* cursor=nullptr;
  StackVec<typename MutableBinaryTree<Data>::MutableNode*> stk;

public:

  // Specific constructors
  BTInOrderMutableIterator(MutableBinaryTree<Data>&); // An iterator over a given mutable binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTInOrderMutableIterator(const BTInOrderMutableIterator<Data>&);

  // Move constructor
  BTInOrderMutableIterator(BTInOrderMutableIterator<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BTInOrderMutableIterator()=default;

  /* ************************************************************************ */

  // Copy assignment
  BTInOrderMutableIterator& operator=(const BTInOrderMutableIterator<Data>&);

  // Move assignment
  BTInOrderMutableIterator& operator=(BTInOrderMutableIterator<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTInOrderMutableIterator<Data>&)const noexcept;
  bool operator!=(const BTInOrderMutableIterator<Data>&)const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  Data& operator*() override; // (throw std::out_of_range when terminated)

};

/* ************************************************************************** */

template <typename Data>
class BTBreadthIterator : virtual public ForwardIterator<Data>,
                          virtual public ResettableIterator<Data>{
  // Must extend ForwardIterator<Data>,
  //             ResettableIterator<Data>

private:

  // ...

protected:

  const typename BinaryTree<Data>::Node* root=nullptr;
  const typename BinaryTree<Data>::Node* cursor=nullptr;

  QueueVec<const typename BinaryTree<Data>::Node*> que;

public:

  // Specific constructors
  BTBreadthIterator(const BinaryTree<Data>&); // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTBreadthIterator(const BTBreadthIterator<Data>&);

  // Move constructor
  BTBreadthIterator(BTBreadthIterator<Data>&&)noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BTBreadthIterator()=default;

  /* ************************************************************************ */

  // Copy assignment
  BTBreadthIterator& operator=(const BTBreadthIterator<Data>&);

  // Move assignment
  BTBreadthIterator& operator=(BTBreadthIterator<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTBreadthIterator<Data>&) const noexcept;
  bool operator!=(const BTBreadthIterator<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  const Data& operator*() const override; // (throw std::out_of_range when terminated)

  bool Terminated() const noexcept override; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  BTBreadthIterator& operator++() override; // (throw std::out_of_range when terminated)

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  void Reset() noexcept override; // (should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class BTBreadthMutableIterator : virtual public MutableIterator<Data>,
                                 virtual public BTBreadthIterator<Data>{
  // Must extend MutableIterator<Data>,
  //             BTBreadthIterator<Data>

private:

  // ...

protected:

  typename MutableBinaryTree<Data>::MutableNode* root=nullptr;
  typename MutableBinaryTree<Data>::MutableNode* cursor=nullptr;
  QueueVec<typename MutableBinaryTree<Data>::MutableNode*> que;

public:

  // Specific constructors
  BTBreadthMutableIterator(MutableBinaryTree<Data>&); // An iterator over a given mutable binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTBreadthMutableIterator(const BTBreadthMutableIterator<Data>&);

  // Move constructor
  BTBreadthMutableIterator(BTBreadthMutableIterator<Data>&&)noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BTBreadthMutableIterator()=default;

  /* ************************************************************************ */

  // Copy assignment
  BTBreadthMutableIterator& operator=(const BTBreadthMutableIterator<Data>&);

  // Move assignment
  BTBreadthMutableIterator& operator=(BTBreadthMutableIterator<Data>&&)noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTBreadthMutableIterator<Data>&) const noexcept;
  bool operator!=(const BTBreadthMutableIterator<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  Data& operator*() override; // (throw std::out_of_range when terminated)

};

/* ************************************************************************** */

}

#include "binarytree.cpp"

#endif
