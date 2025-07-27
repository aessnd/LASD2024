

#include "./zlasdtest/test.hpp"
#include "./zmytest/test.hpp"

#include "./container/container.hpp"
#include "./container/testable.hpp"
#include "./container/dictionary.hpp"
#include "./container/traversable.hpp"
#include "./container/mappable.hpp"
#include "./container/linear.hpp"
#include "./vector/vector.hpp"
#include "./list/list.hpp"
#include "./stack/stack.hpp"
#include "./stack/lst/stacklst.hpp"
#include "./stack/vec/stackvec.hpp"
#include "./queue/queue.hpp"
#include "./queue/lst/queuelst.hpp"
#include "./queue/vec/queuevec.hpp"
#include "./binarytree/binarytree.hpp"
#include "./binarytree/vec/binarytreevec.hpp"
#include "./binarytree/lnk/binarytreelnk.hpp"
#include "./iterator/iterator.hpp"
#include "./bst/bst.hpp"
#include "./hashtable/hashtable.hpp"
#include "./hashtable/clsadr/htclsadr.hpp"
#include "./hashtable/opnadr/htopnadr.hpp"


/* ************************************************************************** */

#include <iostream>

/* ************************************************************************** */

int main() {
  int test=-1;
    do{
        std::cout<<std::endl<<"###############################################################"<<std::endl;
        std::cout<<"  Benvenuto - Grieco Alessandro - Matricola N86004241  "<<std::endl;
        std::cout<<"###############################################################"<<std::endl;
        std::cout<<"#           >(1) Test Professor Mogavero Fabio                #"<<std::endl;
        std::cout<<"#           >(2) Menu                                         #"<<std::endl;
        std::cout<<"#           >(0) Esci dal programma                           #"<<std::endl;
        std::cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<std::endl;
        std::cout<<"Seleziona un percorso: ";
        std::cin>>test;
        std::cout<<"###############################################################"<<std::endl;
        
        switch(test){
            case 0:
                std::cout<<std::endl<<"Arrivederci!"<<std::endl;
                break;
            case 1:
                std::cout<<"Lasd Libreries 2023"<<std::endl;
                lasdtest();
                break;
            case 2:
                //std::cout<<"\033[2J\033[1;1H"; 
                std::cout<<std::endl<<std::endl<<">---------------Indirizzamento alla sezione Menu--------------<"<<std::endl<<std::endl;
                mytest();
                break;
            default:                                                                               
                std::cout<<std::endl<<"----------<Errore: percorso ("<<test<<") non trovato. Riprova>----------"<<std::endl;
                break;
        }
    }while(test!=0);

    
    
}
