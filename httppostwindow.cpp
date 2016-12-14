#include "httppostwindow.h"
#include "ui_http_post.h"

HttppostWindow::HttppostWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HttppostWindow)
{
    ui->setupUi(this);
    nam = new QNetworkAccessManager(this);
    nam->setCookieJar(new QNetworkCookieJar());

    connect(ui->pushButton_submit, SIGNAL(clicked()),
            this, SLOT(on_pushButton_submit_clicked()));
    connect(ui->pushButton_clear, SIGNAL(clicked()),
            this, SLOT(on_pushButton_clear_clicked()));
    connect(nam, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(finished(QNetworkReply*)));
}

HttppostWindow::~HttppostWindow()
{
    delete ui;
}

void HttppostWindow::on_pushButton_clear_clicked()
{
    ui->lineEdit_url->setText("http://");
    ui->pTextEdit_paras->clear();
    ui->textEdit_result->clear();
}

void HttppostWindow::on_pushButton_submit_clicked()
{
    if(ui->pushButton_submit->isEnabled())
        ui->pushButton_submit->setEnabled(false);
    if(ui->pushButton_clear->isEnabled())
        ui->pushButton_clear->setEnabled(false);

    QString url=ui->lineEdit_url->text();
    QString paras=ui->pTextEdit_paras->toPlainText();
    qDebug()<<paras;
    QByteArray post_data;
    post_data.append(paras.toLatin1());
    QNetworkRequest request= QNetworkRequest(QUrl(url));
    //nam->get(request); //get cookies

    request.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
    if(post_data.isEmpty()) {
        nam->get(request);
    } else {
        nam->post(request,post_data);
    }
}

void HttppostWindow::finished(QNetworkReply *reply)
{
    if(reply->error() == QNetworkReply::NoError) {

        //Here i check if there is a cookie for me in the reply and extract it
        QList<QNetworkCookie> cookies = qvariant_cast<QList<QNetworkCookie>>(reply->header(QNetworkRequest::SetCookieHeader));

        qDebug() << "Cookies reply: " << cookies;
        if(cookies.count() != 0){
            //you must tell which cookie goes with which url
            nam->cookieJar()->setCookiesFromUrl(cookies, QUrl(ui->lineEdit_url->text()));
        }

        const QString text = QObject::tr(reply->readAll());
        ui->textEdit_result->setText(text);
        ui->textEdit_plain->setPlainText(text);
    } else {
        ui->textEdit_result->setPlainText(reply->errorString());
    }

    if(!ui->pushButton_submit->isEnabled())
        ui->pushButton_submit->setEnabled(true);

    if(!ui->pushButton_clear->isEnabled())
        ui->pushButton_clear->setEnabled(true);
}
