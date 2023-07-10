#ifndef UART_H
#define UART_H
// 引入串口通信的两个头文件(第一步)
#include <QtSerialPort/QSerialPort>         // 提供访问串口的功能
#include <QtSerialPort/QSerialPortInfo>     // 提供系统中存在的串口信息
QSerialPort     *serial;                            // 定义全局的串口对象（第三步）
#endif // UART_H
class MY_UART
{
public:
void        SerialPortInit();                      // 串口初始化（参数配置）

private:
// 参数配置
    QStringList     baudList;                           //波特率
    QStringList     parityList;                         //校验位
    QStringList     dataBitsList;                       //数据位
    QStringList     stopBitsList;                       //停止位
    QStringList     flowControlList;                    //控制流
};
