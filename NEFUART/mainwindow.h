#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMessageBox>

#include <QMainWindow>
#include <qdebug.h>
#include <QtSerialPort/QSerialPort>         // 提供访问串口的功能
#include <QtSerialPort/QSerialPortInfo>     // 提供系统中存在的串口信息
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSerialPort     *serial1;                            // 定义全局的串口对象（第三步）
    QSerialPort     *serial2;

private slots:


    void on_open1_clicked();

    void on_clear_recv1_clicked();

    void on_clear_recv2_clicked();

    void on_clear_send1_clicked();

    void on_clear_send2_clicked();

    void on_open2_clicked();



    void on_send1_clicked();

    void on_send2_clicked();

    void on_send_all_clicked();

private:
    Ui::MainWindow *ui;

    void RefreshSerialPort(int index);
    void SerialPortInit();                      // 串口初始化（参数配置）
   void DataReceived1();
      void DataReceived2();

        QStringList     baudList;                           //波特率
        QStringList     parityList;                         //校验位
        QStringList     dataBitsList;                       //数据位
        QStringList     stopBitsList;                       //停止位
        QStringList     flowControlList;                    //控制流

};

#endif // MAINWINDOW_H
