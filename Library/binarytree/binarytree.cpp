
namespace lasd {

/* ************************************************************************** */

    //Comparion operators Nodes
    template<typename Data>
    bool BinaryTree<Data>::Node::operator==(const Node& cmp)const noexcept{
        return (Element()==cmp.Element());
    }

    template<typename Data>
    bool BinaryTree<Data>::Node::operator!=(const Node& cmp)const noexcept{
        return (Element()!=cmp.Element());
    }


    //IsLeaf = Haven't left child and haven't right child
    template<typename Data>
    bool BinaryTree<Data>::Node::IsLeaf()const noexcept{
        return (HasLeftChild() || HasRightChild());
    }


    template<typename Data>
    bool BinaryTree<Data>::operator==(const BinaryTree<Data>& cmpbt)const noexcept{
        if(size!=cmpbt.size) {
        return false;
        }
        BTPreOrderIterator it(*this);
        BTPreOrderIterator itcmp(cmpbt);
        while(!(it.Terminated()) && !(itcmp.Terminated())){
            if((*it)!=(*itcmp)) {
                return false;
            }
            ++it; ++itcmp;
        }
        return true;
    }

    template<typename Data>
    bool BinaryTree<Data>::operator!=(const BinaryTree<Data>& cmpbt)const noexcept{
        return !(*this==cmpbt);
    }

    template<typename Data>
    void BinaryTree<Data>::Traverse(const TraverseFun tf)const{
        if(this->Size()!=0)
            PreOrderTraverse(tf,&Root());
    }

    template<typename Data>
    void BinaryTree<Data>::PreOrderTraverse(const TraverseFun tf)const{
        if(this->Size()!=0)
            PreOrderTraverse(tf,&Root());
    }

    template<typename Data>
    void BinaryTree<Data>::PostOrderTraverse(const TraverseFun tf)const{
        if(this->Size()!=0)
            PostOrderTraverse(tf,&Root());
    }

    template<typename Data>
    void BinaryTree<Data>::InOrderTraverse(const TraverseFun tf)const{
        if(this->Size()!=0)
            InOrderTraverse(tf,&Root());
    }

    template<typename Data>
    void BinaryTree<Data>::BreadthTraverse(const TraverseFun tf)const{
        if(this->Size()!=0)
            BreadthTraverse(tf,&Root());
    }

    template<typename Data>
    void BinaryTree<Data>::PreOrderTraverse(const TraverseFun tf,const Node* node)const{
        //Caso base: node!=nullptr
        if(node!=nullptr)
        {
            tf(node->Element());

            if(node->HasLeftChild())
                PreOrderTraverse(tf,&node->LeftChild());
            if(node->HasRightChild())
                PreOrderTraverse(tf,&node->RightChild());
        }
    }

    template<typename Data>
    void BinaryTree<Data>::PostOrderTraverse(const TraverseFun tf,const Node* node)const{
        if(node!=nullptr)
        {
            if(node->HasLeftChild())
                PostOrderTraverse(tf,&node->LeftChild());
            if(node->HasRightChild())
                PostOrderTraverse(tf,&node->RightChild());

            tf(node->Element());
        }
    }

    template<typename Data>
    void BinaryTree<Data>::InOrderTraverse(const TraverseFun tf,const Node* node)const{
        if(node!=nullptr)
        {
            if(node->HasLeftChild())
                InOrderTraverse(tf,&node->LeftChild());

            tf(node->Element());

            if(node->HasRightChild())
                InOrderTraverse(tf,&node->RightChild());
        }
    }

    template<typename Data>
    void BinaryTree<Data>::BreadthTraverse(const TraverseFun tf,const Node* node)const{
        if(node!=nullptr)
        {
            lasd::QueueVec<const Node*> queue;
            queue.Enqueue(node);

            while(!queue.Empty()){

                const BinaryTree<Data>::Node* cursor= queue.Head();
                tf(cursor->Element());

                if(cursor->HasLeftChild())
                    queue.Enqueue(&cursor->LeftChild());

                if(cursor->HasRightChild())
                    queue.Enqueue(&cursor->RightChild());

                queue.Dequeue();

            }
        }
    }

/* ************************************************************************** */


    template<typename Data>
    void MutableBinaryTree<Data>::Map(const MapFun mf){
        if(this->Size()!=0)
            PreOrderMap(mf,&Root());
    }

