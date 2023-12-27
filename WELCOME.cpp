#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAbstractItemView>
#include "bits/stdc++.h"
#include <QTextCodec>

using namespace std;
bool MainWindow::isGBKChineseCharacter( string &str, size_t index) {
    // 检查GBK编码的字符是否为汉字
    if (index < str.size() - 1) {
        unsigned char firstByte = static_cast<unsigned char>(str[index]);
        unsigned char secondByte = static_cast<unsigned char>(str[index + 1]);
        if (firstByte >= 0x81 && firstByte <= 0xFE &&
                ((secondByte >= 0x40 && secondByte <= 0x7E) || (secondByte >= 0x80 && secondByte <= 0xFE))) {
            return true;
        }
    }
    return false;
}

bool MainWindow::containsChineseChar(  const std::string &line, const std::string &target) {
    size_t found = line.find(target);
    return (found != std::string::npos);
}

unsigned char MainWindow::txt_to_byte(string targetChar,unsigned char *out,int max_len,bool flag,int row=0)
{
    unsigned char out_index=0;
    std::ifstream file(FONT_LOCAL); // 替换为你的文件路径
    if (!file.is_open()) {
        qDebug() << "无法打开文件\n";
        return 0xff;
    }
    qDebug() << "打开字库";

    int len=0;
    for (int i = 0; i <targetChar.length() ; i++) {
        if(isGBKChineseCharacter(targetChar, i))
        {    std::string line;
            int lineNumber = 0;
            bool find_flag=0;
            while (std::getline(file, line)) {
                lineNumber++;
                if (containsChineseChar(line, targetChar.substr(i,2))) {
                    char num[4];
                    num[0] = line[3];
                    num [1]= line[4];
                    num [2]= line[5];
                    num [3]= line[6];
                    out[out_index++]=hex2dec(num)>>8;
                    out[out_index++]=hex2dec(num)&0x00ff;
                    find_flag=1;
                    len+=13;
                    break;
                }
            }
            i++;
            file.seekg(0, std::ios::beg);

            if(!find_flag)
            {

                file.close();
              if(flag)  QMessageBox::warning(this,tr("提示"),tr("欢迎字符应为\n英文字母、符号或中文汉字\n不能包含中文符号!"),QMessageBox::Ok);
else          QMessageBox::warning(this, tr("提示"), tr("第%1信道名\n应为英文字母、符号或中文汉字\n不能包含中文符号!").arg(row), QMessageBox::Ok);
                return 0xff;
            }
        }
        else
        {
            len+=7;
            out[out_index++]=targetChar[i];

        }
    }

    file.close();
    if(len>max_len)
    {
         if(flag) QMessageBox::warning(this,tr("提示"),tr("欢迎字符太长!\n英文字符占7，中文字符占13\n总长应不超过128!"),QMessageBox::Ok);
else QMessageBox::warning(this,tr("提示"),tr("第%1信道名太长!\n英文字符占7，中文字符占13\n总长应不超过%2!").arg(row).arg(max_len),QMessageBox::Ok);
        return 0xff;
    }
    return out_index;
}



int MainWindow::read_welcome_param(QString filePath)
{

    ui->wel1->setPlainText("");
    ui->wel2->setPlainText("");

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
    QXlsx::Worksheet* workSheet = static_cast<QXlsx::Worksheet*>(workBook->sheet(1));

    // 检查工作表是否为空指针
    if (workSheet == nullptr)
    {
        QMessageBox::warning(nullptr, QStringLiteral("警告"), QStringLiteral("欢迎字符工作表为空指针"));
        return -1;
    }

    // 获取工作表的行数和列数
    int rowCount = workSheet->dimension().rowCount();
    int columnCount = workSheet->dimension().columnCount();
    qDebug() << QStringLiteral("工作sheet的行数：") << rowCount << QStringLiteral("工作sheet的列数") << columnCount;

    // 检查行数和列数是否为非正数!
    if (rowCount <= 0 || columnCount != 1)
    {
        QMessageBox::warning(nullptr, QStringLiteral("警告"), QStringLiteral("欢迎字符数据表为空!"));
        return -1;
    }


    // 假设你要获取第一列的第一行的值并放到 ui->wel1 中
    QString cellStr;
    QXlsx::Cell* cell = workSheet->cellAt(1, 1); // 获取第一列第一行的单元格值

    if (cell != nullptr) {
        cellStr = cell->value().toString(); // 将单元格的值转换为字符串
        ui->wel1->setPlainText(cellStr); // 将值设置到文本编辑器中
    }



    cell = workSheet->cellAt(2, 1); // 获取第一列第一行的单元格值

    if (cell != nullptr) {
        cellStr = cell->value().toString(); // 将单元格的值转换为字符串
        ui->wel2->setPlainText(cellStr); // 将值设置到文本编辑器中
    }
    return 1;
}


int MainWindow::WELCOME_WRITE()

