
namespace lasd {

/* ************************************************************************** */

    template<typename Data>
    BinaryTreeVec<Data>::NodeVec::NodeVec(const Data& item,unsigned long i,Vector<NodeVec*>* btv){
        this->btv=btv;
        this->item=item;
        this->index=i;
    }

    template<typename Data>
    BinaryTreeVec<Data>::NodeVec::NodeVec(Data&& item,unsigned long i,Vector<NodeVec*>* btv)noexcept{
        std::move(this->btv,btv);
        std::move(this->item,item);
        std::move(this.index,i);
    }

    template<typename Data>
    typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::operator=(const NodeVec& node){
        this->btv=node->bt;
        this->index=node->index;
        return *this;
    }

    template<typename Data>
    typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::operator=(NodeVec&& node)noexcept{
        std::move(this->btv,node->btv);
        std::move(this->index,node->index);
        return *this;
    }

    template<typename Data>
    const Data& BinaryTreeVec<Data>::NodeVec::Element()const noexcept{
        return item; 
    }

    template<typename Data>
    Data& BinaryTreeVec<Data>::NodeVec::Element()noexcept{
        return item; 
    }

    template<typename Data>
    bool BinaryTreeVec<Data>::NodeVec::HasLeftChild()const noexcept{
        return (LCHILD(index)<btv->Size() && (*btv)[LCHILD(index)]!=nullptr);
    }

    template<typename Data>
    bool BinaryTreeVec<Data>::NodeVec::HasRightChild()const noexcept{
        return (RCHILD(index)<btv->Size() && (*btv)[RCHILD(index)]!=nullptr);
    }

    template<typename Data>
    const typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::LeftChild()const{
        if(HasLeftChild())
            return *(*btv)[LCHILD(index)];
        else throw std::out_of_range("Left child not existent!");
    }

    template<typename Data>
    const typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::RightChild()const{
        if(HasRightChild())
            return *(*btv)[RCHILD(index)];
        else throw std::out_of_range("Right child not existent!");
    }

    template<typename Data>
    typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::LeftChild(){
        if(HasLeftChild())
            return *(*btv)[LCHILD(index)];
        else throw std::out_of_range("Left child not existent!");
    }

    template<typename Data>
    typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::RightChild(){
        if(HasRightChild())
            return *(*btv)[RCHILD(index)];
        else throw std::out_of_range("Right child not existent!");
    }

/* ************************************************************************** */

    template<typename Data>
    BinaryTreeVec<Data>::BinaryTreeVec(const TraversableContainer<Data>& tc){
        size=tc.Size();
        vec.Resize(size);
        unsigned long cursor=0;
        tc.Traverse(
            [this,&cursor](const Data& target){
                vec[cursor]=new NodeVec(target,cursor,&vec);
                cursor++;
            }
        );
    }

    template<typename Data>
    BinaryTreeVec<Data>::BinaryTreeVec(MappableContainer<Data>&& mc)noexcept{
        size=mc.Size();
        vec.Resize(size);
        unsigned long cursor=0;
        mc.Map(
            [this,&cursor](Data& target){
                vec[cursor]=new NodeVec(std::move(target),cursor,&vec);
                cursor++;
            }
        );
    }

    template<typename Data>
    BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec<Data>& btv){
        size=btv.size;
        vec.Resize(btv.vec.Size());
        for(unsigned long i=0;i<btv.vec.Size();i++)
            vec[i]=new NodeVec(btv.vec[i]->Element(),i,&vec);
    }

    template<typename Data>
    BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec<Data>&& btv)noexcept{
        std::swap(size,btv.size);
        std::swap(vec,btv.vec);
        for(unsigned long i=0;i<size;i++)
            vec[i]->btv=&vec;
    }

    template <typename Data>
    BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(const BinaryTreeVec<Data>& btv)
    {
        BinaryTreeVec<Data>* newbtv= new BinaryTreeVec<Data>(btv);
        std::swap(*this,*newbtv);
        for(unsigned long i=0;i<size;i++)
            vec[i]->btv=&vec;
        
        delete newbtv;
        return *this;
    }

    template <typename Data>
    BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(BinaryTreeVec<Data>&& btv)noexcept
    {
        std::swap(size,btv.size);
        std::swap(vec,btv.vec);
        for(unsigned long i=0;i<size;i++)
            vec[i]->btv=&vec;
        
        return *this;
    }

    template <typename Data>
    bool BinaryTreeVec<Data>::operator==(const BinaryTreeVec<Data>& cmp_btv)const noexcept{
        if(size!=cmp_btv.size)
            return false;
        else{
            for(unsigned long i=0;i<size;i++){
                if(vec[i]!=cmp_btv.vec[i])
                    return false;
            }
            return true;
        }
    }

    template <typename Data>
    bool BinaryTreeVec<Data>::operator!=(const BinaryTreeVec<Data>& cmp_btv)const noexcept{
        return (!(*this==cmp_btv));
    }

    template <typename Data>
    const typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::Root() const{
        if(size>0)
            return *vec[0];
        else throw std::length_error("Error: binary tree vec is empty!");
    }

    template <typename Data>
    typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::Root(){
        if(size>0)
            return *vec[0];
        else throw std::length_error("Error: binary tree vec is empty!");
    }

    template <typename Data>
    void BinaryTreeVec<Data>::Clear(){
        if(size>0){
            for(unsigned long i=0;i<size;i++)
            {
                delete vec[i];
                vec[i]=nullptr;
            }
            size=0;
        }
    }

    template <typename Data>
    void BinaryTreeVec<Data>::BreadthTraverse(const TraverseFun tf)const{
        for(unsigned long i=0;i<size;i++)
            tf(vec[i]->Element());
    }

    template <typename Data>
    void BinaryTreeVec<Data>::BreadthMap(const MapFun mp){
        for(unsigned long i=0;i<size;i++)
            mp(vec[i]->Element());
    }

/* ************************************************************************** */

/* ************************************************************************** */

}
