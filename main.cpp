#include "mainwindow.h"
#include <QApplication>
#include <iostream>

#include "sqlite3.h"
#include "include/tracker_db.h"

Tracker_DB* Tracker_DB::instance = nullptr;


int main(int argc, char *argv[])
{
    try
    {
        // Получаем синглтон (БД откроется при первом вызове)
        auto& db = Tracker_DB::getInstance();

        sqlite3* conn = db.getDb();
        if (!conn)
        {
            throw std::runtime_error("Database connection is null");
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
        return 1;
    }



    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return QApplication::exec();
}
