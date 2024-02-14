#ifndef SQLMGR_H
#define SQLMGR_H

#include <QSqlDatabase>
#include <QtDebug>

class SqlMgr
{
public:
    SqlMgr();
    ~SqlMgr();

    // C++ 单例模式
    static SqlMgr* instance;
    static SqlMgr* getInstance() {
        if(nullptr == instance) {
            instance = new SqlMgr();
        }
        return instance;
    }

    void init();

    // 登录
    bool login(QString strUser, QString strPass, int &Userid);

    // 获取所有用户，默认不带条件（获取所有数据）
    QVector<QStringList> getUsers(QString strCondition = "");

    // 添加用户
    void AddUser(QVector<QStringList>);

    // 删除用户
    void delUser(QString strId);

    // 获取所有图书
    QVector<QStringList> getBooks(QString strCondition = "");

    // 增加图书
    void AddBooks(QVector<QStringList>);

    // 修改图书
    void UpdateBooks(QStringList);

    // 删除图书
    QString delBooks(QString strId);

    // 图书归还
    QString returnBooks(QString strUserId, QString strBookId);

    // 图书借阅
    QString borrowBooks(QString strUserId, QString strBookId);

    // 获取借阅记录
    QVector<QStringList> getRecord(QString strCondition = "");

    // 清空借阅记录
    void clearRecord();
private:
    QSqlDatabase m_db;
};

#endif // SQLMGR_H
