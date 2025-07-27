
namespace lasd {

/* ************************************************************************** */

    // Default constructor
    template<typename Data>
    HashTableOpnAdr<Data>::HashTableOpnAdr(){
        table= new Data[tableSize]{};
        flag= new Flag[tableSize]{};
    }

    // Specific constructor: A hash table of a given size
    template <typename Data>
    HashTableOpnAdr<Data>::HashTableOpnAdr(const unsigned long givensize) {
        // Calcola la dimensione della tabella in potenza di 2 e che sia almeno 32
        tableSize = std::pow(2, std::ceil(log2((givensize < 32) ? 32 : givensize)));
        table = new Data[tableSize] {};
        flag = new Flag[tableSize] {};
    }

    // Specific constructor: A hash table obtained from a TraversableContainer
    template <typename Data>
    HashTableOpnAdr<Data>::HashTableOpnAdr(const TraversableContainer<Data> &tc) : HashTableOpnAdr(tc.Size() * 2) {
        InsertAll(tc);
    }

    // Specific constructor: A hash table of a given size obtained from a TraversableContainer
    template <typename Data>
    HashTableOpnAdr<Data>::HashTableOpnAdr(const unsigned long givensize, const TraversableContainer<Data> &tc) : HashTableOpnAdr(givensize) {
        InsertAll(tc);
    }

    // Specific constructor: A hash table obtained from a MappableContainer
    template <typename Data>
    HashTableOpnAdr<Data>::HashTableOpnAdr(MappableContainer<Data> &&mc) noexcept : HashTableOpnAdr(mc.Size() * 2) {
        InsertAll(std::move(mc));
    }

    // Specific constructor: A hash table of a given size obtained from a MappableContainer
    template <typename Data>
    HashTableOpnAdr<Data>::HashTableOpnAdr(const unsigned long givensize, MappableContainer<Data> &&mc) noexcept : HashTableOpnAdr(givensize) {
        InsertAll(std::move(mc));
    }

    // Copy constructor
    template <typename Data>
    HashTableOpnAdr<Data>::HashTableOpnAdr(const HashTableOpnAdr &htoa) : HashTable<Data>(htoa) {
        table = new Data[tableSize] {};
        flag = new Flag[tableSize] {};
        for(unsigned long i = 0; i < tableSize; i++) {
            table[i] = htoa.table[i];
            flag[i] = htoa.flag[i];
        }
    }

    // Move constructor
    template <typename Data>
    HashTableOpnAdr<Data>::HashTableOpnAdr(HashTableOpnAdr &&htoa) noexcept : HashTable<Data>(std::move(htoa)) {
        std::swap(table, htoa.table);
        std::swap(flag, htoa.flag);
    }

    // Destructor
    template<typename Data>
    HashTableOpnAdr<Data>::~HashTableOpnAdr(){
        delete[] table;
        delete[] flag;
    }

    // Copy assignment
    template <typename Data>
    HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(const HashTableOpnAdr &htoa) {
        HashTable<Data>::operator=(htoa);
        delete[] table;
        delete[] flag;
        table = new Data[tableSize] {};
        flag = new Flag[tableSize] {};
        for(ulong i = 0; i < tableSize; i++) {
            table[i] = htoa.table[i];
            flag[i] = htoa.flag[i];
        }
        return *this;
    }

    // Move assignment
    template <typename Data>
    HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(HashTableOpnAdr &&htoa) noexcept {
        HashTable<Data>::operator=(std::move(htoa));
        std::swap(table, htoa.table);
        std::swap(flag, htoa.flag);
        return *this;
    }

    // Comparison operator (==)
    template <typename Data>
    bool HashTableOpnAdr<Data>::operator==(const HashTableOpnAdr &htoa) const noexcept {
        if(size != htoa.Size()) {
            return false;
        }
        for(ulong i = 0; i < tableSize; i++) {
            if(flag[i] == valid) {
                if(!htoa.Exists(table[i])) {
                    return false;
                }
            }
        }
        return true;
    }

    // Comparison operator (!=)
    template <typename Data>
    bool HashTableOpnAdr<Data>::operator!=(const HashTableOpnAdr &htoa) const noexcept {
        return !(operator==(htoa));
    }

