#include "../include/InsertNewFoodDialog.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <qmessagebox.h>
#include <qvalidator.h>

#include <iostream>

InsertNewFoodDialog::InsertNewFoodDialog(QWidget* parent) : QDialog(parent)
{
    layout_main = new QVBoxLayout(this);

    auto* layout_product_name = new QHBoxLayout();
    auto* product_label = new QLabel("Продукт");
    auto* product_line_edit = new QLineEdit;
    product_line_edit->setObjectName("product_line_edit");
    layout_product_name->addWidget(product_label);
    layout_product_name->addWidget(product_line_edit);

    auto* layout_kcal = new QHBoxLayout();
    auto* kcal_label = new QLabel("Ккал");
    auto* kcal_line_edit = new QLineEdit;
    kcal_line_edit->setObjectName("kcal_line_edit");
    kcal_line_edit->setValidator(new QDoubleValidator(this));
    layout_kcal->addWidget(kcal_label);
    layout_kcal->addWidget(kcal_line_edit);

    auto* layout_proteins = new QHBoxLayout();
    auto* proteins_label = new QLabel("Белки");
    auto* proteins_line_edit = new QLineEdit;
    proteins_line_edit->setObjectName("proteins_line_edit");
    proteins_line_edit->setValidator(new QDoubleValidator(this));
    layout_proteins->addWidget(proteins_label);
    layout_proteins->addWidget(proteins_line_edit);

    auto* layout_fats = new QHBoxLayout();
    auto* fats_label = new QLabel("Жиры");
    auto* fats_line_edit = new QLineEdit;
    fats_line_edit->setObjectName("fats_line_edit");
    fats_line_edit->setValidator(new QDoubleValidator(this));
    layout_fats->addWidget(fats_label);
    layout_fats->addWidget(fats_line_edit);

    auto* layout_carbohydrates = new QHBoxLayout();
    auto* carbohydrates_label = new QLabel("Углеводы");
    auto* carbohydrates_line_edit = new QLineEdit;
    carbohydrates_line_edit->setObjectName("carbohydrates_line_edit");
    carbohydrates_line_edit->setValidator(new QDoubleValidator(this));
    layout_carbohydrates->addWidget(carbohydrates_label);
    layout_carbohydrates->addWidget(carbohydrates_line_edit);

    auto* layout_buttons = new QHBoxLayout();
    auto* button_ok = new QPushButton("Записать");
    auto* button_cancel = new QPushButton("Отмена");
    layout_buttons->addWidget(button_ok);
    layout_buttons->addWidget(button_cancel);


    //layout->addWidget(button);

    layout_main->addLayout(layout_product_name);
    layout_main->addLayout(layout_kcal);
    layout_main->addLayout(layout_proteins);
    layout_main->addLayout(layout_fats);
    layout_main->addLayout(layout_carbohydrates);
    layout_main->addLayout(layout_buttons);

    // Устанавливаем макет
    setLayout(layout_main);

    // Можно подключить сигналы кнопок к слотам здесь
    connect(button_ok, &QPushButton::clicked, this, &QDialog::accept);
    connect(button_cancel, &QPushButton::clicked, this, &QDialog::reject);
}

bool InsertNewFoodDialog::verifyData()
{
    //std::cerr << verifyName() << " && " << verifyKcal() << " && " << verifyProteins() << " && " << verifyFats() << " && " << verifyCarbohydrates() << std::endl;

    return
        verifyName()
        && verifyKcal()
        && verifyProteins()
        && verifyFats()
        && verifyCarbohydrates();


}

bool InsertNewFoodDialog::verifyName()
{
    if (!name.empty()) {return true;}
    else {return false;}
}

bool InsertNewFoodDialog::verifyKcal()
{
    if (kcal > 0 &&  kcal <= 1500) {return true;}
    else {return false;}
}

bool InsertNewFoodDialog::verifyProteins()
{
    if (proteins >= 0 &&  proteins <= 100) {return true;}
    else {return false;}
}

bool InsertNewFoodDialog::verifyFats()
{
    if (fats >= 0 &&  fats <= 100) {return true;}
    else {return false;}
}

bool InsertNewFoodDialog::verifyCarbohydrates()
{
    if (carbohydrates >= 0 &&  carbohydrates <= 100) {return true;}
    else {return false;}
}

void InsertNewFoodDialog::accept()
{
    auto* name_ptr = findChild<QLineEdit*>("product_line_edit");
    if(name_ptr != nullptr) name = name_ptr->text().toStdString();

    auto* kcal_ptr = findChild<QLineEdit*>("kcal_line_edit");
    if(kcal_ptr != nullptr)
    {
        auto kcal_str = kcal_ptr->text();
        kcal_str.replace(",", ".");
        kcal = kcal_str.toDouble();
    }

    auto* proteins_ptr = findChild<QLineEdit*>("proteins_line_edit");
    if(proteins_ptr != nullptr)
    {
        auto proteins_str = proteins_ptr->text();
        proteins_str.replace(",", ".");
        proteins = proteins_str.toDouble();
    }

    auto* fats_ptr = findChild<QLineEdit*>("fats_line_edit");
    if(fats_ptr != nullptr)
    {
        auto fats_str = fats_ptr->text();
        fats_str.replace(",", ".");
        fats = fats_str.toDouble();
    }

    auto* carbohydrates_ptr = findChild<QLineEdit*>("carbohydrates_line_edit");
    if(carbohydrates_ptr != nullptr)
    {
        auto carbohydrates_str = carbohydrates_ptr->text();
        carbohydrates_str.replace(",", ".");
        carbohydrates = carbohydrates_str.toDouble();
    }

    if(!verifyData())
    {
        //qDebug("not verified");
        QMessageBox *msgBox = new QMessageBox(this);
        msgBox->setIcon(QMessageBox::Warning); // Устанавливаем иконку предупреждения
        msgBox->setText("Данные некорректны!");
        msgBox->setWindowTitle("Предупреждение");
        msgBox->exec(); // Выполняем окно (пользователь нажал кнопку)
        delete msgBox;
    }

    else QDialog::accept();
}