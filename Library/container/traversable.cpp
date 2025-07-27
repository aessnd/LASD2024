
namespace lasd {

/* ************************************************************************** */

    //Specfic member function's description (inhereted for TestableContainer)

    //Checks for the existence of an item into a Container
    template<typename Data>
    bool TraversableContainer<Data>::Exists(const Data& find)const noexcept{
        //Check if Container is empty (Cannot exist an item in an empty Container)
        if(Container::size==0) { return false; }
        //..else..
        bool exist=false;
        this->Traverse(
            [this,find,&exist](const Data& item){
                exist |= (find==item);
           });
        return exist;
    }  

    template<typename Data>
    template<typename Accumulator>
    Accumulator TraversableContainer<Data>::Fold(FoldFun<Accumulator> ff,const Accumulator& start)const{
        Accumulator acc= start;
        this->Traverse(
            [this,&acc/* <- (&start) */,ff](const Data& item){
                acc = ff(item,acc);
            }
        );
        return acc;
    }

    template<typename Data>
    template<typename Accumulator>
    Accumulator PreOrderTraversableContainer<Data>::PreOrderFold(FoldFun<Accumulator> ff,const Accumulator& start)const{
        Accumulator acc= start;
        this->Traverse(
            [this,&acc/* <- (&start) */,ff](const Data& item){
                acc = ff(item,acc);
            }
        );
        return acc;
    }

    template<typename Data>
    template<typename Accumulator>
    Accumulator PostOrderTraversableContainer<Data>::PostOrderFold(FoldFun<Accumulator> ff,const Accumulator& start)const{
        Accumulator acc= start;
        this->PostOrderTraverse(
            [this,ff,&acc/* <- (&start) */](const Data& item){   
                acc= ff(item,acc);
            }
        );
        return acc;
    }   

    template<typename Data>
    template<typename Accumulator>
    Accumulator InOrderTraversableContainer<Data>::InOrderFold(FoldFun<Accumulator> ff,const Accumulator& start)const{
        Accumulator acc=start;
        this->InOrderTraverse(
            [this,ff,&acc/* <- (&start) */](const Data& item){
                acc= ff(item,acc);
            }
        );
        return acc;
    }
    
    template<typename Data>
    template<typename Accumulator>
    Accumulator BreadthTraversableContainer<Data>::BreadthFold(FoldFun<Accumulator> ff,const Accumulator& start)const{
        Accumulator acc=start;
        this->BreadthTraverse(
            [this,ff,&acc/* <- (&start) */](const Data& item){
                acc=ff(item,acc);
            }
        );
        return acc;
    }
/* ************************************************************************** */

}
