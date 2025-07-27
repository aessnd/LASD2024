
namespace lasd {

/* ************************************************************************** */

    //Description Vector's functions

    template<typename Data>
    Vector<Data>::Vector(const unsigned long dim){
        //Allocate memory to new array and set the new size
        elements= new Data[dim]{};
        size=dim;
    }

    template<typename Data>
    Vector<Data>::Vector(const TraversableContainer<Data>& tc){
        size=tc.Size();
        elements=new Data[size]{};
        unsigned long cursor=0;
        tc.Traverse(
            [this,&cursor](const Data& item){
                elements[cursor++]=item;
            }
        );
    }

    template<typename Data>
    Vector<Data>::Vector(MappableContainer<Data>&& mc)noexcept{
        size=mc.Size();
        elements=new Data[size]{};
        unsigned long cursor=0;
        mc.Map(
            [this,&cursor](Data& item){
                elements[cursor++]=std::move(item);
            }
        );
    }

    template<typename Data>
    Vector<Data>::Vector(const Vector<Data>& cpy){
        size=cpy.size;
        elements=new Data[cpy.size]{};

        for(unsigned long i=0;i<cpy.size;i++)
            elements[i]=cpy.elements[i];
    }

    template<typename Data>
    Vector<Data>::Vector(Vector<Data>&& mve)noexcept{
        std::swap(elements,mve.elements);
        std::swap(size,mve.size);
    }

    template<typename Data>
    Vector<Data>::~Vector(){    
        delete[] elements;
    }

    template<typename Data>
    Vector<Data>& Vector<Data>::operator=(const Vector<Data>& cpy){
        Vector<Data> *vec = new Vector<Data>(cpy.size);
        vec->size=cpy.size;
        for(unsigned long i=0; i<cpy.size;i++)
            vec->operator[](i)=cpy.operator[](i);
        
        std::swap(*this,*vec);
        delete vec;
        return *this;
    }

    template<typename Data>
    Vector<Data>& Vector<Data>::operator=(Vector<Data>&& mve)noexcept{
        std::swap(size,mve.size);
        std::swap(elements,mve.elements);
        return *this;
    }

    template<typename Data>
    bool Vector<Data>::operator==(const Vector<Data>& cmp)const noexcept{
        if(size!=cmp.size) { return false; }
        //..else..
        for(unsigned long i=0;i<size;i++){
            if(elements[i]!=cmp.elements[i])
                return false;
        }
        return true;
    }

    template<typename Data>
    bool Vector<Data>::operator!=(const Vector<Data>& cmp)const noexcept{
        return (!(*this==cmp));
    }

    template<typename Data>
    void Vector<Data>::Clear(){
        delete[] elements;
        size=0;
        elements=nullptr;
    }

    template<typename Data>
    void Vector<Data>::Resize(const unsigned long resize){
        //Case 1: resize has dimension 0 => clear the vector
        if(resize==0){
            Clear();
            return;
        }

        //Case 2: risize has the same dimension of size => do nothing
        if(resize==size) { return; }
        
        //Case 3: risize has different dimension of size => border=min(size,resize)
        Data *vecresize = new Data[resize]{};
        unsigned long border=0;
        if(resize>size) { border=size; }
        else if (resize<size) { border = resize; }
        //Copy values from elements to new vector resized
        for(unsigned int i=0;i<border;i++)
            vecresize[i]=elements[i];

        //Then, swap the references and delete the temporary vecresize
        std::swap(elements,vecresize);
        size=resize;
        delete[] vecresize;
    }

    template<typename Data>
    const Data& Vector<Data>::operator[](const unsigned long index)const{
        if(size>index)
            return elements[index];
        else throw std::out_of_range("Out of range: Unable to access a non-existent item");
        
    }

    template<typename Data>
    Data& Vector<Data>::operator[](const unsigned long index){
        if(size>index)
            return elements[index];
        else throw std::out_of_range("Out of range: Unable to access a non-existent item"); 
    }

    template<typename Data>
    const Data& Vector<Data>::Front()const{
        if(Container::Empty())
            throw std::length_error("Lenght error: Unable to access an empty Container");
        else return elements[0];
    }

    template<typename Data>
    Data& Vector<Data>::Front(){
        if(Container::Empty())
            throw std::length_error("Lenght error: Unable to access an empty Container");
        else return elements[0];
    }

    template<typename Data>
    const Data& Vector<Data>::Back()const{
        if(Container::Empty())
            throw std::length_error("Lenght error: Unable to access an empty Container");
        else return elements[size-1];
    }

    template<typename Data>
    Data& Vector<Data>::Back(){
        if(Container::Empty())
            throw std::length_error("Lenght error: Unable to access an empty Container");
        else return elements[size-1];
    }

    //Description SortableVector's functions

template<typename Data>
    SortableVector<Data>::SortableVector(const unsigned long dim)
    {
        //Allocate memory to new array and set the new size
        elements= new Data[dim]{};
        size=dim;
    }

    template<typename Data>
    SortableVector<Data>::SortableVector(const TraversableContainer<Data>& tc)
    {
        size=tc.Size();
        elements=new Data[size]{};
        unsigned long cursor=0;
        tc.Traverse(
            [this,&cursor](const Data& item){
                elements[cursor++]=item;
            }
        );
    }

    template<typename Data>
    SortableVector<Data>::SortableVector(MappableContainer<Data>&& mc)noexcept
    {
        size=mc.Size();
        elements=new Data[size]{};
        unsigned long cursor=0;
        mc.Map(
            [this,&cursor](Data& item){
                elements[cursor++]=std::move(item);
            }
        );
    }

    template<typename Data>
    SortableVector<Data>::SortableVector(const SortableVector<Data>& cpy)
    {
        size=cpy.size;
        elements=new Data[cpy.size]{};

        for(unsigned long i=0;i<cpy.size;i++)
            elements[i]=cpy.elements[i];
    }

    template<typename Data>
    SortableVector<Data>::SortableVector(SortableVector<Data>&& sv)noexcept
    {
        std::swap(elements,sv.elements);
        std::swap(size,sv.size);
    }

    template<typename Data>
    SortableVector<Data>& SortableVector<Data>::operator=(const SortableVector<Data>& cpy){
        SortableVector<Data> *vec = new SortableVector<Data>(cpy.size);
        vec->size=cpy.size;
        for(unsigned long i=0; i<cpy.size;i++)
            vec->operator[](i)=cpy.operator[](i);
        
        std::swap(*this,*vec);
        delete vec;
        return *this;
    }

    template<typename Data>
    SortableVector<Data>& SortableVector<Data>::operator=(SortableVector<Data>&& mve)noexcept{
        std::swap(elements,mve.elements);
        std::swap(size,mve.size);
        return *this;
    }

    template <typename Data>
    void SortableVector<Data>::Sort()noexcept{ //InsectionSort
            for(unsigned int i= 1;i<Container::Size();i++)
            {
                Data tmp=elements[i];
                int j=i-1;
                
                while(j>=0 && tmp <= elements[j]){
                    elements[j+1]= elements[j];
                    j=j-1;
                }
                elements[j+1]=tmp;
            }
    }
/* ************************************************************************** */

}
