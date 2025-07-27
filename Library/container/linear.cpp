
#include <stdexcept>

namespace lasd {

/* ************************************************************************** */

//Compare l-value == r-value (for LinearContainer)
template<typename Data>
bool LinearContainer<Data>::operator==(const LinearContainer& lc)const noexcept{
    //Case (1): check sizes
    if (size!=lc.size){ return false; };
    //..else case (2): check items positions by positions
    for(unsigned long i=0;i<size;i++){
        if (lc[i]!=this->operator[](i))
            return false;
    }
    return true;
}

//Compare l-value != r-value (for LinearContainer)
template<typename Data>
bool LinearContainer<Data>::operator!=(const LinearContainer& lc)const noexcept{
    return !(*this==lc);
}

//Specific member functions (for LinearContainer)
template<typename Data>
const Data& LinearContainer<Data>::Front()const{
    if(Container::Empty())
        throw std::length_error("Lenght error: Unable to access to front element of an empty Container");
    return (this->operator[](0));
}

template<typename Data>
Data& LinearContainer<Data>::Front(){
if(Container::Empty())
        throw std::length_error("Lenght error: Unable to access to front element of an empty Container");
    return (this->operator[](0));
}

template<typename Data>
const Data& LinearContainer<Data>::Back()const{
    if(Container::Empty())
        throw std::length_error("Lenght error : Unable to access to back element of an empty Container");
    return (this->operator[](size-1));
}

template<typename Data>
Data& LinearContainer<Data>::Back(){
    if(Container::Empty())
        throw std::length_error("Lenght error : Unable to access to back element of an empty Container");
    return (this->operator[](size-1));
}

//Specific member function (inhreted from TraversableContainer)
template<typename Data>
void LinearContainer<Data>::Traverse(const TraverseFun tf)const{
    PreOrderTraverse(tf);
}

//Specific member function (inhereted from PreOrderTraversableContainer)
template<typename Data>
void LinearContainer<Data>::PreOrderTraverse(const TraverseFun tf)const{
    for(unsigned long i = 0; i<size;i++)
        tf(this->operator[](i));
}

//Specific member function (inhereted from PostOrderTraversableContainer)
template<typename Data>
void LinearContainer<Data>::PostOrderTraverse(const TraverseFun tf)const{
    for(unsigned long i= size; i!=0;i--)
        tf(this->operator[](i-1));
}

// Specific member function (inherited from MappableContainer)
template<typename Data>
void LinearContainer<Data>::Map(const MapFun mf){
    PreOrderMap(mf);
}

// Specific member function (inherited from PreOrderMappableContainer)
template<typename Data>
void LinearContainer<Data>::PreOrderMap(const MapFun mf){
    for(unsigned long i=0;i<size;i++)
        mf(this->operator[](i));
}

// Specific member function (inherited from PostOrderMappableContainer)
template<typename Data>
void LinearContainer<Data>::PostOrderMap(const MapFun mf){
    for(unsigned long i=size;i!=0;i--)
        mf(this->operator[](i-1));
}

//Compare l-value==r-value(for SortableLinearContainer)
/*template<typename Data>
bool SortableLinearContainer<Data>::operator==(const SortableLinearContainer& slc)const noexcept{
    //Case (1): check sizes
    if (size!=slc.size){ return false; }
    //..else case (2): check items position by position
    for(unsigned long i=0;i<size;i++){
        if (slc[i]!=this[i])
            return false;
    }
    return true;
}

template<typename Data>
bool SortableLinearContainer<Data>::operator!=(const SortableLinearContainer& slc)const noexcept{
    return (!(this==slc));
}

*/
/* ************************************************************************** */

}







