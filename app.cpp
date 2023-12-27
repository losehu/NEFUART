#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAbstractItemView>
#include "bits/stdc++.h"
#include <QTextCodec>
using namespace std;

void MainWindow::on_read_param_triggered()
{
    // 获取用户选择的 Excel 文件路径
    QString filePath = QFileDialog::getOpenFileName(this, tr("选择Excel文件"), "", tr("Excel 文件 (*.xlsx *.xls)"));

    if (!filePath.isEmpty()) {
        if(read_mdc_param(filePath)!=1)return;
if(read_welcome_param(filePath)!=1)return;
if(read_name_param(filePath)!=1)return;

    }else
    {
        QMessageBox::information(nullptr, QStringLiteral("信息"), QStringLiteral("文件不存在！"));
    }

}

void MainWindow::on_save_param_triggered()
{
    // 使用 QFileDialog 获取保存 Excel 文件的路径
    QString filePath = QFileDialog::getSaveFileName(nullptr, "保存 Excel 文件", "", "Excel 文件 (*.xlsx)");

    // 检查文件路径是否不为空
    if (!filePath.isEmpty()) {
        // 获取名为 'mdc_table' 的表格部件的行数和列数
        int row = ui->mdc_table->rowCount();
        int column = ui->mdc_table->columnCount();

        // 创建一个 QXlsx 文档对象
        QXlsx::Document xlsx;

        // 添加第一个工作簿并定义一个 QString 变量来存储单元格的文本内容
        xlsx.addSheet("MDC联系人");
        QString itemStr;

        // 遍历表格部件中的每个单元格，获取其内容
        if(row>15)
        {
            QMessageBox::warning(this, tr("提示"), tr("格式错误!"), QMessageBox::Ok);
            return  ;
        }
        if(column!=3)
        {
            QMessageBox::warning(this, tr("提示"), tr("格式错误!"), QMessageBox::Ok);
            return  ;
        }

        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < column; ++j) {
                // 获取表格部件中位置为 (i, j) 的 QTableWidgetItem
                QTableWidgetItem* item = ui->mdc_table->item(i, j);

                // 检查单元格是否为空（NULL）
                if (item == NULL)
                    itemStr = ""; // 如果为空，将空字符串赋给 itemStr
                else
                    itemStr = item->text(); // 如果不为空，获取 QTableWidgetItem 的文本内容

                // 将单元格的内容写入第一个工作簿的 Excel 文件的位置 (i+1, j+1)
                // Excel 单元格索引从 1 开始，因此使用 i+1 和 j+1
                xlsx.write(i + 1, j + 1, itemStr);
            }
        }

        // 添加第二个工作簿
        xlsx.addSheet("开机欢迎字符");

QString text = ui->wel1->toPlainText(); // 获取文本编辑器中的文本内容

        // 检查单元格是否为空（NULL）
if (text.isEmpty())
    itemStr = ""; // 如果为空，将空字符串赋给 itemStr
        else
            itemStr = text; // 如果不为空，获取 QTableWidgetItem 的文本内容

        // 将单元格的内容写入第一个工作簿的 Excel 文件的位置 (i+1, j+1)
        // Excel 单元格索引从 1 开始，因此使用 i+1 和 j+1
        xlsx.write( 1, 1, itemStr);

         text = ui->wel2->toPlainText(); // 获取文本编辑器中的文本内容

                // 检查单元格是否为空（NULL）
        if (text.isEmpty())
            itemStr = ""; // 如果为空，将空字符串赋给 itemStr
                else
                    itemStr = text; // 如果不为空，获取 QTableWidgetItem 的文本内容
        xlsx.write( 2, 1, itemStr);



  xlsx.addSheet("中文信道名");
  for (int i = 0; i < 200; ++i) {
      xlsx.write( i+1, 1,   QString::number(i+1));

      QTableWidgetItem *item_name = ui->name_table->item(i, 1); // 获取第二列单元格的 item
      if (item_name) {
           itemStr = item_name->text();
          xlsx.write( i+1, 2, itemStr);

      }else
      {
          xlsx.write( i+1, 2, "");

      }
  }




        // 将 Excel 文件保存为指定的 filePath
        if (xlsx.saveAs(filePath))
            QMessageBox::information(nullptr, QStringLiteral("信息"), QStringLiteral("保存成功"));
        else
            QMessageBox::critical(nullptr, QStringLiteral("错误"), QStringLiteral("保存失败\n请检查目录或文件是否被占用"));
    }


}
