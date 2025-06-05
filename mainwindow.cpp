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
short nuove_aggiunte = 0;
std::string path;

void MainWindow::open_file()
{
    fileName = QFileDialog::getOpenFileName(this,
                                            tr("seleziona il file da aprire"),
                                            "data/",
                                            tr("CSV Files (*.csv)"));

    path = fileName.toLocal8Bit().constData();
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

        float media;
        if (cont) {
            media = somma / cont;
            log += QString::number(media) + " anni.";
        } else {
            log = "Non ci sono atlete che hanno vinto un oro.";
        }

        this->ui->textOutput->setText(log);
    }
}

void MainWindow::on_pushButton_7_clicked()
{
    if (!fileName.toStdString().size()) {
        QMessageBox err;
        err.setText("ERR: No File Selected");
        err.exec();
    } else {
        bool valid = this->ui->lineName->text().size() && this->ui->line_familyname->text().size()
                     && this->ui->line_country->text().size() && this->ui->line_sport->text().size()
                     && this->ui->spin_age->text().size() && this->ui->combo_sex
                     && this->ui->combo_typeofmedal;

        if (valid) {
            QString log = "Aggiunti i seguenti dati: \n\n";
            Olympiad o;
            o.setName(this->ui->lineName->text().toStdString());
            o.setFamilyname(this->ui->line_familyname->text().toStdString());
            o.setCountry(this->ui->line_country->text().toStdString());
            o.setAge(this->ui->spin_age->value());
            o.setSex(this->ui->combo_sex->currentText().toStdString());
            o.setSport(this->ui->line_sport->text().toStdString());
            o.setType_of_medal(this->ui->combo_typeofmedal->currentText().toStdString());
            o.setDate(this->ui->dateEdit->text().toStdString());
            qDebug() << o.getDate();
            array.push_back(o);
            nuove_aggiunte++;
            log += QString::fromStdString(o.descrizione());

            {
                this->ui->lineName->clear();
                this->ui->line_familyname->clear();
                this->ui->line_country->clear();
                this->ui->line_sport->clear();
                this->ui->combo_sex->clear();
                this->ui->combo_typeofmedal->clear();
                this->ui->spin_age->clear();
            }

            this->ui->textOutput->setText(log);

        } else {
            QMessageBox err;
            err.setText("ERR: Invalid Input");
            err.exec();
        }
    }
}

void MainWindow::on_pushButton_8_clicked()
{
    if (!fileName.toStdString().size()) {
        QMessageBox err;
        err.setText("ERR: No File Selected");
        err.exec();
    } else if (!nuove_aggiunte) {
        QMessageBox err;
        err.setText("ERR: No additional data was given");
        err.exec();
    } else {
        QString log = "Nuovi dati salvati correttamente. ";
        std::ofstream fout(path, std::ios::app);
        for (int i = array.size() - nuove_aggiunte - 1; i < array.size(); ++i) {
            fout << array[i].descrizione();
        }
        this->ui->textOutput->setText(log);
    }
}
