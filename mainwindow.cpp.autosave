#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "animation.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QtCharts>
#include "kanban.h"
#include <QMediaPlayer>      // For playing media
#include <QVideoWidget>      // For displaying video
#include <QDir>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   Kanban *kanban = new Kanban(this);

            ui->stackedWidget->addWidget(kanban);

            ui->stackedWidget->setCurrentIndex(0); // Initially show the first page

            setCentralWidget(ui->stackedWidget);//configure elements dinterface
}

MainWindow::~MainWindow()
{
    delete ui; //liberation memoire
}


void MainWindow::on_pushButton_15_clicked()
{
    QString ID = ui->lineEdit->text();
    int id = ui->lineEdit->text().toInt();
    QString NOM = ui->lineEdit_2->text();
    QString VILLE = ui->lineEdit_4->text();
    QDate date = ui->dateEdit->date();
    QString HEURE = ui->lineEdit_5->text();
    QRegularExpression regex("^[A-Za-z]+$");
    QRegularExpression reg("^([0-9]{2}):([0-9]{2})$");
    if(ID=="" || NOM=="" || VILLE=="" || HEURE=="")
    {
         QMessageBox::critical(this, "erreur", "les champs sont vides");
    }
    else{
        if (regex.match(NOM).hasMatch())
        {
            if(id>9999999 || id<0)
            {
                QMessageBox::critical(this, "erreur", "l'e nom doit etre uniquement 'id ne doit pas passez le nombre 9999999 ");
            }
            else{
                if (reg.match(HEURE).hasMatch())
                {
                    animation a(ID,NOM,VILLE,date,HEURE);
                    a.ajouter();
                    ui->tableView->setModel(a.afficher());}
                else{
                     QMessageBox::warning(nullptr, "Invalid Input", "Please enter the time in the format xx:xx.");
                }
                }


            }

        else
            QMessageBox::critical(this, "erreur", "le nom doit etre uniquement ");
    }
}

void MainWindow::on_pushButton_16_clicked()
{
    QString ID = ui->lineEdit->text();
    animation a;
    a.supprimer(ID);
    ui->tableView->setModel(a.afficher());
}

void MainWindow::on_pushButton_17_clicked()
{
    QString ID = ui->lineEdit->text();
    QString NOM = ui->lineEdit_2->text();
    QString VILLE = ui->lineEdit_4->text();
    QDate date = ui->dateEdit->date();
    QString HEURE = ui->lineEdit_5->text();
    animation a(ID,NOM,VILLE,date,HEURE);
    a.modifier();
    ui->tableView->setModel(a.afficher());
}

void MainWindow::on_pushButton_18_clicked()
{
    animation a;
    ui->tableView->setModel(a.tri());
}



void MainWindow::on_pushButton_10_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    QSqlQuery query;
    query.exec("SELECT VILLE, COUNT(*) FROM ANIMATIONS GROUP BY VILLE");

    QtCharts::QPieSeries *series = new QtCharts::QPieSeries();//creer le diagramme
    while (query.next()) {
        QString type = query.value(0).toString(); // Récupère le nom de la ville
        int count = query.value(1).toInt(); //Récupère le nombre d'animations pour cette ville
        QtCharts::QPieSlice *slice = new QtCharts::QPieSlice(type, count); //Crée un segment avec le nom de la ville et le nombre d'animations
        series->append(slice); //Ajoute le segment à la série
    }

    QtCharts::QChart *chart = new QtCharts::QChart();//qchart affiche graphique
    chart->addSeries(series);
    chart->setTitle("Statistics based on ANIMATIONS VILLE");//titre
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);//animation

    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setParent(ui->tableView_2);
    chartView->resize(ui->tableView_2->size());
    chartView->show();
}

void MainWindow::on_lineEdit_3_textChanged(const QString &arg1)
{
    animation a;
    ui->tableView->setModel(a.rechercher(arg1));
}

void MainWindow::on_pushButton_11_clicked()
{
    animation a;
    a.exporter();
}





void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);//afficher 2eme page
    QPushButton *returnButton = new QPushButton("Back", this);

        // Get the size of the current widget (page 2)
        QWidget *page = ui->stackedWidget->widget(2);
        QSize pageSize = page->size();

        // Set the button's size
        int buttonWidth = 100;
        int buttonHeight = 30;

        // Position the button at the bottom center
        int x = (pageSize.width() - buttonWidth) / 2;  // Center horizontally
        int y = pageSize.height() - buttonHeight - 20; // 20px margin from the bottom
        returnButton->setGeometry(x, y, buttonWidth, buttonHeight);

        // Add the button to page 2
        returnButton->setParent(page);

        // Connect the button's clicked signal to navigate back to index 0
        connect(returnButton, &QPushButton::clicked, this, [=]() {
            ui->stackedWidget->setCurrentIndex(0); // Navigate back to the first page
        });

        // Make sure the button is visible
        returnButton->show();
}

