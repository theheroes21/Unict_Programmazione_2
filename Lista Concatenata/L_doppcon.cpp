#include <iostream>

using namespace std;

class List;
ostream& operator << (ostream& stream, const List& list);


class Node{
public:
    Node(int d, Node* n = nullptr, Node *p = nullptr) : dato(d) , next (n) , prev (p) {}
    friend class List;
    friend ostream& operator << (ostream& stream, const List& list);

private:
    int dato;
    Node *next;
    Node *prev;
};

class List{
public:
    List() : head(nullptr) , tail(nullptr) {}
    Node* InsertHead(int dato);
    Node* InsertAfert(int dato, Node* p);
    Node* Search(int dato);
    void  found(List& list, int d);
    bool Remove(int dato);
    ~List();

    friend ostream& operator << (ostream& stream, const List& list); 
    
private:
    Node* head;
    Node* tail;
};

Node* List::InsertHead(int dato){
    Node* nuovo = new Node(dato, head, nullptr);
    if(head != nullptr){
        head->prev = nuovo;
    }else{
        tail = nuovo;
    }

    head = nuovo;
    return head;
}

Node* List::InsertAfert(int dato, Node* p){
    if(head == nullptr || p == nullptr){
        return InsertHead(dato);
    }

    Node* nuovo = new Node(dato, p->next , p);
    if(p->next != nullptr){
        p->prev = nuovo;
    }else{
        tail = nuovo;
    }
    p->next = nuovo;
    return nuovo;
}

Node* List::Search(int dato){
    Node *p = head;

    while(p != nullptr){
        if(p->dato == dato){
            return p;
        }

        p = p->next;
    }

    return nullptr;
}

void List::found(List& list, int dato){
    Node* found = list.Search(dato);

    if(found){
        cout <<"Nodo trovato: " << found->dato << endl;
    }else{
        cout <<"Nodo contenente " << dato << " non trovato." << endl;
    }
}

bool List::Remove(int dato){
    Node* cur = head;

    while(cur != nullptr){

        if(cur->dato == dato){                       
            if(cur->prev != nullptr){
                cur->prev->next = cur->next;                
            }else{
                head = cur->next;
            }


            if(cur->next != nullptr){
            cur->next->prev = cur->prev;              
            }else{
            tail = cur->prev;
            }

            
         delete cur;
         return true;
        }

        cur = cur->next;

    }

    return cur;
}

List::~List() {
    Node* cur = head;
    while (cur != nullptr) {
        Node* next = cur->next;
        delete cur;
        cur = next;
    }
    head = tail = nullptr;
}


ostream& operator << (ostream& stream, const List& list){
    Node * p = list.head;
    stream << "Lista avanti: ";
    while(p!= nullptr){
        stream << p->dato;
        if(p->next){
            stream << ", ";
        }
        p = p->next;
    }

    stream << endl;


    p = list.tail;
    stream << "Lista indietro: ";
    while(p != nullptr){
        stream << p->dato;
        if (p->prev){
            stream << ", ";
        } 
        p = p->prev;
    }

    stream << endl;

    return stream;
}

int main(){
    List lista;
    Node* L = nullptr;
    L = lista.InsertAfert(5,L);
    cout << lista;
    L = lista.InsertAfert(3,L);
    L = lista.InsertAfert(7,L);
    cout << lista;
    lista.found(lista,3);
    lista.found(lista,11);
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