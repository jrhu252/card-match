#include <cassert>
#include <algorithm>
#include <random>
#include "mainwindow.h"
#include "ui_MainWindow.h"
#include <QObject>
#include <QTimer>
#include <QMessageBox>
#include <QStatusBar>
#include "cardbutton.h"

using namespace std;

MainWindow::MainWindow(QWidget* parent) :
        QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    statusBar()->showMessage("Guesses: 0        Matches: 0");

    const QString card_base_name[4] = {":/diamond_", ":/hearts_", ":/spades_", ":/clubs_"};
    const int cards_per_row = 13;
    int NUMBER_OF_COLUMNS;
    const QSize CARD_SIZE(71, 94);

    for (int j = 0; j < 4; j++) {
        NUMBER_OF_COLUMNS = 0;
        for (int i = 0; i < cards_per_row; ++i) {
            const QString card_name = card_base_name[j] + QString::number(i + 1);

            shared_ptr<Card> card(nullptr);
            card = make_shared<Card>(card_name, j, i);
            m_cards.push_back(card);

            auto button = std::make_unique<CardButton>();
            button->setIcon(card->icon());
            button->setIconSize(CARD_SIZE);
            button->setFlat(true);
            m_buttons.push_back(std::move(button));

            int row = j;
            int column = NUMBER_OF_COLUMNS;
            NUMBER_OF_COLUMNS = NUMBER_OF_COLUMNS + 1;

            ui->gridLayout->addWidget(m_buttons.back().get(), row, column);

            QObject::connect(m_buttons.back().get(), SIGNAL(clicked()),
                             card.get() , SLOT(flip()));
            QObject::connect(card.get(), SIGNAL(flipped(std::shared_ptr<Card>)),
                             m_buttons.back().get(),SLOT(updateIcon(std::shared_ptr<Card>)));
            QObject::connect(card.get(), SIGNAL(flipped(std::shared_ptr<Card>)),
                             this, SLOT(flippedCard(std::shared_ptr<Card>)));
        }
    }

    disconnect();
    shuffle();
    connect();

    QObject::connect(ui->quitButton, SIGNAL(clicked()),this, SLOT(quit()));
    QObject::connect(ui->resetButton, SIGNAL(clicked()),this, SLOT(reset()));
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::quit() {
    QApplication::quit();
}

void MainWindow::sync() {
    auto cardIt = m_cards.begin();
    auto buttonIt = m_buttons.begin();
    while (cardIt != m_cards.end()) {
        (*buttonIt)->setIcon(cardIt->get()->icon());
        cardIt = cardIt + 1;
        buttonIt = buttonIt + 1;
    }
    assert(buttonIt == m_buttons.end());
}

void MainWindow::disconnect(){

    auto cardIt = m_cards.begin();
    auto buttonIt = m_buttons.begin();
    while (cardIt != m_cards.end()) {
        QObject::disconnect(buttonIt->get(), SIGNAL(clicked()), cardIt->get() , SLOT(flip()));
        QObject::disconnect(cardIt->get(), SIGNAL(flipped(std::shared_ptr<Card>)), buttonIt->get(),SLOT(updateIcon(std::shared_ptr<Card>)));
        QObject::disconnect(cardIt->get(), SIGNAL(flipped(std::shared_ptr<Card>)), this, SLOT(flippedCard(std::shared_ptr<Card>)));

        cardIt = cardIt + 1;
        buttonIt = buttonIt + 1;
    }
}

void MainWindow::connect(){

    auto cardIt = m_cards.begin();
    auto buttonIt = m_buttons.begin();
    while (cardIt != m_cards.end()) {
        QObject::connect(buttonIt->get(), SIGNAL(clicked()), cardIt->get() , SLOT(flip()));
        QObject::connect(cardIt->get(), SIGNAL(flipped(std::shared_ptr<Card>)), buttonIt->get(),SLOT(updateIcon(std::shared_ptr<Card>)));
        QObject::connect(cardIt->get(), SIGNAL(flipped(std::shared_ptr<Card>)), this, SLOT(flippedCard(std::shared_ptr<Card>)));

        cardIt = cardIt + 1;
        buttonIt = buttonIt + 1;
    }
}

void MainWindow::shuffle() {
        auto seed = std::random_device {};
        auto random = std::default_random_engine{seed()};
        std::shuffle(m_cards.begin(), m_cards.end(), random);
        sync();
}

void MainWindow::reset() {
    auto cardIt = m_cards.begin();
    while (cardIt != m_cards.end()) {
        cardIt->get()->reset();
        cardIt = cardIt + 1;
    }
    disconnect();
    shuffle();
    connect();

    match_count = 0;
    guess_count = 0;

    statusBar()->showMessage("Guesses: 0        Matches: 0");
    sync();
}

void MainWindow::flippedCard(std::shared_ptr<Card> mycard) {
    mycard->setSelected(true);
    for (auto &element: m_cards) {
        if (element->getSelected()) {
            if(element != mycard) {
                if ((element->getRank() == mycard->getRank())) {
                    element->setSelected(false);
                    mycard->setSelected(false);

                    mycard->setMatched(true);
                    element->setMatched(true);

                    match_count = match_count + 1;
                    guess_count = guess_count + 1;

                    QString message1 = "Matches: ";
                    message1 += QString::number(match_count);

                    QString message2 = "Guesses: ";
                    message2 += QString::number(guess_count);

                    QString full_message = message2 + "        " + message1;

                    statusBar()->showMessage(full_message);
                }

                else {
                    element->setSelected(false);
                    mycard->setSelected(false);
                    guess_count = guess_count + 1;

                    QString message1 = "Matches: ";
                    message1 += QString::number(match_count);

                    QString message2 = "Guesses: ";
                    message2 += QString::number(guess_count);

                    QString full_message = message2 + "        " + message1;

                    element->changeSide();
                    mycard->changeSide();

                    blockSignals(true);
                    QTimer::singleShot(3000, this, SLOT(timerDone()));
                    statusBar()->showMessage(full_message);
                }
            }
        }
    }
    if(match_count == 26) {
        QMessageBox::warning(this, "Victory", "You have found all the matches and won the game!");
    }
}

void MainWindow::timerDone(){
    blockSignals(false);
    sync();
}

void MainWindow::blockSignals(bool block) {
    auto buttonIt = m_buttons.begin();
    while (buttonIt != m_buttons.end()) {
        (*buttonIt)->blockSignals(block);
        buttonIt = buttonIt + 1;
    }
}

int MainWindow::vecIndex(shared_ptr<Card> c) {
    int index;
    auto it = std::find(m_cards.begin(), m_cards.end(), c);
    if (it != m_cards.end())
        index = distance(m_cards.begin(), it);

    return index;
}
