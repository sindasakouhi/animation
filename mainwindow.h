#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void alerte();
    void switchpage();
    bool insertVideoIntoDatabase(const QByteArray& videoData, QString ID);
private slots:
    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();



    void on_pushButton_10_clicked();

    void on_lineEdit_3_textChanged(const QString &arg1);

    void on_pushButton_11_clicked();

    /*void on_pushButton_clicked();

    void on_pushButton_2_clicked();*/

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    QStackedWidget *stackedWidget;
        QWidget *page0;
};
#endif // MAINWINDOW_H
