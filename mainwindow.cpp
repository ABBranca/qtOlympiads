#include "mainwindow.h"
#include <QFileDialog>
#include "olympiad.h"
#include "ui_mainwindow.h"
#include <algorithm>
#include <map>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionOpen_File, SIGNAL(triggered()), this, SLOT(open_file()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Dichiarazione variabili globali
QString fileName;
std::vector<Olympiad> array;
std::map<std::string, short> medaglie_per_nazione;

void MainWindow::open_file()
{
    fileName = QFileDialog::getOpenFileName(this,
                                            tr("seleziona il file da aprire"),
                                            "data/",
                                            tr("CSV Files (*.csv)"));

    std::string path = fileName.toLocal8Bit().constData();
    qDebug() << path;
    OlympiadFromCSV(path, array);
}

void MainWindow::on_pushButton_clicked()
{
    open_file();
    this->ui->textOutput->setText("");
}

void MainWindow::on_pushButton_2_clicked()
{
    if (!fileName.toStdString().size()) {
        QMessageBox err;
        err.setText("ERR: No File Selected");
        err.exec();
    } else {
        // creates an instance of the ordered file dialog window
        QString ordered_file_log;

        std::sort(array.begin(), array.end(), [](Olympiad a, Olympiad b) {
            return a.getName() < b.getName();
        });

        for (auto el : array) {
            ordered_file_log += QString::fromStdString(el.descrizione());
        }
        this->ui->textOutput->setText(ordered_file_log);
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    if (!fileName.toStdString().size()) {
        QMessageBox err;
        err.setText("ERR: No File Selected");
        err.exec();
    } else {
        medaglie_per_nazione.clear();
        QString log = "Il numero di medaglie per nazione: \n\n";
        for (auto el : array) {
            medaglie_per_nazione[el.getCountry()]++;
        }

        for (auto el : medaglie_per_nazione) {
            log += (QString::fromStdString(el.first) + ": " + QString::number(el.second) + "\n");
        }

        this->ui->textOutput->setText(log);
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    if (!fileName.toStdString().size()) {
        QMessageBox err;
        err.setText("ERR: No File Selected");
        err.exec();
    } else {
        QString log = "Le nazioni con almeno 5 medaglie: \n\n";
        medaglie_per_nazione.clear();

        for (auto el : array) {
            medaglie_per_nazione[el.getCountry()]++;
        }

        for (auto el : medaglie_per_nazione) {
            if (el.second >= 5) {
                log += (QString::fromStdString(el.first) + "\n");
            }
        }

        this->ui->textOutput->setText(log);
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    if (!fileName.toStdString().size()) {
        QMessageBox err;
        err.setText("ERR: No File Selected");
        err.exec();
    } else {
        std::map<std::string, short> giorno_medaglie;
        QString log = "Giorno in cui sono state assegnate piu' medaglie:\n\n";

        for (auto el : array) {
            giorno_medaglie[el.getDate()]++;
        }

        short temp = 0;
        std::string temp_s;

        for (auto el : giorno_medaglie) {
            if (el.second > temp) {
                temp_s = el.first;
                temp = el.second;
            }
        }

        log += QString::fromStdString(temp_s);
        this->ui->textOutput->setText(log);
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    if (!fileName.toStdString().size()) {
        QMessageBox err;
        err.setText("ERR: No File Selected");
        err.exec();
    } else {
        QString log = "L'età media delle atlete che hanno vinto un oro è ";
        short somma = 0, cont = 0;

        for (auto el : array) {
            if (el.getSex() != "Female" || el.getType_of_medal() != "Gold")
                continue;
            somma += el.getAge();
            cont++;
        }

        float media = somma / cont;
        log += QString::number(media) + " anni.";
        this->ui->textOutput->setText(log);
    }
}
