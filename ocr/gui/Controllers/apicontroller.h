#ifndef APICONTROLLER_H
#define APICONTROLLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QTimer>
#include <QDebug>

#include "Models/authormodel.h"
#include "Models/bookmodel.h"

class ApiController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool hasError READ hasError WRITE setHasError NOTIFY hasErrorChanged FINAL)
    Q_PROPERTY(QString typeError READ typeError WRITE setTypeError NOTIFY typeErrorChanged FINAL)
    Q_PROPERTY(QString msg READ msg WRITE setMsg NOTIFY msgChanged FINAL)
public:

    explicit ApiController(QObject *parent = nullptr);

    bool hasError() const;
    void setHasError(bool newHasError);

    QString typeError() const;
    void setTypeError(QString newTypeError);

    QString msg() const;
    void setMsg(QString newMsg);


public slots:
    void apiDataRequest();
    void apiDataResponse();
    void persistDataRequest(int bookId, QString passage, int pageNumber);
    void persistDataResponse();

signals:
    void hasErrorChanged();
    void typeErrorChanged();
    void msgChanged();
    void postRequestStarted();
    void passageSavedDone();
    void jsonDataReady(QJsonDocument &json);

private:
    QNetworkAccessManager m_networkManager;
    QNetworkReply * m_networkReply = nullptr;
    bool m_hasError;
    QString m_msg;
    QString m_typeError;
    const int _timeoutVal; // timeout while process occur

    void checkNetworkErrors();
};

#endif // APICONTROLLER_H
