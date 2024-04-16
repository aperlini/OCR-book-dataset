#ifndef APIDATA_H
#define APIDATA_H

#include <QObject>
#include <QQmlEngine>

class ApiData : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(int dataIndex READ dataIndex WRITE setDataIndex NOTIFY dataIndexChanged FINAL)

    Q_PROPERTY(QString authorFullname READ authorFullname WRITE setAuthorFullname NOTIFY authorFullnameChanged FINAL)
    Q_PROPERTY(int authorId READ authorId WRITE setAuthorId NOTIFY authorIdChanged FINAL)

    Q_PROPERTY(QString bookTitle READ bookTitle WRITE setbookTitle NOTIFY bookTitleChanged FINAL)
    Q_PROPERTY(int bookId READ bookId WRITE setbookId NOTIFY bookIdChanged FINAL)
public:
    explicit ApiData(QObject *parent = nullptr);

    int dataIndex() const;
    void setDataIndex(int newDataIndex);

    int authorId() const;
    void setAuthorId(const int newAuthorId);

    QString authorFullname() const;
    void setAuthorFullname(const QString &newAuthorFullname);

    int bookId() const;
    void setbookId(const int newBookId);

    QString bookTitle() const;
    void setbookTitle(const QString &newbookTitle);

signals:
    int dataIndexChanged();
    void authorFullnameChanged();
    void authorIdChanged();
    void bookTitleChanged();
    void bookIdChanged();

private:
    int m_dataIndex;
    int m_authorId;
    int m_bookId;
    QString m_authorFullname;
    QString m_bookTitle;
};

#endif // APIDATA_H
