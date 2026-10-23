#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "include/tracker_db.h"
#include "include/InsertNewFoodDialog.h"
#include <QInputDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Fit Tracker");

    ui->centralwidget->setLayout(ui->main_app_layout);
    ui->tab_food_dic->setLayout(ui->tab_dic_layout);

    ui->food_dic_view->setModel(Tracker_DB::getInstance().model_select_food_dic);

    connect(ui->food_dic_add_button, SIGNAL(clicked()), SLOT(insertNewFood()));
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

        Tracker_DB::getInstance().model_select_food_dic->clear();
        Tracker_DB::getInstance().setupFoodDicModel();
        ui->food_dic_view->setModel(Tracker_DB::getInstance().model_select_food_dic);



        //emit Tracker_DB::getInstance().model_select_food_dic.u
    }

    delete input_dialog;
}