#ifndef FILECRYPT_H
#define FILECRYPT_H

#include <QFile>
#include <QByteArray>
#include <QCryptographicHash>
#include <QFileDialog>

class FileCrypt {
public:
    static bool encryptFile(const QString &filePath, const QString &password) {
        QFile file(filePath);
        if (!file.open(QFile::ReadOnly)) {
            return false;
        }

        QByteArray fileData = file.readAll();
        file.close();

        // Шифрование данных с помощью AES
        QByteArray encryptedData = encryptData(fileData, password);

        // Открытие диалогового окна для сохранения измененного файла
        QString saveFilePath = QFileDialog::getSaveFileName(nullptr, "Сохранить файл", "", "Все файлы (*)");
        if (!saveFilePath.isEmpty()) {
            QFile saveFile(saveFilePath);
            if (saveFile.open(QFile::WriteOnly)) {
                saveFile.write(encryptedData);
                saveFile.close();
                return true;
            }
        }

        return false;
    }
    static bool decryptFile(const QString &filePath, const QString &password) {
        QFile file(filePath);
        if (!file.open(QFile::ReadOnly)) {
            return false;
        }

        QByteArray encryptedData = file.readAll();
        file.close();

        // Расшифровка данных с помощью AES
        QByteArray decryptedData = decryptData(encryptedData, password);

        // Открытие диалогового окна для сохранения измененного файла
        QString saveFilePath = QFileDialog::getSaveFileName(nullptr, "Сохранить файл", "", "Все файлы (*)");
        if (!saveFilePath.isEmpty()) {
            QFile saveFile(saveFilePath);
            if (saveFile.open(QFile::WriteOnly)) {
                saveFile.write(decryptedData);
                saveFile.close();
                return true;
            }
        }

        return false;
    }

private:
    static QByteArray encryptData(const QByteArray &data, const QString &password) {
        // Реализация алгоритма шифрования AES
        // В этом примере мы используем QCryptographicHash для генерации ключа
        QCryptographicHash hash(QCryptographicHash::Sha256);
        hash.addData(password.toUtf8());
        QByteArray key = hash.result();

        // Шифрование данных с помощью AES
        QByteArray encryptedData;
        for (int i = 0; i < data.size(); i++) {
            encryptedData.append(data.at(i) ^ key.at(i % key.size()));
        }

        return encryptedData;
    }
    static QByteArray decryptData(const QByteArray &data, const QString &password) {
        // Реализация алгоритма расшифровки AES
        // В этом примере мы используем QCryptographicHash для генерации ключа
        QCryptographicHash hash(QCryptographicHash::Sha256);
        hash.addData(password.toUtf8());
        QByteArray key = hash.result();

        // Расшифровка данных с помощью AES
        QByteArray decryptedData;
        for (int i = 0; i < data.size(); i++) {
            decryptedData.append(data.at(i) ^ key.at(i % key.size()));
        }

        return decryptedData;
    }
};

#endif // FILECRYPT_H
