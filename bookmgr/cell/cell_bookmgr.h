#ifndef CELL_BOOKMGR_H
#define CELL_BOOKMGR_H

#include <QStandardItemModel>
#include <QWidget>

namespace Ui {
class Cell_BookMgr;
}

class Cell_BookMgr : public QWidget
{
    Q_OBJECT

public:
    explicit Cell_BookMgr(QWidget *parent = nullptr);
    ~Cell_BookMgr();
    void initPage(QString strCondition = "");

private slots:
    //void on_btn_bk_clicked();

    void on_btn_add_clicked();

    void on_btn_update_clicked();

    void on_btn_del_clicked();

    void on_btn_get_clicked();

    void on_le_search_textChanged(const QString &arg1);

private:
    Ui::Cell_BookMgr *ui;
    QStandardItemModel m_model;
};

#endif // CELL_BOOKMGR_H
