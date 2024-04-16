#include "bookmodel.h"

/*
 * Subclassing QAbstractListModel to provide
 * and expose a data model to QML
 *
 */

BookModel::BookModel(QObject *parent)
    : QAbstractListModel{parent}
{}

// Row count children from data model
int BookModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_apiBookList.size();
}

// Returning data using a specific row, given a role
QVariant BookModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid() && index.row() >= 0 && index.row() <= m_apiBookList.size()) {
        ApiData *apiData = m_apiBookList[index.row()];

        switch((Role)role) {
            case BookIdRole:
                return apiData->bookId();
            case BookTitleRole:
                return apiData->bookTitle();
        }
    }

    return {};
}

// Defines how particular fields of one record are named
QHash<int, QByteArray> BookModel::roleNames() const
{
    QHash<int, QByteArray> names;

    names[BookIdRole] = "bookId";
    names[BookTitleRole] = "bookTitle";

    return names;
}

// Parse json data response and update model
void BookModel::updateDataModel(QJsonDocument &jsonData)
{
    // begin reset current model state
    // before filling our new set of data
    beginResetModel();

    // remove all pointers and clear QList from previous entries
    qDeleteAll(m_apiBookList);
    m_apiBookList.clear();

    // Parse json data
    QJsonArray entries = jsonData.array();

    for(const auto &entry: entries) {

        QJsonObject item = entry.toObject();

        // Get book list entries
        QJsonArray books = item["books"].toArray();

        for(const auto &bookEntry : books) {

            QJsonObject book = bookEntry.toObject();

            // create new data item for each entry
            ApiData *dataItem = new ApiData(this);
            dataItem->setbookId(book["id"].toInteger());
            dataItem->setbookTitle(book["title"].toString());

            // append dataItems to book list
            m_apiBookList << dataItem;
        }
    }

    // end reset current model state
    endResetModel();
}


