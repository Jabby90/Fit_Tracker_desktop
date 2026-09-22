#pragma once
#ifndef TRACKER_DB_H
#define TRACKER_DB_H

#include <string>

#include "sqlite3.h"


class Tracker_DB
{
public:
    static Tracker_DB& getInstance();


    sqlite3* getDb() {return source_db;}

    ~Tracker_DB() {if (source_db) {sqlite3_close(source_db);}}

    Tracker_DB(const Tracker_DB&) = delete;
    Tracker_DB& operator=(const Tracker_DB&) = delete;

private:
    Tracker_DB(const std::string db_name);

    static Tracker_DB* instance;
    sqlite3* source_db;

    void fillTheDB();//Наполнение пустой БД начальными данными

    void createDbStructure();//DDL-операции при создании БД
    void insertBasicData();//DML-операции при создании БД

    void select();//тест функции выбора



};

#endif // TRACKER_DB_H
