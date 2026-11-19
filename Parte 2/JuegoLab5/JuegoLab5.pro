QT += widgets
QT += multimedia

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    caja.cpp \
    canongrafico.cpp \
    colisionproyectil.cpp \
    juego.cpp \
    main.cpp \
    mainwindow.cpp \
    obstaculo.cpp \
    obstaculografico.cpp \
    particula.cpp \
    proyectil.cpp \
    proyectilgrafico.cpp

HEADERS += \
    caja.h \
    canongrafico.h \
    colisionproyectil.h \
    juego.h \
    mainwindow.h \
    obstaculo.h \
    obstaculografico.h \
    particula.h \
    proyectil.h \
    proyectilgrafico.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    archivos.qrc
