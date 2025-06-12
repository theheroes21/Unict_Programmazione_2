#include <iostream>

using namespace std;

class List;
ostream& operator << (ostream& stream, const List& list);

class Node{
public:
    Node (int d, Node* p = nullptr) : dato(d) , next(p) {}
    friend class List;
    friend ostream& operator << (ostream& stream, const List& list);


private:
    int dato;
    Node *next;
};

class List{
public:
    List () : head(nullptr) {}
    Node& InsertHead(int dato);
    Node& Insert(int dato, Node* p);
    Node* Search(int dato);
    void  found(List& list, int d);
    bool Remove(int dato);

    friend ostream& operator << (ostream& stream, const List& list);




private:
    Node * head;
};

Node& List::InsertHead(int d){
    head = new Node(d, head);
    return *head;
}

Node& List::Insert(int d, Node* p){
    if(head == nullptr || p==nullptr){
        return InsertHead(d);
    }

    Node *n = new Node(d,p->next);
    p->next = n;
    return *n;
}

Node* List::Search(int d){
    Node *p = head;
    while(p != nullptr){
        if(p->dato == d){
            return p;
        }

        p = p->next;
    }

    return nullptr;
}

void List::found(List& list, int d){
    Node *found = list.Search(d);

    if(found){
        cout <<"Nodo trovato: " << found->dato << endl;
    }else{
        cout <<"Nodo contenente " << d << " non trovato." << endl;
    }
}

bool List::Remove(int d){
    Node* cur = head;
    Node* ant = nullptr;

    while(cur != nullptr){
        if(cur->dato == d){
            if(ant == nullptr){
                head = cur->next;
            }else{
                ant->next = cur->next;
            }
            delete cur;
            return true;
        }

        ant = cur;
        cur = cur->next;
    }

    return false;
}

ostream& operator << (ostream& stream, const List& list){
    stream << "Gli elementi della lista sono: ";
    Node *p = list.head;
    while(p != nullptr){
        stream << p->dato;
        if(p->next){
            stream << ", ";
        }
        p = p->next;
    }

    stream << endl;
    return stream;
}


int main(){
    List lista;
    Node* L = nullptr;
    L = &lista.Insert(5,L);
    cout << lista;
    L = &lista.Insert(3,L);
    L = &lista.Insert(7,L);
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
