#include <iostream>

using namespace std;

class List;
ostream& operator<<(ostream& stream, const List& list);

class Node{
public:
    Node(int d) : next(nullptr) , dato(d) {}
    friend class List;
    friend ostream& operator << (ostream& stream, const List& list);

private:
  int dato;
  Node *next;
};


class List{
public:
    List() : head(nullptr) {}
    
    void insert(int val);
    bool search(int val);
    bool remove(int val);

    friend ostream& operator <<(ostream& stream, const List& list);
 
private:
    Node* head;
};

void List::insert(int val){
    Node* n = new Node(val);
    n->next = head;
    head = n;
}

bool List::search(int val){
    Node* current = head;
    while(current){
        if(current->dato == val){
            return true;
        }
        current = current->next;
    }

    return false;
}

bool List::remove(int val){
    Node** current = &head;
    while(*current){
        if((*current)->dato == val){
            Node* tmp = *current;
            *current = (*current)->next;
            delete tmp;
            return true;
        }
        current = &((*current)->next);
    }

    return false;
}

ostream& operator << (ostream& stream, const List& list){
    stream << "Gli elementi della lista sono: ";
    Node* p = list.head;
    while (p != nullptr) {
        stream << p->dato << ", ";
        p = p->next;
    }
    stream << endl;
    return stream;
}

int main(){
    List lista;
    cout << lista;
    lista.insert(5);
    lista.insert(3);
    lista.insert(7);
    cout << lista;
    cout << "Il puntatore al nodo 3 e': " << lista.search(3) << endl;
    cout << "Il puntatore al nodo 11 e': " << lista.search(11) << endl;
    cout << "Elemento 3 rimosso: " << lista.remove(3) << endl;
    cout << lista;
    cout << "Elemento 3 rimosso: " << lista.remove(3) << endl;
    cout << lista;
    cout << "Elemento 5 rimosso: " << lista.remove(5) << endl;
    cout << lista;
    cout << "Elemento 7 rimosso: " << lista.remove(7) << endl;
    cout << lista;
    cout << "Elemento 11 rimosso: " << lista.remove(11) << endl;
    cout << lista;

    return 0;
}
