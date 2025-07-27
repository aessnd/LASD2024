
namespace lasd {

/* ************************************************************************** */
    // Specific constructors : A bst obtained from a TraversableContainer
    template <typename Data>
    BST<Data>::BST(const TraversableContainer<Data>& tc) {
        tc.Traverse(
            [this](const Data& value){
                Insert(value);
            }
        );
    }

    // Specific constructors: A bst obtained from a MappableContainer
    template <typename Data>
    BST<Data>::BST(MappableContainer<Data>&& mc) noexcept {
        mc.Map(
            [this](Data& value){
                Insert(std::move(value));
            }
        );
    }

    // Copy constructor
    template<typename Data>
    BST<Data>::BST(const BST<Data>& bst) : BinaryTreeLnk<Data>::BinaryTreeLnk(bst)
    {
    }

    // Move constructor
    template<typename Data>
    BST<Data>::BST(BST<Data>&& bst) noexcept : BinaryTreeLnk<Data>::BinaryTreeLnk(std::move(bst))
    {
    }

    // Copy assignment
    template <typename Data>
    BST<Data>& BST<Data>::operator=(const BST<Data>& bst){
        BinaryTreeLnk<Data>::operator=(bst);
        return *this;
    }

    // Move assignment
    template <typename Data>
    BST<Data>& BST<Data>::operator=(BST<Data>&& bst)noexcept{
        BinaryTreeLnk<Data>::operator=(std::move(bst));
        return *this;
    }

    // Comparison operators
    template <typename Data>
    bool BST<Data>::operator==(const BST& bst) const noexcept {
        if (size == bst.size) {
            BTInOrderIterator<Data> it(*this);
            BTInOrderIterator<Data> itcmp(bst);
            for (; !it.Terminated(); ++it, ++itcmp) {
                if((*it) != (*itcmp))
                    return false;
            }
            
            return true;
        }
        return false;
    }
    
    template <typename Data>
    bool BST<Data>::operator!=(const BST& bst) const noexcept {
        return !(*this==bst);
    }

    // Specific member functions: Minimo in un bst = nodo più a sinistra
    template <typename Data>
    const Data& BST<Data>::Min() const {
        if (root != nullptr) 
            return FindPointerToMin(root)->item;
        else throw std::length_error("Error: BST is empty!");
    }

    // Specific member functions: Cancella minimo e mostra valore
    template <typename Data>
    Data BST<Data>::MinNRemove() {
        if (root != nullptr)
        /*@call functions:  FindPointerToMin(&root) -> r
                            Skip2Right(r) -> q
                            DataNDelete(q)               */
            return DataNDelete(DetachMin(root));
        else throw std::length_error("Error: BST is empty!");
    }

    // Specific member functions: Cancella minimo
    template <typename Data>
    void BST<Data>::RemoveMin() {
        if (root != nullptr)
        /*@call functions:  FindPointerToMin(&root) -> r
                            Skip2Right(r) -> q            */
            delete DetachMin(root);
        else throw std::length_error("Error: BST is empty!");
    }

    // Specific member functions: Massimo in un bst = nodo più a destra
    template <typename Data>
    const Data &BST<Data>::Max() const {
        if (root != nullptr)
            return FindPointerToMax(root)->item;
        else throw std::length_error("Error: BST is empty!");
    }
    
    // Specific member functions: Cancella minimo e mostra valore
    template <typename Data>
    Data BST<Data>::MaxNRemove() {
        if (root != nullptr)
        /*@call functions:  FindPointerToMax(&root) -> r
                            Skip2Left(r) -> q
                            DataNDelete(q)               */
            return DataNDelete(DetachMax(root));
        else throw std::length_error("Error: BST is empty!");
    }

    // Specific member functions: Cancella minimo
    template<typename Data>
    void BST<Data>::RemoveMax() {
        if (root != nullptr)
        /*@call functions:  FindPointerToMin(&root) -> r
                            Skip2Right(r) -> q            */
            delete DetachMax(root);
        else throw std::length_error("Error: BST is empty!");
    }

    // Specific member functions: Ricerca del nodo-predecessore di un dato
    template <typename Data>
    const Data &BST<Data>::Predecessor(const Data &target) const {
        NodeLnk* const* ptr = &FindPointerToPredecessor(root, target);
        if (ptr != nullptr)
            return (*ptr)->item;
        else throw std::length_error("Error: Predecessor not found");
    }

    // Specific member functions: Ricerca e cancellazione del nodo-predecessore di un dato
    template <typename Data>
    Data BST<Data>::PredecessorNRemove(const Data &target) {
        NodeLnk** ptr =&FindPointerToPredecessor(root, target);
        if (ptr != nullptr)
            return DataNDelete(Detach(*ptr));
        else throw std::length_error("Error: Predecessor not found");
    }

