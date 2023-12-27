#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAbstractItemView>
#include "bits/stdc++.h"
#include <QTextCodec>

using namespace std;

int MainWindow::NAME_READ()
{
    ui->name_table->clearContents(); // 清除单元格的内容

    uint8_t en_flag[200];
    for(int i=0;i<10;i++)
    {
        if( read_byte(0x0D60+i*20 , 20, en_flag+i*20)!=1) return -1;

    }
    QTextStream out(stdout);

    for (int i = 0; i < 200; ++i) {
        if((en_flag[i]&0x0f)<=6)
        {
            en_flag[i]=1;
            std::cout<<i<<" OK"<<std::endl;
        }
        else en_flag[i]=0;
    }


    for(int i=0;i<200;i++)
    {
        if(!en_flag[i]) continue;
        uint8_t name[16]={0};
        if( read_byte(0x0F50+i*16 , 16, name)!=1) return -1;
        int len=0;
        string name_true="";
        for(int i=0;i<16;i++)
        {
            if((name[i]>=32&&name[i]<=127))
            {
                name_true.append(1,name[i]);
            }else if(name[i]>=0x80&&name[i]<=0x9b&&i!=15&&name[i+1]!=0)
            {

                char chn_code1[5]; // 4位十六进制字符串 + 结尾的 '\0'
                sprintf(chn_code1, "%04x", (name[i]<<8)+name[i+1]);
                string chn_code=chn_code1;
                name_true.append(find_chinese(chn_code));


                i++;

            }else
            {
                break;

            }
            len++;

        }

        // 获取当前行数

        // 在最后一行插入新行
        if(name_true!="")
            // 将数据插入最后一行
            ui->name_table->setItem(i, 1, new QTableWidgetItem(QTextCodec::codecForName("GBK")->toUnicode(name_true.c_str())));

        else {
          //  ui->name_table->setItem(i, 1, new QTableWidgetItem(QTextCodec::codecForName("GBK")->toUnicode(name_true.c_str())));

                        string a="CH-"+std::string(3 - std::to_string(i).length(), '0') + std::to_string(i+1);
                        ui->name_table->setItem(i, 1, new QTableWidgetItem(QTextCodec::codecForName("GBK")->toUnicode(a.c_str())));
        }
        ui->name_table->setItem(i, 0, new QTableWidgetItem(QString::number(1+i)));
        ui->progressBar->setValue(70+(i+1)*30/200);

    }

    return 1;
}



int MainWindow::NAME_WRITE()

{


    for (int i = 0; i < 200; ++i) {
        QTableWidgetItem *item_name = ui->name_table->item(i, 1); // 获取第二列单元格的 item
        if (item_name) {
            QString text = item_name->text();
            if(text.length()==0)continue;
            unsigned char out2[max(text.length()*2,16)];
            memset(out2,0,sizeof(out2));
            int len=txt_to_byte(QTextCodec::codecForName("GBK")->fromUnicode(text).constData(),out2,92,0,i+1);
            if(len==0xff) return -1;
            string a="CH-"+std::string(3 - std::to_string(i).length(), '0') + std::to_string(i+1);

               if(    QString::fromStdString(a)==text)                   memset(out2,0,sizeof(out2));

            if(write_byte(  0x0F50+i*16,16,out2)!=1)return -1;
            ui->progressBar->setValue(70+(i+1)*30/200);

        }
    }



    return 1;

}


int MainWindow::read_name_param(QString filePath)
{
    // 清空表格内容和行数
    ui->name_table->clearContents();

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
    QXlsx::Worksheet* workSheet = static_cast<QXlsx::Worksheet*>(workBook->sheet(2));

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
    if (rowCount != 200 || columnCount!=2)
    {
        QMessageBox::warning(nullptr, QStringLiteral("警告"), QStringLiteral("中文信道名数据表格式错误！"));
        return -1;
    }

    // 设置表格的行数

    // 设置表格的垂直表头标签
//    QStringList m_Vlist;
//    m_Vlist << QStringLiteral("1") << QStringLiteral("2") << QStringLiteral("3") << QStringLiteral("4");
//    ui->mdc_table->setVerticalHeaderLabels(m_Vlist);

    QString cellStr;
    // 遍历工作表的每个单元格，将值插入到表格中
    for (int i = 1; i <= rowCount; ++i)
    {
        for (int j = 1; j <= columnCount; ++j)
        {
            QXlsx::Cell* cell = workSheet->cellAt(i, j);
            if (cell == nullptr)
                cellStr = "";
            else {
//                QByteArray byteArray = cell->value().toByteArray();
//                QTextCodec *codec = QTextCodec::codecForName("GBK");
//                cellStr = codec->toUnicode(byteArray);




                    cellStr = cell->value().toString(); // 将单元格的值转换为字符串

            }
            // 调用函数将值插入表格
            QTableWidgetItem *item = new QTableWidgetItem(cellStr);
                   ui->name_table->setItem(i - 1, j - 1, item);
        }
    }
    return 1;
}

