#ifndef HTTPPOSTWINDOW_H
#define HTTPPOSTWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkCookie>
#include <QNetworkCookieJar>
#include <QNetworkReply>
#include <QTextCodec>
#include <QtDebug>

namespace Ui {
class HttppostWindow;
}

class HttppostWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit HttppostWindow(QWidget *parent = 0);
    ~HttppostWindow();
    
private slots:
    void on_pushButton_clear_clicked();

    void on_pushButton_submit_clicked();

    void finished(QNetworkReply *reply);

private:
    Ui::HttppostWindow *ui;
    QNetworkAccessManager *nam;
};

#endif // HTTPPOSTWINDOW_H
