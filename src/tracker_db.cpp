#include "../include/tracker_db.h"
#include "../include/constants.h"

#include <filesystem>
#include <iostream>

Tracker_DB& Tracker_DB::getInstance()
{
    if(instance == nullptr)
    {
        //проверка, что существует файл базы данных. Если его нет, то при создании, надо
        //создать таблицы и наполнить их
        if(std::filesystem::exists(ft_constants::DB_NAME))
        {
            instance = new Tracker_DB(ft_constants::DB_NAME);
        }
        else
        {
            instance = new Tracker_DB(ft_constants::DB_NAME);
            instance->fillTheDB();
        }
    }
    return *instance;
}

Tracker_DB::Tracker_DB(const std::string db_name)
{
    int rc = sqlite3_open(db_name.c_str(), &source_db);

    if (rc != SQLITE_OK)
    {
        // Важно: не выбрасывать исключение из конструктора, если есть риск
        // неопределённого поведения. Но для простоты примера делаем так:
        const char* errMsg = sqlite3_errmsg(source_db);
        sqlite3_close(source_db);
        throw std::runtime_error(std::string("Failed to open DB: ") + errMsg);
    }
}

void Tracker_DB::fillTheDB()
{
    int rc;
    const char* sql = "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, name TEXT);";
    char* err = nullptr;
    rc = sqlite3_exec(source_db, sql, nullptr, nullptr, &err);
    if (rc != SQLITE_OK){
        std::cerr << "Error creating table: " << err << "\n";
        sqlite3_free(err);
    }
}
