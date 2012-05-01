#-------------------------------------------------
#
# Project created by QtCreator 2012-05-01T14:07:41
#
#-------------------------------------------------

QT       += core gui
QT       += network

TARGET = GestionnaireAgile-Serveur
TEMPLATE = app


SOURCES += main.cpp\
        serveur.cpp \
    tcpserveur.cpp \
    threadserveur.cpp

HEADERS  += serveur.h \
    tcpserveur.h \
    threadserveur.h

FORMS    += serveur.ui