    // Specific member functions
    template <typename Data>
    void BST<Data>::RemovePredecessor(const Data &target) {
        NodeLnk** ptr=&FindPointerToPredecessor(root,target);
        if (ptr != nullptr)
            delete Detach(*ptr);
        else throw std::length_error("Error: Predecessor not found");
    }

    // Specific member functions: Ricerca del nodo-successore di un dato
    template <typename Data>
    const Data &BST<Data>::Successor(const Data &target) const {
        NodeLnk* const* ptr = &FindPointerToSuccessor(root, target);
        if(ptr !=nullptr)
            return (*ptr)->item;
        else throw std::length_error("Error: Successor not found");
    }

    // Specific member functions: Ricerca e cancellazione del nodo-successore di un dato
    template <typename Data>
    Data BST<Data>::SuccessorNRemove(const Data &target) {
        NodeLnk** ptr = &FindPointerToSuccessor(root, target);
        if (ptr != nullptr)
            return DataNDelete(Detach(*ptr));
        else throw std::length_error("Error: Successor not found");
    }

    // Specific member functions
    template <typename Data>
    void BST<Data>::RemoveSuccessor(const Data &target) {
    NodeLnk **ptr = &FindPointerToSuccessor(root, target);
    if (ptr != nullptr)
        delete Detach(*ptr);
    else throw std::length_error("Error: Successor not found");
    }


    // Specific member functions (inhereted from DictionaryContainer):
    // Inserimento di un dato all'interno del bst.
    // (FindPointerTo non altera le proprietà del bst)
    template <typename Data>
    bool BST<Data>::Insert(const Data &target) {
    NodeLnk * & ptr = FindPointerTo(root, target); 
    if(ptr == nullptr){
        ptr = new NodeLnk(target);
        size++;
        return true;
    }
    return false;
    }

    template <typename Data>
    bool BST<Data>::Insert(Data &&target){
        NodeLnk * & ptr = FindPointerTo(root, target); 
        if(ptr == nullptr){
            ptr = new NodeLnk(std::move(target));
            size++;
            return true;
        }
        return false;
    }

    template <typename Data>
    bool BST<Data>::Remove(const Data &target){
    NodeLnk * & ptr = FindPointerTo(root, target);
        if(ptr != nullptr){
            delete Detach(ptr);
            return true;
        }
        return false;
    }

    template <typename Data>
    bool BST<Data>::Exists(const Data &target) const noexcept {
        return (FindPointerTo(root,target) !=nullptr);
    }

    template <typename Data>
    void BST<Data>::Clear() noexcept {
        BinaryTreeLnk<Data>::Clear();
    }

    template <typename Data>
    inline Data BST<Data>::DataNDelete(NodeLnk *node) {
        Data target=node->item;
        delete node;
        return target;
    }

    // Auxiliary function: Staccare un nodo in una albero bst non alterando le sue propeità.
    // Gestione di 3 casi
    template <typename Data>
    typename lasd::BinaryTreeLnk<Data>::NodeLnk* BST<Data>::Detach(NodeLnk *&node) noexcept {
        if (node != nullptr) {
            if (node->lchild == nullptr)
                //Caso 1: Nodo senza figlio sinistro
                // Stacca node e collega il figlio destro di node(se esiste), al
                // genitore di node
                return Skip2Right(node);
            else if (node->rchild == nullptr)
                // Caso 2: Nodo senza figlio destro
                // Stacca node e collega il figlio sinistro di node (se esiste), al
                // genitore di node
                return Skip2Left(node);
            else {
                // Caso 3: Nodo con entrambi i figli (sx e dx)
                NodeLnk *max = DetachMax(node->lchild);
                std::swap(node->item, max->item);
                return max;
            }
        }
        return nullptr;
    }

    // Auxiliary functions: Trova puntatore al nodo massimo e collega i suoi
    //                      i suoi figli sinistri al nodo genitore di node max
    template<typename Data>
    typename BST<Data>::NodeLnk* BST<Data>::DetachMax(typename BST<Data>::NodeLnk*& node)noexcept{
        return Skip2Left(FindPointerToMax(node));
    }
    // Auxiliary functions
    template <typename Data>
    typename BST<Data>::NodeLnk* BST<Data>::Skip2Left(typename BST<Data>::NodeLnk*& node) noexcept{
        NodeLnk* newlchild = nullptr;
        if (node != nullptr) {
            std::swap(newlchild, node->lchild);
            std::swap(newlchild, node);
            size--;
        }
        return newlchild;
    }

    // Auxiliary functions
    template<typename Data>
    typename BST<Data>::NodeLnk* BST<Data>::DetachMin(typename BST<Data>::NodeLnk*& node)noexcept{
        return Skip2Right(FindPointerToMin(node));
        /* 1) Trovo puntatore j al nodo minimo (più a sinistra)
           2) Se ha figlio k destro (per cui j>k>min), fai puntatore a j -> k e ritorna min*/
    }

