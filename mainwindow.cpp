#include "mainwindow.h"
#include <QFileDialog>
#include "olympiad.h"
#include "ui_mainwindow.h"
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

QString fileName;
std::vector<Olympiad> array;

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
}

void MainWindow::on_pushButton_2_clicked()
{
    if (array.size() == 0) {
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
        std::map<std::string, short> medaglie_per_nazione;
        for (auto el : array) {
        }
    }
}
