
#include "ui_mainwindow.h"

#include "mainwindow.h"
#include "bits/stdc++.h"

using namespace std;
// 串口初始化（参数配置）
void MainWindow::SerialPortInit()
{


    serial1 = new QSerialPort;                       //申请内存,并设置父对象

    // 获取计算机中有效的端口号，然后将端口号的名称给端口选择控件


        QSerialPort temp_serial1;
        bool any_uart=0;
           foreach (const QSerialPortInfo &Info, QSerialPortInfo::availablePorts()) {

               qDebug() << "portName    :"  << Info.portName();//调试时可以看的串口信息
               qDebug() << "Description   :" << Info.description();
               qDebug() << "Manufacturer:" << Info.manufacturer();
               temp_serial1.setPort(Info);
               if(temp_serial1.open(QIODevice::ReadWrite)){//如果串口是可以读写方式打开的
                      ui->uart1->addItem(Info.portName());
any_uart=1;
                   temp_serial1.close();

               }
           }

           if(!any_uart)
           {
               ui->uart1->addItem("无可用串口"); // 添加新的串口项
               ui->open1->setEnabled(false);
           }
}

// 刷新串口
void MainWindow::RefreshSerialPort(int index)
{


    // 获取ComboBox中的所有选项并存储在portNameList中

    QStringList portNameList;
    for (int i = 0; i < ui->uart1->count(); ++i) {
        QString itemText = ui->uart1->itemText(i);
        portNameList.append(itemText);
    }

    // 现在portNameList中包含了ComboBox中的所有选项
    // 可以使用portNameList进行后续处理

    QString prev_uart = ui->uart1->currentText(); // 获取当前选择的串口

    // 获取当前可用串口列表
    QStringList currentPortNames;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        currentPortNames.append(info.portName());
    }

    // 检查串口列表是否发生变化
    if (currentPortNames != portNameList) {



        portNameList = currentPortNames; // 更新串口列表
        ui->uart1->clear(); // 清空combobox
        ui->uart1->addItems(portNameList); // 添加新的串口项

        int index = ui->uart1->findText(prev_uart);
        if (index != -1) {
            ui->uart1->setCurrentText(prev_uart); // 设置回之前选择的串口
        }else
        {
            if(serial1->isOpen())
            {
                 MainWindow::on_open1_clicked(); //打开串口
                 QMessageBox::warning(this,tr("提示"),tr("串口断开连接!"),QMessageBox::Ok);

            }
            int numberOfItems = portNameList.count(); // 获取项目数量
            if(numberOfItems==0)
            {

                ui->uart1->addItem("无可用串口"); // 添加新的串口项
                ui->open1->setEnabled(false);

                return;
            }else
            {
                ui->open1->setEnabled(true);
            }
        }
        serial1->setPortName(ui->uart1->currentText()); // 设置串口号
    }


}
void MainWindow::DataReceived1()
{
    return;
    char BUF[512] = {0};                                       // 存储转换类型后的数据

     QByteArray data = serial1->readAll(); // 读取数据
     QString hexString = data.toHex(' ').toUpper(); // 转换为16进制字符串，以空格分隔并转换为大写
     qDebug() <<"RECV:" <<hexString;

    if(!data.isEmpty())                                 // 接收到数据
    {




    }
}
void MainWindow::CHECK_MDC_TABLE()
{
    // 假设 tableWidget 是你的 QTableWidget 实例
    int row_index = 0;      // 行索引
    int column_index = 1;   // 列索引

    QTableWidgetItem *item = ui->mdc_table->item(row_index, column_index);

    if (item != nullptr) {
        QString data = item->data(Qt::DisplayRole).toString();
        qDebug() << "Row " << row_index << ", Column " << column_index << " 的数据是: " << data;
    } else {
        qDebug() << "找不到指定的单元格";
    }

}

