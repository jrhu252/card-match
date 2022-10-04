
#ifndef CARD_MATCH_BUTTON_H
#define CARD_MATCH_BUTTON_H

#include <QPushButton>
#include "card.h"

class Button : public QPushButton, public std::enable_shared_from_this<Button> {
Q_OBJECT

public slots:

    void updateIcon(std::shared_ptr<Card>);

};


#endif //CARD_MATCH_BUTTON_H
