#include"uart.h"

#include "mainwindow.h"
// 串口初始化（参数配置）
void MY_UART::SerialPortInit()
{
    serial = new QSerialPort;                       //申请内存,并设置父对象

    // 获取计算机中有效的端口号，然后将端口号的名称给端口选择控件
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        serial->setPort(info);                      // 在对象中设置串口
        if(serial->open(QIODevice::ReadWrite))      // 以读写方式打开串口
        {
            ui->PortBox->addItem(info.portName());  // 添加计算机中的端口
            serial->close();                        // 关闭
        } else
        {
            qDebug() << "串口打开失败，请重试";
        }
    }

    // 参数配置
    // 波特率，波特率默认选择57600 ，禁止用户点击
    ui->BaudBox->addItem("57600");
    serial->setBaudRate(QSerialPort::Baud57600);
    ui->BaudBox->setDisabled(true);

    // 校验，校验默认选择无
    ui->ParityBox->addItem("无");
    serial->setParity(QSerialPort::NoParity);

    // 数据位，数据位默认选择8位
    ui->BitBox->addItem("8");
    serial->setDataBits(QSerialPort::Data8);

    // 停止位，停止位默认选择1位
    ui->StopBox->addItem("1");
    serial->setStopBits(QSerialPort::OneStop);

    // 控制流，默认选择无
    ui->ControlBox->addItem("无");
    serial->setFlowControl(QSerialPort::NoFlowControl);

    // 刷新串口
    RefreshSerialPort(0);

    // 信号
connect(serial,&QSerialPort::readyRead,this,&MainWindow::DataReceived);      // 接收数据
connect(ui->SendWordOrder,&QPushButton::clicked,this,&MainWindow::DataSend); // 发送数据
connect(ui->SendButton,&QPushButton::clicked,this,&MainWindow::DataSend);    // 发送数据
connect(ui->SendEditBtn1,&QPushButton::clicked,this,&MainWindow::DataSend);  // 发送数据
connect(ui->SendEditBtn2,&QPushButton::clicked,this,&MainWindow::DataSend);  // 发送数据
connect(ui->SendEditBtn3,&QPushButton::clicked,this,&MainWindow::DataSend);  // 发送数据
}
