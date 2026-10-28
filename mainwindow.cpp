#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "include/tracker_db.h"
#include "include/InsertNewFoodDialog.h"
#include <QInputDialog>
#include <QMessageBox>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Fit Tracker");

    ui->centralwidget->setLayout(ui->main_app_layout);
    ui->tab_food_dic->setLayout(ui->tab_dic_layout);
    ui->tab_food_diary->setLayout(ui->food_diary_layout);

    ui->food_dic_view->setModel(Tracker_DB::getInstance().model_select_food_dic);
    ui->food_dic_view->hideColumn(0); //сокрытие колонки с идентификатором
    //ui->food_dic_view->selectionModel()->currentIndex()

    connect(ui->food_dic_add_button, SIGNAL(clicked()), SLOT(insertNewFood()));
    connect(ui->food_dic_del_button, SIGNAL(clicked()), SLOT(deleteFood()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::insertNewFood()
{
    InsertNewFoodDialog* input_dialog = new InsertNewFoodDialog(this);

    if(input_dialog->exec() == QDialog::Accepted)
    {

        std::string name {input_dialog->getName()};
        std::string kcal {std::to_string(input_dialog->getKcal())};
        std::string proteins {std::to_string(input_dialog->getProteins())};
        std::string fats {std::to_string(input_dialog->getFats())};
        std::string carbohydrates {std::to_string(input_dialog->getCarbohydrates())};

        std::replace(kcal.begin(), kcal.end(), ',', '.');
        std::replace(proteins.begin(), proteins.end(), ',', '.');
        std::replace(fats.begin(), fats.end(), ',', '.');
        std::replace(carbohydrates.begin(), carbohydrates.end(), ',', '.');

        std::string sql_statement =
            "INSERT INTO food (name, Kcal, Proteins, Fats, Carbohydrates) VALUES "
            "('" + name + "', " + kcal + ", " + proteins + ", " + fats + ", " + carbohydrates + ");";

        //qDebug(sql_statement.c_str());

        Tracker_DB::getInstance().runSql(sql_statement);

        //ui->food_dic_view->update();

        //auto model = Tracker_DB::getInstance().model_select_food_dic;
        //QModelIndex topLeft = model->index(0, 0);
        //QModelIndex bottomRight = model->index(model->rowCount() - 1, model->columnCount() - 1);
        //emit model->dataChanged(topLeft, bottomRight, {Qt::DisplayRole});

        //Обновление табличного представления
        Tracker_DB::getInstance().model_select_food_dic->clear();
        Tracker_DB::getInstance().setupFoodDicModel();
        ui->food_dic_view->setModel(Tracker_DB::getInstance().model_select_food_dic);



        //emit Tracker_DB::getInstance().model_select_food_dic.u
    }

    delete input_dialog;
}

void MainWindow::deleteFood()
{
    //Проверяем, выделено ли что-то, если нет - предупреждение
    if (ui->food_dic_view->selectionModel()->selectedRows().empty()
        || ui->food_dic_view->selectionModel()->selectedRows().size() > 1)
    {
        QMessageBox *msgBox = new QMessageBox(this);
        msgBox->setIcon(QMessageBox::Critical); // Устанавливаем иконку предупреждения
        msgBox->setText("Выделите целиком строку, которую хотите удалить");
        msgBox->setWindowTitle("Не выделена строка");
        msgBox->exec();
        delete msgBox;
    }
    else
    {
        //получаем id элемента по номеру строки
        auto selected_index = ui->food_dic_view->selectionModel()->selectedRows();
        auto item = selected_index[0].siblingAtColumn(0).data().toString();

        //формируем запрос на удаление
        std::string sql_statement = "delete from food where id = " + item.toStdString() + ";";
        Tracker_DB::getInstance().runSql(sql_statement);

        //Обновление табличного представления
        Tracker_DB::getInstance().model_select_food_dic->clear();
        Tracker_DB::getInstance().setupFoodDicModel();
        ui->food_dic_view->setModel(Tracker_DB::getInstance().model_select_food_dic);
    }
}