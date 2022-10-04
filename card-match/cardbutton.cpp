#include "cardbutton.h"

void CardButton::updateIcon(std::shared_ptr<Card> card){
    this->setIcon(card->icon());
}
