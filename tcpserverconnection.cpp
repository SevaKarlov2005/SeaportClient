#include "tcpserverconnection.h"

#include <QEventLoop>
#include <QTimer>

TCPServerConnection::TCPServerConnection(QObject *parent) : QObject{parent}
{
    // Ключ шифрования и вектор инициализации
    memcpy(this->key, "01234567012345670123456701234567", 32);
    memcpy(this->iv, "0000000000000000", 16);

    // Контекст шифрования
    this->ctx = EVP_CIPHER_CTX_new();
}

TCPServerConnection::~TCPServerConnection()
{
    if (socket.state() != QAbstractSocket::UnconnectedState)
        socket.abort();

    // Удаляем контекст шифрования
    EVP_CIPHER_CTX_free(this->ctx);
}

QString TCPServerConnection::Encryption(QString data)
{
    // Размеры шифрования
    int old_length = data.toUtf8().length();
    int new_length;
    int converted = 0;
    int tmp = 0;

    if (old_length % 16 == 0)
        new_length = old_length + 16;
    else
        new_length = old_length + (16 - (old_length) % 16) % 16;

    unsigned char* new_message = new unsigned char[new_length];

    // Шифрование сообщения
    EVP_EncryptInit_ex(this->ctx, EVP_aes_256_cbc(), NULL, this->key, this->iv);
    EVP_EncryptUpdate(this->ctx, new_message, &converted, (unsigned char*)data.toUtf8().data(), old_length);
    EVP_EncryptFinal_ex(this->ctx, new_message + converted, &tmp);

    QString result = QByteArray::fromRawData((char*)new_message, converted + tmp).toBase64();

    // Освобождение вспомогательной памяти
    delete[] new_message;

    return result;
}

QString TCPServerConnection::Decryption(QString data)
{
    // Размеры шифрования
    int old_length = QByteArray::fromBase64(data.toUtf8()).length();
    int converted = 0;
    int tmp = 0;

    unsigned char* new_message = new unsigned char[old_length + 16];

    // Расшифровка сообщения
    EVP_DecryptInit_ex(this->ctx, EVP_aes_256_cbc(), NULL, this->key, this->iv);
    EVP_DecryptUpdate(this->ctx, new_message, &converted, (unsigned char*)QByteArray::fromBase64(data.toUtf8()).data(), old_length);
    EVP_DecryptFinal_ex(this->ctx, new_message + converted, &tmp);

    QString result = QString::fromUtf8((char*)new_message, converted + tmp);

    // Освобождение вспомогательной памяти
    delete[] new_message;

    return result;
}

QAbstractSocket::SocketState TCPServerConnection::CheckConnectionState()
{
    // Получение статуса соединения
    return this->socket.state();
}

bool TCPServerConnection::Connect(QString ip_adress, int port)
{
    if (socket.state() != QAbstractSocket::UnconnectedState)
        socket.abort();   // принудительно закрывает и сбрасывает

    this->socket.connectToHost(ip_adress, port);

    if (this->socket.waitForConnected(3000))
        return true;
    else
        return false;
}

bool TCPServerConnection::Disconnect()
{
    // Отключаем сокет
    this->socket.disconnectFromHost();

    // Ждём отключения
    if (this->socket.waitForDisconnected(3000))
        return true;
    else
        return false;
}

bool TCPServerConnection::Send(QString data)
{
    // Шифруем сообщение
    data = Encryption(data);

    // Добавляем заголовок
    int length = data.toUtf8().length();
    QByteArray bytes = (QString::number(length).rightJustified(7, '0') + data).toUtf8();

    if (this->socket.write(bytes) == -1)
        return false;

    // Ждём записи
    while (this->socket.bytesToWrite() > 0)
    {
        QEventLoop loop;
        QTimer::singleShot(100, [&loop]() { loop.quit(); });
        loop.exec();
    }

    return true;
}

QString TCPServerConnection::Receive()
{
    QByteArray header;

    // Читаем заголовок
    while (header.size() < 7)
    {
        header += this->socket.read(7 - header.size());

        if (header.size() < 7)
        {
            QEventLoop loop;
            QTimer::singleShot(100, [&loop]() { loop.quit(); });
            loop.exec();
        }
    }

    int length = header.trimmed().toInt();
    QByteArray bytes;

    // Ждём чтения до конца
    while (bytes.size() < length)
    {
        bytes += this->socket.read(length - bytes.size());

        if (bytes.size() < length)
        {
            QEventLoop loop;
            QTimer::singleShot(100, [&loop]() { loop.quit(); });
            loop.exec();
        }
    }

    return Decryption(QString::fromUtf8(bytes));
}
