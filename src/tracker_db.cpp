#include "../include/tracker_db.h"
#include "../include/constants.h"

#include <filesystem>
#include <iostream>
#include <vector>

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
    ///TODO Здесь создать структуру бд и наполнить данными

    //DDl-операции для развёртывания БД
    createDbStructure();

    //DML-операции для развёртывания БД
    insertBasicData();

}

void Tracker_DB::createDbStructure()
{
    std::vector<std::string*> ddl_arr;

    //здесь - скрипты создания БД

    std::string sql_0 = "CREATE TABLE food (id INTEGER PRIMARY KEY, name TEXT, Kcal real, Proteins real, Fats real, Carbohydrates real);";
    ddl_arr.push_back(&sql_0);

    char* err = nullptr;
    int rc;

    //перебор всех скриптов создания БД
    for(auto& element: ddl_arr)
    {
        rc = sqlite3_exec(source_db, element->c_str(), nullptr, nullptr, &err);
        if (rc != SQLITE_OK)
        {
            std::cerr << "Error in creating default tables: " << err << "\n";
            sqlite3_free(err);
        }
    }

}

void Tracker_DB::insertBasicData()
{
    const char* sql =
        "INSERT INTO food (name, Kcal, Proteins, Fats, Carbohydrates) VALUES "
        "('Vasya', 100, 200, 300.0, 400.5),"
        "('Vasya', 100, 200, 300.0, 400.5),"
        "('Petya', 100, 200, 300.0, 500.5)"
    ";"
    ;

    char* err = nullptr;
    int rc;

    rc = sqlite3_exec(source_db, sql, nullptr, nullptr, &err);
    if (rc != SQLITE_OK)
    {
        std::cerr << "Error in inserting default values: " << err << "\n";
        sqlite3_free(err);
    }
}