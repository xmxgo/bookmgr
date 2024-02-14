#ifndef DLG_BOOKAU_H
#define DLG_BOOKAU_H

#include <QDialog>

namespace Ui {
class Dlg_BookAU;
}

class Dlg_BookAU : public QDialog
{
    Q_OBJECT

public:
    explicit Dlg_BookAU(QWidget *parent = nullptr);
    ~Dlg_BookAU();
    void setType(int id);

private slots:
    void on_btn_cancel_clicked();
    void on_btn_ok_clicked();


private:
    Ui::Dlg_BookAU *ui;
    int m_id = -1;
};

#endif // DLG_BOOKAU_H
