#ifndef BOOKMODEL_H
#define BOOKMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "apidata.h"

class ApiData;

class BookModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Role {
        BookIdRole = Qt::UserRole + 1,
        BookTitleRole
    };

    explicit BookModel(QObject *parent = nullptr);

    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

signals:

public slots:
    void updateDataModel(QJsonDocument &jsonData);

private:
    QList<ApiData *> m_apiBookList;
};

#endif // BOOKMODEL_H
