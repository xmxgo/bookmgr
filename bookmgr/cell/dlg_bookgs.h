#ifndef DLG_BOOKGS_H
#define DLG_BOOKGS_H

#include <QDialog>

namespace Ui {
class Dlg_BookGS;
}

class Dlg_BookGS : public QDialog
{
    Q_OBJECT

public:
    explicit Dlg_BookGS(QWidget *parent = nullptr);
    ~Dlg_BookGS();
    void setType(bool isReturn);
    void setBookId(int id);

private slots:
    void on_btn_get_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::Dlg_BookGS *ui;
    int m_bookid;
    bool m_isReturn = false;
};

#endif // DLG_BOOKGS_H
