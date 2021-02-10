/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QStackedWidget *viewsSW;
    QWidget *loginPage;
    QGridLayout *gridLayout_2;
    QFrame *loginFrame;
    QFormLayout *formLayout_3;
    QGroupBox *newUserGb;
    QFormLayout *formLayout_2;
    QLabel *newUserLabel;
    QLineEdit *newUserLE;
    QLabel *emailLabel;
    QLineEdit *emailLE;
    QLabel *newPasswordLabel;
    QLineEdit *newPasswordLE;
    QPushButton *createPB;
    QGroupBox *userGB;
    QFormLayout *formLayout;
    QLabel *LoginEmailLabel;
    QLineEdit *userLE;
    QLabel *passwordLabel;
    QLineEdit *paswordLE;
    QPushButton *loginButton;
    QWidget *nilePage;
    QGridLayout *gridLayout_3;
    QComboBox *categoriesCB;
    QLineEdit *searchLE;
    QComboBox *orderFCB;
    QPushButton *carPB;
    QPushButton *LogoutPB;
    QScrollArea *stuffSA;
    QWidget *stuffContents;
    QGridLayout *gridLayout_5;
    QGridLayout *productsLO;
    QScrollArea *stuffSA_2;
    QWidget *stuffContents_2;
    QGridLayout *gridLayout_6;
    QGridLayout *productsLO_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1000, 720);
        MainWindow->setMinimumSize(QSize(80, 600));
        MainWindow->setMaximumSize(QSize(1280, 720));
        QFont font;
        font.setFamily(QString::fromUtf8("Century Gothic"));
        MainWindow->setFont(font);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        viewsSW = new QStackedWidget(centralwidget);
        viewsSW->setObjectName(QString::fromUtf8("viewsSW"));
        viewsSW->setFont(font);
        loginPage = new QWidget();
        loginPage->setObjectName(QString::fromUtf8("loginPage"));
        gridLayout_2 = new QGridLayout(loginPage);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        loginFrame = new QFrame(loginPage);
        loginFrame->setObjectName(QString::fromUtf8("loginFrame"));
        loginFrame->setEnabled(false);
        loginFrame->setFont(font);
        loginFrame->setFrameShape(QFrame::StyledPanel);
        loginFrame->setFrameShadow(QFrame::Raised);
        formLayout_3 = new QFormLayout(loginFrame);
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        formLayout_3->setLabelAlignment(Qt::AlignCenter);
        formLayout_3->setFormAlignment(Qt::AlignCenter);
        newUserGb = new QGroupBox(loginFrame);
        newUserGb->setObjectName(QString::fromUtf8("newUserGb"));
        newUserGb->setMaximumSize(QSize(400, 16777215));
        newUserGb->setFont(font);
        newUserGb->setFocusPolicy(Qt::StrongFocus);
        newUserGb->setAlignment(Qt::AlignCenter);
        formLayout_2 = new QFormLayout(newUserGb);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        newUserLabel = new QLabel(newUserGb);
        newUserLabel->setObjectName(QString::fromUtf8("newUserLabel"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("MS Shell Dlg 2"));
        font1.setPointSize(12);
        newUserLabel->setFont(font1);

        formLayout_2->setWidget(1, QFormLayout::LabelRole, newUserLabel);

        newUserLE = new QLineEdit(newUserGb);
        newUserLE->setObjectName(QString::fromUtf8("newUserLE"));
        newUserLE->setFont(font1);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, newUserLE);

        emailLabel = new QLabel(newUserGb);
        emailLabel->setObjectName(QString::fromUtf8("emailLabel"));
        emailLabel->setFont(font1);

        formLayout_2->setWidget(2, QFormLayout::LabelRole, emailLabel);

        emailLE = new QLineEdit(newUserGb);
        emailLE->setObjectName(QString::fromUtf8("emailLE"));
        emailLE->setFont(font1);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, emailLE);

        newPasswordLabel = new QLabel(newUserGb);
        newPasswordLabel->setObjectName(QString::fromUtf8("newPasswordLabel"));
        newPasswordLabel->setFont(font1);

        formLayout_2->setWidget(4, QFormLayout::LabelRole, newPasswordLabel);

        newPasswordLE = new QLineEdit(newUserGb);
        newPasswordLE->setObjectName(QString::fromUtf8("newPasswordLE"));
        newPasswordLE->setFont(font1);
        newPasswordLE->setEchoMode(QLineEdit::Password);

        formLayout_2->setWidget(4, QFormLayout::FieldRole, newPasswordLE);

        createPB = new QPushButton(newUserGb);
        createPB->setObjectName(QString::fromUtf8("createPB"));
        createPB->setEnabled(false);
        createPB->setFont(font1);
        createPB->setCursor(QCursor(Qt::OpenHandCursor));
        createPB->setFocusPolicy(Qt::WheelFocus);
        createPB->setAutoDefault(false);
        createPB->setFlat(false);

        formLayout_2->setWidget(6, QFormLayout::FieldRole, createPB);


        formLayout_3->setWidget(1, QFormLayout::SpanningRole, newUserGb);

        userGB = new QGroupBox(loginFrame);
        userGB->setObjectName(QString::fromUtf8("userGB"));
        userGB->setMaximumSize(QSize(400, 16777215));
        userGB->setFont(font);
        userGB->setAlignment(Qt::AlignCenter);
        formLayout = new QFormLayout(userGB);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        LoginEmailLabel = new QLabel(userGB);
        LoginEmailLabel->setObjectName(QString::fromUtf8("LoginEmailLabel"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Century Gothic"));
        font2.setPointSize(12);
        LoginEmailLabel->setFont(font2);

        formLayout->setWidget(0, QFormLayout::LabelRole, LoginEmailLabel);

        userLE = new QLineEdit(userGB);
        userLE->setObjectName(QString::fromUtf8("userLE"));
        userLE->setFont(font2);

        formLayout->setWidget(0, QFormLayout::FieldRole, userLE);

        passwordLabel = new QLabel(userGB);
        passwordLabel->setObjectName(QString::fromUtf8("passwordLabel"));
        passwordLabel->setFont(font2);

        formLayout->setWidget(1, QFormLayout::LabelRole, passwordLabel);

        paswordLE = new QLineEdit(userGB);
        paswordLE->setObjectName(QString::fromUtf8("paswordLE"));
        paswordLE->setFont(font2);
        paswordLE->setAutoFillBackground(false);
        paswordLE->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(1, QFormLayout::FieldRole, paswordLE);

        loginButton = new QPushButton(userGB);
        loginButton->setObjectName(QString::fromUtf8("loginButton"));
        loginButton->setEnabled(false);
        loginButton->setFont(font2);
        loginButton->setCursor(QCursor(Qt::OpenHandCursor));
        loginButton->setFlat(false);

        formLayout->setWidget(2, QFormLayout::FieldRole, loginButton);


        formLayout_3->setWidget(0, QFormLayout::SpanningRole, userGB);


        gridLayout_2->addWidget(loginFrame, 0, 0, 1, 1);

        viewsSW->addWidget(loginPage);
        nilePage = new QWidget();
        nilePage->setObjectName(QString::fromUtf8("nilePage"));
        gridLayout_3 = new QGridLayout(nilePage);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        categoriesCB = new QComboBox(nilePage);
        categoriesCB->addItem(QString());
        categoriesCB->addItem(QString());
        categoriesCB->addItem(QString());
        categoriesCB->addItem(QString());
        categoriesCB->addItem(QString());
        categoriesCB->addItem(QString());
        categoriesCB->setObjectName(QString::fromUtf8("categoriesCB"));

        gridLayout_3->addWidget(categoriesCB, 0, 0, 1, 1);

        searchLE = new QLineEdit(nilePage);
        searchLE->setObjectName(QString::fromUtf8("searchLE"));

        gridLayout_3->addWidget(searchLE, 0, 1, 1, 1);

        orderFCB = new QComboBox(nilePage);
        orderFCB->addItem(QString());
        orderFCB->addItem(QString());
        orderFCB->addItem(QString());
        orderFCB->setObjectName(QString::fromUtf8("orderFCB"));

        gridLayout_3->addWidget(orderFCB, 0, 2, 1, 1);

        carPB = new QPushButton(nilePage);
        carPB->setObjectName(QString::fromUtf8("carPB"));

        gridLayout_3->addWidget(carPB, 0, 3, 1, 1);

        LogoutPB = new QPushButton(nilePage);
        LogoutPB->setObjectName(QString::fromUtf8("LogoutPB"));

        gridLayout_3->addWidget(LogoutPB, 0, 4, 1, 1);

        stuffSA = new QScrollArea(nilePage);
        stuffSA->setObjectName(QString::fromUtf8("stuffSA"));
        stuffSA->setWidgetResizable(true);
        stuffContents = new QWidget();
        stuffContents->setObjectName(QString::fromUtf8("stuffContents"));
        stuffContents->setGeometry(QRect(0, 0, 633, 610));
        gridLayout_5 = new QGridLayout(stuffContents);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        productsLO = new QGridLayout();
        productsLO->setObjectName(QString::fromUtf8("productsLO"));

        gridLayout_5->addLayout(productsLO, 0, 0, 1, 1);

        stuffSA->setWidget(stuffContents);

        gridLayout_3->addWidget(stuffSA, 1, 0, 1, 2);

        stuffSA_2 = new QScrollArea(nilePage);
        stuffSA_2->setObjectName(QString::fromUtf8("stuffSA_2"));
        stuffSA_2->setWidgetResizable(true);
        stuffContents_2 = new QWidget();
        stuffContents_2->setObjectName(QString::fromUtf8("stuffContents_2"));
        stuffContents_2->setGeometry(QRect(0, 0, 321, 610));
        gridLayout_6 = new QGridLayout(stuffContents_2);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        productsLO_2 = new QGridLayout();
        productsLO_2->setObjectName(QString::fromUtf8("productsLO_2"));

        gridLayout_6->addLayout(productsLO_2, 0, 0, 1, 1);

        stuffSA_2->setWidget(stuffContents_2);

        gridLayout_3->addWidget(stuffSA_2, 1, 2, 1, 3);

        viewsSW->addWidget(nilePage);

        gridLayout->addWidget(viewsSW, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1000, 20));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        viewsSW->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Nile", nullptr));
        newUserGb->setTitle(QCoreApplication::translate("MainWindow", "New to Nile?", nullptr));
        newUserLabel->setText(QCoreApplication::translate("MainWindow", "User Name:", nullptr));
        emailLabel->setText(QCoreApplication::translate("MainWindow", "Email: ", nullptr));
        newPasswordLabel->setText(QCoreApplication::translate("MainWindow", "Password: ", nullptr));
        createPB->setText(QCoreApplication::translate("MainWindow", "Create", nullptr));
        userGB->setTitle(QCoreApplication::translate("MainWindow", "Login", nullptr));
        LoginEmailLabel->setText(QCoreApplication::translate("MainWindow", "Email:", nullptr));
        passwordLabel->setText(QCoreApplication::translate("MainWindow", "Pasword:", nullptr));
        loginButton->setText(QCoreApplication::translate("MainWindow", "Login", nullptr));
        categoriesCB->setItemText(0, QCoreApplication::translate("MainWindow", "Todos los departamentos", nullptr));
        categoriesCB->setItemText(1, QCoreApplication::translate("MainWindow", "Alimentos y Bebidas", nullptr));
        categoriesCB->setItemText(2, QCoreApplication::translate("MainWindow", "Libros", nullptr));
        categoriesCB->setItemText(3, QCoreApplication::translate("MainWindow", "Electr\303\263nicos", nullptr));
        categoriesCB->setItemText(4, QCoreApplication::translate("MainWindow", "Hogar Y Cocina", nullptr));
        categoriesCB->setItemText(5, QCoreApplication::translate("MainWindow", "Deporte y Aire Libre", nullptr));

        orderFCB->setItemText(0, QCoreApplication::translate("MainWindow", "Sin filtro", nullptr));
        orderFCB->setItemText(1, QCoreApplication::translate("MainWindow", "Menor a mayor $", nullptr));
        orderFCB->setItemText(2, QCoreApplication::translate("MainWindow", "Mayor a menor $", nullptr));

        carPB->setText(QCoreApplication::translate("MainWindow", "Carrito de Compra", nullptr));
        LogoutPB->setText(QCoreApplication::translate("MainWindow", "Cerrar Sesion", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
