#include "olympiad.h"

Olympiad::Olympiad() {}

void OlympiadFromCSV(const std::string &filename, std::vector<Olympiad> &dati)
{
    std::ifstream fin(filename);
    char sep = ',';
    QMessageBox msgBox;

    if (fin.good()) {
        dati.clear();
        qDebug() << "File aperto correttamente.";
        std::string labels, row, token;
        std::getline(fin, labels);
        while (std::getline(fin, row)) {
            Olympiad a;
            std::stringstream ss(row);

            QStringList campi = QString::fromStdString(row).split(',');
            qDebug() << campi; // debug code

            std::getline(ss, a.name, sep);
            std::getline(ss, a.familyname, sep);
            std::getline(ss, a.country, sep);
            std::getline(ss, token, sep);
            a.age = stoi(token);
            std::getline(ss, a.sex, sep);
            std::getline(ss, a.sport, sep);
            std::getline(ss, a.type_of_medal, sep);
            std::getline(ss, a.date);
            dati.push_back(a);
        }

        msgBox.setText("File " + QString::fromStdString(filename) + " opened correctly");
        msgBox.exec();
        fin.close();

    } else {
        fin.close();
        qDebug() << "Errore nell'apertura del file...";
        msgBox.setText("ERR: file not valid");
        msgBox.exec();
    }
}

std::string Olympiad::descrizione() const
{
    // restituisce una stringa con tutti gli elementi di una singola istanza
    return this->name + ", " + this->familyname + ", " + this->country + ", "
           + std::to_string(this->age) + ", " + this->sex + ", " + this->sport + ", "
           + this->type_of_medal + ", " + this->date + "\n";
}

std::string Olympiad::getName() const
{
    return name;
}

std::string Olympiad::getFamilyname() const
{
    return familyname;
}

short Olympiad::getAge() const
{
    return age;
}

std::string Olympiad::getSex() const
{
    return sex;
}

std::string Olympiad::getType_of_medal() const
{
    return type_of_medal;
}

std::string Olympiad::getDate() const
{
    return date;
}

std::string Olympiad::getCountry() const
{
    return country;
}
