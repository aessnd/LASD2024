/* ************************************************************************** */

#include <iostream>
#include <string>
#include <random>
#include <cstdlib> 
#include <ctime> 
#include <time.h>
#include <cstring>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

#include "test.hpp"

#define COSTRUCTOR_DIM 10
#define DICTIONARY_DIM 3
#define RANDOM_RANGE 100
using namespace std;

/* ************************************************************************** */

void mytest() {
  int test;

  do{
    cout<<endl<<"-Su quale container vuoi effettuare i test?"<<endl;
    cout<<"(0)Torna indietro"<<endl;
    cout<<"(1)Vettori"<<endl;
    cout<<"(2)Liste"<<endl,
    cout<<"(3)QueueVec"<<endl;
    cout<<"(4)StackVec"<<endl;
    cout<<"(5)BTVec&Iterator"<<endl;
    cout<<"(6)BTLnk&Iterator"<<endl;
    cout<<"(7)BST"<<endl;
    cout<<"(8)HashClsAdr (incompleto)"<<endl;
    cout<<"(9)HashOpnAdr (incompleto)"<<endl; 
    cin>>test;

    switch (test)
    {
    case 0:
      cout<<endl << ">---------------Ritorno alla sezione precedente---------------<" <<endl;
      break;
    case 1:
      testVettore();
      break;
    case 2:
      testLista();
      break;
    case 3:
      testQueueVec();
      break;
    case 4:
      testStackVec();
      break;
    case 5:
      testBTVec();
      break;
    case 6:
      testBTLnk();
      break;
    case 7:
      testBST();
      break;
    case 8:
      testClsAdr();
      break;
    case 9:
      testOpnAdr();
      break;
    case 72:
      testHidden();
      break;
    default:
      cout<<"#N. test "<<"( "<<test<<" )"<<" non trovato#"<<endl;
      break;
    }
  }while(test>0);
}

void testVettore(){
  int test=1;
  int error=0;
  unsigned long dim=0;

  cout<<endl<<"-Inserire una dimensione del vettore (>=0): ";
  cin>>dim;
/* ************************************************** */

  cout<<"####Test Vector/SortableVector<int>####"<<endl;
  lasd::SortableVector<int> vecint(dim);
  populatevec(vecint);

  cout<<"("<<test++<<")"<< " Specific costructor - A vector with a given initial dimension "<<endl;

  cout<<"("<<test++<<")"<< " Using Size() function: ";
  if(vecint.Size()==dim)
    cout<<"Correct!"<<endl;
  else{
    cout<<"Error!"<<endl;
    error++;
  }

  cout<<"("<<test++<<")"<< " Using Empty() function: ";
  if(vecint.Empty()==0 && dim==0){
    cout<<"Error!"<<endl;
    error++;
  }
  else
    cout<<"Correct!"<<endl;

  cout<<"("<<test++<<")"<< " Copy constructor: ";
  lasd::SortableVector<int> cpyvecintC(vecint);
  if(vecint.lasd::Vector<int>::operator==(cpyvecintC))
    cout<<"Correct!"<<endl;
  else{
    cout<<"Error!"<<endl;
    error++;
  }

  cout<<"("<<test++<<")"<< " Move constructor: ";
  lasd::SortableVector<int> mvevecintC(move(cpyvecintC));
  if(vecint.lasd::Vector<int>::operator==(move(mvevecintC)))
    cout<<"Correct!"<<endl;
  else{
    cout<<"Error!"<<endl;
    error++;
  }

  cout<<"("<<test++<<")"<< " Copy assignment: ";
  lasd::SortableVector<int> cpyvecintA=vecint;
  if(vecint.lasd::Vector<int>::operator==(cpyvecintA))
    cout<<"Correct!"<<endl;
  else{
      cout<<"Error"<<endl;
      error++;
  }

  cout<<"("<<test++<<")"<< " Move assignment: ";
  lasd::SortableVector<int> mvevecintA=move(cpyvecintA);
  if(vecint.lasd::Vector<int>::operator==(mvevecintA))
    cout<<"Correct!"<<endl;
  else{
      cout<<"Error"<<endl;
      error++;
  }

  cout<<"("<<test++<<")"<< " Using Exist() function"<<endl;
  vecint.Map(&print<int>);
  cout<<endl<<"-Cercare l'esistenza di un elemento: ";
  int exist;
  cin>>exist;

  if(vecint.lasd::SortableVector<int>::Exists(exist))
    cout<<"Exist!"<<endl;
  else{
    cout<<"Not exist!"<<endl;
  }
  cout<<"Before Sort(): ";
  vecint.Map(&print<int>);
  cout<<endl<<"("<<test++<<")"<< " Auxiliary function: Sort(): "<<endl;
  vecint.Sort();
  vecint.Map(&print<int>);

  try{
    cout<<endl<<"("<<test++<<")"<< " Using Front() function: ";
      if(vecint.Front()==vecint[0])
        cout<<"Correct!"<<endl;
      else{
        cout<<"Error!"<<endl;
        error++;
      }
  }catch(length_error& exc){
    cout<<"Eccezione catturata!"<<endl;
  }catch(exception& exc){
    cout<<"Eccezione non catturata!"<<endl;
    error++;
  }

  try{
    cout<<"("<<test++<<")"<< " Using Back() function: ";
      if(vecint.Back()==vecint[vecint.Size()-1])
        cout<<"Correct!"<<endl;
      else{
        cout<<"Error!"<<endl;
        error++;
      }
    }catch(length_error& exc){
      cout<<"Eccezione catturata!"<<endl;
    }catch(exception& exc){
      cout<<"Eccezione non catturata!"<<endl;
      error++;
    }

    cout<<"("<<test++<<")"<< " Using PreOrderMap function for print container: ";
    vecint.PreOrderMap(&print<int>);

    cout<<endl<<"("<<test++<<")"<< " Using PostOrderMap function for print container: ";
    vecint.PostOrderMap(&print<int>);

    cout<<endl<<"("<<test++<<")"<< " Using PreOrderFold function for container' sum elements: ";
    cout<<vecint.PreOrderFold<int>(&FoldSum<int>,0)<<endl;

    cout<<"("<<test++<<")"<< " Using PostOrderFold function for container' sum parity elements: ";
    cout<<vecint.PostOrderFold<int>(&FoldSumParity<int>,0)<<endl;

    cout<<"("<<test++<<")"<< " Using Resize() function: ";
    vecint.Resize(10);
    if(vecint.Size()==10)
      cout<<"Correct"<<endl;
    else{
      cout<<"Error!"<<endl;
      error++;
    }

    cout<<"("<<test++<<")"<< " Using Clear() function: ";
    vecint.Clear();
    if(vecint.Empty())
      cout<<"Correct!"<<endl;
    else{
      cout<<"Error!"<<endl;
      error++;
    }

/* ************************************************** */

    cout<<endl<<"####Test costruttori Vector<int>###"<<endl;
    unsigned long i;
    lasd::List<int> list;
    populatelist(list,COSTRUCTOR_DIM);
    lasd::StackLst<int> stacklst;
    populatelist(stacklst,COSTRUCTOR_DIM);
    lasd::QueueLst<int> queuelst;
    populatelist(queuelst,COSTRUCTOR_DIM);
    lasd::StackVec<int> stackvec(list);
    lasd::QueueVec<int> queuevec(list);

    cout<<"("<<test++<<")"<< "List to Vector (copy) : ";
    lasd::SortableVector<int> costrvec1(list);
    for(i=0;i<costrvec1.Size();i++){
      if(costrvec1[i]!=list[i])
        {
          error++;
          cout<<"Error!"<<endl;
          break;
        }
    }
    if(i==costrvec1.Size()) cout<<"Correct!"<<endl;

    cout<<"("<<test++<<")"<< "List to Vector (move) : ";
    lasd::SortableVector<int> costrvec2(move(costrvec1));
    for(i=0;i<costrvec2.Size();i++){
      if(costrvec2[i]!=list[i])
        {
          error++;
          cout<<"Error!"<<endl;
          break;
        }
    }
    if(i==costrvec2.Size()) cout<<"Correct!"<<endl;

    cout<<"("<<test++<<")"<< "StackLst to Vector (copy) : ";
    lasd::SortableVector<int> costrvec3(stacklst);
    for(i=0;i<costrvec3.Size();i++){
      if(costrvec3[i]!=stacklst[i])
        {
          error++;
          cout<<"Error!"<<endl;
          break;
        }
    }
    if(i==costrvec3.Size()) cout<<"Correct!"<<endl;

    cout<<"("<<test++<<")"<< "StackLst to Vector (move) : ";
    lasd::SortableVector<int> costrvec4(move(costrvec3));
    for(i=0;i<costrvec4.Size();i++){
      if(costrvec4[i]!=stacklst[i])
        {
          error++;
          cout<<"Error!"<<endl;
          break;
        }
    }
    if(i==costrvec4.Size()) cout<<"Correct!"<<endl;

    cout<<"("<<test++<<")"<< "QueueLst to Vector (copy) : ";
    lasd::SortableVector<int> costrvec5(queuelst);
    for(i=0;i<costrvec5.Size();i++){
      if(costrvec5[i]!=queuelst[i])
        {
          error++;
          cout<<"Error!"<<endl;
          break;
        }
    }
    if(i==costrvec5.Size()) cout<<"Correct!"<<endl;

    cout<<"("<<test++<<")"<< "QueueLst to Vector (move) : ";
    lasd::SortableVector<int> costrvec6(move(costrvec5));
    for(i=0;i<costrvec6.Size();i++){
      if(costrvec6[i]!=queuelst[i])
        {
          error++;
          cout<<"Error!"<<endl;
          break;
        }
    }
    if(i==costrvec6.Size()) cout<<"Correct!"<<endl;

    cout<<"("<<test++<<")"<< "StackVec to Vector (copy) : ";
    lasd::SortableVector<int> costrvec7(stackvec);
    for(i=0;i<costrvec7.Size();i++){
      if(costrvec7[i]!=stackvec[i])
        {
          error++;
          cout<<"Error!"<<endl;
          break;
        }
    }
    if(i==costrvec7.Size()) cout<<"Correct!"<<endl;

    cout<<"("<<test++<<")"<< "StackVec to Vector (move) : ";
    lasd::SortableVector<int> costrvec8(move(costrvec7));
    for(i=0;i<costrvec8.Size();i++){
      if(costrvec8[i]!=stackvec[i])
        {
          error++;
          cout<<"Error!"<<endl;
          break;
        }
    }
    if(i==costrvec8.Size()) cout<<"Correct!"<<endl;

    cout<<"("<<test++<<")"<< "QueueVec to Vector (copy) : ";
    lasd::SortableVector<int> costrvec9(queuevec);
    for(i=0;i<costrvec9.Size();i++){
      if(costrvec9[i]!=queuevec[i])
        {
          error++;
          cout<<"Error!"<<endl;
          break;
        }
    }
    if(i==costrvec9.Size()) cout<<"Correct!"<<endl;

    cout<<"("<<test++<<")"<< "QueueVec to Vector (move) : ";
    lasd::SortableVector<int> costrvec10(move(costrvec9));
    for(i=0;i<costrvec10.Size();i++){
      if(costrvec10[i]!=queuevec[i])
        {
          error++;
          cout<<"Error!"<<endl;
          break;
        }
    }
    if(i==costrvec10.Size()) cout<<"Correct!"<<endl;

    cout<<endl<<"####END VECTOR TEST####"<<endl;
    cout<<"ERRORS: "<<error<<"/"<<test;

  
/* ************************************************** */
}

