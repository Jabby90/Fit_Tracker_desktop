#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralwidget->setLayout(ui->main_app_layout);
    ui->tab_food_dic->setLayout(ui->tab_dic_layout);

}

MainWindow::~MainWindow()
{
    delete ui;
}
