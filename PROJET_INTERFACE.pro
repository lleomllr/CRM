QT += core gui
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ajoutinteraction.cpp \
    contact.cpp \
    creationcontact.cpp \
    fichecontact.cpp \
    ficheinteraction.cpp \
    gestionbd.cpp \
    gestioncontact.cpp \
    gestioninteraction.cpp \
    gestiontodo.cpp \
    interaction.cpp \
    jsonform.cpp \
    main.cpp \
    mainwindow.cpp \
    modificationcontact.cpp \
    popup.cpp \
    todo.cpp

HEADERS += \
    ajoutinteraction.h \
    contact.h \
    creationcontact.h \
    fichecontact.h \
    ficheinteraction.h \
    gestionbd.h \
    gestioncontact.h \
    gestioninteraction.h \
    gestiontodo.h \
    interaction.h \
    jsonform.h \
    mainwindow.h \
    modificationcontact.h \
    popup.h \
    todo.h

FORMS += \
    ajoutinteraction.ui \
    creationcontact.ui \
    fichecontact.ui \
    ficheinteraction.ui \
    jsonform.ui \
    mainwindow.ui \
    modificationcontact.ui \
    popup.ui



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
