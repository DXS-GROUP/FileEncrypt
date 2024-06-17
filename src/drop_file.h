#include <QLabel>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QFile>
#include <QMimeData>
#include <QTextStream>
#include <QDebug>
#include <QFileInfo>

class FileDropWidget : public QLabel {
    Q_OBJECT

public:
    QString filePath;
    FileDropWidget(QWidget *parent = nullptr) : QLabel(parent) {
        setAcceptDrops(true);
    }
    QString getFilePath() const { return filePath; }
    QString getFileName() const {
        QFileInfo fileInfo(filePath);
        return fileInfo.fileName();
    }

protected:
    void dragEnterEvent(QDragEnterEvent *event) override {
        if (event->mimeData()->hasUrls()) {
            event->acceptProposedAction();
        }
    }

    void dropEvent(QDropEvent *event) override {
        QList<QUrl> urls = event->mimeData()->urls();
        if (!urls.isEmpty()) {
            filePath = urls.first().toLocalFile();
            if (QFile::exists(filePath)) {

                qDebug() << "File path: " << filePath;
            }
        }
    }
};
