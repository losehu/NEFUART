#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    SerialPortInit();
}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::on_open1_clicked()
{

    QString temp;
    if(serial1->isOpen())                                  // 如果串口打开了，先给他关闭
    {
        serial1->clear();
        serial1->close();
        // 关闭状态，按钮显示“打开串口”
        ui->open1->setText("打开串口");
        // 关闭状态，允许用户操作
        ui->baud1->setDisabled(false);
        ui->stop1->setDisabled(false);
        ui->data1->setDisabled(false);
        ui->check1->setDisabled(false);

        // 禁止操作“发送字符操作”
        ui->send1->setDisabled(true);
        ui->send_all->setDisabled(true);
        // 关闭状态，颜色为绿色
        ui->open1->setStyleSheet("color: green;");
        // 关闭，显示灯为红色

        // 清空数据

    }
    else                                             // 如果串口关闭了，先给他打开
    {
        //当前选择的串口名字
        temp=ui->uart1->currentText().mid(0,ui->uart1->currentText().indexOf(':'));
        serial1->setPortName(temp);
        qDebug()<<"OPEN:"<<temp<<endl;
        //波特率
        serial1->setBaudRate(    ui->baud1->currentText().toInt());
        qDebug()<<"BAUD:"<<ui->baud1->currentText().toInt()<<endl;
        // 停止位，停止位默认选择1位

        temp= ui->stop1->currentText();
        qDebug()<<"STOP:"<<temp<<endl;
        if(temp=="1")
            serial1->setStopBits(QSerialPort::OneStop);
        else if(temp=="1.5")
            serial1->setStopBits(QSerialPort::OneAndHalfStop);
        else
            serial1->setStopBits(QSerialPort::TwoStop);
        // 数据位，数据位默认选择8位
        temp= ui->data1->currentText();
        qDebug()<<"DATA:"<<temp<<endl;
        if(temp=="5")
            serial1->setDataBits(QSerialPort::Data5);
        else if(temp=="6")
            serial1->setDataBits(QSerialPort::Data6);
        else if (temp=="7")
            serial1->setDataBits(QSerialPort::Data7);
        else if (temp=="8")
            serial1->setDataBits(QSerialPort::Data8);

        // 校验，校验默认选择无
        temp= ui->check1->currentText();
        qDebug()<<"CHECK:"<<temp<<endl;
        if(temp=="None")
            serial1->setParity(QSerialPort::NoParity);
        else if(temp=="Odd")
            serial1->setParity(QSerialPort::OddParity);
        else if (temp=="Even")
            serial1->setParity(QSerialPort::EvenParity);
        else if (temp=="Space")
            serial1->setParity(QSerialPort::SpaceParity);
        else if (temp=="Mark")
            serial1->setParity(QSerialPort::MarkParity);
        // 控制流，默认选择无
        serial1->setFlowControl(QSerialPort::NoFlowControl);
        //用ReadWrite 的模式尝试打开串口，无法收发数据时，发出警告
        if(!serial1->open(QIODevice::ReadWrite))
        {
            QMessageBox::warning(this,tr("提示"),tr("串口打开失败!"),QMessageBox::Ok);
            return;
        }


        // 打开状态，按钮显示“关闭串口”
        ui->open1->setText("关闭串口");
        // 打开状态，禁止用户操作
        ui->baud1->setDisabled(true);
        ui->stop1->setDisabled(true);
        ui->check1->setDisabled(true);
        ui->data1->setDisabled(true);

        // 允许操作“发送字符操作”
        ui->send1->setDisabled(false);
        // 打开状态，颜色为红色
        ui->open1->setStyleSheet("color: red;");
        // 打开，显示灯为绿色
        serial1->setPortName(ui->uart1->currentText());
        qDebug()<<"OK"<<endl;
    }
}


void MainWindow::on_clear_recv1_clicked()
{
    ui->text_recv1->clear();
}


void MainWindow::on_clear_recv2_clicked()
{
        ui->text_recv2->clear();
}


void MainWindow::on_clear_send1_clicked()
{
        ui->text_send1->clear();
}


void MainWindow::on_clear_send2_clicked()
{
     ui->text_send2->clear();
}