void testLista(){
  int test=1;
  int error=0;
  unsigned long dim=0;
  cout<<endl<<"-Inserire una dimensione della lista (>=0): ";
  cin>>dim;

  cout<<"####Test List<int>####"<<endl;
  lasd::List<int> list;
  populatelist(list,dim);

  cout<<endl<<"("<<test++<<")"<<" Test Copy costructor: ";
  lasd::List<int> listCC(list);
  if(list==listCC)
    cout<<"Correct!"<<endl;
  else{
    cout<<"Error!"<<endl;
    error++;
  }

  cout<<endl<<"("<<test++<<")"<<" Test Move costructor: ";
  lasd::List<int> listMC(move(listCC));
  if(listMC==list)
    cout<<"Correct!"<<endl;
  else{
    cout<<"Error!"<<endl;
    error++;
  }

  cout<<endl<<"("<<test++<<")"<<" Test Copy assignment: ";
  lasd::List<int> listCA = list;
  if(list==listCA)
    cout<<"Correct!"<<endl;
  else{
    cout<<"Error!"<<endl;
    error++;
  }

  cout<<endl<<"("<<test++<<")"<<" Test Move assignment: ";
  lasd::List<int> listMA = move(listCA);
  if(list==listMA)
    cout<<"Correct!"<<endl;
  else{
    cout<<"Error!"<<endl;
    error++;
  }

  cout<<endl<<"("<<test++<<")"<<" Test InsertAtFront: ";
  int random1=random_int(RANDOM_RANGE);
  list.InsertAtFront(random1);
  if(list.Front()==random1)
    cout<<"Correct"<<endl;
  else{
    cout<<"Error!"<<endl;
    error++;
  }
  list.Map(&print<int>);
  
  cout<<endl<<"("<<test++<<")"<<" Test RemoveFromFront: ";
  try{
    list.RemoveFromFront();
  }
  catch(length_error &exc){
    cout<<"Exception captured!";
  }catch(exception &exc){
    cout<<"Exception not captured!";
    error++;
  }
  list.Map(&print<int>);

  

  cout<<endl<<"("<<test++<<")"<<" Test FrontNRemove: ";
  try{
    int result = list.FrontNRemove();
    cout<<"("<<result<<")";
    if(result!=list.Front())
      cout<<"Correct!"<<endl;
    else{
      cout<<"Error!"<<endl;
      error++;
    }
  }catch(length_error &exc){
    cout<<"Exception captured!";
  }catch(exception &exc){
    cout<<"Exception not captured!";
    error++;
  }
    
  list.Map(&print<int>);

  cout<<endl<<"("<<test++<<")"<<" Test InsertAtBack: ";
  int random2=random_int(RANDOM_RANGE);
  list.InsertAtBack(random2);
  if(list.Back()==random2)
    cout<<"Correct!"<<endl;
  else{
    cout<<"Error!"<<endl;
    error++;
  }
  list.Map(&print<int>);

  cout<<endl<<"("<<test++<<")"<<" Test Insert: ";
  int random3=random_int(RANDOM_RANGE);
  if(list.Insert(random3))
    cout<<"Correct! (Not exist)"<<endl;
  else if(list.Back()!=random3){
    cout<<"Error!"<<endl;
    error++;
  }else cout<<"Correct! (Already exist)"<<endl;
  list.Map(&print<int>);
  
  cout<<endl<<"("<<test++<<")"<<" Test Remove: ";
  int random4=random_int(RANDOM_RANGE);
  if(list.Remove(random4))
    cout<<"Correct! (Exist)"<<endl;
  else cout<<"Correct! (Not exist)"<<endl;
  list.Map(&print<int>);
  
  cout<<endl<<"("<<test++<<")"<<" Test operator[]: ";
  try{
    cout<<list.operator[](random_int(list.Size()))<<endl;
  }catch(out_of_range &exc){
    cout<<"Exception captured!";
  }catch(exception &exc){
    cout<<"Exception not captured!";
  }
  
  cout<<endl<<"("<<test++<<")"<<" Test Front(): ";
  try{
    cout<<list.Front()<<endl;
  }catch(length_error &exc){
    cout<<"Exception captured!";
  }catch(exception &exc){
    cout<<"Exception not captured!";
  }

  cout<<endl<<"("<<test++<<")"<<" Test Back(): ";
  try{
    cout<<list.Back()<<endl;
  }catch(out_of_range &exc){
    cout<<"Exception captured!";
  }catch(exception &exc){
    cout<<"Exception not captured!";
  }
  
  cout<<endl<<"("<<test++<<")"<<" Test PreOrderFold(sum): "<<list.PreOrderFold<int>(&FoldSum<int>,0);

  cout<<endl<<"("<<test++<<")"<<" Test PostOrderFold(sum ONLY even): "<<list.PostOrderFold<int>(&FoldSumParity<int>,0);
  
  cout<<endl<<"("<<test++<<")"<<" Test PreOrderMap(print): ";
  list.PreOrderMap(&print<int>);

  cout<<endl<<"("<<test++<<")"<<" Test PostOrderMap(print): ";
  list.PostOrderMap(&print<int>);

  cout<<endl<<"("<<test++<<")"<<" Test Clear()";
  list.Clear();
  if(list.Empty())
    cout<<"Correct!"<<endl;
  else{
    cout<<"Error!"<<endl;
    error++;
  }

/* ************************************************** */

  cout<<endl<<"####Test costruttori List<int>###"<<endl;
    unsigned long i;
    lasd::SortableVector<int> vec(COSTRUCTOR_DIM);
    populatevec(vec);
    lasd::StackLst<int> stacklst;
    populatelist(stacklst,COSTRUCTOR_DIM);
    lasd::QueueLst<int> queuelst;
    populatelist(queuelst,COSTRUCTOR_DIM);
    lasd::StackVec<int> stackvec(list);
    lasd::QueueVec<int> queuevec(list);

    cout<<"("<<test++<<")"<< "Vector to List (copy) : ";
    lasd::List<int> costr1(vec);
    for(i=0;i<costr1.Size();i++){
      if(costr1[i]!=vec[i])
        {
          error++;
          cout<<"Error!"<<endl;
          break;
        }
    }
    if(i==costr1.Size()) cout<<"Correct!"<<endl;

    cout<<"("<<test++<<")"<< "Vector to List (move) : ";
    lasd::List<int> costr2(move(costr1));
    for(i=0;i<costr2.Size();i++){
      if(costr2[i]!=vec[i])
        {
          error++;
          cout<<"Error!"<<endl;
          break;
        }
    }
    if(i==costr2.Size()) cout<<"Correct!"<<endl;

    cout<<"("<<test++<<")"<< "StackLst to List (copy) : ";
    lasd::List<int> costr3(stacklst);
    for(i=0;i<costr3.Size();i++){
      if(costr3[i]!=stacklst[i])
        {
          error++;
          cout<<"Error!"<<endl;
          break;
        }
    }
    if(i==costr3.Size()) cout<<"Correct!"<<endl;

    cout<<"("<<test++<<")"<< "StackLst to List (move) : ";
    lasd::List<int> costr4(move(costr3));
    for(i=0;i<costr4.Size();i++){
      if(costr4[i]!=stacklst[i])
        {
          error++;
          cout<<"Error!"<<endl;
          break;
        }
    }
    if(i==costr4.Size()) cout<<"Correct!"<<endl;


    cout<<"("<<test++<<")"<< "StackVec to List (copy) : ";
    lasd::List<int> costr5(stackvec);
    for(i=0;i<costr5.Size();i++){
      if(costr5[i]!=stackvec[i])
        {
          error++;
          cout<<"Error!"<<endl;
          break;
        }
    }
    if(i==costr5.Size()) cout<<"Correct!"<<endl;

    cout<<"("<<test++<<")"<< "StackVec to List (move) : ";
    lasd::List<int> costr6(move(costr5));
    for(i=0;i<costr6.Size();i++){
      if(costr6[i]!=stackvec[i])
        {
          error++;
          cout<<"Error!"<<endl;
          break;
        }
    }
    if(i==costr6.Size()) cout<<"Correct!"<<endl;

    cout<<"("<<test++<<")"<< "QueueLst to List (copy) : ";
    lasd::List<int> costr7(queuelst);
    for(i=0;i<costr7.Size();i++){
      if(costr7[i]!=queuelst[i])
        {
          error++;
          cout<<"Error!"<<endl;
          break;
        }
    }
    if(i==costr7.Size()) cout<<"Correct!"<<endl;

    cout<<"("<<test++<<")"<< "QueueLst to List (move) : ";
    lasd::List<int> costr8(move(costr7));
    for(i=0;i<costr8.Size();i++){
      if(costr8[i]!=queuelst[i])
        {
          error++;
          cout<<"Error!"<<endl;
          break;
        }
    }
    if(i==costr8.Size()) cout<<"Correct!"<<endl;

    cout<<"("<<test++<<")"<< "QueueVec to List (copy) : ";
    lasd::List<int> costr9(queuevec);
    for(i=0;i<costr9.Size();i++){
      if(costr9[i]!=queuevec[i])
        {
          error++;
          cout<<"Error!"<<endl;
          break;
        }
    }
    if(i==costr9.Size()) cout<<"Correct!"<<endl;

    cout<<"("<<test++<<")"<< "QueueVec to List (move) : ";
    lasd::List<int> costr10(move(costr9));
    for(i=0;i<costr10.Size();i++){
      if(costr10[i]!=queuevec[i])
        {
          error++;
          cout<<"Error!"<<endl;
          break;
        }
    }
    if(i==costr10.Size()) cout<<"Correct!"<<endl;

/* ************************************************** */

  cout<<"####Test Dictionary List<int>####"<<endl;
  bool test1;
  bool test2;

  cout<<endl<<"("<<test++<<")"<< "InsertAll di DictionaryContainer (copy): ";
  lasd::List<int> listAIc;
  lasd::SortableVector<int> testvec1(DICTIONARY_DIM);
  lasd::SortableVector<int> testvec2(DICTIONARY_DIM);
  testvec1[0]=1;
  testvec1[1]=5;
  testvec1[2]=10;

  testvec2[0]=4;
  testvec2[1]=6;
  testvec2[2]=8;

  listAIc.InsertAtBack(1);
  listAIc.InsertAtBack(2);
  listAIc.InsertAtBack(3);

  test1= listAIc.InsertAll(testvec1);
  test2= listAIc.InsertAll(testvec2);

  if(test1 || !(test2)){
    error++;
    cout<<"Error!"<<endl;
  }else cout<<"Correct!"<<endl;

  cout<<"("<<test++<<")"<< "RemoveAll di DictionaryContainer: ";
  lasd::List<int> listRA;
  listRA.InsertAtBack(1);
  listRA.InsertAtBack(5);
  listRA.InsertAtBack(10);
  listRA.InsertAtBack(4);

  test1= listRA.RemoveAll(testvec2);
  test2= listRA.RemoveAll(testvec1);

  if(test1 || !(test2))
  {
    error++;
    cout<<"Error!"<<endl;
  }else cout <<"Correct!"<<endl;

  cout<<"("<<test++<<")"<< "RemoveSome di DictionaryContainer: ";
  lasd::List<int> listRS;
  listRS.InsertAtBack(2);
  listRS.InsertAtBack(7);
  listRS.InsertAtBack(11);
  listRS.InsertAtBack(4);

  test1= listRS.RemoveSome(testvec1);
  test2= listRS.RemoveSome(testvec2);

  if(test1 || !(test2))
  {
    error++;
    cout<<"Error!"<<endl;
  }else cout <<"Correct!"<<endl;

  cout<<"("<<test++<<")"<< "InsertSome di DictionaryContainer (copy): ";
  lasd::List<int> listISc;
  listISc.InsertAtBack(1);
  listISc.InsertAtBack(5);
  listISc.InsertAtBack(10);
  listISc.InsertAtBack(4);

  test1=listISc.InsertSome(testvec1);
  test2=listISc.InsertSome(testvec2);

  if(test1 || !(test2)){
    error++;
    cout<<"Error!"<<endl;
  }else cout<<"Correct!"<<endl;


  cout<<"("<<test++<<")"<< "InsertAll di DictionaryContainer (move): ";
  lasd::List<int> listAIm;
  listAIm.InsertAtBack(1);
  listAIm.InsertAtBack(2);
  listAIm.InsertAtBack(3);

  test1= listAIm.InsertAll(move(testvec1));
  test2= listAIm.InsertAll(move(testvec2));

  if(test1 || !(test2)){
    error++;
    cout<<"Error!"<<endl;
  }else cout<<"Correct!"<<endl;

  testvec1[0]=1;
  testvec1[1]=5;
  testvec1[2]=10;

  testvec2[0]=4;
  testvec2[1]=6;
  testvec2[2]=8;

  cout<<"("<<test++<<")"<< "InsertSome di DictionaryContainer (move): ";
  lasd::List<int> listISm;
  listISm.InsertAtBack(1);
  listISm.InsertAtBack(5);
  listISm.InsertAtBack(10);
  listISm.InsertAtBack(4);

  test1=listISm.InsertSome(move(testvec1));
  test2=listISm.InsertSome(move(testvec2));

  if(test1 || !(test2)){
    error++;
    cout<<"Error!"<<endl;
  }else cout<<"Correct!"<<endl;
  


  cout<<endl<<"####END LIST TEST####"<<endl;
  cout<<"ERRORS: "<<error<<"/"<<test;

/* ************************************************** */

}

