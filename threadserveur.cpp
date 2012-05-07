#include "threadserveur.h"

ThreadServeur::ThreadServeur(int Descriptor)
{
    m_socketDescriptor=Descriptor;

    //ip.src==172.16.153.1 or (ip.src==172.16.8.1 and ip.dst==172.16.153.1)
}

void ThreadServeur::run()
{
    QTcpSocket socket;
    QByteArray baReception;
    QStringList str;
    socket.setSocketDescriptor(m_socketDescriptor);
    socket.waitForConnected();
    do
    {
    socket.waitForReadyRead();
    baReception=socket.read(socket.bytesAvailable());
    QString strReception(baReception);
    str=strReception.split(';');
    if(str[0]=="0")
    {
        emit(siRecoieConnection(str[1]));
        socket.write("#");
        socket.waitForBytesWritten();
    }
    }while(str[0]!="9");

    emit(siTermineConnection(str[1]));
    socket.waitForDisconnected();
    socket.close();
}
