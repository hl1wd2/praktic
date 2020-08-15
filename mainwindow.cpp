#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QPlainTextEdit>
#include <QStatusBar>
#include <QCheckBox>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_series = new QLineSeries();
    m_chart = new QChart();
    val = new QString();
    m_chart->addSeries(m_series);
    m_chart->legend()->hide();
    m_chart->setTitle("YEEEEET!");

    QValueAxis *axisX = new QValueAxis();
    axisX->setTitleText("OxO");
    axisX->setLabelFormat("%f");
    axisX->setTickCount(1);
    m_chart->addAxis(axisX, Qt::AlignBottom);
    m_series->attachAxis(axisX);
    QValueAxis *axisY = new QValueAxis();
    axisY->setLabelFormat("%f");
    axisY->setTitleText("OyO");
    m_chart->addAxis(axisY, Qt::AlignLeft);
    m_series->attachAxis(axisY);
    ui->graphicsView->setChart(m_chart);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_chart;
    delete val;
}

void MainWindow::vaaac(){
    database massafaca;

}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"",tr("JSON (*.json *.txt)"));
    if(fileName.isEmpty())return;
    //QString val;
    QFile file(fileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    *val = file.readAll();
    //ui->plainTextEdit->document()->setPlainText(val);
    json2Chatrs(*val);
}

//Эта функция не нужна
//void MainWindow::on_actionOpenCSV_triggered() {
  /*QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("CSV (*.csv)"));
    if(fileName.isEmpty())return;
    QFile file(fileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    QStringList uName;
    QString temp = in.readLine().toUtf8();
    for(QString tempName : temp.split(";")){
    uName.append(tempName);
    }
    int i=0;
    while (!in.atEnd()){
    prib.resize(i+1);
    prib[i].name=ex;
    QString line = in.readLine().toUtf8();
    int j=0;
    for (QString item : line.split(";")) {
    prib[i].datchiki.push_back(uName[j]);
    prib[i].pokazaniya.push_back(item);
    if(j==0)
    prib[i].date=QDateTime::fromString(item,"yyyy-MM-dd hh:mm:ss");
    j++;
    }
    i++;
    }
    min_date=prib[0].date;
    max_date=prib[prib.size()-1].date;
    ui->dateTimeEdit->setDateTimeRange(min_date,max_date);
    ui->dateTimeEdit_2->setDateTimeRange(min_date,max_date);*/
//}

//Функция читки с сайта (не нужна)
void MainWindow::on_actionURL_triggered()
{
    QString url = "http://webrobo.mgul.ac.ru:3000/db_api_REST/calibr/last5min";
    QSslConfiguration ssl = QSslConfiguration::defaultConfiguration();
    ssl.setProtocol(QSsl::AnyProtocol);
    QSslConfiguration::setDefaultConfiguration(ssl);
    QNetworkRequest req;
    req.setUrl(QUrl(url));
    req.setSslConfiguration(ssl);
    manager->get(req);
}
//Функция читки с сайта (не нужна)
void MainWindow::onResult(QNetworkReply *reply) {
    if(reply->error() != QNetworkReply::NoError){
        reply->ignoreSslErrors();
    }else{
        QString res = reply->readAll();
        //ui->plainTextEdit->document()->setPlainText(res);
        json2Chatrs(res);
    }
    reply->deleteLater();
}
//Функция построения графиков
void MainWindow::json2Chatrs(QString jsonstr){
    QJsonDocument json = QJsonDocument::fromJson(jsonstr.toUtf8());
    QJsonObject jsonObj = json.object();
    int x = 0;
    bool flagFirst = true;
    for(const auto& i : jsonObj.keys()){
        QJsonValue value = jsonObj.value(QString(i));
        QJsonObject item = value.toObject();
        QString date = item.value(QString("Date")).toString();
        QString uName = item.value(QString("uName")).toString();
        if(uName == "Тест Студии"){
            QJsonObject temp = item.value(QString("data")).toObject();
            QString pressure = temp.value(QString("BMP280_pressure")).toString();
            if(flagFirst){
                m_chart->axisX()->setRange(x, x);
                m_chart->axisY()->setRange(pressure.toDouble(), pressure.toDouble());
                flagFirst = false;
            }
            addPoint(x, pressure.toDouble());
            x++;
        }
     }
}
void MainWindow::addPoint(qreal x, qreal y){
    m_series->append(x, y);
    qreal xmin,xmax,ymin,ymax;
    xmax = dynamic_cast<QValueAxis*>(m_chart->axisX())->max();
    xmin = dynamic_cast<QValueAxis*>(m_chart->axisX())->min();
    ymax = dynamic_cast<QValueAxis*>(m_chart->axisY())->max();
    ymin = dynamic_cast<QValueAxis*>(m_chart->axisY())->min();
    xmin = (xmin > x) ? x : xmin;
    xmax = (xmax < x) ? x : xmax;
    ymin = (ymin > y) ? y : ymin;
    ymax = (ymax < y) ? y : ymax;
    m_chart->axisX()->setRange(xmin, xmax);
    m_chart->axisY()->setRange(ymin, ymax);
}

/*void MainWindow::on_actionClose_triggered()
{
нужна сделать... потом
}*/
