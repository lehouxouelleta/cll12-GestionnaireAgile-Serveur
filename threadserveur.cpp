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
    termine=1;
    socket.setSocketDescriptor(m_socketDescriptor);
    socket.waitForConnected();
    socket.waitForReadyRead();
    baReception=socket.read(socket.bytesAvailable());
    QString strReception(baReception);
    str=strReception.split(';');
    if(str.at(0)=="0")
    {
        emit(siRecoieConnection(str.at(1)));
        nomClient=str.at(1);
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
                emit(siTacheTerminee(str.at(1),nomClient));
            }
            codeClient="0";
        }
        else
        {
            //
        }
        //Renvoi des tâches
        //socket.write(baTaches);
        if(socket.state()==QAbstractSocket::UnconnectedState)
        {
            emit(siTermineConnection(nomClient));
            termine=0;
        }
        else
        {
            //socket.waitForBytesWritten(1000);
            if(codeServeur!=0)
            {
                if(codeServeur==8)
                {
                    socket.flush();
                    socket.write("8");
                    socket.waitForBytesWritten();
                    codeServeur=0;
                    socket.waitForReadyRead();
                    baReception=socket.read(socket.bytesAvailable());
                    strReception=baReception;
                    str=strReception.split(';');
                    emit(siFermeture());
                }
            }
        }


    }while(str.at(0)!="9"&&termine);

    if(termine)
    {
        emit(siTermineConnection(str[1]));
    }
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

void ThreadServeur::slDeconnection()
{
    codeServeur=8;
}
