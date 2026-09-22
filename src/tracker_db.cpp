#include "../include/tracker_db.h"
#include "../include/constants.h"

#include <filesystem>
#include <iostream>
#include <vector>

static int callback_select(void* data, int argc, char** argv, char** azColName)
{
    int i;
    //fprintf(stderr, "%s: ", (const char*)data);

    for (i = 0; i < argc; i++)
    {
        std::cout << azColName[i] << ' ' << argv[i] << std::endl;
        //printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    //printf("\n");
    return 0;
}

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
        const char* errMsg = sqlite3_errmsg(source_db);
        sqlite3_close(source_db);
        throw std::runtime_error(std::string("Failed to open DB: ") + errMsg);
    }
}

void Tracker_DB::fillTheDB()
{
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
        "('Авокадо', 160.00, 2.00, 14.66, 8.53),"
        "('Апельсины', 47.00, 0.94, 0.12, 11.75),"
        "('Апельсины красные', 36.00, 0.90, 0.20, 8.10),"
        "('Бананы', 89.00, 1.09, 0.33, 22.84),"
        "('Бульон говяжий', 28.60, 2.70, 2.30, 0),"
        "('Говядина запечёная', 203.00, 29.90, 8.37, 0.00),"
        "('Горошек зелёный', 35.00, 3.00, 0.00, 6.00),"
        "('Груша', 62.00, 36.00, 14.00, 15.23),"
        "('Кабачок гриль', 15.00, 1.14, 0.36, 2.69),"
        "('Кальмар гриль', 115.00, 21.80, 2.90, 2.10),"
        "('Капуста квашеная', 19.00, 0.91, 0.14, 4.28),"
        "('Картофель варёный', 86.00, 1.71, 0.10, 20.01),"
        "('Картофель жареный', 265.00, 3.00, 12.52, 35.11),"
        "('Картофель сырой', 77.00, 2.05, 0.09, 17.49),"
        "('Картофель фри', 158.00, 2.75, 5.48, 25.55),"
        "('Кешью', 553.00, 18.22, 43.85, 30.19),"
        "('Креветки варёные', 99.00, 23.98, 0.28, 0.20),"
        "('Крупа гречневая', 350.00, 13.00, 2.50, 68.00),"
        "('Кукуруза консервированная', 50.00, 2.00, 0.00, 11.00),"
        "('Куриная голень запечёная', 191.00, 23.35, 10.15, 0),"
        "('Куриная грудка', 157.00, 32.06, 3.24, 0.00),"
        "('Куриный бульон из грудки', 15.00, 2.00, 0.50, 0.30),"
        "('Лук зелёный', 27.00, 0.97, 0.47, 5.74),"
        "('Мандарины', 53.00, 0.81, 0.31, 13.31),"
        "('Миндаль', 579.00, 21.15, 49.93, 21.55),"
        "('Молоко 2.5%', 53.00, 3.00, 2.50, 4.70),"
        "('Молоко 3.2%', 60.00, 3.00, 3.20, 4.70),"
        "('Морковь жареная', 119.00, 2.50, 5.40, 15.10),"
        "('Морковь сырая', 41.00, 0.93, 0.24, 9.58),"
        "('Огурцы', 15.00, 0.65, 0.11, 3.63),"
        "('Огурцы маринованные', 15.00, 0, 0, 3.80),"
        "('Персики', 39.00, 0.91, 0.25, 9.54),"
        "('Помидоры', 18.00, 0.88, 0.20, 3.89),"
        "('Сахар', 399.00, 0, 0, 99.80),"
        "('Творог мягкий 1%', 49.00, 7.00, 1.00, 3.00),"
        "('Творог мягкий 5%', 85.00, 7.00, 5.00, 3.00),"
        "('Тилапия запечённая', 128.00, 26.15, 2.65, 0.00),"
        "('Яблоки', 52.00, 0.26, 0.17, 13.81),"
        "('Яйцо куриное варёное', 155.00, 12.58, 10.61, 1.12),"
        "('Яйцо куриное жареное', 196.00, 13.61, 14.84, 0.83),"
        "('Яйцо куриное сырое', 143.00, 12.56, 9.51, 0.72)"
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

void Tracker_DB::select()
{
    std::string sql = "select * from food;";

    int rc;
    rc = sqlite3_exec(source_db, sql.c_str(), callback_select, nullptr, nullptr);
}