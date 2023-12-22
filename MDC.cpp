
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAbstractItemView>
#include "bits/stdc++.h"
#include <QTextCodec>
using namespace std;
int MainWindow::MDC_READ()
{
    uint16_t MDC_ADD[4]= {0x1D48, 0x1D88, 0x1DC8,0x1F08};
    uint8_t MDC_NUM=1;
    uint8_t num[2];
    if(read_byte(0X1D00,1,num)!=1) return -1;
    MDC_NUM=num[0];
    if(MDC_NUM>15)MDC_NUM=0;

    std::cout <<MDC_NUM<< std::endl;
    ui->mdc_table->clearContents(); // 清除单元格的内容
    for(int i =0;i<15;i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem(QString::number(i));
        ui->mdc_table->setItem(i, 0, item);
    }

    ui->progressBar->setValue(ui->progressBar->value()+10); // 这将把进度条的值设置为 50
    int start_val = ui->progressBar->value();
    for(int i=0;i<MDC_NUM;i++)
    {

        uint8_t tmp[16];
        if(read_byte(MDC_ADD[i/4]+(i%4)*16,16,tmp)!=1)
        {
            return -1;
        }
        uint16_t MDC_ID=tmp[1]|(tmp[0]<<8);
        std::cout <<hex<<MDC_ID<< " ";
        char MDC_CONTACT[15]={0};
        memcpy(MDC_CONTACT,tmp+2,14);
        char ID_SHOW[5]={0};
        sprintf(ID_SHOW, "%04X", MDC_ID); // %04X确保输出至少有4个字符，不够时在前面填充0


        ui->mdc_table->setItem(i, 1, new QTableWidgetItem(QString::fromLocal8Bit(ID_SHOW,4)));
        std::cout <<MDC_CONTACT<< std::endl;
        int length = 14;

        // 从字符串末尾开始向前查找第一个非空格字符
        while (length > 0 && MDC_CONTACT[length - 1] == ' ') {
            length--;
        }


        ui->mdc_table->setItem(i, 2, new QTableWidgetItem(QString::fromLocal8Bit(MDC_CONTACT,length)));
        ui->progressBar->setValue(start_val+(100-start_val)/NUM_NEED_WRITE/MDC_NUM*(i+1)); // 这将把进度条的值设置为 50

    }
return 1;

}
int MainWindow::MDC_WRITE()
{

    int num=check_mdc();
    if( num==-1)
        return -1;
    uint16_t  MDC_ADD[4]={ 0x1D48, 0x1D88, 0x1DC8,0x1F08};
    uint8_t num_write[2];
    num_write[0]=(uint8_t)num;
    if(write_byte(0X1D00,1,num_write)!=1)  return -1;

    qDebug()<<num<<endl;


    ui->progressBar->setValue(ui->progressBar->value()+10); // 这将把进度条的值设置为 50
    int start_val = ui->progressBar->value();


    for(int i=0;i<num;i++){
      if(  write_byte(MDC_ADD[i/4]+(i%4)*16,16,MDC_INFO[i].sum)!=1)  return -1;

        ui->progressBar->setValue(start_val+(100-start_val)/NUM_NEED_WRITE/num*(i+2)); // 这将把进度条的值设置为 50
    }

    return 1;

}
int MainWindow::getCellContentLength(QTableWidget *tableWidget, int row, int column) {
    QTableWidgetItem *item = tableWidget->item(row, column);

    if(item != nullptr) {
        QString cellContent = item->text();
        return cellContent.length(); // 或者使用 cellContent.size();
    }

    return -1; // 返回-1表示未找到单元格或内容为空
}
void MainWindow::setCellValueToItemValue(int row, int col, QVariant str, int type)
{
    // 获取表格的行数和列数
    int tableRowCount = ui->mdc_table->rowCount();
    int tableColumnCount = ui->mdc_table->columnCount();

    // 检查插入的行和列是否超过表格范围
    if (row >= tableRowCount || col >= tableColumnCount)
    {
        QMessageBox::warning(nullptr, QStringLiteral("警告"), QStringLiteral("插入数值错误"));
        return;
    }

    // 创建一个新的表格项
    QTableWidgetItem* item = new QTableWidgetItem();

    // 设置表格项的用户数据，使用 Qt::UserRole 存储 QVariant
    item->setData(Qt::UserRole, QVariant::fromValue(str));

    // 根据类型(type)设置表格项的文本
    if (type == 0)
    {
        QString userData = item->data(Qt::UserRole).value<QString>();
        item->setText(userData);
    }
    else if (type == 1)
    {
        int userData = item->data(Qt::UserRole).toInt();
        item->setText(QString::number(userData));
    }

    // 将表格项插入到表格中的指定位置
    ui->mdc_table->setItem(row, col, item);
}
int MainWindow::read_mdc_param(QString filePath)
{
    // 清空表格内容和行数
    ui->mdc_table->clearContents();
    ui->mdc_table->setRowCount(0);

    // 读取 Excel 文件
    QXlsx::Document xlsx(filePath);
    QXlsx::Workbook* workBook = xlsx.workbook();

    // 检查工作簿是否为空指针
    if (workBook == nullptr)
    {
        QMessageBox::warning(nullptr, QStringLiteral("警告"), QStringLiteral("工作簿为空指针"));
        return -1;
    }

    // 获取工作薄的数量
    int sheetCount = workBook->sheetCount();

    // 检查工作薄数量是否小于 0
    if (sheetCount < 0)
    {
        QMessageBox::warning(nullptr, QStringLiteral("警告"), QStringLiteral("工作簿小于0个"));
        return -1;
    }
    qDebug() << QStringLiteral("工作薄数量") << sheetCount;

    // 获取第一个工作薄
    QXlsx::Worksheet* workSheet = static_cast<QXlsx::Worksheet*>(workBook->sheet(0));

    // 检查工作表是否为空指针
    if (workSheet == nullptr)
    {
        QMessageBox::warning(nullptr, QStringLiteral("警告"), QStringLiteral("MDC联系人工作表为空指针"));
        return -1;
    }

    // 获取工作表的行数和列数
    int rowCount = workSheet->dimension().rowCount();
    int columnCount = workSheet->dimension().columnCount();
    qDebug() << QStringLiteral("工作sheet的行数：") << rowCount << QStringLiteral("工作sheet的列数") << columnCount;

    // 检查行数和列数是否为非正数
    if (rowCount <= 0 || columnCount!=3)
    {
        QMessageBox::warning(nullptr, QStringLiteral("警告"), QStringLiteral("MDC联系人数据表格式错误！"));
        return -1;
    }

    // 设置表格的行数
    ui->mdc_table->setRowCount(rowCount);

    // 设置表格的垂直表头标签
    QStringList m_Vlist;
    m_Vlist << QStringLiteral("1") << QStringLiteral("2") << QStringLiteral("3") << QStringLiteral("4");
    ui->mdc_table->setVerticalHeaderLabels(m_Vlist);

    QString cellStr;
    // 遍历工作表的每个单元格，将值插入到表格中
    for (int i = 1; i <= rowCount; ++i)
    {
        for (int j = 1; j <= columnCount; ++j)
        {
            QXlsx::Cell* cell = workSheet->cellAt(i, j);
            if (cell == nullptr)
                cellStr = "";
            else
                cellStr = cell->value().toString();

            // 调用函数将值插入表格
            setCellValueToItemValue(i - 1, j - 1, cellStr, 0);
        }
    }
    return 1;
}
