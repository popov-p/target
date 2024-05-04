#ifndef BACKENDMANAGER_H
#define BACKENDMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QStandardItem>
#include <QNetworkReply>
#include <QAuthenticator>
#include <glog/logging.h>

class BackendManager : public QObject {
    Q_OBJECT
public:
    explicit BackendManager(QObject *parent = nullptr);
    ~BackendManager();
    void setBaseURL(QString url);
    void login(QString username, QString password);
    void getHeaders();
    void getAllRecordings();
    void deleteAllRecordings();
    void deleteSelectedRecordings(const QList<int>& studentIds);
    void addRecording(std::map<QString, std::variant<QString, int>> dataMap);
    /*methods to access database fields here*/
    void logout();
private:
    QString baseUrl;
    QNetworkAccessManager *networkManager;
    QMap<QString, std::function<void(QNetworkReply*)>> replyHandlers;

    void handleLogin(QNetworkReply *reply);
    void handleGetHeaders(QNetworkReply *reply);
    void handleGetAllRecordings(QNetworkReply *reply);
    void handleDeleteAllRecordings(QNetworkReply *reply);
    void handleDeleteSelectedRecordings(QNetworkReply *reply);
    void handleAddRecording(QNetworkReply *reply);

    void initConnections();
private slots:
    void slotRequestFinished(QNetworkReply *reply);
signals:
    void loginSuccessful();
    void loginFailed(QNetworkReply::NetworkError errcode);
    void getHeadersSuccessful(QMap<QString, QStringList> fields);
    void getHeadersFailed(QNetworkReply::NetworkError errcode);
    void getAllRecordingsSuccessful(QStringList currentKeyOrder, QList<QList<QStandardItem*>> rows);
    void getAllRecordingsFailed(QNetworkReply::NetworkError errcode);
    void deleteAllRecordingsSuccessful(int countDeleted);
    void deleteAllRecordingsFailed(QNetworkReply::NetworkError errcode);
    void deleteSelectedRecordingsSuccessful();
    void deleteSelectedRecordingsFailed(QNetworkReply::NetworkError errcode);
    void addRecordingSuccessful();
    void addRecordingFailed(QNetworkReply::NetworkError errcode);
};

void multiarg(QByteArray& ba);

template<class T, class... Args>
void multiarg(QByteArray& ba, const T& arg, const Args&... args) {
    ba.append(QString(arg).toUtf8());
    multiarg(ba, args...);
};

#endif // BACKENDMANAGER_H
