
#include "ui_mainwindow.h"
#include<string>
#include "bits/stdc++.h"
#include "stdlib.h"
#include "stdio.h"
#include "QDebug"
using namespace std;
#include "mainwindow.h"
uint8_t XOR_ARRAY[] = {0x16, 0x6c, 0x14, 0xe6, 0x2e, 0x91, 0x0d, 0x40, 0x21, 0x35, 0xd5, 0x40, 0x13, 0x03, 0xe9, 0x80};
int XOR_LEN = sizeof(XOR_ARRAY) / sizeof(XOR_ARRAY[0]);
void MainWindow::payload_xor( uint8_t* payload, int payload_len) {
    for (int i = 0; i < payload_len; ++i) {
        payload[i] ^= XOR_ARRAY[i % XOR_LEN];
    }
}
uint16_t Crc16Tab[256] = {
    0, 4129, 8258, 12387, 16516, 20645, 24774, 28903, 33032, 37161, 41290, 45419, 49548, 53677, 57806, 61935, 4657, 528, 12915, 8786, 21173, 17044, 29431, 25302,
    37689, 33560, 45947, 41818, 54205, 50076, 62463, 58334, 9314, 13379, 1056, 5121, 25830, 29895, 17572, 21637, 42346, 46411, 34088, 38153, 58862, 62927, 50604, 54669, 13907,
    9842, 5649, 1584, 30423, 26358, 22165, 18100, 46939, 42874, 38681, 34616, 63455, 59390, 55197, 51132, 18628, 22757, 26758, 30887, 2112, 6241, 10242, 14371, 51660, 55789,
    59790, 63919, 35144, 39273, 43274, 47403, 23285, 19156, 31415, 27286, 6769, 2640,14899, 10770, 56317, 52188, 64447, 60318, 39801, 35672, 47931, 43802, 27814, 31879,
    19684, 23749, 11298, 15363, 3168, 7233, 60846, 64911, 52716, 56781, 44330, 48395,36200, 40265, 32407, 28342, 24277, 20212, 15891, 11826, 7761, 3696, 65439, 61374,
    57309, 53244, 48923, 44858, 40793, 36728, 37256, 33193, 45514, 41451, 53516, 49453, 61774, 57711, 4224, 161, 12482, 8419, 20484, 16421, 28742, 24679, 33721, 37784, 41979,
    46042, 49981, 54044, 58239, 62302, 689, 4752, 8947, 13010, 16949, 21012, 25207, 29270, 46570, 42443, 38312, 34185, 62830, 58703, 54572, 50445, 13538, 9411, 5280, 1153, 29798,
    25671, 21540, 17413, 42971, 47098, 34713, 38840, 59231, 63358, 50973, 55100, 9939, 14066, 1681, 5808, 26199, 30326, 17941, 22068, 55628, 51565, 63758, 59695, 39368,
    35305, 47498, 43435, 22596, 18533, 30726, 26663, 6336, 2273, 14466, 10403, 52093, 56156, 60223, 64286, 35833, 39896, 43963, 48026, 19061, 23124, 27191, 31254, 2801,
    6864, 10931, 14994, 64814, 60687, 56684, 52557, 48554, 44427, 40424, 36297, 31782, 27655, 23652, 19525, 15522, 11395, 7392, 3265, 61215, 65342, 53085, 57212, 44955,
    49082, 36825, 40952, 28183, 32310, 20053, 24180, 11923, 16050, 3793, 7920
};