    // Auxiliary functions
    template <typename Data>
    typename BST<Data>::NodeLnk* BST<Data>::Skip2Right(typename BST<Data>::NodeLnk*& node) noexcept{
        NodeLnk *newrchild = nullptr;
        if (node != nullptr) {
            std::swap(newrchild, node->rchild);
            std::swap(newrchild, node);
            size--;
        }
        return newrchild;
    }

    // Auxiliary functions (mutable version)
    template<typename Data>
    typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToMin(typename BST<Data>::NodeLnk*& node) noexcept{
        return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToMin(node));
    }

    // Auxiliary functions (mutable version)
    template<typename Data>
    typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToMax(typename BST<Data>::NodeLnk*& node) noexcept{
        return const_cast<NodeLnk*&>(static_cast<const BST<Data> *>(this)->FindPointerToMax(node));
    }

    // Auxiliary functions: Ricerca puntatore al nodo minimo (nodo più a sinistra)
    template<typename Data>
    typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToMin(typename BST<Data>::NodeLnk* const& node)const noexcept{
        NodeLnk* const* ptr=&node;
        NodeLnk* currnode=node;
        if(currnode!=nullptr){
            while(currnode->lchild!=nullptr){
            ptr=&currnode->lchild;
            currnode=currnode->lchild;
            }
        }
        return *ptr;
    }

    // Auxiliary functions: Ricerca puntatore al nodo massimo (nodo più a destra)
    template<typename Data>
    typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToMax(typename BST<Data>::NodeLnk* const& node)const noexcept{
        NodeLnk* const* ptr=&node;
        NodeLnk* currnode=node;
        if(currnode!=nullptr){
            while(currnode->rchild!=nullptr){
                ptr=&currnode->rchild;
                currnode=currnode->rchild;
            }
        }
        return *ptr;
    }


    // Auxiliary functions: Ricerca puntatore ad un nodo specifico
    template<typename Data>
    typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerTo(NodeLnk* const& node, Data target) const noexcept{
    NodeLnk *const *ptr = &node;
    NodeLnk *currnode = node;

    while (currnode != nullptr) {
        if (target > currnode->item) {
            ptr = &currnode->rchild;
            currnode = currnode->rchild;
        } 
        else if (target < currnode->item) {
            ptr = &currnode->lchild;
            currnode = currnode->lchild;
        } // target == currnode->item
        else break;
    }
    return *ptr;
    }

    // Auxiliary functions (mutable version)
    template<typename Data>
    typename BST<Data>::NodeLnk*& BST<Data>::FindPointerTo(NodeLnk*& node, Data target) noexcept{
        return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerTo(node,target));
    }

    // Auxiliary functions: Ricerca del nodo-predecessore di un nodo con valore "target"
    // Condizione: pred<target
    template<typename Data>
    typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToPredecessor(NodeLnk* const& node, Data target) const noexcept{
        NodeLnk *const *pred = nullptr;
        NodeLnk *const *curr = &node;

        while ((*curr) != nullptr && (*curr)->item != target) {
            if ((*curr)->item > target)
                curr = &(*curr)->lchild;
            else if ((*curr)->item < target) {
                pred = curr;
                curr = &(*curr)->rchild;
            }
        }
        if ((*curr) != nullptr && (*curr)->lchild != nullptr)
            pred = &FindPointerToMax((*curr)->lchild);

        return *pred;
    }

    // Auxiliary functions: Ricerca del nodo-successore di un nodo con valore "target"
    // Condizione: successor>target
    template<typename Data>
    typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToSuccessor(NodeLnk* const& node, Data target) const noexcept{
        typename BST<Data>::NodeLnk *const *successor = nullptr;
        typename BST<Data>::NodeLnk *const *curr = &node;

        while ((*curr) != nullptr && (*curr)->item != target) {
            if ((*curr)->item < target) 
                curr = &(*curr)->rchild;
            else if ((*curr)->item > target) {
                successor = curr;
                curr = &(*curr)->lchild;
            }
        }
        if ((*curr) != nullptr && (*curr)->rchild != nullptr) 
            successor = &FindPointerToMin((*curr)->rchild);

        return *successor;
    }

    // Auxiliary functions (mutable version)
    template<typename Data>
    typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToPredecessor(NodeLnk*& node, Data target) noexcept{
        return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToPredecessor(node,target));
    }

    // Auxiliary functions (mutable version)
    template<typename Data>
    typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToSuccessor(NodeLnk*& node, Data target) noexcept{
        return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToSuccessor(node,target));
    }
/* ************************************************************************** */

}
