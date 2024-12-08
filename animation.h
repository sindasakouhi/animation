#ifndef ANIMATION_H
#define ANIMATION_H
#include <QString>
#include <QDate>
#include <QSqlQueryModel> //afficher les resultat d'une requete
class animation
{
    QString ID_ANIMATION;
    QString NOM;
    QString VILLE;
    QDate DATE_ANIMATION;
    QString HEURE;
public:
    animation();
    animation(QString ID_ANIMATION,
    QString NOM,
    QString VILLE,
    QDate DATE_ANIMATION,
    QString HEURE);
    void ajouter();
    QSqlQueryModel *afficher();
    void supprimer(QString ID);
    void modifier();
    QSqlQueryModel *tri();
    QSqlQueryModel *rechercher(QString Nom);
    void exporter();
};

#endif // ANIMATION_H
