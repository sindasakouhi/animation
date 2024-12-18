#include "mainwindow.h"
#include "connection.h"
#include <QApplication>
#include <QMessageBox>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Connection c;
    bool test=c.createconnect();
    if(test)
    {w.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    w.alerte();
    }
    else

        QMessageBox::critical(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection non succesful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


    return a.exec();
}
