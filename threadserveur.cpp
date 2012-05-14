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
    codeServeur=0;
    codeClient="0";
    socket.setSocketDescriptor(m_socketDescriptor);
    socket.waitForConnected();
    socket.waitForReadyRead();
        baReception=socket.read(socket.bytesAvailable());
        QString strReception(baReception);
        str=strReception.split(';');
        if(str.at(0)=="0")
        {
            emit(siRecoieConnection(str.at(1)));
            socket.write("#");
        }
        else
        {
            socket.waitForBytesWritten();
        }

    do
    {

        if(socket.waitForReadyRead(1000))
        {
            baReception=socket.read(socket.bytesAvailable());
            strReception=baReception;
            str=strReception.split(';');
            codeClient=str.at(0);
            if(codeClient=="5")
            {
                emit(siTacheTerminee(str.at(1)));
            }
            codeClient="0";
        }
        else
        {
            if(codeServeur!=0)
            {

            }
        }
        //Renvoi des tâches
        socket.write(baTaches);
        socket.waitForBytesWritten();

    }while(str.at(0)!="9");

    emit(siTermineConnection(str[1]));
    socket.waitForDisconnected();
    socket.close();
}

void ThreadServeur::slNouvelleTache(QStringList qsl)
{
    baTaches=0;
    baTaches.append(2);
    baTaches.append(";");
    for(int i=0;i<qsl.size();i++)
    {
        baTaches.append(qsl.at(i));
        baTaches.append(";");
    }
}
