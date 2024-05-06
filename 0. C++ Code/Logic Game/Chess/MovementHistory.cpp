
#include <iostream>
#include <fstream>
#include<string>
#include <vector>
#include "MovementHistory.h"

using namespace std;

// aqui van los metodos para la clase NodeMoves y stackNodeMoves

void stackMovements::popMov() {

    bool eliminat = false;

    NodeMoves* auxSeguent; //apunta al seguent node del que volem eliminar
    NodeMoves* auxAnterior; //apunta al anterior node del que volem eliminar
    NodeMoves* auxAeliminar;

    auxSeguent = ultimMoviment->getNext();
    auxAnterior = ultimMoviment->getPrev();
    auxAeliminar = ultimMoviment;

    if (getUltimMoviment()->getNext() == nullptr && getUltimMoviment()->getPrev() != nullptr) {  //si eliminem el ultim

        setUltimMoviment(auxAnterior); // este sera nuesto ultimo nodo
        auxAnterior->setNext(nullptr); // al ser el ultimo, no tiene next i el previo no se modifica
    }

    delete auxAeliminar;
    auxAeliminar = auxSeguent;
}

void stackMovements::pushMov(const string& moviment, const string& erasedPiece) { //ARREGLADO

    NodeMoves* aux = new NodeMoves;

    if (ultimMoviment != nullptr) { // si ja tenim nodes 


        aux->setMov(moviment); //ponemos el mov
        aux->setNext(nullptr); //al ser el ultimo no tiene siguinte
        aux->setPrev(ultimMoviment); // su previo sera el exUltimo nodo

        getUltimMoviment()->setNext(aux); //al exUltimo su nuevo next sera nustro nodo recien creado 'aux'

        setUltimMoviment(aux); //al exUltimo su nuevo next sera nustro nodo recien creado 'aux'


    }
    else { //si es el primer node de la llista que afegim


        aux->setMov(moviment); //ponemos el mov
        aux->setNext(nullptr); //al ser el ultimo no tiene siguinte
        aux->setPrev(nullptr); // su previo sera el exUltimo nodo
        setUltimMoviment(aux); //al exUltimo su nuevo next sera nustro nodo recien creado 'aux'



    }
}

bool stackMovements::empty() { // nos indica si esta vacio

    if (getUltimMoviment() == nullptr)
        return true;
    else
        return false;
}









NodeMoves::NodeMoves() {

    m_moviment = "";
    eliminatedPiece = "";
    m_next = nullptr;
    m_prev = nullptr;

}



NodeMoves::~NodeMoves() {

    delete m_next;
    delete  m_next;
    m_next = nullptr;
    m_prev = nullptr;

}
