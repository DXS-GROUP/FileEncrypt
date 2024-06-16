#ifndef DOWNLOAD_FILE_H
#define DOWNLOAD_FILE_H

#include <QEvent>
#include <QFileDialog>
#include <QLabel>
#include <QMouseEvent>
#include <QDebug>

class SaveFileDialogButton : public QLabel {
    Q_OBJECT

public:
    SaveFileDialogButton(const QString &text, QWidget *parent = nullptr)
        : QLabel(text, parent) {}

protected:
    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            QString filePath = QFileDialog::getSaveFileName(this, "Сохранить файл", "", "Все файлы (*.*)");
            if (!filePath.isEmpty()) {
                // Здесь можно обработать filePath
                qDebug() << "Selected file path:" << filePath;
            }
        }
    }
private:
};


#endif // DOWNLOAD_FILE_H
