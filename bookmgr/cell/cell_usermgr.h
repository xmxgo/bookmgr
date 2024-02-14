#ifndef CELL_USERMGR_H
#define CELL_USERMGR_H

#include <QWidget>
#include <QStandardItemModel>

namespace Ui {
class Cell_UserMgr;
}

class Cell_UserMgr : public QWidget
{
    Q_OBJECT

public:
    explicit Cell_UserMgr(QWidget *parent = nullptr);
    ~Cell_UserMgr();
    void initPage(QString strCondition = "");

private slots:
    void on_btn_del_clicked();

    void on_btn_import_clicked();

    void on_le_search_textChanged(const QString &arg1);

private:
    Ui::Cell_UserMgr *ui;
    QStandardItemModel m_model;
};

#endif // CELL_USERMGR_H
