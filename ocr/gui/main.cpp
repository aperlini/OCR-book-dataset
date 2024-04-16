#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>
#include <QThread>

#include "appcontroller.h"
#include "bookmodel.h"
#include "authormodel.h"
#include "apicontroller.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // Registring and exposing singleton instances of models and controllers
    AppController *appCtrl = new AppController(&app);
    qmlRegisterSingletonInstance("xy.myapp.AppCtrl", 1, 0, "AppCtrl", appCtrl);

    ApiController *apiCtrl = new ApiController(&app);
    qmlRegisterSingletonInstance("xy.myapp.ApiCtrl", 1, 0, "ApiCtrl", apiCtrl);

    BookModel *bookModel = new BookModel(&app);
    qmlRegisterSingletonInstance("xy.myapp.BookModel", 1, 0, "BookModel", bookModel);

    AuthorModel *authorModel = new AuthorModel(&app);
    qmlRegisterSingletonInstance("xy.myapp.AuthorModel", 1, 0, "AuthorModel", authorModel);

    // Bind slignal/slot connection to update authors/books lists
    QObject::connect(apiCtrl, &ApiController::jsonDataReady, bookModel, &BookModel::updateDataModel);
    QObject::connect(apiCtrl, &ApiController::jsonDataReady, authorModel, &AuthorModel::updateDataModel);

    QQmlApplicationEngine engine;

    const QUrl url(u"qrc:/gui/Main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
