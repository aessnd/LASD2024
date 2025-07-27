
#ifndef BINARYTREEVEC_HPP
#define BINARYTREEVEC_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"
#include "../../vector/vector.hpp"

#define LCHILD(i)((i*2)+1)
#define RCHILD(i)((i*2)+2)

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeVec : virtual public MutableBinaryTree<Data> {
  // Must extend MutableBinaryTree<Data>

private:

  // ...

protected:

  // ...
  using typename BinaryTree<Data>::Node;
  using typename MutableBinaryTree<Data>::MutableNode;

  struct NodeVec : virtual public MutableBinaryTree<Data>::MutableNode{ // Must extend MutableNode

  friend class BinaryTreeVec<Data>;

  private:

    // ...

  protected:

    // ...

  public:

    Data item;
    unsigned long index;

    // reference to BinaryTreeVec
    Vector<NodeVec*>* btv=nullptr;

    // Default constructor
    NodeVec()=default;

    // Copy constructor
    NodeVec(const Data&,unsigned long ,Vector<NodeVec*>*);

    // Move constructor
    NodeVec(Data&&,unsigned long,Vector<NodeVec*>*)noexcept;

    // Destructor
    virtual ~NodeVec()=default;

    // Copy assignment
    NodeVec& operator=(const NodeVec&);

    // Move assignment
    NodeVec& operator=(NodeVec&&)noexcept;

    // Comparison operators
    // ...

    //Specific member function (inhereted from BinaryTree)
    const Data& Element()const noexcept override;

    bool HasLeftChild() const noexcept override;

    bool HasRightChild() const noexcept override;

    const NodeVec& LeftChild() const override; // throw std::out_of_range when not existent

    const NodeVec& RightChild() const override; // throw std::out_of_range when not existent

    //Specific member function (inhereted from MutableBinaryTree)

    NodeVec& LeftChild() override; // throw std::out_of_range when not existent

    NodeVec& RightChild() override; // throw std::out_of_range when not existent

    Data& Element() noexcept override;

  };

  Vector<typename BinaryTreeVec<Data>::NodeVec*> vec;
  using Container::size;

  

public: 

  // Default constructor
  BinaryTreeVec()=default;

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeVec(const TraversableContainer<Data>&); // A binary tree obtained from a TraversableContainer
  BinaryTreeVec(MappableContainer<Data>&&) noexcept; // A binary tree obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeVec(const BinaryTreeVec<Data>&);

  // Move constructor
  BinaryTreeVec(BinaryTreeVec<Data>&&)noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTreeVec(){ Clear();}

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeVec& operator=(const BinaryTreeVec<Data>&);

  // Move assignment
  BinaryTreeVec& operator=(BinaryTreeVec<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTreeVec<Data>&)const noexcept;
  bool operator!=(const BinaryTreeVec<Data>&)const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  const NodeVec& Root() const override; // Override BinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MutableBinaryTree)

  NodeVec& Root() override; // Override MutableBinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override; // Override ClearableContainer member

  /* ************************************************************************ */

  using typename TraversableContainer<Data>::TraverseFun;

  // Specific member function (inherited from BreadthTraversableContainer)

  void BreadthTraverse(const TraverseFun)const override; // Override BreadthTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthMappableContainer)

  using typename MappableContainer<Data>::MapFun;
  void BreadthMap(const MapFun) override; // Override BreadthMappableContainer member

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "binarytreevec.cpp"

#endif
