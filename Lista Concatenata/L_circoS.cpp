#include <iostream>

using namespace std;

class List;
ostream& operator << (ostream& stream, const List& list);


class Node{
public:
    Node(int d, Node* n = nullptr) : dato(d) , next(n) {}
    friend class List;
    friend ostream& operator << (ostream& stream, const List& list);


private:
    int dato;
    Node* next;
};

class List{
public:
    List() : tail(nullptr) {}

    Node* InsertHead(int dato);
    Node* InsertAfter(int dato,Node* p);
    Node* Search(int dato);
    void  Found(List& list, int dato);
    bool Remove(int dato);
    ~List();

    friend ostream& operator << (ostream& stream, const List& list);


private:
Node* tail;
};


Node* List::InsertHead(int dato){
    Node* nuovo = new Node(dato);

    if(tail==nullptr){
        nuovo->next = nuovo;
        tail = nuovo;
    }else{
        nuovo->next = tail->next;
        tail->next = nuovo;
    }

    return nuovo;
}

Node* List::InsertAfter(int dato, Node* p){
    if(tail == nullptr || p == nullptr){
        return InsertHead(dato);
    }

    Node* nuovo = new Node(dato, p->next);
    p->next = nuovo;

    if(p==tail){
        tail = nuovo;
    }

    return nuovo;
}

Node* List::Search(int dato){

    if(tail== nullptr) return nullptr;

    Node *cur = tail->next;    //partire dalla testa

    do{
        if(cur->dato == dato){
            return cur;
        }
        cur = cur->next;
    }while(cur != tail->next);

    return nullptr;
}

void List::Found(List& list, int dato){
    Node* found = list.Search(dato);

    if(found){
        cout <<"Nodo trovato: " << found->dato << endl;
    }else{
        cout <<"Nodo contenente " << dato << " non trovato." << endl;
    }
}

bool List::Remove(int dato){
    if(tail == nullptr) return false;
    Node* cur = tail->next;
    Node* prev = tail;

    do{
        if(cur->dato == dato){
            if(cur == tail && cur == tail->next){
                delete cur;
                tail = nullptr;
            }else{
                prev->next = cur->next;
                if(cur == tail){
                    tail = prev;
                }

                delete cur;
            }

            return true;
        }

        prev = cur;
        cur = cur->next;
    }while(cur != tail->next);

    return false;

}

List::~List(){
    if(tail==nullptr) return ;

    Node* p = tail->next;
    Node* tmp;

    do{
        tmp = p;
        p = p->next;
        delete tmp;
    }while(p != tail->next);

    tail = nullptr;
}

ostream& operator << (ostream& stream, const List& list){
    if (list.tail == nullptr) {
        stream << "Lista vuota\n";
        return stream;
    }

    Node *p = list.tail->next;  //head
    stream << "Lista: ";
    do{
        stream << p->dato;
        if(p->next != list.tail->next){
            stream <<", ";
        }

        p = p->next;
    }while(p!= list.tail->next);

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