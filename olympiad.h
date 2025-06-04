#ifndef OLYMPIAD_H
#define OLYMPIAD_H
#include <QMessageBox>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class Olympiad
{
private:
    std::string name, familyname, country;
    short age;
    std::string sex, sport, type_of_medal, date;

public:
    Olympiad();
    friend void OlympiadFromCSV(const std::string &filename, std::vector<Olympiad> &dati);
    std::string descrizione() const;
    std::string getName() const;
    std::string getFamilyname() const;
    short getAge() const;
    std::string getSex() const;
    std::string getType_of_medal() const;
    std::string getDate() const;
    std::string getCountry() const;
};

void OlympiadFromCSV(const std::string &filename, std::vector<Olympiad> &dati);

#endif // OLYMPIAD_H