void MainWindow::on_pushButton_4_clicked()
{

    QString videoPath = QFileDialog::getOpenFileName(this, tr("Choose Video"), QDir::currentPath(), tr("Videos (*.mp4 *.avi *.mov *.mkv)"));
    if (videoPath.isEmpty()) {
        return;
    }

    // Read the video file
    QFile file(videoPath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open video file:" << videoPath;
        return;
    }
    QString animationID = ui->lineEdit->text().trimmed();
    QByteArray videoData = file.readAll();
    file.close();





        QString destinationPath = "C:/Users/Admin/Documents/build-projet-Desktop_Qt_5_9_9_MinGW_32bit-Debug/" + animationID + ".mp4";
        QFile destinationFile(destinationPath);
        if (!destinationFile.open(QIODevice::WriteOnly)) {
            qDebug() << "Failed to open destination file for writing:" << destinationPath;
            return;
        }
        // Write video data to the destination file
        qint64 bytesWritten = destinationFile.write(videoData);
        if (bytesWritten == -1) {
            qDebug() << "Failed to write video data to the destination file.";
            return;
        }
        destinationFile.close();
        if (!insertVideoIntoDatabase(videoData, animationID)) {
            qDebug() << "Failed to insert video into database.";
            return;
        }

        qDebug() << "Video inserted into database successfully.";
        qDebug() << "Video saved successfully to:" << destinationPath;



}
bool MainWindow::insertVideoIntoDatabase(const QByteArray& videoData, QString ID) {
    // Prepare SQL query
    QSqlQuery query;
    query.prepare("UPDATE animations SET video = :video WHERE id_animation = :id");
    query.bindValue(":video", videoData);
    query.bindValue(":id", ID);
    // Execute the query
    if (!query.exec()) {
        qDebug() << "Failed to insert video into database:";
        return false;
    }

    return true;
}

void MainWindow::alerte()// animations sont prévues aujourd’hui et envoie une alerte.
{
    QDate todayDate = QDate::currentDate();//recupere date


       QSqlQuery query;//Prépare une requête SQL pour récupérer les noms des animations ayant lieu aujourd'hui
       query.prepare("SELECT nom FROM animations WHERE date_animation = :today");
       query.bindValue(":today", todayDate);

       QStringList animationNames;

       if (query.exec()) {
           // Check if any records match today's date
           while (query.next()) {
               QString nom = query.value("nom").toString();
               animationNames.append(nom);
           }

           if (!animationNames.isEmpty()) {
               // Join all names into one string separated by newline
               QString message = "The following animations are set for today:\n";
               message += animationNames.join("\n");
               QMessageBox::information(nullptr, "Animations for Today", message);
           } else {
               QMessageBox::information(nullptr, "No Animations for Today", "There are no animations set for today.");
           }
       } else {
           qDebug() << "Query failed:" ;
       }

}

void MainWindow::on_pushButton_19_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::switchpage()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_5_clicked()
{
    QString animationID = ui->lineEdit->text().trimmed();

        QString destinationPath = "C:/Users/Admin/Documents/build-projet-Desktop_Qt_5_9_9_MinGW_32bit-Debug/" + animationID + ".mp4";

        QMediaPlayer* player = new QMediaPlayer();
        QVideoWidget* video = new QVideoWidget();
        video->setGeometry(20, 20, 640, 480);

        // Add a play/pause button
        QPushButton* playPauseButton = new QPushButton("Pause");
        QVBoxLayout* layout = new QVBoxLayout();
        layout->addWidget(video);
        layout->addWidget(playPauseButton);

        QWidget* videoWindow = new QWidget();
        videoWindow->setLayout(layout);
        videoWindow->resize(660, 540);
        videoWindow->show();

        player->setVideoOutput(video);
        player->setMedia(QUrl::fromLocalFile(destinationPath));
        player->play();

        // Connect button to toggle play/pause
        QObject::connect(playPauseButton, &QPushButton::clicked, [player, playPauseButton]() {
            if (player->state() == QMediaPlayer::PlayingState) {
                player->pause();
                playPauseButton->setText("Play");
            } else {
                player->play();
                playPauseButton->setText("Pause");
            }
        });

        // Stop player when the video widget is closed
        QObject::connect(videoWindow, &QWidget::destroyed, [player]() {
            player->stop();
            player->deleteLater(); // Ensure proper cleanup
        });
}
