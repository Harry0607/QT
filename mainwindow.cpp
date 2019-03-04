#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QTextStream>
#include <QFile>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSerialPort serial;
    serial.setPortName("/dev/ttyS1");

    if(serial.open(QIODevice::ReadWrite)){
        //Now the serial port is open try to set configuration
        if(!serial.setBaudRate(QSerialPort::Baud9600))
            qDebug()<<serial.errorString();

        if(!serial.setDataBits(QSerialPort::Data8))
            qDebug()<<serial.errorString();

        if(!serial.setParity(QSerialPort::NoParity))
            qDebug()<<serial.errorString();

        if(!serial.setStopBits(QSerialPort::OneStop))
            qDebug()<<serial.errorString();

        if(!serial.setFlowControl(QSerialPort::NoFlowControl))
            qDebug()<<serial.errorString();

        //If any error was returned the serial il corrctly configured

        serial.write("M114 \n");
        //the serial must remain opened

        if(serial.waitForReadyRead(100)){
            //Data was returned
            qDebug()<<"Response: "<<serial.readAll();
        }else{
            //No data
            qDebug()<<"Time out";
        }

        //I have finish alla operation
        serial.close();
    }else{
        qDebug()<<"Serial COM19 not opened. Error: "<<serial.errorString();
    }

    MainWindow w;
    w.show();

    return a.exec();
}
