
namespace lasd {

/* ************************************************************************** */

    template<typename Data>
    BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const NodeLnk& nodelnk){
        this->item=nodelnk.item;

        if(nodelnk.lchild!=nullptr)
            this->lchild=new NodeLnk(*(nodelnk.lchild));
        else this->lchild=nullptr;

        if(nodelnk.rchild!=nullptr)
            this->rchild=new NodeLnk(*(nodelnk.rchild));
        else this->rchild=nullptr;
    }

    template<typename Data>
    BinaryTreeLnk<Data>::NodeLnk::NodeLnk(NodeLnk&& nodelnk)noexcept{
        std::swap(this->item,nodelnk.item);
        std::swap(this->lchild,nodelnk.lchild);
        std::swap(this->rchild,nodelnk.rchild);
    }

    template <typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk &BinaryTreeLnk<Data>::NodeLnk::operator=(const NodeLnk& nodelnk)
    {
        this->item=nodelnk->item;
        return *this;
    }

    template <typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk &BinaryTreeLnk<Data>::NodeLnk::operator=(NodeLnk&& nodelnk) noexcept
    {
        std::swap(this->item,nodelnk->element);
        return *this;
    }

/* ************************************************************************** */

    template <typename Data>
    BinaryTreeLnk<Data>::BinaryTreeLnk(const TraversableContainer<Data> &tc){
        size=tc.Size();
        QueueVec<NodeLnk **> que;
        que.Enqueue(&root);
        tc.Traverse(
            [&que](const Data& target)
            {
                NodeLnk *&cursor = *que.HeadNDequeue();
                cursor = new NodeLnk(target);
                que.Enqueue(&cursor->lchild);
                que.Enqueue(&cursor->rchild);
            }
        );
    }

    template <typename Data>
    BinaryTreeLnk<Data>::BinaryTreeLnk(MappableContainer<Data>&& mc)noexcept{
        size=mc.Size();
        QueueVec<NodeLnk **> que;
        que.Enqueue(&root);
        mc.Map(
            [&que](Data& target)
            {
                NodeLnk *&cursor = *que.HeadNDequeue();
                cursor = new NodeLnk(std::move(target));
                que.Enqueue(&cursor->lchild);
                que.Enqueue(&cursor->rchild);
            }
        );
    }

    template<typename Data>
    BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk<Data>& btl){
        if(btl.root!=nullptr){
            root=new NodeLnk(*btl.root);
            size=btl.size;
        }
    }

    template<typename Data>
    BinaryTreeLnk<Data>::BinaryTreeLnk(BinaryTreeLnk<Data>&& btl)noexcept{
        std::swap(root,btl.root);
        std::swap(size,btl.size);
    }

    template<typename Data>
    bool BinaryTreeLnk<Data>::operator==(const BinaryTreeLnk<Data>& btl)const noexcept{
        return BinaryTree<Data>::operator==(btl);
    }

    template<typename Data>
    bool BinaryTreeLnk<Data>::operator!=(const BinaryTreeLnk<Data>& btl)const noexcept{
        return BinaryTree<Data>::operator!=(btl);
    }

    template<typename Data>
    BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(const BinaryTreeLnk<Data>& btl){
        Clear();
        if(btl.root!=nullptr)
        {
            root=new NodeLnk(*(btl.root));
            size=btl.size;
        }
        return *this;
    }

    template<typename Data>
    BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(BinaryTreeLnk<Data>&& btl)noexcept{
        std::swap(root,btl.root);
        std::swap(size,btl.size);
        return *this;
    }

    template<typename Data>
    void BinaryTreeLnk<Data>::Clear(){
        if(root!=nullptr){
            Clear(root);
            size=0;
            root=nullptr;
        }
    }

    template<typename Data>
    void BinaryTreeLnk<Data>::Clear(NodeLnk* del)noexcept{
        if(del!=nullptr){
            Clear(del->lchild);
            Clear(del->rchild);
            delete del;
            del=nullptr;
        }
    }
/* ************************************************************************** */

}
