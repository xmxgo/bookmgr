#include "cell_bookmgr.h"
#include "ui_cell_bookmgr.h"
#include "lib/sqlmgr.h"
#include "dlg_bookau.h"
#include "dlg_bookgs.h"

#include <QMessageBox>

Cell_BookMgr::Cell_BookMgr(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Cell_BookMgr)
{
    ui->setupUi(this);
    ui->tableView->setModel(&m_model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->le_search->setPlaceholderText("请输入图书名称");
}

Cell_BookMgr::~Cell_BookMgr()
{
    delete ui;
}

void Cell_BookMgr::initPage(QString strCondition)
{
    // 获取所有图书

    // 查询数据库并且显示
    auto l = SqlMgr::getInstance()->getBooks(strCondition);
    m_model.clear();
    m_model.setHorizontalHeaderLabels(QStringList{"图书id", "图书名称", "价格", "类型1", "类型2", "类型3", "数量", "图片"});
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


void Cell_BookMgr::on_btn_add_clicked()
{
    Dlg_BookAU dlg;
    dlg.exec();
    initPage();
}


void Cell_BookMgr::on_btn_update_clicked()
{
    int r = ui->tableView->currentIndex().row();
    if (r < 0)
    {
        QMessageBox::information(nullptr, "信息", "无选中图书");
    }
    else
    {
        auto id = m_model.item(r, 0)->text();
        Dlg_BookAU dlg;
        dlg.setType(id.toInt());
        dlg.exec();
        initPage();
    }
}


void Cell_BookMgr::on_btn_del_clicked()
{
    // 删除用户
    int r = ui->tableView->currentIndex().row();
    if (r < 0)
    {
        QMessageBox::information(nullptr, "信息", "无选中图书");
    }
    else
    {
        auto id = m_model.item(r, 0)->text();
        auto str = SqlMgr::getInstance()->delBooks(id);
        QMessageBox::information(nullptr, "信息", str.isEmpty()?"删除成功":str);
        initPage();
    }
}


void Cell_BookMgr::on_btn_get_clicked()
{
    int r = ui->tableView->currentIndex().row();
    if (r < 0)
    {
        QMessageBox::information(nullptr, "信息", "无选中图书");
        //return;
    }
    else
    {
        auto id = m_model.item(r, 0)->text();
        auto cnt = m_model.item(r, 6)->text().toInt();
        if (cnt <= 0)
        {
            QMessageBox::information(nullptr, "信息", "借阅失败没有库存");
            return;
        }
        Dlg_BookGS dlg;
        dlg.setBookId(id.toInt());
        int ret = dlg.exec();
        QMessageBox::information(nullptr, "信息", ret?"借阅成功":"借阅失败");
        if (ret)
        {
            initPage();
        }
    }
}


void Cell_BookMgr::on_le_search_textChanged(const QString &arg1)
{
    QString strCond = QString("where name like '%%1%' or type1 like '%%1%' or type2 like '%%1%' or type3 like '%%1%'").arg(arg1);
    initPage(strCond);
}

