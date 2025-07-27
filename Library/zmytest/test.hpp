
#ifndef MYTEST_HPP
#define MYTEST_HPP

#include <iostream>
// Exercise1
#include "../container/container.hpp"
#include "../container/testable.hpp"
#include "../container/dictionary.hpp"
#include "../container/traversable.hpp"
#include "../container/mappable.hpp"
#include "../container/linear.hpp"
#include "../vector/vector.hpp"
#include "../list/list.hpp"
#include "../stack/stack.hpp"
#include "../stack/lst/stacklst.hpp"
#include "../stack/vec/stackvec.hpp"
#include "../queue/queue.hpp"
#include "../queue/lst/queuelst.hpp"
#include "../queue/vec/queuevec.hpp"

// Exercise2
#include "../binarytree/binarytree.hpp"
#include "../binarytree/vec/binarytreevec.hpp"
#include "../binarytree/lnk/binarytreelnk.hpp"
#include "../bst/bst.hpp"
#include "../iterator/iterator.hpp"

// Exercise3
#include "../hashtable/hashtable.hpp"
#include "../hashtable/clsadr/htclsadr.hpp"
#include "../hashtable/opnadr/htopnadr.hpp"




/* ************************************************************************** */

void mytest();

void testVettore();
void testLista();
void testQueueVec();
void testStackVec();
void testPreOrderIterator(lasd::BTPreOrderIterator<int>&);
void testPostOrderIterator(lasd::BTPostOrderIterator<int>&);
void testInOrderIterator(lasd::BTInOrderIterator<int>&);
void testBreadthIterator(lasd::BTBreadthIterator<int>&);
void testBT(lasd::MutableBinaryTree<int>&);
void testBTVec();
void testBTLnk();
void testBST();
void testClsAdr();
void testOpnAdr();
void testHidden();

int random_int(int);
double random_double(double);
std::string random_string(unsigned long);
float random_float(float);

template<typename Data>
void populatevec(lasd::Vector<Data>&);

template<typename Data>
void populatelist(lasd::List<Data>&,unsigned long);

template<typename Data>
void print(const Data& val){std::cout<<val<< " - ";}

template<typename Data>
Data FoldSum(const Data& item,const Data& acc){
    return (item+acc);
}

template<typename Data>
Data FoldSumParity(const Data& item,const Data& acc){
    if(item%2==0)
        return (item+acc);
    return acc;
}


/* ************************************************************************** */


#endif