void MainWindow::out_uint8(uint8_t a[],int len)
{
    QByteArray byteArray(reinterpret_cast<char*>(a), len);

    qDebug() <<   byteArray.toHex();
}
uint16_t MainWindow::crc16_ccitt( uint8_t *data, int len) {
    uint16_t i2 = 0;

    for (int i3 = 0; i3 < len; ++i3) {
        uint16_t out = Crc16Tab[((i2 >> 8) ^ data[i3]) & 0xFF];
        i2 = out ^ (i2 << 8);
    }

    return 0xFFFF & i2;
}
bool MainWindow::check_back(QByteArray receivedData,uint16_t CMD)
{
    uint8_t* ucharData = reinterpret_cast< uint8_t*>(receivedData.data());
    uint8_t check_array[receivedData.size()-8];
    for(int i=0;i<receivedData.size()-8;i++)
    {
        check_array[i]=ucharData[4+i];
    }
    payload_xor(check_array,receivedData.size()-8);
    if((CMD&0x00ff)==check_array[0]&&((CMD&0xff00)>>8)==check_array[1])
    {
        return 1;
    }else{
        return 0;
    }
}
int  MainWindow::timetime_set()
{
    uint8_t settime[16]="\xAB\xCD\x08\x00\x02\x69\x10\xE6\xAC\xD1\x79\x25\x9D\xAD\xDC";
    settime[15]='\xBA';

    // 发送数据
    QByteArray dataToSend(reinterpret_cast<const char*>(settime), sizeof(settime));

    // 发送数据
    qint64 bytesWritten = serial1->write(dataToSend); // 将数据发送到串口

    if (bytesWritten == -1) {
        QMessageBox::warning(this,tr("提示"),tr("连接失败!"),QMessageBox::Ok);
        return -1;
    }
    serial1->waitForReadyRead(200); // 等待一小段时间确保缓冲区清空


    // 读取数据
    QByteArray receivedData = serial1->readAll(); // 阻塞接收数据

    if (receivedData.isEmpty()) {
        qDebug() << "连接失败";
        QMessageBox::warning(this,tr("提示"),tr("连接失败!"),QMessageBox::Ok);
        return -1;
    } else {
        qDebug() << "RECV:" << receivedData.toHex(' ').toUpper(); // 以16进制显示接收到的数据

        if(!check_back(receivedData,0x0515))
        {
            qDebug() << "连接失败";
            QMessageBox::warning(this,tr("提示"),tr("连接失败!"),QMessageBox::Ok);
            return -1 ;
        }
    }


    qDebug() << "时间设置OK!";
    return 1;

}



