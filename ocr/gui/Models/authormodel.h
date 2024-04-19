#ifndef AUTHORMODEL_H
#define AUTHORMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "apidata.h"

class ApiData;

class AuthorModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Role {
        AuthorIdRole = Qt::UserRole + 1,
        AuthorFullnameRole,
    };

    explicit AuthorModel(QObject *parent = nullptr);

    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

signals:

public slots:
    void updateDataModel(QJsonDocument &jsonData);

private:
    QList<ApiData *> m_apiAuthorList;
};

#endif // AUTHORMODEL_H
