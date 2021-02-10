/********************************************************************************
** Form generated from reading UI file 'product.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRODUCT_H
#define UI_PRODUCT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Product
{
public:
    QGridLayout *gridLayout;
    QLabel *Price;
    QLabel *Name;
    QPushButton *buyPB;
    QSpinBox *ammountSB;
    QLabel *Image;

    void setupUi(QWidget *Product)
    {
        if (Product->objectName().isEmpty())
            Product->setObjectName(QString::fromUtf8("Product"));
        Product->resize(265, 382);
        gridLayout = new QGridLayout(Product);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        Price = new QLabel(Product);
        Price->setObjectName(QString::fromUtf8("Price"));
        QFont font;
        font.setFamily(QString::fromUtf8("Century Gothic"));
        Price->setFont(font);
        Price->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(Price, 2, 0, 1, 2);

        Name = new QLabel(Product);
        Name->setObjectName(QString::fromUtf8("Name"));
        Name->setFont(font);
        Name->setTextFormat(Qt::AutoText);
        Name->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(Name, 1, 0, 1, 2);

        buyPB = new QPushButton(Product);
        buyPB->setObjectName(QString::fromUtf8("buyPB"));
        buyPB->setFont(font);
        buyPB->setCursor(QCursor(Qt::OpenHandCursor));
        buyPB->setFlat(false);

        gridLayout->addWidget(buyPB, 3, 1, 1, 1);

        ammountSB = new QSpinBox(Product);
        ammountSB->setObjectName(QString::fromUtf8("ammountSB"));
        ammountSB->setFont(font);
        ammountSB->setMinimum(1);

        gridLayout->addWidget(ammountSB, 3, 0, 1, 1);

        Image = new QLabel(Product);
        Image->setObjectName(QString::fromUtf8("Image"));
        Image->setFont(font);
        Image->setCursor(QCursor(Qt::ArrowCursor));
        Image->setFrameShadow(QFrame::Plain);
        Image->setScaledContents(false);
        Image->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(Image, 0, 0, 1, 2);


        retranslateUi(Product);

        buyPB->setDefault(false);


        QMetaObject::connectSlotsByName(Product);
    } // setupUi

    void retranslateUi(QWidget *Product)
    {
        Product->setWindowTitle(QCoreApplication::translate("Product", "Form", nullptr));
        Price->setText(QCoreApplication::translate("Product", "TextLabel", nullptr));
        Name->setText(QCoreApplication::translate("Product", "TextLabel", nullptr));
        buyPB->setText(QCoreApplication::translate("Product", "Comprar Ahora", nullptr));
        Image->setText(QCoreApplication::translate("Product", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Product: public Ui_Product {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRODUCT_H