int MainWindow::read_byte(uint32_t add,uint8_t len,uint8_t *a)
{


if(add<0x00010000){
    uint8_t payload[14+2];
    payload[0]='\x1B';
    payload[1]='\x05';
    payload[2]='\x08';
    payload[3]='\x00';
    payload[4]=(add & 0x00FF);
    payload[5]=(add & 0xFF00) >>8;
    payload[6]=len;
    payload[7]='\x00';
    payload[8]='\x82';
    payload[9]='\x40';
    payload[10]='\x74';
    payload[11]='\x65';

    uint16_t crc = crc16_ccitt(payload, 12 );
    payload[12]=crc & 0xFF;
    payload[13]=(crc >> 8)& 0xFF;



    payload_xor(payload,14);
    uint8_t  message[20];
    message[0]='\xAB';
    message[1]='\xCD';
    message[2]='\x0C';
    message[3]='\x00';
    for(int i =0;i<14;i++) {
        message[i+4]=payload[i];
    }
    message[18]='\xDC';
    message[19]='\xBA';



    // 发送数据
    QByteArray dataToSend(reinterpret_cast<const char*>(message), sizeof(message));

    // 发送数据
    qint64 bytesWritten = serial1->write(dataToSend); // 将数据发送到串口


    if (bytesWritten == -1) {
        QMessageBox::warning(this,tr("提示"),tr("读取失败!"),QMessageBox::Ok);
        return -1;
    }
    serial1->waitForReadyRead(200); // 等待一小段时间确保缓冲区清空

    // 读取数据
    QByteArray receivedData = serial1->readAll(); // 阻塞接收数据

    if (receivedData.isEmpty()) {
        qDebug() << "读取失败";
        QMessageBox::warning(this,tr("提示"),tr("读取失败!"),QMessageBox::Ok);
        return -1;
    } else {
        qDebug() << "RECV:" << receivedData.toHex(' ').toUpper(); // 以16进制显示接收到的数据

        if(!check_back(receivedData,0x051C))
        {
            qDebug() << "读取失败";
            QMessageBox::warning(this,tr("提示"),tr("读取失败!"),QMessageBox::Ok);
            return -1;
        }
    }
    uint8_t* ucharData = reinterpret_cast< uint8_t*>(receivedData.data());
    uint8_t check_array[receivedData.size()-8];
    for(int i=0;i<receivedData.size()-8;i++)
    {
        check_array[i]=ucharData[4+i];
    }
    payload_xor(check_array,receivedData.size()-8);

    for(int i=0;i<len;i++)
    {
       a[i]=check_array[8+i];
    }
    return 1;
}else{
        uint8_t payload[14+2];
        payload[0]='\x2B';
        payload[1]='\x05';
        payload[2]='\x08';
        payload[3]='\x00';
        payload[4]=(add & 0x00FF0000)>>16;
        payload[5]=(add & 0xFF000000) >>24;
        payload[6]=len;
        payload[7]='\x00';
        payload[8]='\x82';
        payload[9]='\x40';
        payload[10]='\x74';
        payload[11]='\x65';
        payload[12]=add & 0x000000FF;
        payload[13]=(add & 0x0000FF00)>>8;

        uint16_t crc = crc16_ccitt(payload, 14 );
        payload[14]=crc & 0xFF;
        payload[15]=(crc >> 8)& 0xFF;



        payload_xor(payload,16);
        uint8_t  message[22];
        message[0]='\xAB';
        message[1]='\xCD';
        message[2]='\x0E';
        message[3]='\x00';
        for(int i =0;i<16;i++) {
            message[i+4]=payload[i];
        }
        message[20]='\xDC';
        message[21]='\xBA';



        // 发送数据
        QByteArray dataToSend(reinterpret_cast<const char*>(message), sizeof(message));

        // 发送数据
        qint64 bytesWritten = serial1->write(dataToSend); // 将数据发送到串口


        if (bytesWritten == -1) {
            QMessageBox::warning(this,tr("提示"),tr("读取失败!"),QMessageBox::Ok);
            return -1;
        }
        serial1->waitForReadyRead(200); // 等待一小段时间确保缓冲区清空

        // 读取数据
        QByteArray receivedData = serial1->readAll(); // 阻塞接收数据

        if (receivedData.isEmpty()) {
            qDebug() << "读取失败";
            QMessageBox::warning(this,tr("提示"),tr("读取失败!"),QMessageBox::Ok);
            return -1;
        } else {
            qDebug() << "RECV:" << receivedData.toHex(' ').toUpper(); // 以16进制显示接收到的数据

            if(!check_back(receivedData,0x051C))
            {
                qDebug() << "读取失败";
                QMessageBox::warning(this,tr("提示"),tr("读取失败!"),QMessageBox::Ok);
                return -1;
            }
        }
        uint8_t* ucharData = reinterpret_cast< uint8_t*>(receivedData.data());
        uint8_t check_array[receivedData.size()-8];
        for(int i=0;i<receivedData.size()-8;i++)
        {
            check_array[i]=ucharData[4+i];
        }
        payload_xor(check_array,receivedData.size()-8);

        for(int i=0;i<len;i++)
        {
           a[i]=check_array[8+i];
        }
        return 1;
}
}



