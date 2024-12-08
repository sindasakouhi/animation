#ifndef KANBAN_H
#define KANBAN_H

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "mainwindow.h"

class Kanban : public QWidget {
    Q_OBJECT

public:
    Kanban(QWidget *parent = nullptr);
    void switchToPage0();
private:
    QListWidget *todoList;
    QListWidget *inProgressList;
    QListWidget *doneList;
    QLineEdit *newTaskEdit;
    void addNewTask();
    void addNewTas();
    void setupUI();


};

#endif