    template<typename Data>
    void MutableBinaryTree<Data>::PreOrderMap(const MapFun mf){
        if(this->Size()!=0)
            PreOrderMap(mf,&Root());
    }

    template<typename Data>
    void MutableBinaryTree<Data>::PostOrderMap(const MapFun mf){
        if(this->Size()!=0)
            PostOrderMap(mf,&Root());
    }

    template<typename Data>
    void MutableBinaryTree<Data>::InOrderMap(const MapFun mf){
        if(this->Size()!=0)
            InOrderMap(mf,&Root());
    }

    template<typename Data>
    void MutableBinaryTree<Data>::BreadthMap(const MapFun mf){
        if(this->Size()!=0)
            BreadthMap(mf,&Root());
    }

    template<typename Data>
    void MutableBinaryTree<Data>::PreOrderMap(const MapFun mf,MutableNode* node){
        if(node!=nullptr)
        {
            mf(node->Element());

            if(node->HasLeftChild())
                PreOrderMap(mf,&node->LeftChild());
            if(node->HasRightChild())
                PreOrderMap(mf,&node->RightChild());
        }
    }

    template<typename Data>
    void MutableBinaryTree<Data>::PostOrderMap(const MapFun mf,MutableNode* node){
        if(node!=nullptr)
        {
            if(node->HasLeftChild())
                PostOrderMap(mf,&node->LeftChild());
            if(node->HasRightChild())
                PostOrderMap(mf,&node->RightChild());

            mf(node->Element());
        }
    }

    template<typename Data>
    void MutableBinaryTree<Data>::InOrderMap(const MapFun mf,MutableNode* node){
        if(node!=nullptr)
        {
            if(node->HasLeftChild())
                InOrderMap(mf,&node->LeftChild());

            mf(node->Element());

            if(node->HasRightChild())
                InOrderMap(mf,&node->RightChild());

        }
    }

    template<typename Data>
    void MutableBinaryTree<Data>::BreadthMap(const MapFun mf,MutableNode* node){
        if(node!=nullptr)
        {
            lasd::QueueVec<MutableNode*> queue;
            queue.Enqueue(node);

            while(!queue.Empty()){

                MutableBinaryTree<Data>::MutableNode* cursor= queue.Head();
                mf(cursor->Element());

                if(cursor->HasLeftChild())
                    queue.Enqueue(&cursor->LeftChild());

                if(cursor->HasRightChild())
                    queue.Enqueue(&cursor->RightChild());

                queue.Dequeue();

            }
        }
    }

/* ************************************************************************** */
    template<typename Data>
    BTPreOrderIterator<Data>::BTPreOrderIterator(const BinaryTree<Data>& bt){
        if(!bt.Empty()){
            root=&bt.Root();
            cursor=root;
        }
    }

    template<typename Data>
    BTPreOrderIterator<Data>::BTPreOrderIterator(const BTPreOrderIterator<Data>& bt){
        root=bt.root;
        cursor=bt.cursor;
        stk=bt.stk;
    }

    template<typename Data>
    BTPreOrderIterator<Data>::BTPreOrderIterator(BTPreOrderIterator<Data>&& bt)noexcept {
        std::swap(root,bt.root);
        std::swap(cursor,bt.cursor);
        std::swap(stk,bt.stk);
    }

    template<typename Data>
    BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(const BTPreOrderIterator<Data>& bt){
        root=bt.root;
        cursor=bt.cursor;
        stk=bt.stk;
        return *this;
    }

    template<typename Data>
    BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(BTPreOrderIterator<Data>&& bt)noexcept{
        std::swap(root,bt.root);
        std::swap(stk,bt.stk);
        std::swap(cursor,bt.cursor);
        return *this;
    }

    template<typename Data>
    bool BTPreOrderIterator<Data>::operator==(const BTPreOrderIterator<Data>& bt)const noexcept{
        return (stk==bt.stk && cursor!=bt.cursor);
    }

    template<typename Data>
    bool BTPreOrderIterator<Data>::operator!=(const BTPreOrderIterator<Data>& bt)const noexcept{
        return (!(operator==(bt)));
    }

    template<typename Data>
    const Data& BTPreOrderIterator<Data>::operator*()const{
        if(Terminated())
            throw std::out_of_range("Error: Iterator terminated!");
        else return cursor->Element();
    }

