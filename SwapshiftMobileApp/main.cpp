#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <fstream>
#include <QtSql>
#include <stdlib.h>
#include "shiftreader.h"
#include "structs.h"

using namespace std;

int main(int argc, char *argv[])
{
    //--SQL--
    //RETRIEVE DATABASE PASSWORD
    ifstream fPASS;
    string DB_PASS;

    fPASS.open("C:\\Users\\DannyG\\Desktop\\Projects\\Files\\DB_PASS.txt");

    if(fPASS.good())
        getline(fPASS, DB_PASS);
    else
        qDebug() << "Cannot Open DB_PASS File";
   //---------------------------

    //Create DB connection
    QSqlDatabase sql_db = QSqlDatabase::addDatabase("QMYSQL");

    sql_db.setDatabaseName("swapshift_db");
    sql_db.setHostName("127.0.0.1");
    sql_db.setUserName("root");
    sql_db.setPassword(QString::fromStdString(DB_PASS));

    //Open DB
    if(sql_db.open())
        qDebug() << "Success";
    else
    {
        qDebug() << sql_db.lastError();
    }

    //Shifts
    ShiftReader sr(&sql_db);
    vector<shift> s = sr.get_shifts(4);

    for(int i = 0; i < s.size(); i++)
    {
        qDebug() << s[i].date;
    }

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
