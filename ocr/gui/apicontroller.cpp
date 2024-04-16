#include "apicontroller.h"

// anonymous namespace only accessible with that file
namespace {
    const QString &authorsBooksEndpoint = "http://localhost:8989/authors-books";
    const QString &passageCreateEndpoint = "http://localhost:8989/passages";
}

ApiController::ApiController(QObject *parent)
    : QObject{parent}, m_hasError{false}, _timeoutVal{1000}
{
}

// Handle network errors for communicating w/ the api
void ApiController::checkNetworkErrors()
{
    if(m_networkReply->error() == QNetworkReply::NoError) {

        m_hasError = false;
        emit hasErrorChanged();

    } else if(m_networkReply->error() != QNetworkReply::OperationCanceledError) {

        m_hasError = true;
        m_typeError = "Reponse error : "; // Network error
        m_msg = m_networkReply->errorString();
        emit hasErrorChanged();
        emit typeErrorChanged();
        emit msgChanged();

    }
}

// Fetching default data from api (authors + books)
void ApiController::apiDataRequest()
{
    m_networkReply = m_networkManager.get(QNetworkRequest(QUrl(authorsBooksEndpoint)));
    connect(m_networkReply, &QNetworkReply::finished, this, &ApiController::apiDataResponse);
}

// Api response on data fetch
void ApiController::apiDataResponse()
{
    // check whether service is available
    checkNetworkErrors();

    // Reading data response from api
    QByteArray data = m_networkReply->readAll();

    // Create Json document object representation of parsed data
    QJsonDocument json = QJsonDocument::fromJson(data);

    // emit json data to update list data models
    emit jsonDataReady(json);

    // free network ressources
    m_networkReply->deleteLater();
    m_networkReply = nullptr;
}

// Saving new passage entry to api
void ApiController::persistDataRequest(int bookId, QString passage, int pageNumber)
{
    // Prepare body request with params
    QJsonObject obj;
    obj["content"] = passage;
    obj["page"] = pageNumber;
    obj["book_id"] = bookId;

    QJsonDocument payload(obj);

    // Set POST request
    QNetworkRequest newPostRequest(passageCreateEndpoint);
    newPostRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // send POST request to server
    m_networkReply = m_networkManager.post(newPostRequest, payload.toJson());
    connect(m_networkReply, &QNetworkReply::finished, this, &ApiController::persistDataResponse);

    // emit signal on start
    emit postRequestStarted();

}

// Api response on save
void ApiController::persistDataResponse()
{
    // check whether service is available
    checkNetworkErrors();

    // read server response
    // QString contents = QString::fromUtf8(m_networkReply->readAll());

    QTimer::singleShot(_timeoutVal, this, [=](){
        // emit signal on done
        emit passageSavedDone();
    });


    m_networkReply->deleteLater();
    m_networkReply = nullptr;
}

/*
 * API properties exposed to QML
 *
 */

// Current Api status
bool ApiController::hasError() const
{
    return m_hasError;
}

// Set new Api status
void ApiController::setHasError(bool newHasError)
{
    if(m_hasError != newHasError) {
        m_hasError = newHasError;
        emit hasErrorChanged();
    }
}

// Error type
QString ApiController::typeError() const
{
    return m_typeError;
}

// Set new error type
void ApiController::setTypeError(QString newTypeError)
{
    if(m_typeError != newTypeError) {
        m_typeError = newTypeError;
        emit typeErrorChanged();
    }
}

// Api msg
QString ApiController::msg() const
{
    return m_msg;
}

// Api set msg
void ApiController::setMsg(QString newMsg)
{
    if(m_msg != newMsg) {
        m_msg = newMsg;
        emit msgChanged();
    }
}



