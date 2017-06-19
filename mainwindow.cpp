#include "mainwindow.h"
#include "ui_mainwindow.h"

#define MULT 10

const uint8_t Logo128[8][128]=//128x64 pixel, каждые 8 вертикальных точек собраны в байт
{
    {	0xFF,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
        0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
        0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
        0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
        0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
        0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
        0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
        0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0xFF
    },
    {	0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xE0,0xC0,0xE0,0xF0,0xF0,0xF0,
        0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xE0,0xE0,0xE0,0xC0,0x80,0x00,
        0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,
        0x00,0x80,0x80,0x00,0x00,0x80,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x80,0x00,0x00,
        0x80,0x00,0x00,0x80,0x00,0x80,0x00,0x80,0x80,0x80,0x00,0x80,0x80,0x00,0x00,0x80,
        0x00,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,
        0x00,0x00,0x80,0x00,0x80,0x00,0x00,0x80,0x80,0x80,0x00,0x80,0x00,0x00,0x80,0x00,
        0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x3F
    },
    {	0x1F,0xC0,0xE0,0xE0,0xFC,0xFE,0xF3,0xE3,0xE3,0xE3,0xE3,0xAF,0x6F,0xFF,0xFF,0xFF,
        0xBF,0xBF,0xFF,0xFF,0x7F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
        0xFF,0xF6,0xF4,0x1F,0x21,0xE2,0x61,0x6F,0x60,0x6F,0x64,0x6F,0x60,0x6F,0x65,0x68,
        0x60,0x6F,0x62,0x61,0x67,0x68,0x67,0x60,0x6A,0x67,0x60,0x6E,0x61,0x6F,0x60,0x67,
        0x6A,0x6B,0x60,0x6F,0x65,0x68,0x60,0x60,0x6F,0x60,0x60,0x6F,0x62,0x61,0x67,0x68,
        0x67,0x60,0x6F,0x62,0x6F,0x60,0x6F,0x64,0x6F,0x60,0x6F,0x65,0x68,0x64,0x6A,0x6F,
        0x60,0x60,0x6F,0x64,0x6F,0x60,0x60,0x60,0x6F,0x60,0x67,0x6A,0x6B,0x60,0x6D,0x62,
        0x6D,0x60,0x6F,0x62,0x6F,0x60,0x6F,0x64,0x6F,0x60,0x6F,0x65,0x68,0x64,0x6A,0x6F
    },
    {	0xFE,0x3F,0x3F,0x3F,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xF9,0x77,0x37,
        0x03,0x03,0x01,0x00,0x00,0x00,0x00,0x01,0x07,0x0F,0x13,0x01,0x00,0x00,0x01,0x07,
        0xD7,0x0E,0x08,0xC0,0x00,0x10,0x0F,0xF8,0x00,0x00,0x80,0xE0,0xF8,0xFE,0xFF,0xFF,
        0xFF,0xFE,0x00,0x00,0x00,0x00,0x00,0xC0,0xF0,0xFE,0xFF,0xFF,0xFF,0xFE,0x00,0x00,
        0x00,0xE0,0xF0,0xF8,0xFC,0x7C,0x3E,0x1E,0x1F,0x0F,0x0F,0x0F,0x0F,0x1F,0x1E,0x1E,
        0x3E,0x7C,0xFC,0xF8,0xF0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x80,0xC0,0xF0,0xFC,0xFE,0xFF,0xFF,0xFE,0x00,0x00,0x06,0x0F,0x0F,0x0F,0x0F,0x0F,
        0x0F,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x06,0xF0
    },
    {	0x3F,0xE0,0x00,0x00,0x01,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0x3F,0x3F,0x00,0x00,0xE0,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x01,0x01,0xC1,0xE0,0xE0,0xF9,0xFF,0xFC,0xFF,0xFF,0x7F,0x1F,0xFF,0xFF,0xFF,
        0xFF,0xFF,0x80,0xE0,0xF8,0xFE,0xFF,0xFF,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,
        0x00,0x00,0x01,0x01,0x00,0x00,0x00,0x30,0x78,0x78,0xFC,0xFC,0xFC,0xFC,0x78,0x78,
        0x30,0x00,0x01,0x07,0xFF,0xFF,0xFF,0xFC,0x00,0x00,0x00,0x00,0x80,0xE0,0xF8,0xFE,
        0xFF,0xFF,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF
    },
    {	0xFC,0x01,0x03,0x04,0x18,0x20,0x40,0x81,0x87,0x07,0x07,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,
        0x80,0xE4,0xE7,0xFB,0xFF,0xFF,0x7F,0x3F,0x0F,0x03,0x01,0x00,0x00,0xFF,0xFF,0xFF,
        0xFF,0xFF,0xFF,0x7F,0x1F,0x07,0x03,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,
        0x00,0x70,0xF8,0xF8,0xF0,0xE0,0xE0,0xC0,0xC0,0x80,0x80,0x80,0x80,0xC0,0xC0,0xC0,
        0xE0,0xF0,0xFC,0xFF,0x7F,0x3F,0x0F,0x81,0xE0,0xF8,0xFC,0xFF,0xFF,0x3F,0x1F,0x07,
        0x01,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF
    },
    {	0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x02,0x02,0x04,0x04,0x04,0x0C,
        0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x04,0x04,0x04,0x02,0x03,0x01,0x00,
        0x00,0x03,0x07,0x07,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x07,0x07,
        0x07,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x07,0x07,0x07,0x03,0x00,0x00,
        0x00,0x00,0x00,0x01,0x01,0x03,0x03,0x03,0x07,0x07,0x07,0x07,0x07,0x07,0x03,0x03,
        0x03,0x01,0x01,0x00,0x00,0x00,0x00,0x03,0x07,0x07,0x07,0x03,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x03,0x07,0x07,0x07,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x03,0x07,0x07,0x07,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF
    },
    {	0xFF,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
        0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
        0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
        0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
        0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
        0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
        0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
        0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xFF
    }
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //intelasation LCD
    image = QImage (128*MULT,64*MULT, QImage::Format_RGB32);

    lcd.LCDinit();
//    for(uint8_t p=0; p<8; p++) {//Цикл по всем 8-ми страницам индикатора
//        lcd.WriteCodeL(p|0xB8);//Установка текущей страницы для левого кристалла индикатора
//        lcd.WriteCodeL(0x40);//Установка текущего адреса для записи данных в 0 для левого кристалла индикатора
//        for(uint8_t c=0; c<64; c++) {//Цикл вывода данных в левую половину индикатора
//            lcd.WriteDataL(Logo128[p][c]);//Вывод очередного байта в индикатор
//        }
//        lcd.WriteCodeR(p|0xB8);//Установка текущей страницы для правого кристалла индикатора
//        lcd.WriteCodeR(0x40);//Установка текущего адреса для записи данных в 0 для правого кристалла индикатора
//        for(uint8_t c=64; c<128; c++) {//Цикл вывода данных в правую половину индикатора
//           lcd.WriteDataR(Logo128[p][c]);//Вывод очередного байта в индикатор
//        }
//    }
    for (int i=0;i<128;i++){
        for(int j=0;j<64;j++){
            lcd.Pset(i,j,true);
        }
    }


   // lcd.Pset(1,1,1);

    for (int i=0;i<128;i++){
        for(int j=0;j<64;j++){
            setPixel(i,j,lcd.getPixel(i,j));
        }
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setPixel (int x, int y, bool i){
    if (i){
        for(int x1=x*MULT;x1<(x+1)*MULT;x1++)
            for(int y1=y*MULT;y1<(y+1)*MULT;y1++)
                image.setPixel(x1,y1,qRgb(255, 0, 255));
    }else{
        for(int x1=x*MULT;x1<(x+1)*MULT;x1++)
            for(int y1=y*MULT;y1<(y+1)*MULT;y1++)
                image.setPixel(x1,y1,qRgb(0, 0, 0));
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
}