    template <typename Data>
    bool HashTableOpnAdr<Data>::Insert(const Data &target) {
        unsigned long probe = 0;
        if(size * 2 > tableSize)
            Resize(tableSize * 2);

        unsigned long adr = FindEmpty(target, probe);
        if(flag[adr] != valid){
            table[adr] = target;
            flag[adr] = valid;
            ++size;
            return !Remove(target,++probe); 
        }
        probe = 0;
        return false;
    }
            
    template <typename Data>
    bool HashTableOpnAdr<Data>::Insert(Data &&target) {
        unsigned long probe = 0;
        if(size * 2 > tableSize)
            Resize(tableSize * 2);

        unsigned long adr = FindEmpty(target, probe);
        if(flag[adr] != valid){
            table[adr] = std::move(target);
            flag[adr] = valid;
            ++size;
            return !Remove(target,++probe); 
        }
        probe = 0;
        return false;
    }

    template <typename Data>
    bool HashTableOpnAdr<Data>::Remove(const Data &target) {
        unsigned long probe = 0;
        return Remove(target,probe);
    }

    template <typename Data>
    bool HashTableOpnAdr<Data>::Exists(const Data &target) const noexcept {
        unsigned long probe = 0;
        unsigned long adr = HashKey(Hashable<Data>()(target));
        return Find(target,adr, probe);
    }

    template <typename Data>
    void HashTableOpnAdr<Data>::Resize(const unsigned long resize) {
        unsigned long exposize = (resize <= 32)? 32 : std::pow(2, std::ceil(log2(resize)));

        Data* resTable = new Data[exposize] {};
        Flag* resFlag = new Flag[exposize] {}; 

        std::swap(exposize, tableSize);
        std::swap(resTable, table);
        std::swap(resFlag, flag);

        size = 0;
        for(unsigned long i = 0; i < exposize; i++){
            if(resFlag[i] == valid) {
                Insert(resTable[i]);
            }
        }   
        delete[] resTable;
        delete[] resFlag;
    }

    template <typename Data>
    void HashTableOpnAdr<Data>::Clear() {
        for(unsigned long i = 0; i < tableSize; i++) {
            flag[i] = dirty;
        }
        size = 0;
    }

    // Probing quadratico
    template <typename Data> 
    ulong HashTableOpnAdr<Data>::HashKey(const Data& key, unsigned long& probe) const noexcept {
        unsigned long adr = HashKey(Hashable<Data>()(key));
        unsigned long c= 17;
        return (adr + c * ((probe * probe) + probe)/2) % tableSize;
    }

    // Auxiliary member function: trova un elemento nella tabella hash
    template <typename Data>
    bool HashTableOpnAdr<Data>::Find(const Data& target,unsigned long& index, unsigned long& probe) const noexcept {
        unsigned long adr = HashKey(target, probe);
        unsigned long attempt = 0;
        do{
            if(attempt == tableSize - 1) {
                return false;
            }
            if((table[adr] == target) && (flag[adr] == valid)) {
                index = adr;
                return true;
            }
            adr = HashKey(target, ++probe);
            attempt++;
        } while(flag[adr] != free);
        return false;
    }

    // Auxiliary member function: trova un indirizzo vuoto nella tabella hash
    template <typename Data>
    ulong HashTableOpnAdr<Data>::FindEmpty(const Data& target, unsigned long& probe) const noexcept {
        unsigned long adr = HashKey(target, probe);

        // Itera fin quando non trova un indirizzo vuoto
        while((flag[adr] == valid) && (table[adr] != target)) {   
            adr = HashKey(target, ++probe);
        }
        return adr;
    }

    // Auxiliary member function: rimuove elemento dalla tabella hash con probing
    template <typename Data>
    bool HashTableOpnAdr<Data>::Remove(const Data& target,unsigned long& probe) noexcept {
        unsigned long adr=0;
        if(Find(target, adr, probe)){
            flag[adr] = dirty;
            size--;
            probe = 0;

            // Controllo della effettiva dimensione della tabella, nel caso, ridimensiona
            if((size < tableSize / 5) && (tableSize > 32)) {
                Resize(tableSize / 2);
            }
            return true;
        }
        probe = 0;
        return false;
    }
}