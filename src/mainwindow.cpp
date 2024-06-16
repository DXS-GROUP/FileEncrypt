#include "mainwindow.h"

#include <QObject>
#include <QPushButton>

#include "encrypt.cpp"
#include "decrypt.cpp"

#include "drop_file.h"

#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    this->setFixedSize(350, 350);

    fileDrop = new FileDropWidget();
    fileDrop->setPixmap(QPixmap(":/get.png").scaled(180, 180, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    closeBtn = new QPushButton("");
    closeBtn->setFixedSize(15, 15);
    closeBtn->setStyleSheet("QPushButton {"
                            "    border-color: rgba(0, 0, 0, 0);"
                            "    background-color: rgba(0, 0, 0, 0);"
                            "    background-image: url(':/red.png');"
                            "    background-repeat: no-repeat;"
                            "}"

                            "QPushButton:hover {"
                            "    border-color: rgba(0, 0, 0, 0);"
                            "    background-image: url(':/redHovered.png');"
                            "    background-repeat: no-repeat;"
                            "    background-color: rgba(0, 0, 0, 0);"
                            "}");

    startEncrypt = new QPushButton("Start process");
    startEncrypt->setFixedSize(150, 25);

    centralWidget = new QWidget();
    this->setCentralWidget(centralWidget);

    mainLayout = new QGridLayout;
    centralWidget->setLayout(mainLayout);

    mainLayout->addWidget(closeBtn, 0, 0, 1, 4, Qt::AlignLeft);
    mainLayout->addWidget(fileDrop, 1, 0, 4, 4, Qt::AlignCenter);
    mainLayout->addWidget(startEncrypt, 5, 0, 1, 4, Qt::AlignCenter);

    connect(closeBtn, SIGNAL(clicked()), this, SLOT(closeButtonClicked()));
    connect(startEncrypt, SIGNAL(clicked()), this, SLOT(fileEncrypt()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::closeButtonClicked() {
    this->close();
}

void MainWindow::fileEncrypt() {
    qDebug() << "Encrypting";
}