int MainWindow::write_byte(uint32_t add,uint8_t len,uint8_t *a)
{

        uint8_t payload[14+len+2];
        payload[0]='\x38';
        payload[1]='\x05';
        payload[2]=(len& 0xFF)+8+2;
        payload[3]='\x00';
        payload[4]=(add & 0x00FF0000)>>16;
        payload[5]=(add & 0xFF000000) >>24;
        payload[6]=len+2;
        payload[7]='\x00';
        payload[8]='\x82';
        payload[9]='\x40';
        payload[10]='\x74';
        payload[11]='\x65';
        payload[12]=add & 0x000000FF;
        payload[13]=(add & 0x0000FF00)>>8;

        memcpy(payload+12+2,a,len);

        uint16_t crc = crc16_ccitt(payload, 12+len+2 );
        payload[12+len+2]=crc & 0xFF;
        payload[13+len+2]=(crc >> 8)& 0xFF;


        payload_xor(payload,14+len+2);
        uint8_t  message[20+len+2];
        message[0]='\xAB';
        message[1]='\xCD';
        message[2]=(0x0e + (len&0xFF));
        message[3]='\x00';
        for(unsigned int i =0;i<14+len+2;i++) {
            message[i+4]=payload[i];
        }
        message[18+len+2]='\xDC';
        message[19+len+2]='\xBA';



        // 发送数据
        QByteArray dataToSend(reinterpret_cast<const char*>(message), sizeof(message));

        // 发送数据
        qint64 bytesWritten = serial1->write(dataToSend); // 将数据发送到串口

        QString hexString = dataToSend.toHex().toUpper(); // Convert to hexadecimal string in uppercase
        qDebug() << hexString; // Output the hexadecimal string
        if (bytesWritten == -1) {
            QMessageBox::warning(this,tr("提示"),tr("写入失败!"),QMessageBox::Ok);
            return -1;
        }
        serial1->waitForReadyRead(200); // 等待一小段时间确保缓冲区清空

        // 读取数据
        QByteArray receivedData = serial1->readAll(); // 阻塞接收数据

        if (receivedData.isEmpty()) {
            qDebug() << "写入失败";
            QMessageBox::warning(this,tr("提示"),tr("写入失败!"),QMessageBox::Ok);
            return -1;
        } else {
            qDebug() << "RECV:" << receivedData.toHex(' ').toUpper(); // 以16进制显示接收到的数据

            if(!check_back(receivedData,0x051E))
            {
                qDebug() << "写入失败";
                QMessageBox::warning(this,tr("提示"),tr("写入失败!"),QMessageBox::Ok);
                return -1;
            }
        }


    return 1;
}
bool MainWindow::mdc_chinese_check(int row,int col)
{
    // 假设要检查第一行第一列的单元格中是否包含中文字符
    QTableWidgetItem *item = ui->mdc_table->item(row, col);

    if(item != nullptr) {
        QString cellContent = item->text();

        bool containsChinese = false;

        // 遍历单元格文本内容，检查每个字符是否为中文字符
        for(const QChar &character : cellContent) {
            // 中文字符的Unicode范围一般是4E00–9FFF
            if(character >= 0x4E00 && character <= 0x9FFF) {
                containsChinese = true;
                break;
            }
        }

        if(containsChinese) {
            return 1;
        } else {
            return 0;
        }
    }

}


int  MainWindow::c2i(char ch)
{
    // 如果是数字，则用数字的ASCII码减去48, 如果ch = '2' ,则 '2' - 48 = 2
    if(ch >= '0' && ch <= '9')
        return ch - 48;

    // 如果是字母，但不是A~F,a~f则返回
    if( ch < 'A' || (ch > 'F' && ch < 'a') || ch > 'z' )
        return -1;
    // 如果是大写字母，则用数字的ASCII码减去55, 如果ch = 'A' ,则 'A' - 55 = 10
    // 如果是小写字母，则用数字的ASCII码减去87, 如果ch = 'a' ,则 'a' - 87 = 10
    if(isalpha(ch))
        return isupper(ch) ? ch - 55 : ch - 87;
    return -1;
}

/*
  * 功能：将十六进制字符串转换为整型(int)数值
  * */
int  MainWindow::hex2dec(char *hex)
{
    int len;
    int num = 0;
    int temp;
    int bits;
    int i;

    // 此例中 hex = "1de" 长度为3, hex是main函数传递的
    len = 4;

    for (i=0, temp=0; i<len; i++, temp=0)
    {
        temp = c2i( *(hex + i) );

        bits = (len - i - 1) * 4;
        temp = temp << bits;

        // 此处也可以用 num += temp;进行累加
        num = num | temp;
    }

    // 返回结果
    return num;
}


