#include "button.h"
#include <cassert>

void Button::updateIcon(std::shared_ptr<Card> card){
    this->setIcon(card->icon());
}
