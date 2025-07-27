Strutture Dati - Implementazione in C++ 🔧📚
Descrizione

Questo progetto fornisce un'implementazione modulare e flessibile di diverse strutture dati fondamentali in C++. L'obiettivo principale è garantire riusabilità, estendibilità e manutenibilità attraverso l'uso di classi astratte e interfacce generiche.

Le strutture implementate includono:

    Stack (pila)

    Queue (coda)

    List (lista concatenata)

    Vector (vettore dinamico)

    BinaryTree (albero binario)

    Hashtable (tabella hash)

Il progetto è progettato con un approccio object-oriented e segue il principio SOLID della programmazione.
Caratteristiche principali

    ✅ Classi astratte per ogni tipo di struttura, permettendo un alto grado di flessibilità per estensioni future.

    🧪 Sistema di test completo tramite due file di test (zlasdtest.cpp e mytest.cpp) che verificano la correttezza e le performance delle strutture.

    🔄 Interfacce uniformi tra le varie strutture dati per garantire un uso coerente.

    🚀 Efficienza garantita da implementazioni ottimizzate, sia in termini di memoria che di tempo di esecuzione.

Architettura del progetto

├── include/
│   ├── stack.hpp
│   ├── queue.hpp
│   ├── list.hpp
│   ├── vector.hpp
│   ├── binarytree.hpp
│   ├── hashtable.hpp
│   └── ...
├── src/
│   ├── stack.cpp
│   ├── queue.cpp
│   ├── list.cpp
│   ├── vector.cpp
│   ├── binarytree.cpp
│   ├── hashtable.cpp
│   └── ...
├── test/
│   ├── zlasdtest.cpp
│   └── mytest.cpp
├── README.md
├── Makefile
└── main.cpp

Requisiti

    Compilatore C++ (supporto per C++11 o superiore)

    GNU Make (per l'uso del Makefile)

Compilazione

Per compilare l'intero progetto, è sufficiente eseguire:

make

Per eseguire i test:

make test
./zlasdtest
./mytest

Esempio d'uso

#include "stack.hpp"

int main() {
    Stack<int>* myStack = new ArrayStack<int>();

    myStack->Push(10);
    myStack->Push(20);

    std::cout << "Top element: " << myStack->Top() << std::endl;

    myStack->Pop();

    delete myStack;
    return 0;
}

Dettagli sulle Strutture Dati
Struttura	Descrizione breve
Stack	LIFO (Last In, First Out), implementato tramite array dinamici o liste
Queue	FIFO (First In, First Out), con implementazioni basate su array circolari o liste
List	Liste semplici e doppiamente collegate
Vector	Wrapper su array dinamico con resizing automatico
BinaryTree	Implementazione base di alberi binari e traversal ricorsivi e iterativi
Hashtable	Tabelle hash con open addressing o chaining (a seconda della configurazione)
Estendibilità

Grazie all'uso di interfacce astratte (AbstractStack, AbstractQueue, etc.), è possibile:

    Aggiungere nuove implementazioni (es. Stack basato su lista vs array).

    Sostituire una struttura con un'altra senza modificare il codice utente.

    Integrare facilmente nuove strutture dati (es. AVLTree, PriorityQueue, etc.)

Testing
zlasdtest.cpp

    Test ufficiali forniti per la valutazione.

    Verifica funzionalità base e avanzate.

mytest.cpp

    Test personalizzati.

    Include casi limite, stress test e test di performance.

Contributi

Contributi sono benvenuti! Sentiti libero di aprire issue o pull request.
Licenza

Distribuito sotto licenza MIT. Vedi il file LICENSE per i dettagli.