    template<typename Data>
    bool BTPreOrderIterator<Data>::Terminated() const noexcept{
        if(cursor==nullptr)
            return true;
        else return false;
    }

    template<typename Data>
    BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator++(){

        // Mentre visita l'albero a sx o dx, memorizza il nodo rispettivamente
        // a dx o sx ("fratello" del nodo visitato), se presente.

        // Arrivati al nodo foglia, si interrogano i nodi memorizzati
        if(!Terminated()){
            if(cursor->HasLeftChild()){
                if(cursor->HasRightChild())
                {
                    stk.Push(&cursor->RightChild());
                }
                cursor=&cursor->LeftChild();
            }
            else if (cursor->HasRightChild()){
                if(cursor->HasLeftChild())
                {
                    stk.Push(&cursor->LeftChild());
                }
                cursor=&cursor->RightChild();
            }
            else {
                if(!stk.Empty())
                    cursor=(stk.TopNPop());
                else{
                    cursor=nullptr;
                }
            }
            return *this;
            }
        else throw std::out_of_range("The binary tree is terminated!");
    }

    template<typename Data>
    void BTPreOrderIterator<Data>::Reset() noexcept{
        cursor=root;
        stk.Clear();
    }
/* ************************************************************************** */

    template<typename Data>
    BTPreOrderMutableIterator<Data>::BTPreOrderMutableIterator(MutableBinaryTree<Data>& bt) : BTPreOrderIterator<Data>(bt)  
    {
    }

    template<typename Data>
    BTPreOrderMutableIterator<Data>::BTPreOrderMutableIterator(const BTPreOrderMutableIterator<Data>& bt) : BTPreOrderIterator<Data>(bt)
    {
    }

    template<typename Data>
    BTPreOrderMutableIterator<Data>::BTPreOrderMutableIterator(BTPreOrderMutableIterator<Data>&& bt)noexcept : BTPreOrderIterator<Data>(std::move(bt))
    {
    }

    template<typename Data>
    BTPreOrderMutableIterator<Data>& BTPreOrderMutableIterator<Data>::operator=(const BTPreOrderMutableIterator<Data>& bt)
    {
        this->root=bt.root;
        this->cursor=bt.cursor;
        this->stk=bt.stk;
        return *this;
    }

    template<typename Data>
    BTPreOrderMutableIterator<Data>& BTPreOrderMutableIterator<Data>::operator=(BTPreOrderMutableIterator<Data>&& bt)noexcept
    {
        std::swap(this->root,bt.root);
        std::swap(this->stk,bt.stk);
        std::swap(this->cursor,bt.cursor);
        return *this;
    }

    template<typename Data>
    bool BTPreOrderMutableIterator<Data>::operator==(const BTPreOrderMutableIterator<Data>& bt)const noexcept{
        return (BTPreOrderIterator<Data>::operator==(bt));
    }

    template<typename Data>
    bool BTPreOrderMutableIterator<Data>::operator!=(const BTPreOrderMutableIterator<Data>& bt)const noexcept{
        return (BTPreOrderIterator<Data>::operator!=(bt));
    }

    template<typename Data>
    Data& BTPreOrderMutableIterator<Data>::operator*(){
        if(BTPreOrderIterator<Data>::Terminated())
            throw std::out_of_range("Error: Iterator terminated!");
        else
            return const_cast<Data&>(this->cursor->Element());
    }

/* ************************************************************************** */

    template<typename Data>
    BTPostOrderIterator<Data>::BTPostOrderIterator(const BinaryTree<Data>& bt){
        if(!bt.Empty()){
            root=&bt.Root();
            cursor=DeepNode(root);
        }
    }

    template<typename Data>
    BTPostOrderIterator<Data>::BTPostOrderIterator(const BTPostOrderIterator<Data>& bt){
        root=bt.root;
        cursor=bt.cursor;
        stk=bt.stk;
    }

    template<typename Data>
    BTPostOrderIterator<Data>::BTPostOrderIterator(BTPostOrderIterator<Data>&& bt)noexcept{
        std::swap(root,bt.root);
        std::swap(cursor,bt.cursor);
        std::swap(stk,bt.stk);
    }

    template<typename Data>
    BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(const BTPostOrderIterator<Data>& bt){
        BTPostOrderIterator<Data>::BTPostOrderIterator(bt);
        return *this;
    }

