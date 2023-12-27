#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAbstractItemView>
#include "bits/stdc++.h"
#include <QTextCodec>
using namespace std;
void MainWindow::onTimeout() {
    RefreshSerialPort(0);

    for(int i =0;i<15;i++)
    {

        ui->mdc_table->setItem(i, 0, new QTableWidgetItem(QString::number(i+1)));
    }


}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->open1->setStyleSheet("color: green;");

    SerialPortInit();

    timer = new QTimer(this);

    // 连接定时器的超时信号到槽函数
    connect(timer, &QTimer::timeout, this, &MainWindow::onTimeout);

    // 设置定时器间隔，单位为毫秒
    timer->setInterval(1000); // 1000毫秒 = 1秒

    // 启动定时器
    timer->start();
    ui->mdc_table->setColumnWidth(0, 40);
    ui->mdc_table->setColumnWidth(1, 60);
    ui->mdc_table->setColumnWidth(2, 200);
    ui->name_table->setColumnWidth(0, 60);
    ui->name_table->setColumnWidth(1, 180);
    ui->progressBar->setValue(0);

    for(int i =0;i<15;i++)
    {

        ui->mdc_table->setItem(i, 0, new QTableWidgetItem(QString::number(i+1)));
    }

    for(int i =0;i<200;i++)
    {

        ui->name_table->setItem(i, 0, new QTableWidgetItem(QString::number(i+1)));
    }
    for (int row = 0; row < ui->name_table->rowCount(); ++row) {
        QTableWidgetItem *item = ui->name_table->item(row, 0);
        if (item)
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_open1_clicked() //打开串口
{

    QString temp;
    if(serial1->isOpen())                                  // 如果串口打开了，先给他关闭
    {

        serial1->clear();
        serial1->close();
        // 关闭状态，按钮显示“打开串口”
        ui->open1->setText("打开串口");

        // 关闭状态，颜色为绿色
        ui->open1->setStyleSheet("color: green;");
        // 关闭，显示灯为红色

        // 清空数据
        ui->uart1->setEnabled(true);
        ui->write->setEnabled(false);
        ui->read->setEnabled(false);

    }
    else                                             // 如果串口关闭了，先给他打开
    {
        //当前选择的串口名字
        temp=ui->uart1->currentText().mid(0,ui->uart1->currentText().indexOf(':'));
        serial1->setPortName(temp);
        //波特率
        serial1->setBaudRate(QSerialPort::Baud38400);
        // 停止位，停止位默认选择1位


        serial1->setStopBits(QSerialPort::OneStop);

        // 数据位，数据位默认选择8位

        serial1->setDataBits(QSerialPort::Data8);

        // 校验，校验默认选择无

        serial1->setParity(QSerialPort::NoParity);

        // 控制流，默认选择无
        serial1->setFlowControl(QSerialPort::NoFlowControl);
        //用ReadWrite 的模式尝试打开串口，无法收发数据时，发出警告
        if(!serial1->open(QIODevice::ReadWrite))
        {
            QMessageBox::warning(this,tr("提示"),tr("串口打开失败!"),QMessageBox::Ok);
            // 关闭状态，按钮显示“打开串口”
            ui->open1->setText("打开串口");

            // 关闭状态，颜色为绿色
            ui->open1->setStyleSheet("color: green;");
            // 关闭，显示灯为红色

            // 清空数据
            ui->uart1->setEnabled(true);
            ui->write->setEnabled(false);
            ui->read->setEnabled(false);


            return;

        }
        serial1->setDataTerminalReady(true);
        //            connect(serial1, SIGNAL(readyRead()), this, SLOT(DataReceived1())); // Connect data reception signal

        // 打开状态，按钮显示“关闭串口”
        ui->open1->setText("关闭串口");
        // 打开状态，禁止用户操作



        // 打开状态，颜色为红色
        ui->open1->setStyleSheet("color: red;");
        // 打开，显示灯为绿色
        serial1->setPortName(ui->uart1->currentText());
        ui->uart1->setEnabled(false);
        ui->write->setEnabled(true);
        ui->read->setEnabled(true);

        qDebug()<<"OPEN:"<<temp<<"OK"<<endl;
    }
}






// 捕捉粘贴事件
void MainWindow::keyPressEvent(QKeyEvent *event) {
    if ((event->modifiers() & Qt::ControlModifier) && (event->key() == Qt::Key_V)) {
        pasteFromClipboard(); // 执行粘贴操作
    } else {
        QWidget::keyPressEvent(event); // 其他情况正常处理按键事件
    }
}

// 粘贴操作的实现


void MainWindow::pasteFromClipboard() {
    QClipboard *clipboard = QApplication::clipboard();
    QString clipboardText = clipboard->text();

    // 解析粘贴板内容，以换行符和制表符分割
    QStringList rows = clipboardText.split("\n", Qt::SkipEmptyParts);
    for (int i = 0; i < rows.size(); ++i) {
        QStringList columns = rows[i].split("\t", Qt::SkipEmptyParts);
        for (int j = 0; j < columns.size(); ++j) {
            QTableWidgetItem *item = new QTableWidgetItem(columns[j]);
            int currentRow = ui->mdc_table->currentRow();
            int  currentColumn= ui->mdc_table->currentColumn();
            ui->mdc_table->setItem(currentRow, currentColumn, item);

        }
    }
}


void MainWindow::on_pushButton_clicked()
{
    if(timetime_set()==-1) {
        return ;
    }
    uint8_t name[17]="\x84\x6C\x88\xD9\x8C\x6C\x88\x18\x8F\x8C\x96\x27\x80\x07";
    write_byte(0x0F50 , 16, name);

NAME_READ();


}




void MainWindow::on_read_clicked()
{
    ui->progressBar->setValue(0);

    QWidget *mainWindow = QApplication::activeWindow(); // 获取当前活动的主窗口
    if (mainWindow) {
        mainWindow->setDisabled(true); // 禁用主窗口中的所有部件
    }
    if(timetime_set()==-1) {
        if (mainWindow) {
            mainWindow->setDisabled(false); // 禁用主窗口中的所有部件
        }
        ui->progressBar->setValue(0);

        return ;

    }
    ui->progressBar->setValue(10);

   if( MDC_READ()!=1)goto end;
   ui->progressBar->setValue(40);

   if( WELCOME_READ()!=1)goto end;
   ui->progressBar->setValue(70);

           if( NAME_READ()!=1)goto end;

           ui->progressBar->setValue(100);

   QMessageBox::warning(this,tr("提示"),tr("读取成功!"),QMessageBox::Ok);
end:
   ui->progressBar->setValue(0);

    if (mainWindow) {
        mainWindow->setDisabled(false); // 禁用主窗口中的所有部件
    }

}

void MainWindow::on_write_clicked()
{
    ui->progressBar->setValue(0);
    QWidget *mainWindow = QApplication::activeWindow(); // 获取当前活动的主窗口
    if (mainWindow) {
        mainWindow->setDisabled(true); // 禁用主窗口中的所有部件
    }

    if(timetime_set()==-1) {
        if (mainWindow) {
            mainWindow->setDisabled(false); // 禁用主窗口中的所有部件
        }
        ui->progressBar->setValue(0);

        return ;

    }
    ui->progressBar->setValue(10);

    if(MDC_WRITE()!=1) goto end;
    ui->progressBar->setValue(40);

    if(WELCOME_WRITE()!=1) goto end;
    ui->progressBar->setValue(70);


            if(NAME_WRITE()!=1) goto end;
            ui->progressBar->setValue(100);


    QMessageBox::warning(this, tr("提示"), tr("写入成功!"), QMessageBox::Ok);

end:
    ui->progressBar->setValue(0);

    if (mainWindow) {
        mainWindow->setDisabled(false); // 禁用主窗口中的所有部件
    }

}



