#include "authormodel.h"

/*
 * Subclassing QAbstractListModel to provide
 * and expose a data model to QML
 *
 */
AuthorModel::AuthorModel(QObject *parent)
    : QAbstractListModel{parent}
{}

// Row count children from data model
int AuthorModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_apiAuthorList.size();
}

// Returning data using a specific row, given a role
QVariant AuthorModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid() && index.row() >= 0 && index.row() <= m_apiAuthorList.size()) {
        ApiData *apiData = m_apiAuthorList[index.row()];

        switch((Role)role) {
        case AuthorIdRole:
                return apiData->authorId();
            case AuthorFullnameRole:
                return apiData->authorFullname();
        }
    }

    return {};
}

// Defines how particular fields of one record are named
QHash<int, QByteArray> AuthorModel::roleNames() const
{
    QHash<int, QByteArray> names;

    names[AuthorIdRole] = "authorId";
    names[AuthorFullnameRole] = "authorFullname";

    return names;
}

// Parse json data response and update model
void AuthorModel::updateDataModel(QJsonDocument &jsonData)
{
    // begin reset current model state
    // before filling our new set of data
    beginResetModel();

    // remove all pointers and clean QList from previous data
    qDeleteAll(m_apiAuthorList);
    m_apiAuthorList.clear();

    QJsonArray authors = jsonData.array();

    // access each authors entry
    for(const auto &authorEntry: authors) {

        // create new data item for each entry
        ApiData *dataItem = new ApiData(this);

        // author object
        QJsonObject author = authorEntry.toObject();

        // merge to fullname
        QString fullname = author["firstname"].toString() + " " + author["lastname"].toString();
        dataItem->setAuthorId(author["id"].toInteger());
        dataItem->setAuthorFullname(fullname);

        // append dataItems to author list
        m_apiAuthorList << dataItem;
    }

    // end reset current model state
    endResetModel();
}

