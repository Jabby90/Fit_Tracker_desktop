#pragma once

#ifndef INSERTNEWFOODDIALOG_H
#define INSERTNEWFOODDIALOG_H
#include <QDialog>
#include <qboxlayout.h>
#include <string_view>
#include <string>


class InsertNewFoodDialog : public QDialog
{
    Q_OBJECT
public:

    InsertNewFoodDialog(QWidget* parent = 0);
    //~InserNewFoodDialog();

    void setName(std::string_view name_in) {name = name_in;}
    void setKcal(double kcal_in){kcal = kcal_in;}
    void setProteins(double proteins_in){proteins = proteins_in;}
    void setFats(double fats_in){fats = fats_in;}
    void setCarbohydrates(double carbohydrates_in){carbohydrates = carbohydrates_in;}

    std::string_view getName() const {return name;}
    double getKcal() const {return kcal;}
    double getProteins() const {return proteins;}
    double getFats() const {return fats;}
    double getCarbohydrates() const {return carbohydrates;}


private:
    QVBoxLayout* layout_main;

    std::string name{};
    double kcal{};
    double proteins{};
    double fats{};
    double carbohydrates{};


    void accept() override;
    bool verifyData();
    bool verifyName();
    bool verifyKcal();
    bool verifyProteins();
    bool verifyFats();
    bool verifyCarbohydrates();

public slots:
    //QDialog::DialogCode acceptData();
};

#endif // INSERTNEWFOODDIALOG_H
