#ifndef CARD_H
#define CARD_H

#include <QIcon>
#include <QString>
#include <QObject>

class Card : public QObject, public std::enable_shared_from_this<Card>{
Q_OBJECT

public:
    explicit Card(QString iconName, int x, int y, QObject* parent = nullptr);

    [[nodiscard]] const QIcon& icon() const {
        static QIcon back(":/back.png");
        return m_up ? m_front : back;
    }

    int getSuit();

    int getRank();

    bool getSelected();

    void setSelected(bool set);

    void changeSide();

    void reset();

    void setMatched(bool v);

signals:
    void flipped(std::shared_ptr<Card>);

public slots:
    void flip() {
        if(!matched) {
            selected = !selected;
            m_up = !m_up;
            emit flipped(shared_from_this());
        }

    };

private:
    QIcon m_front;
    int Suit;
    int Rank;
    bool m_up = false;
    bool selected = false;
    bool matched = false;
};

#endif // CARD_H
