#include "cell_main.h"
#include "ui_cell_main.h"

#include <QPushButton>
#include <QtDebug>

Cell_Main::Cell_Main(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Cell_Main)
    , m_userPage(nullptr)
    , m_bookPage(nullptr)
    , m_recordPage(nullptr)
{
    ui->setupUi(this);
    initPage();
}

Cell_Main::~Cell_Main()
{
    delete ui;
}

void Cell_Main::initPage()
{
    m_userPage = new Cell_UserMgr(this);
    m_bookPage = new Cell_BookMgr(this);
    m_recordPage = new Cell_Record(this);

    ui->stackedWidget->addWidget(m_userPage);
    ui->stackedWidget->addWidget(m_bookPage);
    ui->stackedWidget->addWidget(m_recordPage);
    ui->stackedWidget->setCurrentIndex(0); //切换到用户管理

    auto l = ui->tool->children();
    for (auto it : l)
    {
        if (it->objectName().contains("btn"))
        {
            connect(static_cast<QPushButton*>(it), &QPushButton::clicked, this, &Cell_Main::dealMenu);
        }
    }
    m_userPage->initPage();
}

void Cell_Main::dealMenu()
{
    auto str = sender()->objectName();

    do
    {
        if ("btn_user" == str)
        {
            m_userPage->initPage();
            ui->stackedWidget->setCurrentIndex(0);
            break;
        }
        if ("btn_book" == str)
        {
            m_bookPage->initPage();
            ui->stackedWidget->setCurrentIndex(1);
            break;
        }
        if ("btn_his" == str)
        {
            m_recordPage->initPage();
            ui->stackedWidget->setCurrentIndex(2);
            break;
        }
    }while(false);
}
