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
    socket.setSocketDescriptor(m_socketDescriptor);
    socket.waitForConnected();
    socket.waitForReadyRead();
    baReception=socket.read(socket.bytesAvailable());
    emit(siRecoieConnection(baReception));
    //socket.close();
}