    template<typename Data>
    BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(BTPostOrderIterator<Data>&& bt)noexcept{
        BTPostOrderIterator<Data>::BTPostOrderIterator(std::move(bt));
        return *this;
    }

    template<typename Data>
    bool BTPostOrderIterator<Data>::operator==(const BTPostOrderIterator<Data>& bt)const noexcept{
        return (cursor==bt.cursor && stk==bt.stk);
    }

    template<typename Data>
    bool BTPostOrderIterator<Data>::operator!=(const BTPostOrderIterator<Data>& bt)const noexcept{
        return (!(*this==bt));
    }

    template<typename Data>
    const Data& BTPostOrderIterator<Data>::operator*()const{
        if(Terminated())
            throw std::out_of_range("Error: Iterator terminated!");
        else return cursor->Element();
    }
    
    template<typename Data>
    bool BTPostOrderIterator<Data>::Terminated()const noexcept{
        if(cursor==nullptr)
            return true;
        else return false;
    }

    template<typename Data>
    BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator++(){

        // Visitati i nodi sinistri, prima di visitare il nodo radice del
        // sottoalbero, interrogo la visita sui figli destri, e se presenti,
        // sui loro figli sinistri. Per evitare visite aggiuntive sul figlio
        // destro, controllo che il figlio destro non sia proprio il nodo da
        // cui risalgo. Se ciò non accade, prelevo dallo stack esattamente il
        // nodo radice del sottoalbero.
        if(!Terminated()){
            if(!(stk.Empty())){
                if (stk.Top()->HasRightChild() && !(&(stk.Top()->RightChild()) == cursor))
                    cursor = DeepNode(&(stk.Top()->RightChild()));
                else
                    cursor = stk.TopNPop();
            }
            else cursor = nullptr;
        }
        else throw std::out_of_range("Error: iterator terminated!");

    return *this;
    }

    template<typename Data>
    void BTPostOrderIterator<Data>::Reset() noexcept{
        stk.Clear();
        cursor=DeepNode(root);
    }
    
/* ************************************************************************** */

    template<typename Data>
    BTPostOrderMutableIterator<Data>::BTPostOrderMutableIterator(MutableBinaryTree<Data>& bt) : BTPostOrderIterator<Data>(bt){
    }
    
    template<typename Data>
    BTPostOrderMutableIterator<Data>::BTPostOrderMutableIterator(const BTPostOrderMutableIterator<Data>& bt) : BTPostOrderIterator<Data>(bt){
        
    }

    template<typename Data>
    BTPostOrderMutableIterator<Data>::BTPostOrderMutableIterator(BTPostOrderMutableIterator<Data>&& bt)noexcept : BTPostOrderIterator<Data>(std::move(bt)){
        
    }

    template<typename Data>
    BTPostOrderMutableIterator<Data>& BTPostOrderMutableIterator<Data>::operator=(const BTPostOrderMutableIterator<Data>& bt){
        this->root=bt.root;
        this->cursor=bt.cursor;
        this->stk=bt.stk;
        return *this;
    }

    template<typename Data>
    BTPostOrderMutableIterator<Data>& BTPostOrderMutableIterator<Data>::operator=(BTPostOrderMutableIterator<Data>&& bt) noexcept{
        std::swap(this->root,bt.root);
        std::swap(this->cursor,bt.cursor);
        std::swap(this->stk,bt.stk);
        return *this;
    }

    template<typename Data>
    bool BTPostOrderMutableIterator<Data>::operator==(const BTPostOrderMutableIterator<Data>& bt)const noexcept{
        return (BTPostOrderIterator<Data>::operator==(bt));
    }

    template<typename Data>
    bool BTPostOrderMutableIterator<Data>::operator!=(const BTPostOrderMutableIterator<Data>& bt)const noexcept{
        return (BTPostOrderIterator<Data>::operator!=(bt));
    }

    template<typename Data>
    Data& BTPostOrderMutableIterator<Data>::operator*(){
        if(BTPostOrderIterator<Data>::Terminated())
            throw std::out_of_range("Error: Iterator terminated!");
        else
            return const_cast<Data&>(this->cursor->Element());
    }



/* ************************************************************************** */

    template<typename Data>
    BTInOrderIterator<Data>::BTInOrderIterator(const BinaryTree<Data>& bt){
        if(!bt.Empty()){
            root=&bt.Root();
            cursor=DeepNode(root);
        }
    }

