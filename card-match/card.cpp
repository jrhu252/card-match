#include "card.h"
#include <cassert>

Card::Card(QString iconName, int x, int y, QObject* parent) : m_front(iconName), Suit(x), Rank(y) {      //Constructor, populates private members
    assert(!m_front.isNull());
}

void Card::setSelected(bool set) {
    selected = set;
}

void Card::changeSide(){
    m_up = !m_up;
}

void Card::reset(){
    m_up = false;
    selected = false;
    matched = false;
}


bool Card::getSelected(){
    return selected;
}

int Card::getSuit() {
    return Suit;
}

int Card::getRank() {
    return Rank;
}

void Card::setMatched(bool v){
    matched = v;
}
