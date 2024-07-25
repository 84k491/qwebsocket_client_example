#include "mainwindow.h"
#include <iostream>

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget * parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    static const QUrl url("wss://fstream.binance.com/ws/btcusdt@aggTrade");
    connect(&m_client, &QWebSocket::connected, this, &MainWindow::onConnected);
    m_client.open(url);
}

MainWindow::~MainWindow()
{
    m_client.close();
    delete ui;
}

void MainWindow::onConnected()
{
    std::cout << "WebSocket connected" << std::endl;
    connect(&m_client, &QWebSocket::textMessageReceived,
            this, &MainWindow::onTextMessageReceived);
}

void MainWindow::onTextMessageReceived(QString message)
{
    std::cout << "Message received:" << message.toStdString() << std::endl;
}
