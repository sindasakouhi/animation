#include "kanban.h"
#include <QLineEdit>

Kanban::Kanban(QWidget *parent) : QWidget(parent) {
    setupUI();
}

void Kanban::setupUI() {
    // Create List Widgets
    todoList = new QListWidget(this);
    inProgressList = new QListWidget(this);
    doneList = new QListWidget(this);


    QListWidget *lists[] = {todoList, inProgressList, doneList};
      for (QListWidget *list : lists) {
          list->setDragEnabled(true);
          list->setAcceptDrops(true);
          list->setDropIndicatorShown(true);
          list->setDefaultDropAction(Qt::MoveAction); // Use move action

    }
    // Create Buttons (Optional)
    QPushButton *addTodo = new QPushButton("Add Task to To Do", this);

    // Layouts
    QVBoxLayout *todoLayout = new QVBoxLayout();
        todoLayout->addWidget(todoList);
        todoLayout->addWidget(newTaskEdit = new QLineEdit(this));
        todoLayout->addWidget(addTodo);

        QVBoxLayout *inProgressLayout = new QVBoxLayout();
        inProgressLayout->addWidget(inProgressList);

        QVBoxLayout *doneLayout = new QVBoxLayout();
        doneLayout->addWidget(doneList);

        QHBoxLayout *mainLayout = new QHBoxLayout(this);
        mainLayout->addLayout(todoLayout);
        mainLayout->addLayout(inProgressLayout);
        mainLayout->addLayout(doneLayout);

        setLayout(mainLayout);

    connect(addTodo, &QPushButton::clicked, this, &Kanban::addNewTask);

    // Sample data
    todoList->addItem("TO-DO-List");
    inProgressList->addItem("IN-PROGRESS");
    doneList->addItem("DONE");

}
void Kanban::addNewTask() {
    QString newTask = newTaskEdit->text();
      if (!newTask.isEmpty()) {
          todoList->addItem(newTask);
          newTaskEdit->clear();
      }
}

