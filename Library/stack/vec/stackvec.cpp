
#define STK_VEC_SIZE 4
#define STK_VEC_EXP 2
#define STK_VEC_REDUCE 0.75
namespace lasd {

/* ************************************************************************** */

    template<typename Data>
    StackVec<Data>::StackVec(){
        size=STK_VEC_SIZE;
        elements=new Data[size]{};
        front=0;
    }

    template<typename Data>
    StackVec<Data>::StackVec(const TraversableContainer<Data>& tc){
        size=tc.Size();
        elements=new Data[size]{};
        tc.Traverse(
            [this](const Data& item){
                Push(item);
            }
        );
        front=size;
    }

    template<typename Data>
    StackVec<Data>::StackVec(MappableContainer<Data>&& mc)noexcept{
        size=mc.Size();
        elements=new Data[size]{};
        mc.Traverse(
            [this](Data& item){
                Push(std::move(item));
            }
        );
        front=size;
    }

    template<typename Data>
    StackVec<Data>::StackVec(const StackVec<Data>& cpy){
        size=cpy.size;
        elements=new Data[size]{};
        for(unsigned long i = 0; i < cpy.front;i++)
            elements[i]=cpy[i];
        front=cpy.front;
    }

    template<typename Data>
    StackVec<Data>::StackVec(StackVec<Data>&& mve)noexcept{
        std::swap(front,mve.front);
        std::swap(elements,mve.elements);
        std::swap(size,mve.size);
    }

    template<typename Data>
    StackVec<Data>& StackVec<Data>::operator=(const StackVec<Data>& cpy){
        StackVec<Data> * newstkvec = new StackVec<Data>(cpy);
        std::swap(*newstkvec,*this);
        delete newstkvec;
        return *this;
    }

    template<typename Data>
    StackVec<Data>& StackVec<Data>::operator=(StackVec<Data>&& mve)noexcept{
        std::swap(front,mve.front);
        std::swap(elements,mve.elements);
        std::swap(size,mve.size);
        return *this;
    }

    template<typename Data>
    bool StackVec<Data>::operator==(const StackVec<Data>& cmp)const noexcept{
        if(front!=cmp.front){
        return false;
        }
        else{
            for(unsigned long i=0;i<cmp.front;i++){
                if(elements[i]!=cmp.elements[i])
                    return false;
            }
            return true;
        }
    }

    template<typename Data>
    bool StackVec<Data>::operator!=(const StackVec<Data>& cmp)const noexcept{
        return (!(*this==cmp));
    }    

    template<typename Data>
    const Data& StackVec<Data>::Top()const{
        if(Empty())
            throw std::length_error("Lenght error: Unable to access an empty container");
        else return elements[front-1];
    }

    template<typename Data>
    Data& StackVec<Data>::Top(){
        if(Empty())
            throw std::length_error("Lenght error: Unable to access an empty container");
        else return elements[front-1];
    }

    template<typename Data>
    void StackVec<Data>::Pop(){
        if(Empty())
            throw std::length_error("Lenght error: Unable to access an empty container");
        else{
            front--;
            if(front==0)
                Clear();
            else
            Reduce();
        }
    }

    template<typename Data>
    Data StackVec<Data>::TopNPop(){
        if(Empty())
            throw std::length_error("Lenght error: Unable to access an empty container");
        else{
            Data result= elements[front-1];
            Pop();
            return result;
        }
    }

    template<typename Data>
    void StackVec<Data>::Push(const Data& item){
        Expand();
        elements[front++]=item;
    }

    template<typename Data>
    void StackVec<Data>::Push(Data&& item)noexcept{
        Expand();
        elements[front++]=std::move(item);
    }

    template<typename Data>
    bool inline StackVec<Data>::Empty()const noexcept{
        return front==0;
    }

    template<typename Data>
    unsigned long inline StackVec<Data>::Size()const noexcept{
        return front;
    }

    template<typename Data>
    void StackVec<Data>::Clear(){
        delete [] elements;
        size=STK_VEC_SIZE;
        elements=new Data[size]{};
        front=0;
    }

    template<typename Data>
    void StackVec<Data>::Reduce(){
        if(Size() <= size/2 && Size()>=STK_VEC_SIZE)
            Vector<Data>::Resize(size*STK_VEC_REDUCE);
    }

    template<typename Data>
    void StackVec<Data>::Expand(){
        if(Size()==size)
            Vector<Data>::Resize(size*STK_VEC_EXP);
    }


/* ************************************************************************** */

}
