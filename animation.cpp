#include "animation.h"
#include <QSqlQuery> //requetes
#include <QPdfWriter> //creation docs pdf
#include <QPainter> // modif docs pdf
#include <QDesktopServices>
#include <QUrl> //ouverture auto de pdf
animation::animation()
{

}
animation::animation(QString ID_ANIMATION,QString NOM,QString VILLE,QDate DATE_ANIMATION,QString HEURE)
{
    this->ID_ANIMATION=ID_ANIMATION;
    this->NOM=NOM;
    this->DATE_ANIMATION=DATE_ANIMATION;
    this->VILLE=VILLE;
    this->HEURE=HEURE;
}
void animation::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO animations (ID_ANIMATION, NOM, DATE_ANIMATION, VILLE, HEURE) "
                  "VALUES (:id, :nom, :date, :heure, :participants)");
    query.bindValue(":id", ID_ANIMATION); //assigne des valeurs pour eviter les injection sql
    query.bindValue(":nom", NOM);
    query.bindValue(":date", DATE_ANIMATION);
    query.bindValue(":heure", VILLE);
    query.bindValue(":participants", HEURE);
    query.exec();
}

QSqlQueryModel * animation::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("select * from animations");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_ANIMATION")); //comme un tableau
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_ANIMATION"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("VILLE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("HEURE"));
    return model;
}
void animation::supprimer(QString id)
{
        QSqlQuery query;//executer la requete
        query.prepare("delete from animations where ID_ANIMATION = :ID_ANIMATION");
        query.bindValue(":ID_ANIMATION", id);
        query.exec();
}
void animation::modifier()
{
    QSqlQuery query;
          query.prepare("update  animations set  NOM=:Nom, DATE_ANIMATION=:date,VILLE=:ville,HEURE=:heure where(ID_ANIMATION=:id)");
          query.bindValue(":id", ID_ANIMATION);
          query.bindValue(":Nom", NOM);
          query.bindValue(":ville", VILLE);
          query.bindValue(":date", DATE_ANIMATION);
          query.bindValue(":heure", HEURE);
          query.exec();
}
QSqlQueryModel * animation::tri()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("select * from animations ORDER BY DATE_ANIMATION ASC");//DESC or ASC
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_ANIMATION"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_ANIMATION"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("VILLE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("HEURE"));
    return model;
}
QSqlQueryModel * animation::rechercher(QString Nom)
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("select * from animations WHERE NOM like '%"+Nom+"%'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_ANIMATION"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_ANIMATION"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("VILLE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("HEURE"));
    return model;
}
void animation::exporter()
{
    QPdfWriter pdf("C:/Users/Admin/Desktop/projet/animation.pdf");

           QPainter painter(&pdf);
           int i = 4100;
          const QImage image("C:/Users/Admin/Desktop/logo.png");
                       const QPoint imageCoordinates(155,0);
                       int width1 = 2000;
                       int height1 = 2000;
                       QImage img=image.scaled(width1,height1);
                       painter.drawImage(imageCoordinates, img );

                  QColor dateColor(0x4a5bcf);
                  painter.setPen(dateColor);

                  painter.setFont(QFont("Montserrat SemiBold", 11));
                  QDate cd = QDate::currentDate();
                  painter.drawText(7700,250,cd.toString("Ariana, El Ghazela"));
                  painter.drawText(8100,500,cd.toString("dd/MM/yyyy"));

                  QColor titleColor(0x341763);
                  painter.setPen(titleColor);
                  painter.setFont(QFont("Montserrat SemiBold", 25));

                  painter.drawText(3000,2700,"Liste des ANIMATIONS");

                  painter.setPen(Qt::black);
                  painter.setFont(QFont("Time New Roman", 15));
                  //painter.drawRect(100,100,9400,2500);
                  painter.drawRect(100,3300,9400,500);

                  painter.setFont(QFont("Montserrat SemiBold", 10));
                              painter.drawText(300,3600,"Nom");
                              painter.drawText(2000,3600,"VILLE");
                              painter.drawText(3000,3600,"heure");

                  painter.setFont(QFont("Montserrat", 10));
                  painter.drawRect(100,3300,9400,9000);
                    QDate d=QDate::currentDate();
                  QSqlQuery query;
                  query.prepare("SELECT * FROM animations WHERE date_animation = :today");//exportation date aujourd'hui
                  query.bindValue(":today", d);
                  if (query.exec()) {
                  int y=4300;
                  while (query.next())
                  {
                      painter.drawLine(100,y,9490,y);
                      y+=500;
                          painter.drawText(300,i,query.value(1).toString());
                          painter.drawText(2000,i,query.value(2).toString());
                          painter.drawText(3000,i,query.value(4).toString());
                     i = i + 500;
                  }
                  QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/Admin/Desktop/projet/animation.pdf"));
                  }
}
