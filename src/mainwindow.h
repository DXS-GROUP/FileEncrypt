#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPoint>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QGridLayout>
#include <QPushButton>
#include <encrypt.cpp>
#include <QComboBox>

#include "drop_file.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QLabel *label;

protected:
    void mousePressEvent(QMouseEvent *event) override
    {
        if (event->button() == Qt::LeftButton) {
            m_dragPosition = event->globalPos() - frameGeometry().topLeft();
            event->accept();
        } else {
            QMainWindow::mousePressEvent(event);
        }
    }

    void mouseMoveEvent(QMouseEvent *event) override
    {
        if (event->buttons() & Qt::LeftButton) {
            move(event->globalPos() - m_dragPosition);
            event->accept();
        } else {
            QMainWindow::mouseMoveEvent(event);
        }
    }


private slots:
    void closeButtonClicked();
    void startProcessing();

private:
    QPoint m_dragPosition;

    FileDropWidget *fileDrop;

    QPushButton *closeBtn;
    QPushButton *startEncrypt;

    QLineEdit *password;

    QComboBox *process;

    QWidget *centralWidget;
    QGridLayout *mainLayout;

    FileCrypt *fileCrypt;

    MainWindow *mainWindow;
};
#endif // MAINWINDOW_H
