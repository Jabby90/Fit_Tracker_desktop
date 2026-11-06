#include "../include/InsertNewEatingDialog.h"
#include <QLayout>
#include <QLabel>
#include <QDateTimeEdit>
#include <QLineEdit>


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
    food_table = new QTableWidget(1, 2);
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

    connect(food_table, SIGNAL(cellChanged(int,int)), this, SLOT(checkTheCells(int,int)));

}

void InsertNewEatingDialog::checkTheCells(int changed_row, int changed_column)
{
    int total_rows{food_table->rowCount()};
    QTableWidgetItem* item;

    //TODO Здесь лезе ошибка при удалении строки. Разобраться, как её убрать. Логика, на первый взгляд, работает
    if(rowIsEmpty(changed_row) && total_rows > 1) food_table->removeRow(changed_row);
    //if(rowIsEmpty(changed_row) && total_rows > 1)
    //{
    //    food_table->removeCellWidget(changed_row, 0);
    //    food_table->removeCellWidget(changed_row, 1);
    //
    //}


    if(tableIsFull()) food_table->insertRow(food_table->rowCount());

    // }
    //if(!need_to_remove_row && changed_row == max_rows-1) food_table->removeRow(max_rows-1);
    //if(max_rows == 1){}
    //qDebug("checking th cells");
}

bool InsertNewEatingDialog::rowIsEmpty(int row)
{
    int cols = food_table->columnCount();
    QTableWidgetItem* item;

    for(int col = 0; col < cols; ++col)
    {
        item = food_table->item(row, col);
        if(item && item->text().size() > 0) return false;
    }
    return true;
}

bool InsertNewEatingDialog::rowIsFull(int row)
{
    int cols = food_table->columnCount();
    QTableWidgetItem* item;

    for(int col = 0; col < cols; ++col)
    {
        item = food_table->item(row, col);
        if(!item) return false;
        else if(item->text().size() == 0) return false;
    }
    return true;
}

bool InsertNewEatingDialog::tableIsFull()
{
    int rows = food_table->rowCount();

    for(int row = 0; row < rows; ++row)
    {
        if(!rowIsFull(row)) return false;
    }
    return true;
}