void testQueueVec(){
  int operation=0;
  cout<<endl<<"####Test QueueVec<int>####"<<endl;
  cout<<"##QueueVec default size: "<<QUE_VEC_SIZE<<"##"<<endl;

  lasd::QueueVec<int> que;
  cout<<endl<<"Queue size(): "<<que.Size()<<endl;
  que.Map(&print<int>);



  do{
    cout<<endl<<"-Choose test to run on QueueVec";
    cout<<endl<<">(0)Exit";
    cout<<endl<<">(1)Enqueue an random item";
    cout<<endl<<">(2)Enqueue an random item (move)";
    cout<<endl<<">(3)Dequeue an item at the head of the queue";
    cout<<endl<<">(4)Dequeue an item at the head of the queue and show value";
    cout<<endl<<">(5)Show item in head";
    cout<<endl<<">(6)Delete queue";
    cout<<endl<<">(7)Searches for existance of an element";
    cout<<endl<<">(8)Print queue";
    cout<<endl<<">(9)FoldAdd";
    cout<<endl<<">(10)Costructors";
    cout<<endl<<">(11)Assignments";

    cout<<endl<<"+Your choise: ";
    cin>>operation;

    switch(operation)
    {
      case 0:
        cout<<endl << ">---------------Ritorno alla sezione precedente---------------<" <<endl; 
        break;
      case 1:
      {
        que.Enqueue(random_int(100));
        cout<<endl<<"Queue size(): "<<que.Size()<<endl;
        que.Map(&print<int>);


      }
        break;
      
      case 2:
      {
        que.Enqueue(move(random_int(100)));
        cout<<endl<<"Queue size(): "<<que.Size()<<endl;
        que.Map(&print<int>);

      }
        break;
      
      case 3:
      {
        try{
          que.Dequeue();
          cout<<endl<<"Queue size(): "<<que.Size()<<endl;
          que.Map(&print<int>);

        }catch(length_error &exc){
          cout<<"Exception captured! "<<exc.what();
        }catch(exception &exc){
          cout<<"Error: Exception not captured";
        }
      }
        break;
      
      case 4:
      {
        try{
          cout<<endl<<"Item deleted: "<<que.HeadNDequeue();
          cout<<endl<<"Queue size(): "<<que.Size()<<endl;
          que.Map(&print<int>);

        }catch(length_error &exc){
          cout<<"Exception captured! "<<exc.what();
        }catch(exception &exc){
          cout<<"Error: Exception not captured";
        }
      }
        break;
      
      case 5:
      {
        try{
          cout<<endl<<"Item on queue's head: "<<que.Head();
        }catch(length_error &exc){
          cout<<"Exception captured! "<<exc.what();
        }catch(exception &exc){
          cout<<"Error: Exception not captured";
        }
      }
        break;
      
      case 6:
      {
        que.Clear();
        cout<<endl<<"Queue deleted, size: "<<que.Size();
      }
        break;

      case 7:
      {
        int target;
        cout<<endl<<"Insert item to search the existance: ";
        cin>>target;

        if(que.Exists(target))
          cout<<endl<<"Item exists in the queue!";
        else cout<<endl<<"Item NOT exists in the queue!";
      }
        break;

      case 8:
      {
        cout<<endl<<"-Queue print (Map): ";
        que.Map(&print<int>);

        cout<<endl<<"-Queue print (Traverse)";
        que.Traverse(&print<int>);
      }
        break;

      case 9:
      {
        cout<<endl<<"Queue PreOrder FoldSum: "<<que.PreOrderFold<int>(&FoldSum<int>,0);
        cout<<endl<<"Queue PostOrder foldAdd: "<<que.PostOrderFold<int>(&FoldSum<int>,0);
      }
        break;
      case 10:
      {
        int test=0;
        int error=0;
        cout<<endl<<"####Test costructors QueueVec<int>####"<<endl;
        unsigned long i;
        lasd::SortableVector<int> vec(COSTRUCTOR_DIM);
        populatevec(vec);
        lasd::List<int> list;
        populatelist(list,COSTRUCTOR_DIM);
        lasd::StackLst<int> stacklst;
        populatelist(stacklst,COSTRUCTOR_DIM);
        lasd::QueueLst<int> queuelst;
        populatelist(queuelst,COSTRUCTOR_DIM);
        lasd::StackVec<int> stackvec(list);
        lasd::QueueVec<int> queuevec(list);

        cout<<"("<<test++<<")"<< "Vector to QueueVec (copy) : ";
        lasd::QueueVec<int> costr1(vec);
        for(i=0;i<costr1.Size();i++){
          if(costr1[i]!=vec[i])
            {
              error++;
              cout<<"Error!"<<endl;
              break;
            }
        }
        if(i==costr1.Size()) cout<<"Correct!"<<endl;

            cout<<"("<<test++<<")"<< "Vector to QueueVec (move) : ";
        lasd::QueueVec<int> costr2(move(costr1));
        for(i=0;i<costr2.Size();i++){
          if(costr2[i]!=vec[i])
            {
              error++;
              cout<<"Error!"<<endl;
              break;
            }
        }
        if(i==costr2.Size()) cout<<"Correct!"<<endl;

        cout<<"("<<test++<<")"<< "StackLst to QueueVec (copy) : ";
        lasd::QueueVec<int> costr3(stacklst);
        for(i=0;i<costr3.Size();i++){
          if(costr3[i]!=stacklst[i])
            {
              error++;
              cout<<"Error!"<<endl;
              break;
            }
        }
        if(i==costr3.Size()) cout<<"Correct!"<<endl;

        cout<<"("<<test++<<")"<< "StackLst to QueueVec (move) : ";
        lasd::QueueVec<int> costr4(move(costr3));
        for(i=0;i<costr4.Size();i++){
          if(costr4[i]!=stacklst[i])
            {
              error++;
              cout<<"Error!"<<endl;
              break;
            }
        }
        if(i==costr4.Size()) cout<<"Correct!"<<endl;


        cout<<"("<<test++<<")"<< "StackVec to QueueVec (copy) : ";
        lasd::QueueVec<int> costr5(stackvec);
        for(i=0;i<costr5.Size();i++){
          if(costr5[i]!=stackvec[i])
            {
              error++;
              cout<<"Error!"<<endl;
              break;
            }
        }
        if(i==costr5.Size()) cout<<"Correct!"<<endl;

        cout<<"("<<test++<<")"<< "StackVec to QueueVec (move) : ";
        lasd::QueueVec<int> costr6(move(costr5));
        for(i=0;i<costr6.Size();i++){
          if(costr6[i]!=stackvec[i])
            {
              error++;
              cout<<"Error!"<<endl;
              break;
            }
        }
        if(i==costr6.Size()) cout<<"Correct!"<<endl;

        cout<<"("<<test++<<")"<< "QueueLst to QueueVec (copy) : ";
        lasd::QueueVec<int> costr7(queuelst);
        for(i=0;i<costr7.Size();i++){
          if(costr7[i]!=queuelst[i])
            {
              error++;
              cout<<"Error!"<<endl;
              break;
            }
        }
        if(i==costr7.Size()) cout<<"Correct!"<<endl;

        cout<<"("<<test++<<")"<< "QueueLst to QueueVec (move) : ";
        lasd::QueueVec<int> costr8(move(costr7));
        for(i=0;i<costr8.Size();i++){
          if(costr8[i]!=queuelst[i])
            {
              error++;
              cout<<"Error!"<<endl;
              break;
            }
        }
        if(i==costr8.Size()) cout<<"Correct!"<<endl;

        cout<<"("<<test++<<")"<< "QueueVec to QueueVec (copy) : ";
        lasd::QueueVec<int> costr9(queuevec);
        for(i=0;i<costr9.Size();i++){
          if(costr9[i]!=queuevec[i])
            {
              error++;
              cout<<"Error!"<<endl;
              break;
            }
        }
        if(i==costr9.Size()) cout<<"Correct!"<<endl;

        cout<<"("<<test++<<")"<< "QueueVec to QueueVec (move) : ";
        lasd::QueueVec<int> costr10(move(costr9));
        for(i=0;i<costr10.Size();i++){
          if(costr10[i]!=queuevec[i])
            {
              error++;
              cout<<"Error!"<<endl;
              break;
            }
        }
        if(i==costr10.Size()) cout<<"Correct!"<<endl;

        cout<<"("<<test++<<")"<< "List to QueueVec (copy) : ";
        lasd::QueueVec<int> costr11(list);
        for(i=0;i<costr11.Size();i++){
          if(costr11[i]!=list[i])
            {
              error++;
              cout<<"Error!"<<endl;
              break;
            }
        }
        if(i==costr11.Size()) cout<<"Correct!"<<endl;

        cout<<"("<<test++<<")"<< "List to QueueVec (move) : ";
        lasd::QueueVec<int> costr12(move(costr11));
        for(i=0;i<costr12.Size();i++){
          if(costr12[i]!=list[i])
            {
              error++;
              cout<<"Error!"<<endl;
              break;
            }
        }
        if(i==costr12.Size()) cout<<"Correct!"<<endl;

        
        cout<<endl<<"####END QUEUEVEC COSTRUCTORS TEST####"<<endl;
        cout<<"ERRORS: "<<error<<"/"<<test;
      }
        break;
      
      case 11:
      {
        int test=0;
        int error=0;
        cout<<"("<<test++<<")"<< "Copy assignment (QueueVec -> QueueVec): ";
        lasd::QueueVec<int> queCA=que;
        if(queCA!=que)
          {
            error++;
            cout<<"Error";
            break;
          }
        else cout<<"Correct!"<<endl;

        cout<<"("<<test++<<")"<< "Move assignment (QueueVec -> QueueVec): ";
        lasd::QueueVec<int> queMA= move(queCA);
        if(queMA!=que)
          { 
            error++;
            cout<<"Error";
            break;
          }
        else cout<<"Correct!"<<endl;

        cout<<endl<<"####END QUEUEVEC ASSIGMENT TEST####"<<endl;
        cout<<"ERRORS: "<<error<<"/"<<test;

      }
        break;

      default:
        cout<<"Operation not found! Try again."<<endl;
      break;
    }
  }while (operation !=0);
}

