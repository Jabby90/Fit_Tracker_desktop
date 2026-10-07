#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "include/tracker_db.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Fit Tracker");

    ui->centralwidget->setLayout(ui->main_app_layout);
    ui->tab_food_dic->setLayout(ui->tab_dic_layout);

    ui->food_dic_view->setModel(Tracker_DB::getInstance().model_select_food_dic);

}

MainWindow::~MainWindow()
{
    delete ui;
}
