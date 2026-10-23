#include "mainwindow.h"
#include <QApplication>
//#include <QCoreApplication>
#include <iostream>


#include "sqlite3.h"
#include "include/tracker_db.h"

Tracker_DB* Tracker_DB::instance = nullptr;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    try
    {
        // Получаем инстанс (БД откроется при первом вызове)
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

    MainWindow w;
    w.show();
    QApplication::exec();



    sqlite3_free(Tracker_DB::getInstance().getDb());
    return 0;
}


//#include "main.moc"