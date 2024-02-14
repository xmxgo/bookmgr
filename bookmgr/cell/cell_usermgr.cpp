#include "cell_usermgr.h"
#include "ui_cell_usermgr.h"
#include "lib/sqlmgr.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QTextCodec>

Cell_UserMgr::Cell_UserMgr(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Cell_UserMgr)
{
    ui->setupUi(this);
    ui->tableView->setModel(&m_model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->le_search->setPlaceholderText("请输入用户名");
#if 0
    for (int i = 0; i < 10; i ++)
    {
        QList<QStandardItem*> items;
        items.append(new QStandardItem("1"));
        items.append(new QStandardItem("1年1班"));
        items.append(new QStandardItem("机械工程系"));
        items.append(new QStandardItem("zhangsan"));
        items.append(new QStandardItem("张二蛋"));
        items.append(new QStandardItem("学生"));
        m_model.appendRow(items);
    }
#endif
}

Cell_UserMgr::~Cell_UserMgr()
{
    delete ui;
}

void Cell_UserMgr::initPage(QString strCondition)
{
    // 查询数据库并且显示
    auto l = SqlMgr::getInstance()->getUsers(strCondition);
    m_model.clear();
    m_model.setHorizontalHeaderLabels(QStringList{"用户id", "年级", "部门", "权限", "用户名", "密码", "昵称"});
    for (int i = 0; i < l.size(); i ++)
    {
        QList<QStandardItem*> items;
        for (int j = 0; j < l[i].size(); j ++)
        {
            items.append(new QStandardItem(l[i][j]));
        }

        m_model.appendRow(items);
    }
}

void Cell_UserMgr::on_btn_del_clicked()
{
    // 删除用户
    int r = ui->tableView->currentIndex().row();
    if (r < 0)
    {
        QMessageBox::information(nullptr, "信息", "无选中用户");
    }
    else
    {
        auto id = m_model.item(r, 0)->text();
        SqlMgr::getInstance()->delUser(id);
        initPage();
    }
}
// static QString convertUTF8(QString strGBK)
// {
//     return QString();
// }

void Cell_UserMgr::on_btn_import_clicked()
{
    auto strPath = QFileDialog::getOpenFileName(nullptr, "输入文件路径");

    if (!strPath.isEmpty())
    {
        QFile f(strPath);
        f.open(QFile::ReadOnly);
        QVector<QStringList> vecData;
        while (!f.atEnd())
        {
            QString str = f.readLine();
            auto l = str.split(",");
            // todo gbk转utf8
            // for (auto &itC:l)
            // {
            //     itC = convertUTF8(itC);
            // }
            if (l.size() != 6)
            {
                QMessageBox::information(nullptr, "信息", "导入失败");
                return;
            }
            l[l.size() - 1] = l[l.size() - 1].chopped(4);
            vecData.push_back(l);
        }

        SqlMgr::getInstance()->AddUser(vecData);
        ui->le_search->clear();
        initPage();
    }
}


void Cell_UserMgr::on_le_search_textChanged(const QString &arg1)
{
    QString strCond = QString("where username like '%%1%' or nickname like '%%1%'").arg(arg1);
    initPage(strCond);
}