    template<typename Data>
    BTInOrderIterator<Data>::BTInOrderIterator(const BTInOrderIterator<Data>& bt){
        root=bt.root;
        cursor=bt.cursor;
        stk=bt.stk;
    }

    template<typename Data>
    BTInOrderIterator<Data>::BTInOrderIterator(BTInOrderIterator<Data>&& bt)noexcept{
        std::swap(root,bt.root);
        std::swap(cursor,bt.cursor);
        std::swap(stk,bt.stk);
    }

    template<typename Data>
    BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(const BTInOrderIterator<Data>& bt){
        BTInOrderIterator<Data>::BTInOrderIterator(bt);
        
        return *this;
    }

    template<typename Data>
    BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(BTInOrderIterator<Data>&& bt)noexcept{
        BTInOrderIterator<Data>::BTInOrderIterator(std::move(bt));
        
        return *this;
    }

    template<typename Data>
    bool BTInOrderIterator<Data>::operator==(const BTInOrderIterator<Data>& bt)const noexcept{
        return (stk==bt.stk && cursor==bt.cursor);
    }

   template<typename Data>
    bool BTInOrderIterator<Data>::operator!=(const BTInOrderIterator<Data>& bt)const noexcept{
        return (!(*this==bt));
    }


    template<typename Data>
    const Data& BTInOrderIterator<Data>::operator*()const{
        if(Terminated())
            throw std::out_of_range("Error: Iterator terminated!");
        else return cursor->Element();
    }

    template<typename Data>
    bool BTInOrderIterator<Data>::Terminated() const noexcept{
        if(cursor==nullptr)
            return true;
        else return false;
    }

    template<typename Data>
    BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator++(){
        if(!Terminated()){
            if(cursor->HasRightChild())
                cursor=DeepNode(&cursor->RightChild());
            else if(!stk.Empty())
                cursor=stk.TopNPop();
            else
                cursor=nullptr;
        }
        return *this;
    }

    template<typename Data>
    void BTInOrderIterator<Data>::Reset() noexcept{
        stk.Clear();
        cursor=DeepNode(root);
    }

/* ************************************************************************** */

    template<typename Data>
    BTInOrderMutableIterator<Data>::BTInOrderMutableIterator(MutableBinaryTree<Data>& bt) : BTInOrderIterator<Data>(bt){
    }

    template<typename Data>
    BTInOrderMutableIterator<Data>::BTInOrderMutableIterator(const BTInOrderMutableIterator<Data>& bt) : BTInOrderIterator<Data>(bt){
    }

    template<typename Data>
    BTInOrderMutableIterator<Data>::BTInOrderMutableIterator(BTInOrderMutableIterator<Data>&& bt)noexcept : BTInOrderIterator<Data>(std::move(bt)){
    }

    template<typename Data>
    BTInOrderMutableIterator<Data>& BTInOrderMutableIterator<Data>::operator=(const BTInOrderMutableIterator<Data>& bt){
        this->root=bt.root;
        this->cursor=bt.cursor;
        this->stk=bt.stk;
        return *this;
    }

    template<typename Data>
    BTInOrderMutableIterator<Data>& BTInOrderMutableIterator<Data>::operator=(BTInOrderMutableIterator<Data>&& bt)noexcept{
        std::swap(this->root,bt.root);
        std::swap(this->cursor,bt.cursor);
        std::swap(this->stk,bt.stk);
        return *this;
    }

    template<typename Data>
    bool BTInOrderMutableIterator<Data>::operator==(const BTInOrderMutableIterator<Data>& bt)const noexcept {
        return (BTInOrderIterator<Data>::operator==(bt));
    }

    template<typename Data>
    bool BTInOrderMutableIterator<Data>::operator!=(const BTInOrderMutableIterator<Data>& bt)const noexcept {
        return (BTInOrderIterator<Data>::operator!=(bt));
    }

    template<typename Data>
    Data& BTInOrderMutableIterator<Data>::operator*(){
        if(BTInOrderIterator<Data>::Terminated())
            throw std::out_of_range("Error: Iterator terminated!");
        else return const_cast<Data&>(this->cursor->Element());
    }

/* ************************************************************************** */

    template<typename Data>
    BTBreadthIterator<Data>::BTBreadthIterator(const BinaryTree<Data>& bt){
        if(!bt.Empty()){
            root=&bt.Root();
            cursor=root;
        }
    }

