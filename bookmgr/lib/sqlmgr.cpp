#include "sqlmgr.h"
#include <QCoreApplication>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QStringList>
#include <QDateTime>

SqlMgr* SqlMgr::instance = nullptr;
SqlMgr::SqlMgr()
{

}

SqlMgr::~SqlMgr()
{

}

void SqlMgr::init()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    qDebug() << QSqlDatabase::drivers();
    m_db.setDatabaseName(QCoreApplication::applicationDirPath() + "/db/book.db");
    qDebug() << m_db.open();
}

bool SqlMgr::login(QString strUser, QString strPass, int &Userid)
{
    QSqlQuery q(m_db);
    QString strsql = QString("select * from user where username='%1' and password='%2'").arg(strUser).arg(strPass);
    bool ret = q.exec(strsql);
    if (!ret)
    {
        qDebug() << q.lastError().text();
    }
    else
    {
        ret = q.next();
        if (ret)
        {
            Userid = q.value(0).toInt();
        }
    }
    return ret;
}

QVector<QStringList> SqlMgr::getUsers(QString strCondition)
{
    //username like '%x%' or nickname like '%t%'

    QSqlQuery q(m_db);
    QString strSql = QString("select * from user %1").arg(strCondition);

    QVector<QStringList> vec;
    bool ret = q.exec(strSql);
    if (!ret)
    {
        qDebug() << q.lastError().text();
    }
    else
    {
        int iCols = q.record().count();
        QStringList l;
        while (q.next())
        {
            l.clear();
            for (int i = 0; i < iCols; i ++)
            {
                l << q.value(i).toString();
            }
            vec.push_back(l);
        }
    }
    return vec;
}

void SqlMgr::AddUser(QVector<QStringList> v)
{
    m_db.transaction();
    QSqlQuery q(m_db);
    for (auto it:v)
    {
        QString strsql = QString("insert into user values(NULL, '%1', '%2', '%3', '%4', '%5', '%6');")
                             .arg(it[0])
                             .arg(it[1])
                             .arg(it[2])
                             .arg(it[3])
                             .arg(it[4])
                             .arg(it[5]);
        bool ret = q.exec(strsql);
        if (!ret)
        {
            qDebug() << q.lastError().text();
        }
    }

    m_db.commit();
}

void SqlMgr::delUser(QString strId)
{
    QSqlQuery q(m_db);
    QString strsql = QString("delete from user where userid=%1").arg(strId);
    bool ret = q.exec(strsql);
    if (!ret)
    {
        qDebug() << q.lastError().text();
    }
}

QVector<QStringList> SqlMgr::getBooks(QString strCondition)
{
    QSqlQuery q(m_db);
    QString strSql = QString("select * from book %1").arg(strCondition);

    QVector<QStringList> vec;
    bool ret = q.exec(strSql);
    if (!ret)
    {
        qDebug() << q.lastError().text();
    }
    else
    {
        int iCols = q.record().count();
        QStringList l;
        while (q.next())
        {
            l.clear();
            for (int i = 0; i < iCols; i ++)
            {
                l << q.value(i).toString();
            }
            vec.push_back(l);
        }
    }
    return vec;
}

void SqlMgr::AddBooks(QVector<QStringList> vec)
{
    if (0 == vec.size())
    {
        return;
    }
    auto ldata = vec[0];
    QSqlQuery q(m_db);
    QString strsql = QString("INSERT INTO book "
                             "VALUES(null, '%1','%2', '%3', '%4', '%5', %6, '')")
                         .arg(ldata[1])
                         .arg(ldata[2])
                         .arg(ldata[3])
                         .arg(ldata[4])
                         .arg(ldata[5])
                         .arg(ldata[6]);

    bool ret = q.exec(strsql);
    if (!ret)
    {
        qDebug() << q.lastError().text();
    }
}

void SqlMgr::UpdateBooks(QStringList ldata)
{
    QSqlQuery q(m_db);
    QString strsql = QString("update book "
                             "set name = '%1', price = '%2', type1 = '%3', type2 = '%4', type3 = '%5', cnt = '%6'"
                             "where bookid = '%7'")
     .arg(ldata[1])
     .arg(ldata[2])
     .arg(ldata[3])
     .arg(ldata[4])
     .arg(ldata[5])
     .arg(ldata[6])
     .arg(ldata[0]);

    bool ret = q.exec(strsql);
    if (!ret)
    {
        qDebug() << q.lastError().text();
    }
}

QString SqlMgr::delBooks(QString strId)
{
    QString strRet;
    QSqlQuery q(m_db);
    QString strsql = QString("delete from book where bookid=%1").arg(strId);
    bool ret = q.exec(strsql);
    if (!ret)
    {
        qDebug() << q.lastError().text();
        strRet = "删除失败，请检查";
    }
    return strRet;
}

QString SqlMgr::returnBooks(QString strUserId, QString strBookId)
{
    QSqlQuery q(m_db);
    QString strsql = QString("update book set cnt = cnt + 1 where bookid = %1;").arg(strBookId);

    bool ret = q.exec(strsql);
    if (!ret)
    {
        qDebug() << q.lastError().text();
    }

    strsql = QString("delete from record where bookid = %1 and userid = %2 ").arg(strBookId).arg(strUserId);
    ret = q.exec(strsql);
    if (!ret)
    {
        qDebug() << q.lastError().text();
    }
    return QString("");
}

QString SqlMgr::borrowBooks(QString strUserId, QString strBookId)
{
    // 实现图书借阅
    QSqlQuery q(m_db);
    QString strsql = QString("update book set cnt = cnt - 1 where bookid = %1;").arg(strBookId);

    bool ret = q.exec(strsql);
    if (!ret)
    {
        qDebug() << q.lastError().text();
    }

    strsql = QString("insert into record values(null, %1, %2, %3, %4)")
                 .arg(strUserId)
                 .arg(strBookId)
                 .arg(QDateTime::currentSecsSinceEpoch())
                 .arg(QDateTime::currentSecsSinceEpoch() + 3600*24*10);
    ret = q.exec(strsql);
    if (!ret)
    {
        qDebug() << q.lastError().text();
    }
    return QString("");
}

QVector<QStringList> SqlMgr::getRecord(QString strCondition)
{
    QSqlQuery q(m_db);
    QString strSql = QString("select * from record join user using(userid) join book using(bookid) %1").arg(strCondition);

    QVector<QStringList> vec;
    bool ret = q.exec(strSql);
    if (!ret)
    {
        qDebug() << q.lastError().text();
    }
    else
    {
        int iCols = q.record().count();
        QStringList l;
        while (q.next())
        {
            l.clear();
            for (int i = 0; i < iCols; i ++)
            {
                l << q.value(i).toString();
            }
            vec.push_back(l);
        }
    }
    return vec;
}

void SqlMgr::clearRecord()
{
    QSqlQuery q(m_db);
    QString strsql = QString("delete from book; delete from sqlite_sequence where name='book';");
    bool ret = q.exec(strsql);
    if (!ret)
    {
        qDebug() << q.lastError().text();
    }
}