void testStackVec(){
  int operation=0;
  cout<<endl<<"####Test StackVec<int>####"<<endl;
  cout<<"##StackVec default size: "<<STK_VEC_SIZE<<"##"<<endl;

  lasd::StackVec<int> stk;
  cout<<endl<<"Stack size(): "<<stk.Size()<<endl;
  stk.Map(&print<int>);

  do{
    cout<<endl<<"-Choose test to run on StackVec";
    cout<<endl<<">(0)Exit";
    cout<<endl<<">(1)Push an random item";
    cout<<endl<<">(2)Push an random item (move)";
    cout<<endl<<">(3)Pop an item at the top of the stack";
    cout<<endl<<">(4)Pop an item at the top of the stack and show value";
    cout<<endl<<">(5)Show item in top";
    cout<<endl<<">(6)Delete queue";
    cout<<endl<<">(7)Searches for existance of an element";
    cout<<endl<<">(8)Print stack";
    cout<<endl<<">(9)FoldAdd";
    cout<<endl<<">(10)Costructors";
    cout<<endl<<">(11)Assignments";

    cout<<endl<<"+Your choise: ";
    cin>>operation;

    switch(operation)
    {
      case 0:
        cout<<endl << ">---------------Ritorno alla sezione precedente---------------<" <<endl; 
        break;
      case 1:
      {
        stk.Push(random_int(100));
        cout<<endl<<"Stack size: "<<stk.Size()<<endl;
        stk.Map(&print<int>);
      }
        break;

      case 2:
      {
        stk.Push(move(random_int(100)));
        cout<<endl<<"Stack size: "<<stk.Size()<<endl;
        stk.Map(&print<int>);
      }
        break;

      case 3:
      {
        try{
          stk.Pop();
          cout<<endl<<"Stack size: "<<stk.Size()<<endl;
          stk.Map(&print<int>);
        }catch(length_error &exc){
          cout<<"Exception captured!"<<exc.what();
        }catch(exception &exc){
          cout<<"Error: Exception not captured!";
        }
      }
  
        break;

      case 4:
      {
        try{
          cout<<endl<<"Item deleted: "<<stk.TopNPop();
          cout<<endl<<"Stack size: "<<stk.Size()<<endl;
          stk.Map(&print<int>);

        }catch(length_error &exc){
          cout<<"Exception captured!"<<exc.what();
        }catch(exception &exc){
          cout<<"Error: Exception not captured!";
        }
      }
        break;

      case 5:
      {
        try{
          cout<<endl<<"Item on stack's top: "<<stk.Top();
        }catch(length_error &exc){
          cout<<"Exception captured! "<<exc.what();
        }catch(exception &exc){
          cout<<"Error: Exception not captured";
        }
      }
        break;
      
      case 6:
      {
        stk.Clear();
        cout<<endl<<"Stack deleted, size: "<<stk.Size();
      }
        break;
      
      case 7:
      {
        int target;
        cout<<endl<<"Insert item to search the existance: ";
        cin>>target;

        if(stk.Exists(target))
          cout<<endl<<"Item exists in the stack!";
        else cout<<endl<<"Item NOT exists in the srack!";
      }
        break;

      case 8:
      {
        cout<<endl<<"-Stack print (Map): ";
        stk.Map(&print<int>);

        cout<<endl<<"-Stack print (Traverse)";
        stk.Traverse(&print<int>);
      }
        break;
      
      case 9:
      {
        cout<<endl<<"Queue PreOrder FoldSum: "<<stk.PreOrderFold<int>(&FoldSum<int>,0);
        cout<<endl<<"Queue PostOrder foldAdd: "<<stk.PostOrderFold<int>(&FoldSum<int>,0);
      }
        break;
      
      case 10:
      {
        int test=1;
        int error=0;
        cout<<endl<<"####Test costructors StackVec<int>####"<<endl;
        unsigned long i;
        lasd::SortableVector<int> vec(COSTRUCTOR_DIM);
        populatevec(vec);
        lasd::List<int> list;
        populatelist(list,COSTRUCTOR_DIM);
        lasd::StackLst<int> stacklst;
        populatelist(stacklst,COSTRUCTOR_DIM);
        lasd::QueueLst<int> queuelst;
        populatelist(queuelst,COSTRUCTOR_DIM);
        lasd::StackVec<int> stackvec(list);
        lasd::QueueVec<int> queuevec(list);
        cout<<"("<<test++<<")"<< "Vector to StackVec (copy) : ";
        lasd::StackVec<int> costr1(vec);
        for(i=0;i<costr1.Size();i++){
          if(costr1[i]!=vec[i])
            {
              error++;
              cout<<"Error!"<<endl;
              break;
            }
        }
        if(i==costr1.Size()) cout<<"Correct!"<<endl;

        cout<<"("<<test++<<")"<< "Vector to StackVec (move) : ";
        lasd::StackVec<int> costr2(move(costr1));
        for(i=0;i<costr2.Size();i++){
          if(costr2[i]!=vec[i])
            {
              error++;
              cout<<"Error!"<<endl;
              break;
            }
        }
        if(i==costr2.Size()) cout<<"Correct!"<<endl;

        cout<<"("<<test++<<")"<< "StackLst to StackVec (copy) : ";
        lasd::StackVec<int> costr3(stacklst);
        for(i=0;i<costr3.Size();i++){
          if(costr3[i]!=stacklst[i])
            {
              error++;
              cout<<"Error!"<<endl;
              break;
            }
        }
        if(i==costr3.Size()) cout<<"Correct!"<<endl;

        cout<<"("<<test++<<")"<< "StackLst to StackVec (move) : ";
        lasd::StackVec<int> costr4(move(costr3));
        for(i=0;i<costr4.Size();i++){
          if(costr4[i]!=stacklst[i])
            {
              error++;
              cout<<"Error!"<<endl;
              break;
            }
        }
        if(i==costr4.Size()) cout<<"Correct!"<<endl;


        cout<<"("<<test++<<")"<< "StackVec to StackVec (copy) : ";
        lasd::StackVec<int> costr5(stackvec);
        for(i=0;i<costr5.Size();i++){
          if(costr5[i]!=stackvec[i])
            {
              error++;
              cout<<"Error!"<<endl;
              break;
            }
        }
        if(i==costr5.Size()) cout<<"Correct!"<<endl;

        cout<<"("<<test++<<")"<< "StackVec to StackVec (move) : ";
        lasd::StackVec<int> costr6(move(costr5));
        for(i=0;i<costr6.Size();i++){
          if(costr6[i]!=stackvec[i])
            {
              error++;
              cout<<"Error!"<<endl;
              break;
            }
        }
        if(i==costr6.Size()) cout<<"Correct!"<<endl;

        cout<<"("<<test++<<")"<< "QueueLst to StackVec (copy) : ";
        lasd::StackVec<int> costr7(queuelst);
        for(i=0;i<costr7.Size();i++){
          if(costr7[i]!=queuelst[i])
            {
              error++;
              cout<<"Error!"<<endl;
              break;
            }
        }
        if(i==costr7.Size()) cout<<"Correct!"<<endl;

        cout<<"("<<test++<<")"<< "QueueLst to StackVec (move) : ";
        lasd::StackVec<int> costr8(move(costr7));
        for(i=0;i<costr8.Size();i++){
          if(costr8[i]!=queuelst[i])
            {
              error++;
              cout<<"Error!"<<endl;
              break;
            }
        }
        if(i==costr8.Size()) cout<<"Correct!"<<endl;

        cout<<"("<<test++<<")"<< "QueueVec to StackVec (copy) : ";
        lasd::StackVec<int> costr9(queuevec);
        for(i=0;i<costr9.Size();i++){
          if(costr9[i]!=queuevec[i])
            {
              error++;
              cout<<"Error!"<<endl;
              break;
            }
        }
        if(i==costr9.Size()) cout<<"Correct!"<<endl;

        cout<<"("<<test++<<")"<< "QueueVec to StackVec (move) : ";
        lasd::StackVec<int> costr10(move(costr9));
        for(i=0;i<costr10.Size();i++){
          if(costr10[i]!=queuevec[i])
            {
              error++;
              cout<<"Error!"<<endl;
              break;
            }
        }
        if(i==costr10.Size()) cout<<"Correct!"<<endl;

        cout<<"("<<test++<<")"<< "List to StackVec (copy) : ";
        lasd::StackVec<int> costr11(list);
        for(i=0;i<costr11.Size();i++){
          if(costr11[i]!=list[i])
            {
              error++;
              cout<<"Error!"<<endl;
            }
        }
        if(i==costr11.Size()) cout<<"Correct!"<<endl;

        cout<<"("<<test++<<")"<< "List to StackVec (move) : ";
        lasd::StackVec<int> costr12(move(costr11));
        for(i=0;i<costr12.Size();i++){
          if(costr12[i]!=list[i])
            {
              error++;
              cout<<"Error!"<<endl;
            }
        }
        if(i==costr12.Size()) cout<<"Correct!"<<endl;

        cout<<endl<<"####END STACKVEC TEST####"<<endl;
        cout<<"ERRORS: "<<error<<"/"<<test;
      }
        break;
      
      case 11:
      {
        int test=0;
        int error=0;
        cout<<"("<<test++<<")"<< "Copy assignment (StackVec -> StackVec): ";
        lasd::StackVec<int> stkCA=stk;
        if(stkCA!=stk)
          {
            error++;
            cout<<"Error";
          }
        else cout<<"Correct!"<<endl;

        cout<<"("<<test++<<")"<< "Move assignment (StackVec -> StackVec): ";
        lasd::StackVec<int> stkMA= move(stkCA);
        if(stkMA!=stk)
          { 
            error++;
            cout<<"Error";
          }
        else cout<<"Correct!"<<endl;

        cout<<endl<<"####END STACKVEC ASSIGMENT TEST####"<<endl;
        cout<<"ERRORS: "<<error<<"/"<<test;
      }
        break;
      
      default:
        cout<<"Operation not found! Try again."<<endl;
      break;
    }
  }while(operation != 0);
}
/* ************************************************** */


