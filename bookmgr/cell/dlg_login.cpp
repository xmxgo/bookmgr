#include "dlg_login.h"
#include "ui_dlg_login.h"
#include "lib/sqlmgr.h"

#include <QMessageBox>

Dlg_Login::Dlg_Login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dlg_Login)
{
    ui->setupUi(this);
}

Dlg_Login::~Dlg_Login()
{
    delete ui;
}

void Dlg_Login::on_btn_login_clicked()
{
    int bookid = 0;
    auto ret = SqlMgr::getInstance()->login(ui->le_user->text(), ui->le_password->text(), bookid);
    if (ret)
    {
        setResult(1);
        hide();
    }
    else
    {
        QMessageBox::information(nullptr, "信息", "用户名或者密码错误");
    }
}


void Dlg_Login::on_btn_exit_clicked()
{
    setResult(0);
}

