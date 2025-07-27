
namespace lasd {

/* ************************************************************************** */

//Node functions' definition

    template <typename Data>
    List<Data>::Node::Node(const Data& item){
        element=item;
        next=nullptr;
    }

    template<typename Data>
    List<Data>::Node::Node(Data&& item)noexcept{
        std::swap(element,item);
        next=nullptr;
    }

    template<typename Data>
    List<Data>::Node::Node(const Node& node){
        element=node.element;
        next=node.next;
    }

    template<typename Data>
    List<Data>::Node::Node(Node&& node)noexcept{
        std::swap(element,node.element);
        std::swap(next,node.next);
    }


    //List functions' definition

    template<typename Data>
    List<Data>::List(const TraversableContainer<Data>& tc){
        tc.Traverse(
            [this](const Data& item){
                InsertAtBack(item);
            }
        );
    }

    template<typename Data>
    List<Data>::List(MappableContainer<Data>&& mc)noexcept{
        mc.Map(
            [this](Data& item){
                InsertAtBack(std::move(item));
            }
        );
    }

    template<typename Data>
    List<Data>::List(const List<Data>& cpy){
        if(cpy.head==nullptr){
            this->head=nullptr;
            size=0;
        }
        else{
            size=cpy.size;
            this->head=new Node(cpy.head->element);
            Node* cursor=cpy.head->next;
            Node* tmp= head;

            while(cursor!=nullptr)
            {
                Node* newnode = new Node(cursor->element);
                tmp->next=newnode;
                tmp=tmp->next;
                cursor=cursor->next;
            }
        }
    }

    template<typename Data>
    List<Data>::List(List<Data>&& mve)noexcept{
        std::swap(size,mve.size);
        std::swap(head,mve.head);
    }

    template<typename Data>
    List<Data>::~List(){
        Clear();
    }

    //...

    template<typename Data>
    List<Data>& List<Data>::operator=(const List<Data>& cpy){
        List<Data>* newlist = new List<Data>(cpy);
        std::swap(*this,*newlist);
        delete newlist;
        return *this;
    }

    template<typename Data>
    List<Data>& List<Data>::operator=(List<Data>&& mve)noexcept{
        std::swap(head,mve.head);
        std::swap(size,mve.size);
        return *this;
    }

    //...

    template<typename Data>
    bool List<Data>::operator==(const List<Data>& cmp)const noexcept{
        if(size!=cmp.size)  { return false; }

        Node* cursorMain=head;
        Node* cursorCmp=cmp.head;

        while(cursorMain!=nullptr)
        {
            if (cursorMain->element!=cursorCmp->element)
                return false;
            cursorMain=cursorMain->next;
            cursorCmp=cursorCmp->next;
        }
        return true;
    }

    template<typename Data>
    bool List<Data>::operator!=(const List<Data>& cmp)const noexcept{
        return (!(*this==cmp));
    }

    //...

    template<typename Data>
    void List<Data>::InsertAtFront(const Data& item){
        Node* newnode= new Node(item);
        newnode->next=head;
        head=newnode;
        size++;
    }    

    template<typename Data>
    void List<Data>::InsertAtFront(Data&& item)noexcept{
        Node* newnode= new Node(std::move(item));
        newnode->next=head;
        head=newnode;
        size++;
    }

    template<typename Data>
    void List<Data>::RemoveFromFront(){
        if(size==0) //head==nullptr
            throw std::length_error("Lenght error: Unable to remove a node from an empty list");
        else{
            Node *deletenode= head;
            head=head->next;
            delete deletenode;
            size--;
        }
    }

    template<typename Data>
    Data List<Data>::FrontNRemove(){
        if(size==0)
            throw std::length_error("Lenght error: Unable to remove a node from an empty list");
        else{
            Data datadeleted= Front();
            RemoveFromFront();
            return datadeleted;
        }
    }

    template<typename Data>
    void List<Data>::InsertAtBack(const Data& item){
        if(head==nullptr)
            head=new Node(item);
        else{
            Node* cursor=head;
            while(cursor->next!=nullptr)
                cursor=cursor->next;
            
            cursor->next=new Node(item);
        }
        size++;
    }

    template<typename Data>
    void List<Data>::InsertAtBack(Data&& item)noexcept{
        if(head==nullptr)
            head=new Node(std::move(item));
        else{
            Node* cursor=head;
            while(cursor->next!=nullptr)
                cursor=cursor->next;
            
            cursor->next=new Node(std::move(item));
        }
        size++;
    }

    //...