int MainWindow::check_mdc()
{
    // 获取表格中第一行第一列的item
    int mdc_num=0;
    for(int i=0;i<15;i++)
    {
        QTableWidgetItem *item_id = ui->mdc_table->item(i, 1);
        QTableWidgetItem *item_name = ui->mdc_table->item(i, 2);

        if((item_name==nullptr||getCellContentLength(ui->mdc_table,i,2)==0)&&(item_id == nullptr||getCellContentLength(ui->mdc_table,i,1)==0))
        {
            break;
        }else  if((item_name==nullptr||getCellContentLength(ui->mdc_table,i,2)==0)&&(item_id != nullptr||getCellContentLength(ui->mdc_table,i,1)!=0))


        {

            QMessageBox::warning(this, tr("提示"), tr("MDC表格中\n第%1行缺少联系人名!").arg(i+1), QMessageBox::Ok);
            return-1;
        }else             if((item_name!=nullptr||getCellContentLength(ui->mdc_table,i,2)!=0)&&(item_id == nullptr||getCellContentLength(ui->mdc_table,i,1)==0))


        {
            QMessageBox::warning(this, tr("提示"), tr("MDC表格中\n第%1行缺少ID!").arg(i+1), QMessageBox::Ok);
            return -1;
        }else
        {



            QString cellContent = item_id->text();
            QByteArray byteArray = cellContent.toUtf8();
            const char *data = byteArray.constData();
            uint8_t *ID_DATA = reinterpret_cast<uint8_t *>(const_cast<char *>(data));

            QString cellContent1 = item_name->text();
            QByteArray byteArray1 = cellContent1.toUtf8();
            const char *data1 = byteArray1.constData();
            uint8_t *NAME_DATA = reinterpret_cast<uint8_t *>(const_cast<char *>(data1));



            //1.检查全部中文字符 ok
            //2.检查ID 四位16进制
            //3.检查name小于14字符
            if(mdc_chinese_check(i,1))
            {
                QMessageBox::warning(this, tr("提示"), tr("MDC表格中\n第%1行MDC ID包含中文字符!").arg(i+1), QMessageBox::Ok);
                return -1;

            }
            if(mdc_chinese_check(i,2))
            {
                QMessageBox::warning(this, tr("提示"), tr("MDC表格中\n第%1行联系人名称包含中文字符!").arg(i+1), QMessageBox::Ok);
                return -1;

            }
            if(getCellContentLength(ui->mdc_table,i,1)!=4)
            {

                QMessageBox::warning(this, tr("提示"), tr("MDC表格中\n第%1行ID应为4位16进制数!").arg(i+1), QMessageBox::Ok);

                return  -1;
            }
            for (int j=0;j<4;j++) {
                if(!((ID_DATA[j]>='0'&&ID_DATA[j]<='9')||(ID_DATA[j]>='a'&&ID_DATA[j]<='f')||(ID_DATA[j]>='A'&&ID_DATA[j]<='F')))
                {

                    QMessageBox::warning(this, tr("提示"), tr("MDC表格中\n第%1行ID应为4位16进制数!").arg(i+1), QMessageBox::Ok);
                    return  -1;
                }
            }
            if(getCellContentLength(ui->mdc_table,i,2)>14)
            {
                QMessageBox::warning(this, tr("提示"), tr("MDC表格中\n第%1行联系人名称长度应小于等于14!").arg(i+1), QMessageBox::Ok);
                return  -1;
            }
            //            if(getCellContentLength(ui->mdc_table,i,2)==0)
            //            {
            //                QMessageBox::warning(this, tr("提示"), tr("MDC表格中\n第%1行缺少联系人名!").arg(i+1), QMessageBox::Ok);
            //                return-1;
            //            }
            MDC_INFO[i].ID=hex2dec((char *)ID_DATA);
            memset(MDC_INFO[i].name,' ',14);
            memcpy(MDC_INFO[i].name,NAME_DATA,getCellContentLength(ui->mdc_table,i,2));
            MDC_INFO[i].name[14]=0;
            MDC_INFO[i].sum[1]=(MDC_INFO[i].ID&0x00ff);
            MDC_INFO[i].sum[0]=(MDC_INFO[i].ID&0xff00)>>8;
            memcpy(&(MDC_INFO[i].sum[2]),MDC_INFO[i].name,14);
            mdc_num=i+1;

        }
    }
    qDebug()<<"联系人:"<<endl;
    for(int i=0;i<mdc_num;i++)
    {
        std::cout<< hex<<MDC_INFO[i].ID<<" "<<MDC_INFO[i].name<<endl;
    }
    for(int i=mdc_num;i<15;i++)
    {
        ui->mdc_table->setItem(i, 1, nullptr);
        ui->mdc_table->setItem(i, 2, nullptr);
    }


    return mdc_num;
}