void MainWindow::on_open2_clicked()
{
    QString temp;
        if(serial2->isOpen())                                  // 如果串口打开了，先给他关闭
        {
            serial2->clear();
            serial2->close();
            // 关闭状态，按钮显示“打开串口”
            ui->open2->setText("打开串口");
            // 关闭状态，允许用户操作
            ui->baud2->setDisabled(false);
            ui->stop2->setDisabled(false);
            ui->data2->setDisabled(false);
            ui->check2->setDisabled(false);

            // 禁止操作“发送字符操作”
            ui->send2->setDisabled(true);
            ui->send_all->setDisabled(true);
            // 关闭状态，颜色为绿色
            ui->open2->setStyleSheet("color: green;");
            // 关闭，显示灯为红色

            // 清空数据

        }
        else                                             // 如果串口关闭了，先给他打开
        {
            //当前选择的串口名字
            temp=ui->uart2->currentText().mid(0,ui->uart2->currentText().indexOf(':'));
            serial2->setPortName(temp);
            qDebug()<<"OPEN:"<<temp<<endl;
            //波特率
            serial2->setBaudRate(    ui->baud2->currentText().toInt());
            qDebug()<<"BAUD:"<<ui->baud2->currentText().toInt()<<endl;
            // 停止位，停止位默认选择1位

            temp= ui->stop2->currentText();
            qDebug()<<"STOP:"<<temp<<endl;
            if(temp=="1")
                serial2->setStopBits(QSerialPort::OneStop);
            else if(temp=="1.5")
                serial2->setStopBits(QSerialPort::OneAndHalfStop);
            else
                serial2->setStopBits(QSerialPort::TwoStop);
            // 数据位，数据位默认选择8位
            temp= ui->data2->currentText();
            qDebug()<<"DATA:"<<temp<<endl;
            if(temp=="5")
                serial2->setDataBits(QSerialPort::Data5);
            else if(temp=="6")
                serial2->setDataBits(QSerialPort::Data6);
            else if (temp=="7")
                serial2->setDataBits(QSerialPort::Data7);
            else if (temp=="8")
                serial2->setDataBits(QSerialPort::Data8);

            // 校验，校验默认选择无
            temp= ui->check2->currentText();
            qDebug()<<"CHECK:"<<temp<<endl;
            if(temp=="None")
                serial2->setParity(QSerialPort::NoParity);
            else if(temp=="Odd")
                serial2->setParity(QSerialPort::OddParity);
            else if (temp=="Even")
                serial2->setParity(QSerialPort::EvenParity);
            else if (temp=="Space")
                serial2->setParity(QSerialPort::SpaceParity);
            else if (temp=="Mark")
                serial2->setParity(QSerialPort::MarkParity);
            // 控制流，默认选择无
            serial2->setFlowControl(QSerialPort::NoFlowControl);
            //用ReadWrite 的模式尝试打开串口，无法收发数据时，发出警告
            if(!serial2->open(QIODevice::ReadWrite))
            {
                QMessageBox::warning(this,tr("提示"),tr("串口打开失败!"),QMessageBox::Ok);
                return;
            }


            // 打开状态，按钮显示“关闭串口”
            ui->open2->setText("关闭串口");
            // 打开状态，禁止用户操作
            ui->baud2->setDisabled(true);
            ui->stop2->setDisabled(true);
            ui->check2->setDisabled(true);
            ui->data2->setDisabled(true);

            // 允许操作“发送字符操作”
            ui->send2->setDisabled(false);
            // 打开状态，颜色为红色
            ui->open2->setStyleSheet("color: red;");
            // 打开，显示灯为绿色
            serial2->setPortName(ui->uart2->currentText());
            qDebug()<<"OK"<<endl;
        }
}




void MainWindow::on_send1_clicked()
{    serial1->write(ui->text_send1->toPlainText().toLatin1());      // 串口发送数据

}


void MainWindow::on_send2_clicked()
{
        serial2->write(ui->text_send2->toPlainText().toLatin1());      // 串口发送数据
}


void MainWindow::on_send_all_clicked()
{
        serial1->write(ui->text_send1->toPlainText().toLatin1());      // 串口发送数据
       serial2->write(ui->text_send2->toPlainText().toLatin1());      // 串口发送数据
}