    template<typename Data>
    void List<Data>::Clear(){
        if(!(Empty())){
            Node* deletenode;
            Node* cursor=head;
            
            while(cursor!=nullptr){
                deletenode=cursor;
                cursor=cursor->next;
                delete deletenode;
            }
            head=nullptr;
            size=0;
        }
    }

    //...

    template<typename Data>
    bool List<Data>::Insert(const Data& item){
        if(TraversableContainer<Data>::Exists(item))
            return false;
        
        InsertAtBack(item);
        return true;
    }

    template<typename Data>
    bool List<Data>::Insert(Data&& item)noexcept{
        if(TraversableContainer<Data>::Exists(std::move(item)))
            return false;
        
        InsertAtBack(std::move(item));
        return true;
    }

    template<typename Data>
    bool List<Data>::Remove(const Data& item){
        if(!(TraversableContainer<Data>::Exists(item)))
            return false;
        if(head->element==item){
            RemoveFromFront();
            return true;
        }
        else{
        Node* cursor=head->next;
        Node* previouscursor=head;
        while(cursor!=nullptr){
            if(cursor->element==item){
                previouscursor->next=cursor->next;
                delete cursor;
                return true;
            }else{
                previouscursor=previouscursor->next;
                cursor=cursor->next;
                }
            }
            return false;   
        }
    }

    //...

    template<typename Data>
    const Data& List<Data>::operator[](const unsigned long index)const{
        if(index>=size)
            throw std::out_of_range("Out of range: Unable access to" + std::to_string(index));
        else{
            if(index==0)
                return head->element;
            Node* cursor=head;
            for(unsigned long i =0;i<index;i++)
                cursor=cursor->next;
            
            return cursor->element;
        }
    }

    template<typename Data>
    Data& List<Data>::operator[](const unsigned long index){
        if(index>=size)
            throw std::out_of_range("Out of range: Unable access to" + std::to_string(index));
        else{
            if(index==0)
                return head->element;
            Node* cursor=head;
            for(unsigned long i =0;i<index;i++)
                cursor=cursor->next;
            
            return cursor->element;
        }
    }

    template<typename Data>
    const Data& List<Data>::Front()const{
        if(Empty())
            throw std::length_error("Lenght error: Unable to access to an empty list!");
        else
            return head->element;
    }

    template<typename Data>
    Data& List<Data>::Front(){
        if(Empty())
            throw std::length_error("Lenght error: Unable to access to an empty list!");
        else
            return head->element;
    }

    template<typename Data>
    const Data& List<Data>::Back()const{
        if(Empty())
            throw std::length_error("Lenght error: Unable to access to an empty list!");
        else{
            Node* cursor=head;
            while(cursor->next!=nullptr)
                cursor=cursor->next;
            
            return cursor->element;
        }
    }

    template<typename Data>
    Data& List<Data>::Back(){
        if(Empty())
            throw std::length_error("Lenght error: Unable to access to an empty list!");
        else{
            Node* cursor=head;
            while(cursor->next!=nullptr)
                cursor=cursor->next;
            
            return cursor->element;
        }
    }

    //...

    template<typename Data>
    void List<Data>::Traverse(const TraverseFun tf)const{
        PreOrderTraverse(tf);
    }

    template<typename Data>
    void List<Data>::PreOrderTraverse(const TraverseFun tf)const{
        Node*cursor=head;
        while(cursor!=nullptr){
            tf(cursor->element);
            cursor=cursor->next;
        }
    }

    template<typename Data>
    void List<Data>::PostOrderTraverse(const TraverseFun tf)const{
        PostOrderTraverse(tf,head);
    }

    //...

    template<typename Data>
    void List<Data>::Map(const MapFun mf){
        PreOrderMap(mf);
    }

    template<typename Data>
    void List<Data>::PreOrderMap(const MapFun mf){
        Node* cursor=head;
        while(cursor!=nullptr){
            mf(cursor->element);
            cursor=cursor->next;
        }
    }

    template<typename Data>
    void List<Data>::PostOrderMap(const MapFun mf){
        PostOrderMap(mf,head);
    }

    //...

    template<typename Data>
    void List<Data>::PostOrderTraverse(const TraverseFun tf, Node* cursor)const{
        if(cursor==nullptr)
            return;
        else{
            PostOrderTraverse(tf,cursor->next);
            tf(cursor->element);
        }
    }

    template<typename Data>
    void List<Data>::PostOrderMap(const MapFun mf, Node* cursor){
        if(cursor==nullptr)
            return;
        else{
            PostOrderMap(mf,cursor->next);
            mf(cursor->element);
        }
    }
/* ************************************************************************** */

}