void testPreOrderIterator(lasd::BTPreOrderIterator<int>& it){
  cout<<endl<<"##PRE ORDER ITERATOR##";
  int operation=0;
  do{
    cout<<endl<<"-Operazioni:";
    cout<<endl<<">(0)Torna indietro";
    cout<<endl<<">(1)Operator*()";
    cout<<endl<<">(2)Operator++()";
    cout<<endl<<">(3)Terminated()";
    cout<<endl<<">(4)Reset"<<endl;

    cin>>operation;
    switch(operation)
    {
      case 0:
        cout<<endl << ">---------------Ritorno alla sezione precedente---------------<" <<endl;
        break;
      case 1:
      {
        try{
          cout<<endl<<"-Operator*() = "<<it.operator*();
        }catch(out_of_range &exc){
          cout<<endl<<"Exception captured!";
        }catch(exception &exc){
          cout<<endl<<"Error: Exception NOT captured!";
        }
      }
        break;
      case 2:
      {
        try{
          ++it;
          cout<<endl<<"++it: "<<it.operator*();
        }catch(out_of_range &exc){
          cout<<endl<<"Exception captured!";
        }catch(exception &exc){
          cout<<endl<<"Error: Exception NOT captured!";
        }
      }
        break;
      
      case 3:
      {
        if(it.Terminated())
          cout<<"Iterator terminated!";
        else cout<<"Iterator NOT terminated!";
      }
        break;
      case 4:
      {
        it.Reset();
        cout<<endl<<"Iterator resetted!";
        
      }
        break;
      default:
        cout<<endl<<"Operazione non trovata, riprova";
        break;
    }
  }while(operation!=0);

}

