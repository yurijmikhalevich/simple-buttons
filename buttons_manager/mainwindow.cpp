#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    refreshPortList();
    QTimer *trefresh = new QTimer(this);
    connect(trefresh, SIGNAL(timeout()), this, SLOT(refreshPortList()));
    trefresh->setInterval(1000);
    trefresh->setSingleShot(false);
    trefresh->start();
    QTimer *tread = new QTimer(this);
    connect(tread, SIGNAL(timeout()), this, SLOT(readAndDisplay()));
    tread->setInterval(25);
    tread->setSingleShot(false);
    tread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshPortList()
{
    ui->comboBoxPortList->clear();
    portList = QSerialPortInfo::availablePorts();
    foreach (const QSerialPortInfo &info, portList) {
        ui->comboBoxPortList->addItem(info.portName() + ": " + info.description() + "(" + info.manufacturer() + ")");
    }
}

void MainWindow::readAndDisplay()
{
    if (ui->pushButton->isChecked()) {
        QString buf;
        while (!arduino.atEnd()) {
            buf = arduino.readLine();
            if (buf.contains("rb")) {
                order.append("rb");
                ui->rb->setChecked(true);
                ui->rb->setText(QString::number(order.size()));
            } else if (buf.contains("rg")) {
                order.append("rg");
                ui->rg->setChecked(true);
                ui->rg->setText(QString::number(order.size()));
            } else if (buf.contains("ry")) {
                order.append("ry");
                ui->ry->setChecked(true);
                ui->ry->setText(QString::number(order.size()));
            } else if (buf.contains("rr")) {
                order.append("rr");
                ui->rr->setChecked(true);
                ui->rr->setText(QString::number(order.size()));
            } else if (buf.contains("lb")) {
                order.append("lb");
                ui->lb->setChecked(true);
                ui->lb->setText(QString::number(order.size()));
            } else if (buf.contains("lg")) {
                order.append("lg");
                ui->lg->setChecked(true);
                ui->lg->setText(QString::number(order.size()));
            } else if (buf.contains("ly")) {
                order.append("ly");
                ui->ly->setChecked(true);
                ui->ly->setText(QString::number(order.size()));
            } else if (buf.contains("lr")) {
                order.append("lr");
                ui->lr->setChecked(true);
                ui->lr->setText(QString::number(order.size()));
            }
        }
    }
}

void MainWindow::on_pushButton_toggled(bool checked)
{
    if (checked) {
        arduino.setPort(portList.at(ui->comboBoxPortList->currentIndex()));
        arduino.setBaudRate(9600);
        if (arduino.open(QIODevice::ReadWrite)) {
            arduino.write("l");
            ui->comboBoxPortList->setEnabled(false);
            ui->reset->setEnabled(true);
        } else {
            QMessageBox::critical(this, "Ошибка", "Невозможно открыть порт");
            ui->pushButton->setChecked(false);
        }
    } else {
        arduino.write("l");
        arduino.close();
        ui->comboBoxPortList->setEnabled(true);
        ui->reset->setEnabled(false);
    }
}

void MainWindow::on_reset_clicked()
{
    if (ui->pushButton->isChecked()) {
        arduino.write("r");
        ui->rb->setChecked(false);
        ui->rb->setText(".");
        ui->rg->setChecked(false);
        ui->rg->setText(".");
        ui->ry->setChecked(false);
        ui->ry->setText(".");
        ui->rr->setChecked(false);
        ui->rr->setText(".");
        ui->lb->setChecked(false);
        ui->lb->setText(".");
        ui->lg->setChecked(false);
        ui->lg->setText(".");
        ui->ly->setChecked(false);
        ui->ly->setText(".");
        ui->lr->setChecked(false);
        ui->lr->setText(".");
    }
}
