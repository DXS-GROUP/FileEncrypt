#include "mainwindow.h"

#include <QObject>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include <QDebug>
#include <QThread>
#include <QTimer>

#include "encrypt.cpp"

#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    this->setFixedSize(350, 370);

    fileDrop = new FileDropWidget();
    fileDrop->setPixmap(QPixmap(":/get.png").scaled(180, 180, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    label = new QLabel("FileEncrypt");

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

    fileCrypt = new FileCrypt();

    process = new QComboBox();
    process->setFixedSize(150, 30);
    process->addItem("Encrypt");
    process->addItem("Decrypt");

    password = new QLineEdit();
    password->setPlaceholderText("Password");
    password->setFixedSize(150, 30);

    centralWidget = new QWidget();
    this->setCentralWidget(centralWidget);

    mainLayout = new QGridLayout;
    centralWidget->setLayout(mainLayout);

    mainLayout->addWidget(label, 0, 0, 1, 4, Qt::AlignRight);
    mainLayout->addWidget(closeBtn, 0, 0, 1, 4, Qt::AlignLeft);
    mainLayout->addWidget(fileDrop, 1, 0, 4, 4, Qt::AlignCenter);
    mainLayout->addWidget(process, 5, 0, 1, 4, Qt::AlignCenter);
    mainLayout->addWidget(password, 6, 0, 1, 4, Qt::AlignCenter);
    mainLayout->addWidget(startEncrypt, 7, 0, 1, 4, Qt::AlignCenter);

    QThread *styleThread = new QThread;
    QObject::connect(styleThread, &QThread::started, this, [this]() {
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, [=]() {
            label->setText(fileDrop->getFileName());
        });
        timer->start(500);
    });
    styleThread->start();

    connect(closeBtn, SIGNAL(clicked()), this, SLOT(closeButtonClicked()));
    connect(startEncrypt, SIGNAL(clicked()), this, SLOT(startProcessing()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::closeButtonClicked() {
    this->close();
}

void MainWindow::startProcessing() {
    QString processName = process->currentText();
    if(processName == "Encrypt") {
        qDebug() << "Encrypting";
        QString passwordStr = password->text();

        QString filePath = fileDrop->getFilePath();
        fileCrypt->encryptFile(filePath, passwordStr);
    }
    if(processName == "Decrypt") {
        qDebug() << "Decrypting";
        QString passwordStr = password->text();

        QString filePath = fileDrop->getFilePath();

        fileCrypt->decryptFile(filePath, passwordStr);
    }
}
