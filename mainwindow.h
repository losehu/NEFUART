#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMessageBox>
#include "QTimer"
#include <QMainWindow>
#include <qdebug.h>
#include "QTableWidget"
#include <QtSerialPort/QSerialPort>         // 提供访问串口的功能
#include <QtSerialPort/QSerialPortInfo>     // 提供系统中存在的串口信息
#include <QApplication>
#include <QTableWidget>
#include <QKeyEvent>
#include <QClipboard>
#include "QFileDialog"
#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
#include "string"
using namespace QXlsx;
#define FONT_LOCAL "./chinese_map.txt"
//#define FONT_LOCAL "C:/Users/RUPC/Desktop/UV-K6/NEFUART/build/chinese_map.txt"
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
typedef unsigned char uint8_t;
typedef unsigned short  uint16_t;
typedef unsigned int uint32_t;
#define NUM_NEED_WRITE 1
class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void DataReceived1();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSerialPort     *serial1;                            // 定义全局的串口对象（第三步）
          // 创建定时器
    void payload_xor( uint8_t* payload, int payload_len);
    int read_byte(uint32_t add,uint8_t len,uint8_t *a);
    int write_byte(uint32_t add,uint8_t len,uint8_t *a);

        uint16_t crc16_ccitt( uint8_t *data, int len) ;
        int  timetime_set();
        bool check_back(QByteArray receivedData,uint16_t CMD);
        void out_uint8(uint8_t a[],int len);
        int MDC_READ();
        int MDC_WRITE();
        void setCellValueToItemValue(int row, int col, QVariant str, int type);
        int read_mdc_param(QString filePath);
        int read_welcome_param(QString filePath);
        int check_mdc();
        bool mdc_chinese_check(int row,int col);
        int getCellContentLength(QTableWidget *tableWidget, int row, int column) ;
        int  c2i(char ch);
        int  hex2dec(char *hex);
        int WELCOME_WRITE();
        int WELCOME_READ();
        uint8_t is_chn(uint8_t num) ;
        int NAME_READ();
        int NAME_WRITE();
        int read_name_param(QString filePath);

        std::string find_chinese(std::string searchString ) ;

        struct MDC_T
        {
            uint16_t ID;
            char name[15];
            uint8_t sum[16];
        }MDC_INFO[15];
        void keyPressEvent(QKeyEvent *event) ;
            void pasteFromClipboard() ;
private slots:

    void on_open1_clicked();

    void onTimeout() ;



    void on_read_clicked();

    void on_write_clicked();
    void CHECK_MDC_TABLE();

    unsigned char txt_to_byte(std::string targetChar,unsigned char *out,int max_len,bool flag,int row);


    void on_read_param_triggered();

    void on_save_param_triggered();


    bool isGBKChineseCharacter( std::string &str, size_t index) ;

    bool containsChineseChar(const std::string &line, const std::string &target) ;
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer; // 定时器对象

    void RefreshSerialPort(int index);
    void SerialPortInit();                      // 串口初始化（参数配置）

        QStringList     baudList;                           //波特率
        QStringList     parityList;                         //校验位
        QStringList     dataBitsList;                       //数据位
        QStringList     stopBitsList;                       //停止位
        QStringList     flowControlList;                    //控制流
};

#endif // MAINWINDOW_H
