
#include <string>
namespace lasd {

/* ************************************************************************** */

    // Default constructor
    template<typename Data>
    HashTableClsAdr<Data>::HashTableClsAdr(){
        table= new List<Data>[tableSize]{};
    }

    // A hash table of a given size
    template<typename Data>
    HashTableClsAdr<Data>::HashTableClsAdr(const unsigned long givensize){
        if(givensize>32)
            tableSize=std::pow(2,std::ceil(std::log2(givensize)));
        
        table=new List<Data>[tableSize]{};
    }

    // A hash table obtained from a TraversableContainer
    template <typename Data>    
    HashTableClsAdr<Data>::HashTableClsAdr(const TraversableContainer<Data>& tc) : HashTableClsAdr(tc.Size()){
        InsertAll(tc);
    }

    // A hash table of a given size obtained from a TraversableContainer
    template <typename Data>    
    HashTableClsAdr<Data>::HashTableClsAdr(const unsigned long givensize, const TraversableContainer<Data>& tc) : HashTableClsAdr(givensize){
        InsertAll(tc);
    }

    // A hash table obtained from a MappableContainer
    template <typename Data>    
    HashTableClsAdr<Data>::HashTableClsAdr(MappableContainer<Data>&& mc)noexcept : HashTableClsAdr(mc.Size()){
        InsertAll(std::move(mc));
    }

    // A hash table of a given size obtained from a MappableContainer
    template <typename Data>    
    HashTableClsAdr<Data>::HashTableClsAdr(const unsigned long givensize, MappableContainer<Data>&& mc)noexcept : HashTableClsAdr(givensize){
        InsertAll(std::move(mc));
    }

    // Copy constructor
    template<typename Data>
    HashTableClsAdr<Data>::HashTableClsAdr(const HashTableClsAdr& htca) : HashTable<Data>(htca){
        table= new List<Data>[tableSize]{};
        for(unsigned long i=0;i<tableSize;i++)
            table[i]=htca.table[i];
    }

    // Move constructor
    template<typename Data>
    HashTableClsAdr<Data>::HashTableClsAdr(HashTableClsAdr&& htca)noexcept : HashTable<Data>(std::move(htca)){
        std::swap(table,htca.table);
    }

    // Destructor
    template<typename Data>
    HashTableClsAdr<Data>::~HashTableClsAdr(){
        delete[] table;
    }

    // Copy assignment
    template<typename Data>
    HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(const HashTableClsAdr<Data>& htca){
        HashTableClsAdr<Data>* newhtca= new HashTableClsAdr(htca);
        std::swap(*this,*newhtca);
        delete newhtca;
        return *this;
    }

    // Move assignment
    template<typename Data>
    HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(HashTableClsAdr<Data>&& htca)noexcept{
        HashTable<Data>::operator=(std::move(htca));
        std::swap(table,htca.table);
        return *this;
    }

    // Comparison operator (==)
    template<typename Data>
    bool HashTableClsAdr<Data>::operator==(const HashTableClsAdr<Data>& htca) const noexcept{
        if(size==htca.size)
        {
            for(unsigned long i=0;i<tableSize;i++){
                if(table[i]!=htca.table[i])
                    return false;
            }
            return true;
        }
        else return false;
    }


    // Comparison operator (!=)
    template<typename Data>
    bool HashTableClsAdr<Data>::operator!=(const HashTableClsAdr<Data>& htca) const noexcept{
        return (!(operator==(htca)));
    }

    // Specific member function overrided 
    template<typename Data>
    bool HashTableClsAdr<Data>::Insert(const Data& target){
        if(table[HashKey(Hashable<Data>()(target))].List<Data>::Insert(target)){
            size++;
            return true;
        }
        else return false;
    }

    template<typename Data>
    bool HashTableClsAdr<Data>::Insert(Data&& target){
        if(table[HashKey(Hashable<Data>()(std::move(target)))].List<Data>::Insert(std::move(target))){
            size++;
            return true;
        }
        else return false;
    }

    template<typename Data>
    bool HashTableClsAdr<Data>::Remove(const Data& target){
        if(table[HashKey(Hashable<Data>()(target))].List<Data>::Remove(target)){
            size--;
            return true;
        }
        else return false;
    }

    template<typename Data>
    bool HashTableClsAdr<Data>::Exists(const Data& find) const noexcept{
        if(table[HashKey(Hashable<Data>()(find))].List<Data>::Exists(find))
            return true;
        else return false;
    }
    
    template<typename Data>
    void HashTableClsAdr<Data>::Clear(){
        delete[] table;
        size=0;
        table= new List<Data>[tableSize]{};
    }

    template<typename Data>
    void HashTableClsAdr<Data>::Resize(const unsigned long resize){
        unsigned long restsize=32;
        size=0;
        if(resize>32)
            restsize=std::pow(2,std::ceil(std::log2(resize)));
            
        List<Data>* newtable= new List<Data>[restsize]{};
        std::swap(newtable,table);
        std::swap(restsize,tableSize);
        for(unsigned long i=0;i<restsize;i++)
            InsertAll(newtable[i]);
        
        delete [] newtable;

    }
/* ************************************************************************** */

}
