
namespace lasd {

/* ************************************************************************** */

//Specific member functions' description

//Insert ALL type Data and checks it (for TrasversableContainer)
template<typename Data>
bool DictionaryContainer<Data>::InsertAll(const TraversableContainer<Data>& tc){
    bool flag=true;
    tc.Traverse(
        [this,&flag](const Data& item){
            flag &= Insert(item);  // :- flag = flag & Insert(..)

                //TRUE: if all item have been inserted
                //FALSE:if at least one item has not been inserted
        }
    );
    return flag;
}

//Insert ALL type Data and check it (for MappableContainer)
template<typename Data>
bool DictionaryContainer<Data>::InsertAll(MappableContainer<Data>&& mc) noexcept{
    bool flag=true;
    mc.Map(
        [this,&flag](Data& item){
            flag &= Insert(std::move(item));   //:- flag= flag & Insert(..)

                //TRUE: if all item have been inserted
                //FALSE:if at least one item has not been inserted
        }
    );
    return flag;
}

//Remove ALL type Data and checks it (for TraversableContainer)
template<typename Data>
bool DictionaryContainer<Data>::RemoveAll(const TraversableContainer<Data>& tc){
    bool flag=true;
    tc.Traverse(
        [this,&flag](const Data &item){
            flag &= Remove(item);  // :- flag = flag & Remove(..)

                //TRUE: if all item have been removed
                //FALSE:if at least one item has not been removed
        }
    );
    return flag;
}

//Insert SOME type Data and checks it (for TraversableContainer)
template<typename Data>
bool DictionaryContainer<Data>::InsertSome(const TraversableContainer<Data>& tc){
    bool flag=false;
    tc.Traverse(
        [this,&flag](const Data &item){
            flag |= Insert(item);  // :- flag = flag | Insert(..)

                //TRUE: if at least one item has been inserted
                //FALSE: if all item have not been inserted
        }
    );
    return flag;
}

//Insert SOME type Data and checks it (for MappableContainer)
template<typename Data>
bool DictionaryContainer<Data>::InsertSome(MappableContainer<Data>&& mc)noexcept{
    bool flag=false;
    mc.Map(
        [this,&flag](Data& item){
            flag |= Insert(std::move(item));   // :- flag = flag | Insert(..)

                //TRUE: if at least one item has been inserted
                //FALSE: if all item have not been inserted
        }
    );
    return flag;
}

//Remove SOME type Data and checks it (for TraversableContainer)
template<typename Data>
bool DictionaryContainer<Data>::RemoveSome(const TraversableContainer<Data>& tc){
    bool flag= false;
    tc.Traverse(
        [this,&flag](const Data& item){
            flag |= Remove(item);  // :- flag = flag | Remove(..)

                //TRUE: if at least one item has been removed
                //FALSE: if all item have not been removed
        }
    );
    return flag;
}


/* ************************************************************************** */

}
