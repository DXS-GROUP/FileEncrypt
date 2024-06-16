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
    void dropEvent(QDropEvent *event) override
    {
        QString filePath = event->mimeData()->text();
        QFileInfo fileInfo(filePath);
        QString fileSuffix = fileInfo.suffix();

        qDebug() << "[Dropped file]:" << filePath;
    }
};

#endif // DROP_FILE_H
