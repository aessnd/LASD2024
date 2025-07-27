
namespace lasd {

/* ************************************************************************** */

    template<typename Data>
    StackLst<Data>::StackLst() : List<Data>::List()
    {}

    template<typename Data>
    StackLst<Data>::StackLst(const TraversableContainer<Data>& tc) : List<Data>::List(tc)
    {}

    template<typename Data>
    StackLst<Data>::StackLst(MappableContainer<Data>&& mc)noexcept : List<Data>::List(std::move(mc))
    {}

    template<typename Data>
    StackLst<Data>::StackLst(const StackLst<Data>& cpy) : List<Data>::List(cpy)
    {}

    template<typename Data>
    StackLst<Data>::StackLst(StackLst<Data>&& mve)noexcept : List<Data>::List(std::move(mve))
    {}

    template<typename Data>
    StackLst<Data>& StackLst<Data>::operator=(const StackLst<Data>& cpy)
    {
        List<Data>::operator=(cpy);
        return *this;
    }

    template<typename Data>
    StackLst<Data>& StackLst<Data>::operator=(StackLst<Data>&& mve)noexcept
    {
        List<Data>::operator=(std::move(mve));
        return *this;
    }

    template<typename Data>
    bool StackLst<Data>::operator==(const StackLst<Data>& cmp)const noexcept
    {
        return (List<Data>::operator==(cmp));
    }

    template<typename Data>
    bool inline StackLst<Data>::operator!=(const StackLst<Data>& cmp)const noexcept
    {
        return (!(*this==cmp));
    }

    // Specific member functions (inherited from Stack)
    template<typename Data>
    const Data& StackLst<Data>::Top()const{
        return List<Data>::Front();
    }

    template<typename Data>
    Data& StackLst<Data>::Top(){
        return List<Data>::Front();
    }

    template<typename Data>
    void StackLst<Data>::Pop(){
        return List<Data>::RemoveFromFront();
    }

    template<typename Data>
    Data StackLst<Data>::TopNPop(){
        return List<Data>::FrontNRemove();
    }

    template<typename Data>
    void StackLst<Data>::Push(const Data& item){
        List<Data>::InsertAtFront(item);
    }

    template<typename Data>
    void StackLst<Data>::Push(Data&& item)noexcept{
        List<Data>::InsertAtFront(std::move(item));
    }



/* ************************************************************************** */

}
