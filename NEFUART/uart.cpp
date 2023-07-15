
#include "ui_mainwindow.h"

#include "mainwindow.h"

// 串口初始化（参数配置）
void MainWindow::SerialPortInit()
{

    serial1 = new QSerialPort;                       //申请内存,并设置父对象
    serial2= new QSerialPort;                       //申请内存,并设置父对象

    // 获取计算机中有效的端口号，然后将端口号的名称给端口选择控件


        QSerialPort temp_serial1;
                QSerialPort temp_serial2;
           foreach (const QSerialPortInfo &Info, QSerialPortInfo::availablePorts()) {

               qDebug() << "portName    :"  << Info.portName();//调试时可以看的串口信息
               qDebug() << "Description   :" << Info.description();
               qDebug() << "Manufacturer:" << Info.manufacturer();
               temp_serial1.setPort(Info);
               if(temp_serial1.open(QIODevice::ReadWrite)){//如果串口是可以读写方式打开的
                      ui->uart1->addItem(Info.portName()+':'+Info.manufacturer());

                   temp_serial1.close();

               }
           }

 foreach (const QSerialPortInfo &Info, QSerialPortInfo::availablePorts()) {

     qDebug() << "portName    :"  << Info.portName();//调试时可以看的串口信息
     qDebug() << "Description   :" << Info.description();
     qDebug() << "Manufacturer:" << Info.manufacturer();
     temp_serial2.setPort(Info);
     if(temp_serial2.open(QIODevice::ReadWrite)){//如果串口是可以读写方式打开的
            ui->uart2->addItem(Info.portName()+':'+Info.manufacturer());

         temp_serial2.close();

     }
 }

//    // 参数配置
//    // 波特率，波特率默认选择57600 ，禁止用户点击
//    ui->BaudBox->addItem("57600");
//    serial1->setBaudRate(QSerialPort::Baud57600);
//    ui->BaudBox->setDisabled(true);

//    // 校验，校验默认选择无
//    ui->ParityBox->addItem("无");
//    serial1->setParity(QSerialPort::NoParity);

//    // 数据位，数据位默认选择8位
//    ui->BitBox->addItem("8");
//    serial1->setDataBits(QSerialPort::Data8);

//    // 停止位，停止位默认选择1位
//    ui->StopBox->addItem("1");
//    serial1->setStopBits(QSerialPort::OneStop);

//    // 控制流，默认选择无
//    ui->ControlBox->addItem("无");
//    serial1->setFlowControl(QSerialPort::NoFlowControl);

//    // 刷新串口
 // RefreshSerialPort(0);

//    // 信号
//connect(serial1,&QSerialPort::readyRead,this,&MainWindow::DataReceived);      // 接收数据
//connect(ui->SendWordOrder,&QPushButton::clicked,this,&MainWindow::DataSend); // 发送数据
//connect(ui->SendButton,&QPushButton::clicked,this,&MainWindow::DataSend);    // 发送数据
//connect(ui->SendEditBtn1,&QPushButton::clicked,this,&MainWindow::DataSend);  // 发送数据
//connect(ui->SendEditBtn2,&QPushButton::clicked,this,&MainWindow::DataSend);  // 发送数据
//connect(ui->SendEditBtn3,&QPushButton::clicked,this,&MainWindow::DataSend);  // 发送数据
            connect(serial1,&QSerialPort::readyRead,this,&MainWindow::DataReceived1);
                    connect(serial2,&QSerialPort::readyRead,this,&MainWindow::DataReceived2);
}

// 刷新串口
void MainWindow::RefreshSerialPort(int index)
{


    QStringList portNameList;                                        // 存储所有串口名
        if(index != 0)
        {
            serial1->setPortName(ui->uart1->currentText());             //设置串口号
        }
        else
        {
            ui->uart1->clear();                                        //关闭串口号
            ui->uart1->addItem("刷新");                                //添加刷新
            foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts()) //添加新串口
            {
                portNameList.append(info.portName());
            }
            ui->uart1->addItems(portNameList);
            ui->uart1->setCurrentIndex(1);                             // 当前串口号为COM1
            serial1->setPortName(ui->uart1->currentText());             //设置串口号
       }

}
void MainWindow::DataReceived1()
{
    char BUF[512] = {0};                                       // 存储转换类型后的数据
    QByteArray data = serial1->readAll();                      // 读取数据

    if(!data.isEmpty())                                 // 接收到数据
    {
        QString str = ui->text_recv1->toPlainText();  // 返回纯文本
        str += tr(data);                         // 数据是一行一行传送的，要保存所有数据
        ui->text_recv1->clear();                      // 清空之前的数据
        ui->text_recv1->append(str);                  // 将数据放入控件中
        qDebug() << "str info: " << ui->text_recv1->toPlainText();

         // 清除之前的数据，防止追加，因为每次获取的数据不一样
        int index = str.indexOf("\r\n");                // 找到，返回索引值，找不到，返回-1
        if(index != -1)
        {
            snprintf(BUF,500,"%s", str.left(index + 2).toUtf8().data()); // QString转为char * 类型
            qDebug() << "BUF info: " << BUF;        // 数据类型转换成功
            str.remove(0,index + 2);

            // 处理获取到的数据，将其放入对应的控件中
            // .....

        }
    }
}




void MainWindow::DataReceived2()
{
    char BUF[2048] = {0};                                       // 存储转换类型后的数据
    QByteArray data = serial2->readAll();                      // 读取数据

    if(!data.isEmpty())                                 // 接收到数据
    {
        QString str = ui->text_recv2->toPlainText();  // 返回纯文本
        str += tr(data);                         // 数据是一行一行传送的，要保存所有数据
        ui->text_recv2->clear();                      // 清空之前的数据
        ui->text_recv2->append(str);                  // 将数据放入控件中
        qDebug() << "str2 info: " << ui->text_recv2->toPlainText();

         // 清除之前的数据，防止追加，因为每次获取的数据不一样
        int index = str.indexOf("\r\n");                // 找到，返回索引值，找不到，返回-1
        if(index != -1)
        {
            snprintf(BUF,2048,"%s", str.left(index + 2).toUtf8().data()); // QString转为char * 类型
            qDebug() << "BUF info: " << BUF;        // 数据类型转换成功
            str.remove(0,index + 2);

            // 处理获取到的数据，将其放入对应的控件中
            // .....

        }
    }
}
