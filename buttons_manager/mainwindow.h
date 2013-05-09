#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include "../serialport/qserialportinfo.h"
#include "../serialport/qserialport.h"
#include <QStringList>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_pushButton_toggled(bool checked);
    void on_reset_clicked();
    void refreshPortList();
    void readAndDisplay();

private:
    Ui::MainWindow *ui;
    QList<QSerialPortInfo> portList;
    QSerialPort arduino;
    QStringList order;
};

#endif // MAINWINDOW_H