void testPostOrderIterator(lasd::BTPostOrderIterator<int>& it){
  int operation=0;
  cout<<endl<<"##POST ORDER ITERATOR##";
  do{
    cout<<endl<<"-Operazioni:";
    cout<<endl<<">(0)Torna indietro";
    cout<<endl<<">(1)Operator*()";
    cout<<endl<<">(2)Operator++()";
    cout<<endl<<">(3)Terminated()";
    cout<<endl<<">(4)Reset"<<endl;

    cin>>operation;
    switch(operation)
    {
      case 0:
        cout<<endl << ">---------------Ritorno alla sezione precedente---------------<" <<endl;
        break;
      case 1:
      {
        try{
          cout<<endl<<"-Operator*() = "<<it.operator*();
        }catch(out_of_range &exc){
          cout<<endl<<"Exception captured!";
        }catch(exception &exc){
          cout<<endl<<"Error: Exception NOT captured!";
        }
      }
        break;
      case 2:
      {
        try{
          ++it;
          cout<<endl<<"++it: "<<it.operator*();
        }catch(out_of_range &exc){
          cout<<endl<<"Exception captured!";
        }catch(exception &exc){
          cout<<endl<<"Error: Exception NOT captured!";
        }
      }
        break;
      
      case 3:
      {
        if(it.Terminated())
          cout<<"Iterator terminated!";
        else cout<<"Iterator NOT terminated!";
      }
        break;
      case 4:
      {
        it.Reset();
        cout<<endl<<"Iterator resetted!";
      }
        break;
      default:
        cout<<endl<<"Operazione non trovata, riprova";
        break;
    }
  }while(operation!=0);

}

void testInOrderIterator(lasd::BTInOrderIterator<int>& it){
  int operation=0;
  cout<<endl<<"##IN ORDER ITERATOR##";
  do{
    cout<<endl<<"-Operazioni:";
    cout<<endl<<">(0)Torna indietro";
    cout<<endl<<">(1)Operator*()";
    cout<<endl<<">(2)Operator++()";
    cout<<endl<<">(3)Terminated()";
    cout<<endl<<">(4)Reset"<<endl;

    cin>>operation;
    switch(operation)
    {
      case 0:
        cout<<endl << ">---------------Ritorno alla sezione precedente---------------<" <<endl;
        break;
      case 1:
      {
        try{
          cout<<endl<<"-Operator*() = "<<it.operator*();
        }catch(out_of_range &exc){
          cout<<endl<<"Exception captured!";
        }catch(exception &exc){
          cout<<endl<<"Error: Exception NOT captured!";
        }
      }
        break;
      case 2:
      {
        try{
          ++it;
          cout<<endl<<"++it: "<<it.operator*();
        }catch(out_of_range &exc){
          cout<<endl<<"Exception captured!";
        }catch(exception &exc){
          cout<<endl<<"Error: Exception NOT captured!";
        }
      }
        break;
      
      case 3:
      {
        if(it.Terminated())
          cout<<"Iterator terminated!";
        else cout<<"Iterator NOT terminated!";
      }
        break;
      case 4:
      {
        it.Reset();
        cout<<endl<<"Iterator resetted!";
      }
        break;
      default:
        cout<<endl<<"Operazione non trovata, riprova";
        break;
    }
  }while(operation!=0);

}

void testBreadthIterator(lasd::BTBreadthIterator<int>& it){
  int operation=0;
  cout<<endl<<"##BREADTH ITERATOR##";
  do{
    cout<<endl<<"-Operazioni:";
    cout<<endl<<">(0)Torna indietro";
    cout<<endl<<">(1)Operator*()";
    cout<<endl<<">(2)Operator++()";
    cout<<endl<<">(3)Terminated()";
    cout<<endl<<">(4)Reset"<<endl;

    cin>>operation;
    switch(operation)
    {
      case 0:
        cout<<endl << ">---------------Ritorno alla sezione precedente---------------<" <<endl;
        break;
      case 1:
      {
        try{
          cout<<endl<<"-Operator*() = "<<it.operator*();
        }catch(out_of_range &exc){
          cout<<endl<<"Exception captured!";
        }catch(exception &exc){
          cout<<endl<<"Error: Exception NOT captured!";
        }
      }
        break;
      case 2:
      {
        try{
          ++it;
          cout<<endl<<"++it: "<<it.operator*();
        }catch(out_of_range &exc){
          cout<<endl<<"Exception captured!";
        }catch(exception &exc){
          cout<<endl<<"Error: Exception NOT captured!";
        }
      }
        break;
      
      case 3:
      {
        if(it.Terminated())
          cout<<"Iterator terminated!";
        else cout<<"Iterator terminated!";
      }
        break;
      case 4:
      {
        it.Reset();
        cout<<endl<<"Iterator resetted!";
      }
        break;
      default:
        cout<<endl<<"Operazione non trovata, riprova";
        break;
    }
  }while(operation!=0);

}

void testBTVec(){
  unsigned long dim=0;
  cout<<endl<<"##TEST BT VEC##";
  cout<<endl<<"-Inserisci dimensione del bt vec (>=0): ";
  cin>>dim;
  lasd::Vector<int> vec(dim);
  populatevec(vec);
  lasd::BinaryTreeVec<int> btv(vec);
  testBT(btv);
}

void testBTLnk(){
  unsigned long dim=0;
  cout<<endl<<"##TEST BT LNK##";
  cout<<endl<<"-Inserisci dimensione del bt lnk (>=0): ";
  cin>>dim;
  lasd::List<int> list;
  populatelist(list,dim);
  lasd::BinaryTreeVec<int> btl(list);
  testBT(btl);
}

