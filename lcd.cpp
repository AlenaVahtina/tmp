#include "lcd.h"

LCD::LCD()
{
    //ram=std::vector<std::vector<bool> >(128, std::vector<bool>(64));
}

void LCD::LCDinit(void) {
    setE(false);//Начальное значение сигнала индикатору
    setRES(false);//Выдать сигнал RES=0 индикатору
   // Delay(>1us);//Задержка на время больше 1 мкс
    setRES(true);//Снять сигнал RES
   // Delay(>10us);//Задержка на время больше 10 мкс
    WriteCodeL(0xC0);//Верхнюю строку на 0
    WriteCodeR(0xC0);//Верхнюю строку на 0
    WriteCodeL(0x3F);//Display on
    WriteCodeR(0x3F);//Display on
}

void LCD::Pset(uint8_t x, uint8_t y, bool c) {//Записать одну точку в индикатор (координата 0,0 в левом верхнем углу индикатора)
uint8_t c8;//Временное хранение считаного из индикатора байта
uint8_t m8;//Маска нужного бита в байте
    if ((x>127)||(y>63)) return;//Выход за пределы индикатора
    if (x<64) {//Выводить в левую половину индикатора
        WriteCodeL(0xB8|(y>>3));//Установить нужную страницу индикатора
        WriteCodeL(0x40|x);//Установить адрес нужного байта
        c8=ReadDataL();//Фиктивное чтение
        c8=ReadDataL();//Чтение нужного байта из индикатора
        m8=1<<(y&0x07);//Вычислить маску нужного бита в байте
        if (c==1)	//Зажигать точку?
            c8|=m8;//Установить нужный бит в байте
        else		//Или гасить точку?
            c8&=~m8;//Сбросить нужный бит в байте
        WriteCodeL(0x40|x);//Снова установить адрес нужного байта
        WriteDataL(c8);//Записать изменённый байт обратно в индикатор
    } else {//Выводить в правую половину индикатора
        WriteCodeR(0xB8|(y>>3));//Установить нужную страницу индикатора
        WriteCodeR(0x40|(x-64));//Установить адрес нужного байта
        c8=ReadDataR();//Фиктивное чтение
        c8=ReadDataR();//Чтение нужного байта из индикатора
        m8=1<<(y&0x07);//Вычислить маску нужного бита в байте
        if (c==1)	//Зажигать точку?
            c8|=m8;//Установить нужный бит в байте
        else		//Или гасить точку?
            c8&=~m8;//Сбросить нужный бит в байте
        WriteCodeR(0x40|(x-64));//Снова установить адрес нужного байта
        WriteDataR(c8);//Записать изменённый байт обратно в индикатор
    }
}

void LCD::WriteCodeL(uint8_t b) { WriteByte(b,0,1,0); }//Команду в левый кристалл индикатора
void LCD::WriteCodeR(uint8_t b) { WriteByte(b,0,0,1); }//Команду в правый кристалл индикатора

void LCD::WriteDataL(uint8_t b) { WriteByte(b,1,1,0); }//Данные в левую половину индикатора
void LCD::WriteDataR(uint8_t b) { WriteByte(b,1,0,1); }//Данные в правую половину индикатора

uint8_t LCD::ReadDataL(void) { return ReadByte(1,1,0); }//Прочитать байт данных из левой половины индикатора
uint8_t LCD::ReadDataR(void) { return ReadByte(1,0,1); }//Прочитать байт данных из правой половины индикатора

//Процедура выдачи байта в индикатор
void LCD::WriteByte(uint8_t b, bool cd, bool l, bool r) {
    if ((l==1)&&(r==1)) return;	//Читать (для опроса готовности) одновременно из обоих кристаллов недопустимо!
    WaitReady(l,r);		//Ждать готовности индикатора
//При необходимости настроить здесь шину данных на вывод
    setRW(false); setA0(cd);	//Выдача байта в индикатор как данных или команды
    setE1(l); setE2(r);	//Выбрать нужные нужные кристаллы в индикаторе
    setD(b);		//Выдать байт на шину данных индикатора
    //Delay(>140ns);		//Это время предустановки адреса (tAW)
    setE(true);		//Сформировать строб записи в индикатор E=1
    //Delay(>450ns);		//Длительность сигнала E=1 (время предустановки данных попало сюда (tDS))
    setE(false);		//Сбросить сигнал E
    //Delay(>(1000ns-140ns-450ns));	//Минимально допустимый интервал между сигналами E=1
}

uint8_t LCD::ReadByte(bool cd, bool l, bool r) {
uint8_t b;
    if ((l==1)&&(r==1)) return 0;	//Читать одновременно из обоих кристаллов недопустимо!
    WaitReady(l,r);		//Ждать готовности индикатора
    setRW(true); setA0(cd);	//Будем читать байт как команду или данные
    setE1(l); setE2(r);	//Выбрать нужные нужные кристаллы в индикаторе
    //Delay(>140ns);		//Это время предустановки адреса (tAW)
    setE(true);		//Выдать строб в индикатор
   // Delay(>450ns);		//Минимально допустимая длительность сигнала E=1 (время доступа (tDDR) попало сюда)
    b=getD();		//Прочитать данные с шины индикатора (они на ней уже минимум 130нс)
    setE(false);		//Сбросить сигнал E
   // Delay(>(1000ns-140ns-450ns));	//Минимально допустимый интервал между сигналами E=1
    return b;		//Вернуть прочитанный байт
}

void LCD::WaitReady(bool l, bool r) {//Ждать готовности индикатора, опрашивая байт статуса
//При необходимости настроить здесь шину данных на ввод
    setRW(true); setA0(false);	//Чтение флага занятости
    setE1(l); setE2(r);		//Выбрать нужные нужные кристаллы в индикаторе
  //  Delay(>140ns);		//Это время предустановки адреса (tAW)
    setE(true);// Delay(>450ns);	//Минимальная длительность сигнала E=1 (информация на шину данных индикатором будет выдана раньше, не более чем через 320нс)
   // while(D.7==1);	//Ждать сброса флага занятости
    setE(false);		//Сбросить сигнал E
   // Delay(>(1000ns-140ns-450ns));	//Минимально допустимый интервал между сигналами E=1
}

void LCD::handle(){
    if(RW){
        if(A0){//read data
            if(E1){D = l.readData();}
            if(E2){D = r.readData();}
        }else{//read status

        }
    }else{
        if(A0){//write data
            if(E1){l.writeData(D);}
            if(E2){r.writeData(D);}
        }else{
            if(D & 0x80){
                if(D & 0x40){//displaystartline
                    if(E1){l.displayStartLine(D & 0x3F);}
                    if(E2){r.displayStartLine(D & 0x3F);}
                }else if((D & 0xB8) == 0xB8){//setpage
                    if(E1){l.setPage(D & 0x07);}
                    if(E2){r.setPage(D & 0x07);}
                }
            }else{
                if(D & 0x40){//setadress
                    if(E1){l.setAddress(D & 0x3F);}
                    if(E2){r.setAddress(D & 0x3F);}
                }else if((D & 0x3E) == 0x3E){//on/off
                    if(E1){l.displayOnOff(D & 0x01);}
                    if(E2){r.displayOnOff(D & 0x01);}
                }
            }
        }
    }
}

bool LCD::getPixel(uint8_t x, uint8_t y){
    if(x<64)
        return l.getPixel(x,y);
    return r.getPixel(x%64,y);
}
