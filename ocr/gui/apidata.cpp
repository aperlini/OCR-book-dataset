#include "apidata.h"

/*
 *  Class exposing API data properties
 *
 */

ApiData::ApiData(QObject *parent)
    : QObject{parent}
{}

int ApiData::dataIndex() const
{
    return m_dataIndex;
}

void ApiData::setDataIndex(int newDataIndex)
{
    if(m_dataIndex != newDataIndex) {
        m_dataIndex = newDataIndex;
        emit dataIndexChanged();
    }
}

int ApiData::authorId() const
{
    return m_authorId;
}

void ApiData::setAuthorId(const int newAuthorId)
{
    if(m_authorId == newAuthorId)
        return;
    m_authorId = newAuthorId;
}

QString ApiData::authorFullname() const
{
    return m_authorFullname;
}

void ApiData::setAuthorFullname(const QString &newAuthorFullname)
{
    if(m_authorFullname == newAuthorFullname)
        return;
    m_authorFullname = newAuthorFullname;

    emit authorFullnameChanged();
}

int ApiData::bookId() const
{
    return m_bookId;
}

void ApiData::setbookId(const int newBookId)
{
    if(m_bookId == newBookId)
        return;
    m_bookId = newBookId;
    emit bookIdChanged();
}

QString ApiData::bookTitle() const
{
    return m_bookTitle;
}

void ApiData::setbookTitle(const QString &newbookTitle)
{
    if(m_bookTitle == newbookTitle)
        return;
    m_bookTitle = newbookTitle;
    emit bookTitleChanged();
}
