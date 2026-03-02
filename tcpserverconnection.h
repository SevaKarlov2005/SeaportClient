#ifndef TCPSERVERCONNECTION_H
#define TCPSERVERCONNECTION_H

#include <QObject>
#include <QTcpSocket>
#include <openssl/evp.h>

class TCPServerConnection : public QObject
{
    Q_OBJECT
private:
    unsigned char key[32];
    unsigned char iv[16];
    EVP_CIPHER_CTX* ctx;
    QTcpSocket socket;
public:
    explicit TCPServerConnection(QObject *parent = nullptr);
    ~TCPServerConnection();
    QString Encryption(QString data);
    QString Decryption(QString data);
    QAbstractSocket::SocketState CheckConnectionState();
    bool Connect(QString ip_adress, int port);
    bool Disconnect();
    bool Send(QString data);
    QString Receive();
signals:
};

#endif // TCPSERVERCONNECTION_H
