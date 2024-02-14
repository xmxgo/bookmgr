#include "dlg_bookau.h"
#include "ui_dlg_bookau.h"
#include "lib/sqlmgr.h"

Dlg_BookAU::Dlg_BookAU(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dlg_BookAU)
{
    ui->setupUi(this);
}

Dlg_BookAU::~Dlg_BookAU()
{
    delete ui;
}

void Dlg_BookAU::setType(int id)
{
    m_id = id;
    // 执行sql语句获取图书信息，并且显示到对应的控件上
    auto l = SqlMgr::getInstance()->getBooks(QString(" where bookid = %1").arg(id));
    if (1 == l.size())
    {
        auto data = l[0];
        ui->le_name->setText(data[1]);
        ui->le_price->setText(data[2]);
        ui->cb1->setCurrentText(data[3]);
        ui->cb2->setCurrentText(data[4]);
        ui->cb3->setCurrentText(data[5]);
        ui->le_cnt->setText(data[6]);
    }
}

void Dlg_BookAU::on_btn_ok_clicked()
{
    QStringList l;
    l << QString::number(m_id);
    l << ui->le_name->text();
    l << ui->le_price->text();
    l << ui->cb1->currentText();
    l << ui->cb2->currentText();
    l << ui->cb3->currentText();
    l << ui->le_cnt->text();
    l << "";

    if (-1 != m_id)
    {
        // update
        SqlMgr::getInstance()->UpdateBooks(l);
    }
    else
    {
        // add
        QVector<QStringList> vec;
        vec.push_back(l);
        SqlMgr::getInstance()->AddBooks(vec);
    }
    this->hide();
}


void Dlg_BookAU::on_btn_cancel_clicked()
{
    this->hide();
}

