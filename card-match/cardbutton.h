#ifndef CARD_MATCH_CARDBUTTON_H
#define CARD_MATCH_CARDBUTTON_H

#include <QPushButton>
#include "card.h"

class CardButton : public QPushButton, public std::enable_shared_from_this<CardButton> {

Q_OBJECT

public slots:
    void updateIcon(std::shared_ptr<Card>);
};

#endif //CARD_MATCH_CARDBUTTON_H
