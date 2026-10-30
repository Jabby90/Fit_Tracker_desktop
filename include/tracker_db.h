#pragma once
#ifndef TRACKER_DB_H
#define TRACKER_DB_H

#include <string>
#include <QSqlQueryModel>
#include <QTableView>

#include "sqlite3.h"


class Tracker_DB : public QObject
{
public:
    static Tracker_DB& getInstance();


    sqlite3* getDb() {return source_db;}

    ~Tracker_DB();

    Tracker_DB(const Tracker_DB&) = delete;
    Tracker_DB& operator=(const Tracker_DB&) = delete;

    void runSql(const std::string& data);

    QSqlQueryModel* model_select_food_dic{nullptr};
    QSqlQueryModel* model_select_food_diary{nullptr};

    //инициализаця моделей справочников

    void setupFoodDicModel();
    void setupFoodDiaryModel();

private:
    Tracker_DB(const std::string db_name);

    static Tracker_DB* instance;
    sqlite3* source_db;

    QSqlDatabase db;


    void fillTheDB();//Наполнение пустой БД начальными данными

    void createDbStructure();//DDL-операции при создании БД
    void insertBasicData();//DML-операции при создании БД

    // void select();//тест функции выбора

};

#endif // TRACKER_DB_H
