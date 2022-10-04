#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <vector>
#include <memory>
#include "card.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private slots:
    static void quit();

    void reset();

    void flippedCard(std::shared_ptr<Card> mycard);

    void blockSignals(bool block);

    void sync();

    void shuffle();

    void timerDone();

    void disconnect();

    void connect();

    int vecIndex(std::shared_ptr<Card> c);

private:
    int match_count = 0;
    int guess_count = 0;
    Ui::MainWindow* ui;
    std::vector<std::shared_ptr<QPushButton>> m_buttons;
    std::vector<std::shared_ptr<Card>> m_cards;
};

#endif // MAINWINDOW_H
