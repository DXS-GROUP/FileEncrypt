#ifndef DROP_FILE_H
#define DROP_FILE_H

#include <QDebug>
#include <QWidget>
#include <QFileInfo>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QString>
#include <QLabel>

class FileDropWidget : public QLabel {
    Q_OBJECT

public:
    FileDropWidget(QLabel *parent = nullptr) : QLabel(parent) {}

protected:
    void dragEnterEvent(QDragEnterEvent *event) override {
        if (event->mimeData()->hasUrls()) {
            event->acceptProposedAction();
        }
    }

    void dropEvent(QDropEvent *event) override {
        const QMimeData *mimeData = event->mimeData();
        if (mimeData->hasUrls()) {
            QList<QUrl> urls = mimeData->urls();
            foreach (const QUrl &url, urls) {
                QString filePath = url.toLocalFile();
                QString fileExtension = QFileInfo(filePath).suffix();

                // Здесь можно обработать filePath и fileExtension
                qDebug() << "File path:" << filePath;
                qDebug() << "File extension:" << fileExtension;
            }
        }
    }
};

#endif // DROP_FILE_H