void testBT(lasd::MutableBinaryTree<int>& btv){
  int operation=0;
  
  cout<<endl<<"Size: "<<btv.Size();

  do{
    cout<<endl<<"-Operazioni:";
    cout<<endl<<">(0)Torna indietro";
    cout<<endl<<">(1)Costruttori/assignments";
    cout<<endl<<">(2)Root()";
    cout<<endl<<">(3)Clear()";
    cout<<endl<<">(4)BreadthTraverse/BreadthMap";
    cout<<endl<<">(5)PreOrderIterator";
    cout<<endl<<">(6)PostOrderIterator";
    cout<<endl<<">(7)InOrderIterator";
    cout<<endl<<">(8)BreadthIterator"<<endl;
    cin>>operation;

    switch(operation){
      case 0:
        cout<<endl << ">---------------Ritorno alla sezione precedente---------------<" <<endl;
        break;
      
      case 1:
      {
        lasd::Vector<int> vec(COSTRUCTOR_DIM);
        populatevec(vec);
        lasd::BinaryTreeVec<int> btvc(vec);

        lasd::List<int> list;
        populatelist(list,COSTRUCTOR_DIM);
        lasd::BinaryTreeLnk<int> btlc(list);

        cout<<endl<<"Copy constructor <btvec> : ";
        lasd::BinaryTreeVec<int> btvcpyC(btvc);
        lasd::BTBreadthIterator<int> itcpy1(btvc);
        lasd::BTBreadthIterator<int> itcpy2(btvcpyC);
        for(;!itcpy2.Terminated();++itcpy1,++itcpy2){
          if(itcpy1.operator*()!=itcpy2.operator*()){
            cout<<"Error!";
            break;
            }
        }
        cout<<"Correct!";

        cout<<endl<<"Move constructor <btvec>: ";
        lasd::BinaryTreeVec<int> btvmveC(move(btvcpyC));
        lasd::BTBreadthIterator<int> itmve1(btvc);
        lasd::BTBreadthIterator<int> itmve2(btvmveC);
        for(;!itmve2.Terminated();++itmve1,++itmve2){
          if(itmve1.operator*()!=itmve2.operator*()){
            cout<<"Error!";
            break;
          }
        }
        cout<<"Correct!";

        cout<<endl<<"Copy assignment <btvec>: ";
        lasd::BinaryTreeVec<int> btvcpyA=btvc;
        lasd::BTBreadthIterator<int> itcpy3(btvc);
        lasd::BTBreadthIterator<int> itcpy4(btvcpyA);
          for(;!itcpy4.Terminated();++itcpy3,++itcpy4){
            if(itcpy3.operator*()!=itcpy4.operator*()){
            cout<<"Error!";
            break;
          }
        }
          cout<<"Correct!";

        cout<<endl<<"Move assignment<btvec>: ";
        lasd::BinaryTreeVec<int> btvmveA= move(btvcpyA);
        lasd::BTBreadthIterator<int> itmve3(btvc);
        lasd::BTBreadthIterator<int> itmve4(btvmveA);
        for(;!itmve4.Terminated();++itmve3,++itmve4){
          if(itmve3.operator*()!=itmve4.operator*()){
              cout<<"Error!";
              break;
            }
        }
        cout<<"Correct!";

        cout<<endl<<"Copy constructor <btvlnk>: ";
        lasd::BinaryTreeLnk<int> btlcpyC(btlc);
        lasd::BTBreadthIterator<int> itcpy1l(btlc);
        lasd::BTBreadthIterator<int> itcpy2l(btlcpyC);
        for(;!itcpy2l.Terminated();++itcpy1l,++itcpy2l){
          if(itcpy1l.operator*()!=itcpy2l.operator*()){
            cout<<"Error!";
            break;
            }
        }
        cout<<"Correct!";

        cout<<endl<<"Move constructor <btvlnk>: ";
        lasd::BinaryTreeLnk<int> btlmveC(move(btlcpyC));
        lasd::BTBreadthIterator<int> itmve1l(btlc);
        lasd::BTBreadthIterator<int> itmve2l(btlmveC);
        for(;!itmve2l.Terminated();++itmve1l,++itmve2l){
          if(itmve1l.operator*()!=itmve2l.operator*()){
            cout<<"Error!";
            break;
          }
        }
        cout<<"Correct!";

        cout<<endl<<"Copy assignment <btvlnk>: ";
        lasd::BinaryTreeLnk<int> btlcpyA=btlc;
        lasd::BTBreadthIterator<int> itcpy3l(btlc);
        lasd::BTBreadthIterator<int> itcpy4l(btlcpyA);
          for(;!itcpy4l.Terminated();++itcpy3l,++itcpy4l){
            if(itcpy3l.operator*()!=itcpy4l.operator*()){
            cout<<"Error!";
            break;
          }
        }
          cout<<"Correct!";

        cout<<endl<<"Move assignment <btvlnk>: ";
        lasd::BinaryTreeLnk<int> btlmveA= move(btlcpyA);
        lasd::BTBreadthIterator<int> itmve3l(btlc);
        lasd::BTBreadthIterator<int> itmve4l(btlmveA);
        for(;!itmve4l.Terminated();++itmve3l,++itmve4l){
          if(itmve3l.operator*()!=itmve4l.operator*()){
              cout<<"Error!";
              break;
            }
        }
        cout<<"Correct!";
      }
        break;
      
      case 2:
      {
        try{
          cout<<endl<<"-Root: "<<(&btv.Root())->Element();
        }catch(length_error &exc){
          cout<<endl<<"Exception captured!";
        }catch(exception &exc){
          cout<<endl<<"Exception NOT captured!";
        }
      }
        break;
      
      case 3:
      {
        btv.Clear();
      }
        break;
      
      case 4:
      {
        cout<<endl<<"Traverse print: ";
        btv.BreadthTraverse(&print<int>);
        cout<<endl<<"Map print: ";
        btv.BreadthMap(&print<int>);
        cout<<endl<<"FoldSum: "<<btv.Fold<int>(&FoldSum<int>,0);
      }
        break;
      
      case 5:
      {
        lasd::BTPreOrderIterator<int> itpre(btv);
        testPreOrderIterator(itpre);
      }
        break;
      
      case 6:
      {
        lasd::BTPostOrderIterator<int> itpost(btv);
        testPostOrderIterator(itpost);
      }
        break;
      
      case 7:
      {
        lasd::BTInOrderIterator<int> itin(btv);
        testInOrderIterator(itin);
      }
        break;
      
      case 8:
      {
        lasd::BTBreadthIterator<int> itbr(btv);
        testBreadthIterator(itbr);
      }
        break;

    }
  }while(operation!=0);
}

void testBST(){
  int operation=0;
  cout<<endl<<"##BST TEST <int>##";
  lasd::BST<int> bst;
  do{
    cout<<endl<<"-Operazioni:";
    cout<<endl<<">(0)Torna indietro";
    cout<<endl<<">(1)Mostra Minimo";
    cout<<endl<<">(2)Rimuovi Minimo";
    cout<<endl<<">(3)Mostra Massimo";
    cout<<endl<<">(4)Rimuovi Massimo";
    cout<<endl<<">(5)Mostra Predecessore di un dato";
    cout<<endl<<">(6)Rimuovi Predecessore di un dato";
    cout<<endl<<">(7)Mostra Successore di un dato";
    cout<<endl<<">(8)Rimuovi Successore di un dato";
    cout<<endl<<">(9)Root()";
    cout<<endl<<">(10)Inserisci nodo (copy)";
    cout<<endl<<">(11)Inserisci nodo (move)";
    cout<<endl<<">(12)Rimuovi nodo";
    cout<<endl<<">(13)Cancella BST";
    cout<<endl<<">(14)Constructors & Assignments";
    cout<<endl<<">(15)Map/Traverse/Fold";
    cout<<endl<<">(16)Verifica esistenza di un dato"<<endl;

    cin>>operation;

    switch(operation)
    {
      case 0:
        cout<<endl << ">---------------Ritorno alla sezione precedente---------------<" <<endl;
        break;
      
      case 1:
      {
        try{
          cout<<endl<<"Minimo: "<<bst.Min();
        }catch(length_error &exc){
          cout<<endl<<"Exception captured! Empty bst";
        }catch(exception &exc){
          cout<<endl<<"Exception NOT captured!";
        }
      }
      break;

      case 2:
      {
        try{
          cout<<endl<<"Eliminazione minimo: "<<bst.MinNRemove();
          cout<<endl<<"Size: "<<bst.Size();
        }catch(length_error &exc){
          cout<<endl<<"Exception captured! Empty bst";
        }catch(exception &exc){
          cout<<endl<<"Exception NOT captured!";
        }
      }
      break;

      case 3:
      {
        try{
          cout<<endl<<"Massimo: "<<bst.Max();
        }catch(length_error &exc){
          cout<<endl<<"Exception captured! Empty bst";
        }catch(exception &exc){
          cout<<endl<<"Exception NOT captured!";
        }
      }
      break;

      case 4:
      {
        try{
          cout<<endl<<"Eliminazione massimo: "<<bst.MaxNRemove();
          cout<<endl<<"Size: "<<bst.Size();
        }catch(length_error &exc){
          cout<<endl<<"Exception captured! Empty bst";
        }catch(exception &exc){
          cout<<endl<<"Exception NOT captured!";
        }
      }
      break;

      case 5:
      {
        int pred=0;
        cout<<endl<<"Inserire dato di cui si vuole cercare predecessore: ";
        cin>>pred;
        try{
          cout<<endl<<"Predecessore di "<<pred<<" :"<<bst.Predecessor(pred);
        }catch(length_error &exc){
          cout<<endl<<"Exception captured! Predecessore non trovato";
        }catch(exception &exc){
          cout<<endl<<"Exception NOT captured! Predecessore non trovato";
        }
      }
      break;

      case 6:
      {
        int pred=0;
        cout<<endl<<"Inserire dato di cui si vuole eliminare il predecessore: ";
        cin>>pred;
        try{
          cout<<endl<<"Eliminazione predecessore di "<<pred<<" :"<<bst.PredecessorNRemove(pred);
        }catch(length_error &exc){
          cout<<endl<<"Exception captured! Predecessore non trovato";
        }catch(exception &exc){
          cout<<endl<<"Exception NOT captured! Predecessore non trovato";
        }
      }
      break;

      case 7:
      {
        int succ=0;
        cout<<endl<<"Inserire dato di cui si vuole cercare il successore: ";
        cin>>succ;
        try{
          cout<<endl<<"Successore di "<<succ<<" :"<<bst.Successor(succ);
        }catch(length_error &exc){
          cout<<endl<<"Exception captured! Successore non trovato";
        }catch(exception &exc){
          cout<<endl<<"Exception NOT captured! Successore non trovato";
        }
      }
      break;

      case 8:
      {
        int succ=0;
        cout<<endl<<"Inserire dato di cui si vuole eliminare il successore: ";
        cin>>succ;
        try{
          cout<<endl<<"Eliminazione successore di "<<succ<<" :"<<bst.SuccessorNRemove(succ);
        }catch(length_error &exc){
          cout<<endl<<"Exception captured! Successore non trovato";
        }catch(exception &exc){
          cout<<endl<<"Exception NOT captured! Successore non trovato";
        }
      }
      break;

      case 9:
      {
        try{
          cout<<endl<<"Root :"<< &bst.Root().Element();
        }catch(length_error &exc){
          cout<<endl<<"Exception captured! Empty bst";
        }catch(exception &exc){
          cout<<endl<<"Exception NOT captured!";
        }
      }
      break;

      case 10:
      {
        int insert=0;
        cout<<endl<<"-Inserisci intero nel BST (copy): ";
        cin>>insert;
        if(bst.Insert(insert)){
          cout<<endl<<"Intero inserito correttamente!";
        }else cout<<endl<<"Inserimento intero fallito!";
      }
      break;

      case 11:
      {
        int insert=0;
        cout<<endl<<"-Inserisci intero nel BST (move): ";
        cin>>insert;
        if(bst.Insert(move(insert))){
          cout<<endl<<"Intero inserito correttamente!";
        }else cout<<endl<<"Inserimento intero fallito!";
      }
      break;

      case 12:
      {
        int remove=0;
        cout<<endl<<"-Rimuovi intero nel BST : ";
        cin>>remove;
        if(bst.Remove(remove)){
          cout<<endl<<"Intero rimosso correttamente!";
        }else cout<<endl<<"Rimozione intero fallito!";
      }
      break;

      case 13:
      {
        bst.Clear();
        cout<<endl<<"BST cancellato.. Size: "<<bst.Size();
      }
      break;

      case 14:
      {
        cout<<endl<<"-Copy constructor: ";
        lasd::BST<int> bstcc(bst);
        if(bstcc==bst) cout<<"Correct";
        else cout<<"Error";

        cout<<endl<<"-Move constructor: ";
        lasd::BST<int> bstmc(move(bstcc));
        if(bstmc==bst) cout<<"Correct";
        else cout<<"Error";

        cout<<endl<<"-Copy assignment: ";
        lasd::BST<int> bstca=bst;
        if(bstca==bst) cout<<"Correct";
        else cout<<"Error";

        cout<<endl<<"-Move assignment: ";
        lasd::BST<int> bstma=move(bstca);
        if(bstma==bst) cout<<"Correct";
        else cout<<"Error";
      }
      break;

      case 15:
      {
        cout<<endl<<"Map print: ";
        bst.BreadthMap(&print<int>);
        
        cout<<endl<<"Traverse print: ";
        bst.BreadthTraverse(&print<int>);
        cout<<endl<<"Fold summ: "<<bst.Fold<int>(&FoldSum<int>,0);
      }
      break;

      case 16:
      {
        int exist;
        cout<<endl<<"-Inserisci intero per verificare esistenza nel bst: ";
        cin>>exist;
        if(bst.Exists(exist)) cout<<endl<<"-"<<exist<<" esiste!";
        else cout<<endl<<"-"<<exist<<" non esiste!";
      }
      break;

    }
  }while(operation!=0); 
}

