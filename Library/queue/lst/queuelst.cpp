
namespace lasd {

/* ************************************************************************** */

    template<typename Data>
    QueueLst<Data>::QueueLst(const TraversableContainer<Data>& tc) : List<Data>::List(tc)
    {
    }

    template<typename Data>
    QueueLst<Data>::QueueLst(MappableContainer<Data>&& mc)noexcept : List<Data>::List(std::move(mc))
    {
    }

    template<typename Data>
    QueueLst<Data>::QueueLst(const QueueLst<Data>& cpy) : List<Data>::List(cpy)
    {
    }

    template<typename Data>
    QueueLst<Data>::QueueLst(QueueLst<Data>&& mve)noexcept : List<Data>::List(std::move(mve))
    {
    }

    template<typename Data>
    QueueLst<Data>& QueueLst<Data>::operator=(const QueueLst<Data>& cpy)
    {
        List<Data>::operator=(cpy);
        return *this;
    }

    template<typename Data>
    QueueLst<Data>& QueueLst<Data>::operator=(QueueLst<Data>&& mve)noexcept
    {
        List<Data>::operator=(std::move(mve));
        return *this;
    }

    template<typename Data>
    bool QueueLst<Data>::operator==(const QueueLst<Data>& cmp)const noexcept{
        return List<Data>::operator==(cmp);
    }

    template<typename Data>
    bool inline QueueLst<Data>::operator!=(const QueueLst<Data>& cmp)const noexcept{
        return (!(*this==cmp));
    }

    template<typename Data>
    const Data& QueueLst<Data>::Head()const{
        if(List<Data>::Empty())
            throw std::length_error ("Lenght error: Unable to access an empty container!");
        else return List<Data>::Front();
    }

    template<typename Data>
    Data& QueueLst<Data>::Head(){
        if(List<Data>::Empty())
            throw std::length_error ("Lenght error: Unable to access an empty container!");
        else return List<Data>::Front();
    }

    template<typename Data>
    void QueueLst<Data>::Dequeue(){
        if(List<Data>::Empty())
            throw std::length_error ("Lenght error: Unable to access an empty container!");
        else List<Data>::RemoveFromFront();
    }

    template<typename Data>
    Data QueueLst<Data>::HeadNDequeue(){
        if(List<Data>::Empty())
            throw std::length_error ("Lenght error: Unable to access an empty container!");
        else return List<Data>::FrontNRemove();
    }

    template<typename Data>
    void QueueLst<Data>::Enqueue(const Data& item){
        List<Data>::InsertAtBack(item);
    }

    template<typename Data>
    void QueueLst<Data>::Enqueue(Data&& item)noexcept{
        List<Data>::InsertAtBack(std::move(item));
    }
/* ************************************************************************** */

}
