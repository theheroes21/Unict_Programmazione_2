#include <iostream>

using namespace std;

class List;
ostream& operator << (ostream& sstream, const List& list);


class Node{
public:
    Node(int d, Node* n = nullptr, Node* p= nullptr) : dato(d) , next(n), prev(p) {}
    friend class List;
    friend ostream& operator << (ostream& sstream, const List& list);


private:
    int dato;
    Node* next;
    Node* prev;
};


class List{
public:
    List() : head(nullptr), tail(nullptr) {}
    ~List();

    Node* InsertHead(int dato);
    Node* InsertAfter(int dato, Node* p);
    Node* Search(int dato);
    void Found(List& list, int dato);
    bool Remove(int dato);

    friend ostream& operator << (ostream& sstream, const List& list);


private:
    Node* head;
    Node* tail;
};


Node* List::InsertHead(int dato){
    Node* nuovo = new Node(dato);

    if(head == nullptr){
        nuovo->next = nuovo;
        nuovo->prev = nuovo;
        head = nuovo;
        tail = nuovo;
    }else{
        nuovo->next = head;
        nuovo->prev = tail;
        head->prev = nuovo;
        tail->next = nuovo;
        head = nuovo;
    }

    return nuovo;
}

Node* List::InsertAfter(int dato, Node* p){
    if(head == nullptr || p == nullptr){
        return InsertHead(dato);
    }

    Node* nuovo = new Node(dato);
    nuovo->next = p->next;
    nuovo->prev = p;
    p->next->prev = nuovo;
    p->next = nuovo;

    if(p==tail){
        tail = nuovo;
    }

    return nuovo;
}

Node* List::Search(int dato){
    if(head==nullptr) return nullptr;

    Node* cur = head;

    do{
        if(cur->dato == dato){
            return cur;
        }
        cur = cur->next;
    }while(cur != head);

    return nullptr;
}

void List::Found(List& list, int dato){
    Node *found = list.Search(dato);

    if(found){
        cout << "Nodo trovato: " << found->dato << endl;
    }else{
        cout <<"Nodo contenente " << dato << " non trovato." << endl;
    }
}

bool List::Remove(int dato){
    if (!head) return false;

    Node* p = head;

    do{
        if(p->dato == dato){
            if(p->next == p){
                delete p;
                head = nullptr;
                tail = nullptr;
            }else{
                p->prev->next = p->next;
                p->next->prev = p->prev;

                if (p == head) head = p->next;
                if (p == tail) tail = p->prev;

                delete p;
            }

            return true;

        }

        p = p->next;
    }while(p != head);

    return false;
}

List::~List(){
    if (!head) return;

    Node *p = head->next;
    while(p!=head){
        Node* temp = p;
        p = p->next;
        delete temp;
    }

    delete head;
    head = nullptr;
    tail = nullptr;
}

ostream& operator << (ostream& stream, const List& list){
    if(!list.head){
        stream << "Lista vuota\n";
        return stream;
    }

    stream << "Lista avanti: ";
    Node* p = list.head;

    do{
        stream << p->dato;
        if(p->next != list.head){
            stream << ", ";
        }
        p = p->next;
    }while(p != list.head);
    stream << endl;

    stream << "Lista indietro: ";
    p = list.tail;
    Node* stop = p;

    do{
        stream << p->dato;
        if(p->prev != stop){
            stream << ", ";
        }

        p = p->prev;
    }while(p != stop);
    stream << endl;

    return stream; 
}

int main(){

    List lista;
    Node *L = lista.InsertAfter(5,L);
    cout << lista;
    L = lista.InsertAfter(3,L);
    L = lista.InsertAfter(7,L);
    cout << lista;
    lista.Found(lista,3);
    lista.Found(lista,11);
    cout << "Elemento 3 rimosso: " << lista.Remove(3) << endl;
    cout << lista;
    cout << "Elemento 3 rimosso: " << lista.Remove(3) << endl;
    cout << lista;
    cout << "Elemento 5 rimosso: " << lista.Remove(5) << endl;
    cout << lista;
    cout << "Elemento 7 rimosso: " << lista.Remove(7) << endl;
    cout << lista;
    cout << "Elemento 11 rimosso: " << lista.Remove(11) << endl;
    cout << lista;

    return 0;
}