void testClsAdr(){
  int operation=0;
  cout<<endl<<"##Hash Table ClsAdr##";
  lasd::HashTableClsAdr<int> htca;
  do{
    cout<<endl<<">(0)Torna indietro";
    cout<<endl<<">(1)Constructors & Assignments";
    cout<<endl<<">(2)Insert";
    cout<<endl<<">(3)Remove";
    cout<<endl<<">(4)Exists";
    cout<<endl<<">(5)Resize";
    cout<<endl<<">(6)Clear";
    cin>>operation;

    switch(operation){
      case 0:
        cout<<endl << ">---------------Ritorno alla sezione precedente---------------<" <<endl;
        break;
      
      case 1:
      {
        lasd::List<int> lst1;
        populatelist(lst1,COSTRUCTOR_DIM);
        
      }
      break;

      case 2:
      {
        int insert=0;
        cout<<endl<<"Aggiungi elemento: ";
        cin>>insert;

        if(htca.Insert(insert))
          cout<<endl<<"Element inserted!";
        else
          cout<<endl<<"Element already exist. NOT inserted!";
      }
      break;
      
      case 3:
      {
        int remove=0;
        cout<<endl<<"Rimuove elemento: ";
        cin>>remove;

        if(htca.Remove(remove))
          cout<<endl<<"Element removed!";
        else
          cout<<endl<<"Element NOT removed!";
      }
      break;

      case 4:
      {
        int exist=0;
        cout<<endl<<"Cerca esistenza elemento:";
        cin>>exist;

        if(htca.Exists(exist))
          cout<<endl<<"The element does exist!";
        else
          cout<<endl<<"The elements does not exist!";
      }
      break;

      case 5:
      {
        unsigned long newdim=0;
        cout<<endl<<"Inserisci nuova dimensione: ";
        cin>>newdim;

        htca.Resize(newdim);

      }
      break;

      case 6:
      {
        htca.Clear();
        cout<<endl<<"Hash table cleared!";
      }
      break;
      
    }
  }while(operation!=0);
}

void testOpnAdr(){
  int operation=0;
  cout<<endl<<"##Hash Table OpnAdr##";
  lasd::HashTableOpnAdr<int> htoa;
  do{
    cout<<endl<<">(0)Torna indietro";
    cout<<endl<<">(1)Constructors & Assignments";
    cout<<endl<<">(2)Insert";
    cout<<endl<<">(3)Remove";
    cout<<endl<<">(4)Exists";
    cout<<endl<<">(5)Resize";
    cout<<endl<<">(6)Clear";
    cin>>operation;

    switch(operation){
      case 0:
        cout<<endl << ">---------------Ritorno alla sezione precedente---------------<" <<endl;
        break;
      
      case 1:
      {
        lasd::List<int> lst1;
        populatelist(lst1,COSTRUCTOR_DIM);
        
      }
      break;

      case 2:
      {
        int insert=0;
        cout<<endl<<"Aggiungi elemento: ";
        cin>>insert;

        if(htoa.Insert(insert))
          cout<<endl<<"Element inserted!";
        else
          cout<<endl<<"Element already exist. NOT inserted!";
      }
      break;
      
      case 3:
      {
        int remove=0;
        cout<<endl<<"Rimuove elemento: ";
        cin>>remove;

        if(htoa.Remove(remove))
          cout<<endl<<"Element removed!";
        else
          cout<<endl<<"Element NOT removed!";
      }
      break;

      case 4:
      {
        int exist=0;
        cout<<endl<<"Cerca esistenza elemento:";
        cin>>exist;

        if(htoa.Exists(exist))
          cout<<endl<<"The element does exist!";
        else
          cout<<endl<<"The elements does not exist!";
      }
      break;

      case 5:
      {
        unsigned long newdim=0;
        cout<<endl<<"Inserisci nuova dimensione: ";
        cin>>newdim;

        htoa.Resize(newdim);

      }
      break;

      case 6:
      {
        htoa.Clear();
        cout<<endl<<"Hash table cleared!";
      }
      break;
      
    }
  }while(operation!=0);
}

void testHidden(){

}
int random_int(int val){

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(0,val);
    int random_int =distribution(generator);

    return random_int;
}


template<typename Data>
void populatevec(lasd::Vector<Data> &vec){
    //Data==int
    if(is_same<Data,int>::value){
        for(unsigned long i=0;i<vec.Size();i++)
            vec[i]=random_int(100);
    }

    //Data==double
    if(is_same<Data,double>::value){
        for(unsigned long i=0;i<vec.Size();i++)
            vec[i]=random_double(2);
    }

    //Data==float
    if(is_same<Data,float>::value){
        for(unsigned long i=0;i<vec.Size();i++)
            vec[i]=random_float(2);
    }

}

template<typename Data>
void populatelist(lasd::List<Data>& lst,unsigned long dim){
    if(dim<=0)
        return;
    else{
        if(is_same<Data,int>::value){
            for(unsigned long i=0;i<dim;i++)
                lst.InsertAtBack(random_int(100));      
        }
        if(is_same<Data,double>::value){
            for(unsigned long i=0;i<dim;i++)
                lst.InsertAtBack(random_double(2));
        }
        if(is_same<Data,float>::value){
            for(unsigned long i=0;i<dim;i++)
                lst.InsertAtBack(random_float(2));
        }
    }
}