    template<typename Data>
    BTBreadthIterator<Data>::BTBreadthIterator(const BTBreadthIterator<Data>& bt){
        root=bt.root;
        cursor=bt.cursor;
        que=bt.que;
    }

    template<typename Data>
    BTBreadthIterator<Data>::BTBreadthIterator(BTBreadthIterator<Data>&& bt)noexcept : que(std::move(bt.que)){
        std::swap(root,bt.root);
        std::swap(cursor,bt.cursor);
    }

    template<typename Data>
    BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(const BTBreadthIterator<Data>& bt){
        BTBreadthIterator<Data>::BTBreadthIterator(bt);
        return *this;
    }

    template<typename Data>
    BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(BTBreadthIterator<Data>&& bt) noexcept{
        BTBreadthIterator<Data>::BTBreadthIterator(std::move(bt));
        return *this;
    }

    template<typename Data>
    bool BTBreadthIterator<Data>::operator==(const BTBreadthIterator<Data>& bt) const noexcept{
        return (cursor==bt.cursor && que==bt.que);
    }

    template<typename Data>
    bool BTBreadthIterator<Data>::operator!=(const BTBreadthIterator<Data>& bt) const noexcept{
        return (!(*this==bt));
    }

    template<typename Data>
    const Data& BTBreadthIterator<Data>::operator*() const{
        if(Terminated())
            throw std::out_of_range("Error: Iterator terminated!");
        else return cursor->Element();
    }

    template<typename Data>
    bool BTBreadthIterator<Data>::Terminated()const noexcept{
        if(cursor==nullptr)
            return true;
        else return false;
    }

    template<typename Data>
    BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator++(){
        if(!Terminated()){
            if(cursor->HasLeftChild())
                que.Enqueue(&cursor->LeftChild());
            if(cursor->HasRightChild())
                que.Enqueue(&cursor->RightChild());
            if(!que.Empty())
                cursor=que.HeadNDequeue();
            else
                cursor=nullptr;

            return *this;
        }
        else throw std::out_of_range("Error: iterator terminated");
    }

    template<typename Data>
    void BTBreadthIterator<Data>::Reset() noexcept{
        que.Clear();
        cursor=root;
    }


/* ************************************************************************** */

    template<typename Data>
    BTBreadthMutableIterator<Data>::BTBreadthMutableIterator(MutableBinaryTree<Data>& bt) : BTBreadthIterator<Data>(bt){
    }

    template<typename Data>
    BTBreadthMutableIterator<Data>::BTBreadthMutableIterator(const BTBreadthMutableIterator<Data>& bt) : BTBreadthIterator<Data>(bt){
    }

    template<typename Data>
    BTBreadthMutableIterator<Data>::BTBreadthMutableIterator(BTBreadthMutableIterator<Data>&& bt)noexcept : BTBreadthIterator<Data>(std::move(bt)){
        
    }

    template<typename Data>
    BTBreadthMutableIterator<Data>& BTBreadthMutableIterator<Data>::operator=(const BTBreadthMutableIterator<Data>& bt){
        this->root=bt.root;
        this->cursor=bt.cursor;
        this->stk=bt.stk;
        return *this;
    }

    template<typename Data>
    BTBreadthMutableIterator<Data>& BTBreadthMutableIterator<Data>::operator=(BTBreadthMutableIterator<Data>&& bt)noexcept{
        std::swap(this->root,bt.root);
        std::swap(this->cursor,bt.cursor);
        std::swap(this->stk,bt.stk);
        return *this;
    }

    template<typename Data>
    bool BTBreadthMutableIterator<Data>::operator==(const BTBreadthMutableIterator<Data>& bt)const noexcept{
        return (BTBreadthIterator<Data>::operator==(bt));
    }

    template<typename Data>
    bool BTBreadthMutableIterator<Data>::operator!=(const BTBreadthMutableIterator<Data>& bt)const noexcept{
        return (BTBreadthIterator<Data>::operator!=(bt));
    }

    template<typename Data>
    Data& BTBreadthMutableIterator<Data>::operator*(){
        if (BTBreadthIterator<Data>::Terminated())
            throw std::out_of_range("Error: Iterator terminated");
        else return const_cast<Data&>(this->cursor->Element());
    }

/* ************************************************************************** */


}