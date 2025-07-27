#define QUE_VEC_SIZE 4
#define QUE_VEC_MEASURE_EXP 2
#define QUE_VEC_MEASURE_REDUCE 0.75
namespace lasd {

/* ************************************************************************** */

    //Default constructor
    template<typename Data>
    QueueVec<Data>::QueueVec(){
        size=QUE_VEC_SIZE;
        front= 0;
        wraparound=false;
        rear=-1;
        elements=new Data[size]{};
    }

    //Specific constructor
    template <typename Data>
    QueueVec<Data>::QueueVec(const TraversableContainer<Data>& tc){
        size=tc.Size();
        elements=new Data[size];
        front=0;
        wraparound=false;
        rear=size-1;
        unsigned long cursor=0;
        tc.Traverse(
            [this,&cursor](const Data& target){
                elements[cursor++]=target;
            }
        );
    }

    //Specific constructor
    template <typename Data>
    QueueVec<Data>::QueueVec(MappableContainer<Data>&& mp)noexcept{
        size=mp.Size();
        elements=new Data[size];
        front=0;
        wraparound=false;
        rear=size-1;
        unsigned long cursor=0;
        mp.Map(
            [this,&cursor](Data& target){
                elements[cursor++]=std::move(target);
            }
        );
    }
    //Copy constructor
    template <typename Data>
    QueueVec<Data>::QueueVec(const QueueVec<Data>& cpy) : Vector<Data>::Vector(cpy){
        front=cpy.front;
        rear=cpy.rear;
        wraparound=cpy.wraparound;
    }   

    //Move constructor
    template <typename Data>
    QueueVec<Data>::QueueVec(QueueVec<Data>&& mve)noexcept{
        std::swap(size,mve.size);
        std::swap(front,mve.front);
        std::swap(wraparound,mve.wraparound);
        std::swap(rear,mve.rear);
        std::swap(elements,mve.elements);
    }

    //Comparison assigment(==)
    template <typename Data>
    bool QueueVec<Data>::operator==(const QueueVec<Data>& cmp)const noexcept{
        if(Size()!=cmp.Size()){
            return false;
        }else{
            for(unsigned long i=0;i<Size();i++)
                if(elements[(i+front)%size]!=cmp.elements[(i+cmp.front)%size])
                    return false;
                
            return true;
        }

    }

    //Comparison assigment(!=)
    template <typename Data>
    bool QueueVec<Data>::operator!=(const QueueVec<Data>& cmp)const noexcept{
        return !(*this==cmp);
    }

    //Copy assigment
    template <typename Data>
    QueueVec<Data>& QueueVec<Data>::operator=(const QueueVec<Data>& cpy){
        Clear();
        QueueVec<Data> * newQueuevec=new QueueVec<Data>(cpy);
        newQueuevec->size=cpy.size;
        for(unsigned long i=0;i<cpy.size;i++)
            newQueuevec->elements[i]=cpy.elements[i];

        std::swap(*newQueuevec,*this);
        delete newQueuevec;
        front=cpy.front;
        rear=cpy.rear;
        wraparound=cpy.wraparound;
        return *this;
    }

    //Move assigment
    template <typename Data>
    QueueVec<Data>& QueueVec<Data>::operator=(QueueVec<Data>&& mve)noexcept{
        std::swap(size,mve.size);
        std::swap(front,mve.front);
        std::swap(rear,mve.rear);
        std::swap(wraparound,mve.wraparound);
        std::swap(elements,mve.elements);

        return *this;
    }

    //Specific member functions (inhereted from Queue)
    template <typename Data>
    const Data& QueueVec<Data>::Head()const{
        if(Size()!=0)
            return elements[front];
        else
            throw std::length_error("Unable to access an empty queue vector!");
    }


    //Specific member functions (inhereted from Queue)
    template <typename Data>
    Data& QueueVec<Data>::Head(){
        if(Size()!=0)
            return elements[front];
        else   
            throw std::length_error("Unable to access an empty queue vector!");
        
    }


    //Specific member functions (inhereted from Queue)
    template <typename Data>
    void QueueVec<Data>::Dequeue(){
        if(Size()!=0)
        {
            if(front==rear)
                Clear();
            else{
                front=(front+1)%size;
            }

            if(front==0)
                wraparound=false;
            if((Size()<=(size/2)) && (Size()>=QUE_VEC_SIZE)){
                Reduce();
            }
            
        }
        else
            throw std::length_error("Unable to dequeue an empty queue vector!");
    }


    //Specific member functions (inhereted from Queue)
    template <typename Data>
    Data QueueVec<Data>::HeadNDequeue(){
        if(Size()!=0)
        {
            Data result = Head(); 
            Dequeue();
            return result;
        }else
            throw std::length_error("Unable to dequeue an empty queue vector!");
    }


    //Specific member functions (inhereted from Queue)
    template <typename Data>
    void QueueVec<Data>::Enqueue(const Data& target){
        if(Size()==size){
            Expand();
        }
        rear=(rear+1)%size;
        elements[rear]=target;
        if(rear<front)
            wraparound=true;
        
    }


    //Specific member functions (inhereted from Queue)
    template <typename Data>
    void QueueVec<Data>::Enqueue(Data&& target)noexcept{
        if(Size()==size){
            Expand();
        }

        rear=(rear+1)%size;
        elements[rear]=target;
        if(rear<front)
            wraparound=true; 
               


    }

    // Specific member functions (inherited from Container)
    template <typename Data>
    inline bool QueueVec<Data>::Empty()const noexcept{
        return (Size()==0);
    }

    // Specific member functions (inherited from Container)
    template<typename Data>
    inline unsigned long QueueVec<Data>::Size()const noexcept{
        if(wraparound)
            return (((rear + (size + 1)) - front) % (size + 1));
        else return (( (rear + 1) + (size + 1) - front ) % (size + 1));
    }

    // Specific member function (inherited from ClearableContainer)
    template <typename Data>
    void QueueVec<Data>::Clear(){
        delete [] elements;
        front=0;
        size=4;
        wraparound=false;
        rear=-1;
        elements=new Data[size]{};
    }
    // Auxiliary member functions
    template <typename Data>
    void QueueVec<Data>::SwapVectors(unsigned long swapper){
        if (swapper == 0)
        {
            Clear();
        }
        else if (size != swapper)
        {
            unsigned long wall = (size < swapper) ? size : swapper;
            Data *cursor = new Data[swapper]{};
            for (unsigned long i = 0; i < wall; i++)
                cursor[i]=elements[(i+front)%size];
            
            std::swap(elements, cursor);
            rear=Size()-1;
            front=0;
            size = swapper;
            wraparound=false;
            delete[] cursor;
        }
    }

    // Auxiliary member functions
    template <typename Data>
    void QueueVec<Data>::Expand(){
        SwapVectors(size*QUE_VEC_MEASURE_EXP);
    }
    // Auxiliary member functions
    template <typename Data>
    void QueueVec<Data>::Reduce(){
    SwapVectors(size*QUE_VEC_MEASURE_REDUCE);
    }
}
