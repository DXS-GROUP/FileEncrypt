#include "mainwindow.h"

#include <QObject>
#include <QPushButton>
#include "download_file.h"
#include "drop_file.h"

#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    this->setFixedSize(700, 250);

    fileDrop = new FileDropWidget();
    fileDrop->setPixmap(QPixmap(":/drop.png").scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    fileDownload = new SaveFileDialogButton("");
    fileDownload->setPixmap(QPixmap(":/get.png").scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));

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

    startEncrypt = new QPushButton(">");
    startEncrypt->setFixedSize(210, 210);
    startEncrypt->setStyleSheet("QPushButton {background-color: transparent; border: 0px transparent; font-size: 60px;}");

    centralWidget = new QWidget();
    this->setCentralWidget(centralWidget);

    mainLayout = new QGridLayout;
    centralWidget->setLayout(mainLayout);

    mainLayout->addWidget(closeBtn, 0, 1, 1 , 4, Qt::AlignLeft);
    mainLayout->addWidget(fileDrop, 1, 1, 2, 2, Qt::AlignCenter);
    mainLayout->addWidget(fileDownload, 1, 4, 2, 2, Qt::AlignCenter);
    mainLayout->addWidget(startEncrypt, 1, 3, 1, 1, Qt::AlignCenter);

    connect(closeBtn, SIGNAL(clicked()), this, SLOT(closeButtonClicked()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::closeButtonClicked() {
    this->close();
}
