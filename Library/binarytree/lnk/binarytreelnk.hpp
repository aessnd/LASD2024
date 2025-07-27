
#ifndef BINARYTREELNK_HPP
#define BINARYTREELNK_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeLnk : virtual public MutableBinaryTree<Data>{
  // Must extend MutableBinaryTree<Data>

private:

  // ...

protected:

  using Container::size;

  // ...

  struct NodeLnk :virtual public MutableBinaryTree<Data>::MutableNode{ // Must extend MutableNode

  friend class BinaryTreeLnk<Data>;

  private:

    // ...

  protected:

  

  public:
  Data item;
  NodeLnk *rchild=nullptr;
  NodeLnk *lchild=nullptr;

    // Default constructor
    NodeLnk()=default;

    // Specific constructor
    NodeLnk(const Data& target){item=target;  rchild=lchild=nullptr;};

    NodeLnk(Data&& target)noexcept{std::swap(item,target);  rchild=lchild=nullptr;};

    // Copy constructor
    NodeLnk(const NodeLnk&);

    // Move constructor
    NodeLnk(NodeLnk&&)noexcept;

    // Destructor
    virtual ~NodeLnk()=default;

    // Copy assignment
    NodeLnk& operator=(const NodeLnk&);

    // Move assignment
    NodeLnk& operator=(NodeLnk&&)noexcept;

    // Comparison operators
    // ...

  /* ************************************************************************ */

    // Specific member functions(inhereted from BinaryTree)
    const Data& Element() const noexcept override{
      return item;
    }

    bool HasLeftChild() const noexcept override{
      return (lchild!=nullptr);
    }

    bool HasRightChild() const noexcept override{
      return (rchild!=nullptr);
    }

    const NodeLnk& LeftChild() const override{
      if(HasLeftChild())
        return *lchild;
      else throw std::out_of_range("Error: Left child doesnt exist!");
    }

    const NodeLnk& RightChild() const override{
      if(HasRightChild())
        return *rchild;
      else throw std::out_of_range("Error: Right child doesnt exist!");
    }

    // Specific member functions(inhereted from BinaryTree)
    
    Data& Element() noexcept override{
      return item;
    }

    NodeLnk& LeftChild() override{
      if(HasLeftChild())
        return *lchild;
      else throw std::out_of_range("Error: Right child doesnt exist!");
    }

    NodeLnk& RightChild() override{
      if(HasRightChild())
        return *rchild;
      else throw std::out_of_range("Error: Right child doesnt exist!");
    }
  };

  NodeLnk* root=nullptr;

  //Auxiliary function: delete BT in postorder
  void Clear(NodeLnk*)noexcept;


public:

  // Default constructor

  BinaryTreeLnk()=default;

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeLnk(const TraversableContainer<Data>&); // A binary tree obtained from a TraversableContainer
  BinaryTreeLnk(MappableContainer<Data>&&) noexcept; // A binary tree obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeLnk(const BinaryTreeLnk<Data>&);

  // Move constructor
  BinaryTreeLnk(BinaryTreeLnk<Data>&&)noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTreeLnk(){
    Clear();
  }

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeLnk& operator=(const BinaryTreeLnk<Data>&);

  // Move assignment
  BinaryTreeLnk& operator=(BinaryTreeLnk<Data>&&)noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTreeLnk<Data>&) const noexcept;
  bool operator!=(const BinaryTreeLnk<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  const NodeLnk& Root() const override{
    if(size>0)
      return *root;
    else throw std::length_error("Error: binary tree lnk is empty!");
  } // Override BinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MutableBinaryTree)

  NodeLnk& Root() override{
    if(size>0)
      return *root;
    else throw std::length_error("Error: binary tree lnk is empty!");
  } // Override MutableBinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override; // Override ClearableContainer member

};

/* ************************************************************************** */

}

#include "binarytreelnk.cpp"

#endif
