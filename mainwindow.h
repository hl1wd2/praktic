#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QtCharts>
#include <QNetworkReply>
#include <vector>
using namespace QtCharts;
//Структура с нужными полями которые будут читаться тип данных наконец то верен
struct database{
    std::vector<int> system_RSSI;
    std::vector<double> TCS34725_lux;
    std::vector<double> colorTempCT;
    std::vector<double> BH1750_lux;
    std::vector<int> BH1750_blink;
    std::vector<int> BH1750_blinkmin;
    std::vector<int> BH1750_blinkmax;
    std::vector<double> AM2321_temp;
    std::vector<double> AM2321_humidity;
    std::vector<double> BME280_temp;
    std::vector<double> BME280_pressure;
    std::vector<double> BME280_humidity;
    std::vector<double> BMP280_temp;
    std::vector<double> BMP280_pressure;
    std::vector<double> DS18B20_temp;

};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();
    void onResult(QNetworkReply *reply);

    void on_actionURL_triggered();

    //void on_actionOpenCSV_triggered();

    //void on_actionLoad_HTTPS_triggered();

    //void on_actionClose_triggered();

private:
    //json2Chatrs рисует графики addPoint добавляет точку vaaac ничего не делает
    void json2Chatrs(QString jsonstr);
    void addPoint(qreal x, qreal y);
    void vaaac();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *manager;
    QLineSeries *m_series;
    QChart *m_chart;
    QString *val;
};
#endif // MAINWINDOW_H
