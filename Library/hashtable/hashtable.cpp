
namespace lasd {

/* ************************************************************************** */

    template <>
    class Hashable<int> {
    public:
        ulong operator()(const int & dat) const noexcept {
            return (dat * dat);
        }
    };

    template<>
    class Hashable<std::string> {
        public:
            unsigned long operator()(const std::string& str) const noexcept{
                unsigned long hash = 5381;
                for(unsigned long i = 0; i < str.length(); i++)
                    hash = (hash << 5) + str[i];
                    
                return hash;
            }
    };

    template<>
    class Hashable<double> {
        public:
            ulong operator()(const double& dat) const noexcept {
                ulong intgpart = floor(dat);
                ulong fracpart = pow(2, 24) * (dat - intgpart);
                return (intgpart * fracpart);
            }
    };

    template<typename Data>
    HashTable<Data>::HashTable(){
        foff=randomHash(1);
        loff=randomHash(0);
    }

    template<typename Data>
    HashTable<Data>::HashTable(const HashTable<Data>& ht){
        foff=ht.foff;
        loff=ht.loff;
        tableSize=ht.tableSize;
        size=ht.size;
    }

    template<typename Data>
    HashTable<Data>::HashTable(HashTable<Data>&& ht)noexcept{
        std::swap(foff,ht.foff);
        std::swap(loff,ht.loff);
        std::swap(tableSize,ht.tableSize);
        std::swap(size,ht.size);
    }

    template<typename Data>
    HashTable<Data>& HashTable<Data>::operator=(const HashTable& ht){
        foff=ht.foff;
        loff=ht.loff;
        tableSize=ht.tableSize;
        size=ht.size;
        
        return *this;
    }

    template<typename Data>
    HashTable<Data>& HashTable<Data>::operator=(HashTable&& ht)noexcept{
        std::swap(foff,ht.foff);
        std::swap(loff,ht.loff);
        std::swap(tableSize,ht.tableSize);
        std::swap(size,ht.size);

        return *this;
    }


    //Auxiliary function: generate random hash
    template<typename Data>
    unsigned long HashTable<Data>::HashKey(unsigned long key)const noexcept{
        return (((foff + key + loff)%primenum)%tableSize);
    }
    template<typename Data>
    unsigned long HashTable<Data>::randomHash(const int& generator){
        std::default_random_engine gen(std::random_device{}());
        std::uniform_int_distribution<unsigned long> dis(generator,primenum-1);
        return dis(gen);
    }
/* ************************************************************************** */

}
