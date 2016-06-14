#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <iostream>


int main(int argc, char *argv[])
{//file for the output, will not be added to Master-branche
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QObject *rootObject = engine.rootObjects().first();
    QObject *obj = rootObject->findChild<QObject*>("list");

    if(obj!=NULL){
        QVariant data = "Orange";
        //add data from cpp
           bool ret = QMetaObject::invokeMethod(obj, "add",
               Q_ARG(QVariant, data));
           if (!ret){
               std::cout<<"Fehler"<<std::endl;
           }
           //delete data from cpp
           QVariant data2=1;
           bool ret2 = QMetaObject::invokeMethod(obj, "remove",
               Q_ARG(QVariant, data2));
           if (!ret2){
               std::cout<<"Fehler"<<std::endl;
           }
    }else{
        std::cout<<"Kein Objekt"<<std::endl;
    }

    return app.exec();
}
