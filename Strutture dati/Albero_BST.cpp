#include <iostream>

using namespace std;

class BST_Node
{
public:
    BST_Node(int d): data(d), left(nullptr), right(nullptr), parent(nullptr) {}

    BST_Node* getLeft() const {return left;}
    BST_Node* getRight() const {return right;}
    BST_Node* getParent() const {return parent;}
    int getData() const {return data;}

    void setLeft(BST_Node* l) {left = l;}
    void setRight(BST_Node* r) {right = r;}
    void setParent(BST_Node* p) {parent = p;}



private:
    int data;
    BST_Node* left;
    BST_Node* right;
    BST_Node* parent;
};

class BST
{
public:
    BST() : root(nullptr) {}

    bool insert(int val);

    BST_Node* search(int val);
    BST_Node* min();
    BST_Node* max();
    BST_Node* successivo(BST_Node* node);
    
    void trapianta(BST_Node* u, BST_Node*v);
    bool remove(int d);
    
    void print_pre(ostream& os) const {return print_pre(os,root);}
    void print_in(ostream& os) const {return print_in(os,root);}
    void print_post(ostream& os) const {return print_post(os,root);}

    void print_pre(ostream& os,BST_Node* b) const;
    void print_in(ostream& os,BST_Node* b) const;
    void print_post(ostream& os,BST_Node* b) const;


private:
    BST_Node* root;

    BST_Node* search(BST_Node* node, int val);
    BST_Node* min(BST_Node* node);
    BST_Node* max(BST_Node* node);
    


};


bool BST::insert(int val)
{
    BST_Node* x = root;                   //Ci permette di scorrere l'albero
    BST_Node* y = nullptr;                // Tiene traccia del parent del nodo da inserire

    while(x != nullptr)                   // Viene eseguito dopo aver inserito un nodo
    {
        y = x;

        if(val == x->getData())             //Cosi evitiano duplicati 
            return false;

        else if(val < x->getData())         // Il valore è minore, vai a sinistra
            x = x->getLeft();               

        else
            x = x->getRight();              // Il valore è maggiore, vai a destra
    }

    BST_Node* node = new BST_Node(val);     //Creazione nuovo nodo con il suo dato
    node->setParent(y);                     // Collega il nuovo nodo al suo parent

    if(y == nullptr)                        // Albero vuoto, nuovo nodo diventa root
        root = node;                        

    else if(val < y->getData())             
        y->setLeft(node);                   // Inserisci come figlio sinistro

    else
        y->setRight(node);                  // Inserisci come figlio destro

    return true;
}

BST_Node* BST::search(int val)
{
    return search(root, val);
}

BST_Node* BST::search(BST_Node* node, int val)
{

    if(node == nullptr || node->getData() == val)
        return node;

    if(val < node->getData())
        return search(node->getLeft(), val);
    else
        return search(node->getRight(), val);
}

BST_Node* BST::min()
{
    return min(root);
}


BST_Node* BST::min(BST_Node* node)
{
    if(node == nullptr || node->getLeft() == nullptr)
    return node;

    return min(node->getLeft());
}

BST_Node* BST::max()
{
    return max(root);
}


BST_Node* BST::max(BST_Node* node)
{
    if(node == nullptr || node->getRight() == nullptr)
    return node;

    return max(node->getRight());
}

BST_Node* BST::successivo(BST_Node* node)
{
    if(node == nullptr )
        return nullptr;

    if(node->getRight())
        return min(node->getRight());

    BST_Node* genitore = node->getParent();
    while(genitore && node == genitore->getRight())
    {
        node = genitore;
        genitore = node->getParent();
    }

    return genitore;
}

void BST::trapianta(BST_Node* u, BST_Node*v)
{
    if(u->getParent() == nullptr)
    {
        root = v;
    }
    else if(u == u->getParent()->getLeft())
    {
        u->getParent()->setLeft(v);
    }
    else
    {
        u->getParent()->setRight(v);
    }

    if(v != nullptr)
    {
        v->setParent(u->getParent());
    }
}

bool BST::remove(int d)
{
    BST_Node* p = search(d);

    if(p == nullptr)
    {
        cout << "Nessun nodo contenente il valore : " << d << endl;
        return false;
    }

    // Caso 1: Foglia
    if(!p->getLeft() && !p->getRight())
    {
       trapianta(p,nullptr);
       delete p;
       return true;
    }

    // Caso 2: Solo figlio destro
    if(!p->getLeft())
    {
        trapianta(p,p->getRight());
        delete p;
        return true;
    }

    // Caso 2: Solo figlio sinistro
    if(!p->getRight())
    {
        trapianta(p,p->getLeft());
        delete p;
        return true;
    }

    // Caso 3: Entrambi figli
    BST_Node* next = successivo(p);

    if(next->getParent() != p)
    {
        trapianta(next,next->getRight());
        next->setRight(p->getRight());
        next->getRight()->setParent(next);
    }
    
    trapianta(p,next);

    if(p->getLeft())
    {
        next->setLeft(p->getLeft());
        next->getLeft()->setParent(next);
    }

    delete p;
    return true;
    
}

void BST::print_pre(ostream& os, BST_Node* b) const
{
    if(b==nullptr) return;

    os << b->getData() << " ";
    print_pre(os,b->getLeft());
    print_pre(os,b->getRight());
}

void BST::print_in(ostream& os, BST_Node* b) const
{
    if(b==nullptr) return;

    print_in(os,b->getLeft());
    os << b->getData() << " ";
    print_in(os,b->getRight());
}

void BST::print_post(ostream& os, BST_Node* b) const
{
    if(b==nullptr) return;

    print_post(os,b->getLeft());
    print_post(os,b->getRight());
    os << b->getData() << " ";
}

ostream& operator << (ostream& os, const BST& b)
{
   os << "=== PRE ORDER ===" << endl;
   b.print_pre(os);
   os << endl;

   os << "=== IN ORDER ===" << endl;
   b.print_in(os);
   os << endl;

   os << "=== POST ORDER ===" << endl;
   b.print_post(os);
   os << endl;

   return os;
}


int main()
{
    BST b;
    b.insert(40);
    b.insert(30);
    b.insert(50);
    b.insert(20);
    b.insert(25);
    b.insert(35);
    b.insert(45);
    b.insert(60);
    b.insert(70);
    b.insert(65);
    b.insert(55);
    b.insert(75);

    cout << b << endl;

    BST_Node* s = b.search(50);
    BST_Node* s1 = b.search(80);

    if(s)
        cout << "NODO TROVATO: "<< s->getData() << endl;
    else
        cout << "NODO NON TROVATO" << endl;

    if(s1)
        cout << "NODO TROVATO: "<< s1->getData() << endl;
    else
        cout << "NODO NON TROVATO" << endl;

    BST_Node* min = b.min();
    cout << "NODO CON IL VALORE MINIMO DELL'ALBERO: " << min->getData() << endl;

    BST_Node* max = b.max();
    cout << "NODO CON IL VALORE MASSIMO DELL'ALBERO: " << max->getData() << endl;

    b.remove(45); // caso 1 foglia;
    b.remove(70); // caso 2 figlio (dx)
    b.remove(65); // caso 3 entrambi figli

    cout << b << endl;

    return 0;
}