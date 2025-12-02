voli = new Volo* [capienza_voli];
}

~Sistema_Prenotazione()
{
    for(int i=0; i<contatore_voli; i++)
    {
        delete voli[i];
    }

    for(int i=0; i<contatore_prenotazioni; i++)
    {
        delete prenotazioni[i];
    }

    delete [] voli;
    delete [] prenotazioni;
}

string getName() const {return name;}

void add_prenotazioni(Prenotazione* p)
{
    if(!p)
        return;

    if(contatore_prenotazioni >= capienza_prenotazioni)
        resize_array(prenotazioni,contatore_prenotazioni,capienza_prenotazioni);

    prenotazioni[contatore_prenotazioni++] = p;
}

bool add_voli(Volo* v)
{
    if(!v)
        return false;

    if(contatore_voli >= capienza_voli)
        resize_array(voli,contatore_voli,capienza_voli);

    voli[contatore_voli++] = v;
    return true;
}


bool remove_voli(Volo* v)
{
    for(int i=0; i<contatore_voli; i++)
    {
       if(voli[i]->getId_volo() == v->getId_volo())
       {
            for(int j=0; j<contatore_prenotazioni; j++)
            {
                if(prenotazioni[j]->getVolo() == v)
                {
                    remove_prenotazione(prenotazioni[j]);
                    j--;
                }
            }

            delete voli[i];

            for(int j=i ; j<contatore_voli-1; j++)
            {
                voli[j] = voli[j+1];
            }

            voli[contatore_voli-1] = nullptr;
            contatore_voli--;
            cout << "Volo Rimosso: ";
            v->print();
            cout << endl;
            return true;
        }
    }

    cout << "ERRORE: Volo non registrato" << endl;
    return false;
}


bool remove_prenotazione(Prenotazione* p)
{
    for(int i=0; i<contatore_prenotazioni; i++)
    {
        if(prenotazioni[i]->getId_prenotazione() == p->getId_prenotazione())
        {
            delete prenotazioni[i]; 

            for(int j=i ; j<contatore_prenotazioni-1; j++)
            {
                prenotazioni[j] = prenotazioni[j+1];
            }

            prenotazioni[contatore_prenotazioni-1] = nullptr;
            contatore_prenotazioni--;
            return true;
        }
    }

    return false;
}

bool conferma_prenotazione(Prenotazione* p)
{
    if(!p)
        return false;

    bool success = p->richiesta_prenotazione();

    if(success)
    {
        add_prenotazioni(p);
        cout << "\nPrenotazione effettuata con successo!" << endl;
        p->getPasseggero()->print();
        p->getVolo()->print();
        return true;
    }
    else
    {
        cout << "Errore: prenotazione non andata a buon fine" << endl;
        return false;
    }

    cout << "Errore: prenotazione inesistente nel databese" << endl;
    return false;
}

bool annulla_prenotazione(Prenotazione* p)
{
     if(!p)
        return false;

    bool success = p->richiesta_annullamento_prenotazione();

    if(success)
    {
        remove_prenotazione(p);
        cout << "Prenotazione annullata!" << endl;
        p->getPasseggero()->print();
        p->getVolo()->print();
        cout << endl;
        return true;
    }
    else
    {
        cout << "Errore: annullamento prenotazione non andata a buon fine" << endl;
        cout << endl;
        return false;
    }

    cout << "Errore: impossibile annullare la prenotazione inesistente nel databese" << endl;
    cout << endl;
    return false;
}

bool ricerca_volo_disp(string destinazione)
{
    for(int i=0; i<contatore_voli; i++)
    {
        if(voli[i]->getDestinazione() == destinazione)
        {
            if(voli[i]->getPosti_disponibli() > 0)
            {
                cout << "Conferma posti disponibili per il seguente volo: "<< endl;
                voli[i]->print();
                cout << endl;
                return true;
            }
            else
            {
                cout << "ERRORE: Nessun posto disponibile per il seguente volo: " << endl;
                voli[i]->print();
                cout << endl;
                return false;
            }
        }
    }

    cout << "ERRORE: Nessuno volo per la seguente destinazione" << endl;
    return false;
}

void ricerca_passeggero_speciale(Volo* v)
{
    for(int i=0; i<contatore_prenotazioni; i++)
    {
        if(prenotazioni[i]->getVolo() == v)
        {
            if(prenotazioni[i]->getPasseggero()->getStatus())
            {
                prenotazioni[i]->getPasseggero()->print();
            }
        }
    }
    cout << endl;
}

void print_passeggero(Passeggero* p) const 
{

    p->print();
    cout << "Elenco delle sue prenotazioni: "<<endl;
    bool success = false;


    for(int i=0; i<contatore_prenotazioni; i++)
    {
        if(prenotazioni[i]->getPasseggero() == p)
        {
            prenotazioni[i]->getVolo()->print();
            success = true;
        }
    }

    if(!success)
        cout << "Nessuna prenotazione effettuata" << endl;
}
