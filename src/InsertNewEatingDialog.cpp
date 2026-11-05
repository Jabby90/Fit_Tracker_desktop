#include "../include/InsertNewEatingDialog.h"
#include <QLayout>
#include <QLabel>
#include <QDateTimeEdit>
#include <QLineEdit>
#include <QTableWidget>

InsertNewEatingDialog::InsertNewEatingDialog(QWidget* parent) : QDialog(parent)
{
    auto* layout_main = new QHBoxLayout(this);

    auto* layout_left = new QVBoxLayout();

    auto* datetime_layout = new QHBoxLayout();
    auto* datetime_label = new QLabel("Дата/время");
    auto* datetime_line_edit = new QDateTimeEdit(QDateTime::currentDateTime());
    datetime_line_edit->setCalendarPopup(true);
    datetime_layout->addWidget(datetime_label);
    datetime_layout->addWidget(datetime_line_edit);

    auto* remark_layout = new QHBoxLayout();
    auto* remark_label = new QLabel("Примечание");
    auto* remark_line_edit = new QLineEdit();
    remark_layout->addWidget(remark_label);
    remark_layout->addWidget(remark_line_edit);

    auto* layout_right = new QVBoxLayout();

    auto* food_layout = new QHBoxLayout();
    auto* food_label = new QLabel("Блюда");
    auto* food_table = new QTableWidget(1, 2);
    food_table->setMinimumSize(250, 200);
    food_table->setHorizontalHeaderLabels({"Блюдо", "Масса, гр."});
    food_layout->addWidget(food_label);
    food_layout->addWidget(food_table);



    layout_left->addLayout(datetime_layout);
    layout_left->addLayout(remark_layout);
    layout_right->addLayout(food_layout);
    layout_main->addLayout(layout_left);
    layout_main->addLayout(layout_right);


    setLayout(layout_main);

}