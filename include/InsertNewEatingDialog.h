#pragma once
#ifndef INSERTNEWEATINGDIALOG_H
#define INSERTNEWEATINGDIALOG_H
#include <QDialog>
#include <QTableWidget>

class InsertNewEatingDialog : public QDialog
{
    Q_OBJECT
public:
    InsertNewEatingDialog(QWidget* parent = 0);


private:
    QTableWidget* food_table{nullptr};

    bool rowIsEmpty(int row); //проверка строки на пустоту или пустой текст
    bool rowIsFull(int row); //проверка строки на заполненость целиком
    bool tableIsFull(); //проверка, что вся таблица заполнена

private slots:
    void checkTheCells(int row, int column);

};

#endif // INSERTNEWEATINGDIALOG_H