{
    QString qstr = ui->wel1->toPlainText();
    QTextCodec *codec = QTextCodec::codecForName("GBK");
    QByteArray gbkData = codec->fromUnicode(qstr);

    // 将 QByteArray 转换为 std::string
    std::string str = gbkData.constData();



    QString qstr2 = ui->wel2->toPlainText();

    QTextCodec *codec2 = QTextCodec::codecForName("GBK");
    QByteArray gbkData2 = codec2->fromUnicode(qstr2);

    // 将 QByteArray 转换为 std::string
    std::string str2 = gbkData2.constData();



    unsigned char out[str.length()*2];
    unsigned char out_index[2]={0};
    out_index[0]=txt_to_byte(str,out,128,1);
    if(out_index[0]==0xff) return -1;

    unsigned char out2[str2.length()*2];
    out_index[1]=txt_to_byte(str2,out2,128,1);
    if(out_index[1]==0xff)  return -1;

    ui->progressBar->setValue(55);

    qDebug()<<"欢迎字符"<<(int)out_index[0]<<" "<<(int)out_index[1]<<endl;
    std::cout<<str.length()*2<<std::endl<<str2<<std::endl;
    if(write_byte(0x1e31e,1,out_index)!=1||write_byte(0x1e31f,1,out_index+1)!=1|| write_byte(0x1e320,out_index[0],out)!=1||write_byte(0x1e333,out_index[1],out2)!=1)    return -1;



    return 1;

}
uint8_t MainWindow::is_chn(uint8_t num) {
    if (num>=0x80) return 1;
    return 255;
}

string MainWindow::find_chinese(string searchString ) {
    std::ifstream file(FONT_LOCAL); // 替换为你的文件名
    std::string line;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            if (line.find(searchString) != std::string::npos) {
                file.close();
                return  line.substr(0,2);
            }
        }
        file.close();
        QMessageBox::warning(nullptr, QStringLiteral("警告"), QStringLiteral("欢迎字符读取错误！"));
        return NULL;

    } else {
        QMessageBox::warning(nullptr, QStringLiteral("警告"), QStringLiteral("字库打开错误！"));
        return NULL;
    }

    return NULL;
}


int MainWindow::WELCOME_READ()
{
    uint8_t read_index[2];
    uint8_t read_wel1[18]={0},read_wel2[18]={0};
    if(read_byte(0x1e31e,2,read_index)!=1||read_byte(0x1e320,read_index[0],read_wel1)!=1||    read_byte(0x1e333,read_index[1],read_wel2)!=1)      return -1;
    if(read_index[0]>18) read_index[0]=0;
    if(read_index[1]>18) read_index[1]=0;

    int char_num=0;
    bool cn_flag[read_index[0]];
    uint16_t true_char[read_index[0]];

    for(int i=0;i<read_index[0];i++)
    {
        uint8_t chn_judge = is_chn(read_wel1[i]);
        if (chn_judge == 255 && read_wel1[i] != '\0') {
            true_char[char_num]=read_wel1[i];
            cn_flag[char_num]=0;

            char_num++;
        }
        else if (chn_judge != 255) {
            cn_flag[char_num]=1;
            true_char[char_num]=(read_wel1[i]<<8)|read_wel1[i+1];
            i++;
            char_num++;
        }
    }
    string welcome1="";
    for(int i=0;i<char_num;i++)
    {
        if(cn_flag[i])
        {
            char chn_code1[5]; // 4位十六进制字符串 + 结尾的 '\0'
            sprintf(chn_code1, "%04x", true_char[i]);
            string chn_code=chn_code1;
            welcome1.append(find_chinese(chn_code));
        }
        else  {
            welcome1.append( 1,(char)true_char[i]); // 使用 append 方法向字符串末尾添加字符
        }
    }

    ui->wel1->setPlainText(QString::fromLocal8Bit(welcome1.c_str()));

    ui->progressBar->setValue(55);



    //wel2

    int char_num2=0;
    bool cn_flag2[read_index[1]];
    uint16_t true_char2[read_index[1]];

    for(int i=0;i<read_index[1];i++)
    {
        uint8_t chn_judge = is_chn(read_wel2[i]);
        if (chn_judge == 255 && read_wel2[i] != '\0') {
            true_char2[char_num2]=read_wel2[i];
            cn_flag2[char_num2]=0;

            char_num2++;
        }
        else if (chn_judge != 255) {
            cn_flag2[char_num2]=1;
            true_char2[char_num2]=(read_wel2[i]<<8)|read_wel2[i+1];
            i++;
            char_num2++;
        }
    }
    string welcome2="";
    for(int i=0;i<char_num2;i++)
    {
        if(cn_flag2[i])
        {
            char chn_code1[5]; // 4位十六进制字符串 + 结尾的 '\0'
            sprintf(chn_code1, "%04x", true_char2[i]);
            string chn_code=chn_code1;
            welcome2.append(find_chinese(chn_code));
        }
        else  {
            welcome2.append( 1,(char)true_char2[i]); // 使用 append 方法向字符串末尾添加字符
        }
    }
    ui->wel2->setPlainText(QString::fromLocal8Bit(welcome2.c_str()));








    return 1;
}

