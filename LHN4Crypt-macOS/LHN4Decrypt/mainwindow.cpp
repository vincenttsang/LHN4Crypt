#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <QFileDialog>
#include <QtGlobal>
#include <QProcess>
#include <cstdlib>

QString openFile="";
QString saveFile="";
QString sslUtils="/usr/local/share/lhn4crypt";
QString sslCmd=" enc -d ";
QString sslCipher=" -aes-256-cbc ";
QString sslMisc=" -pbkdf2";
QString sslPwd="";
QString finalCmd="";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
    setFixedSize(this->width(), this->height());
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_inputBtn_clicked()
{
    openFile=QFileDialog::getOpenFileName(this,"打开","～./","*.lhn");
    openFile=openFile.replace(" ","\\ ");
    if(openFile == ""){
        QMessageBox::critical(this, "错误", "请先打开一个档案", QMessageBox::Yes, QMessageBox::Yes);
    }
    else{
        ui->inputLabel->setText(openFile);
    }
}

void MainWindow::on_outputBtn_clicked()
{
    saveFile=QFileDialog::getSaveFileName(this,"保存","~./","");
    saveFile=saveFile.replace(" ","\\ ");
    if(saveFile == ""){
        QMessageBox::critical(this, "错误", "请选择档案保存位置", QMessageBox::Yes, QMessageBox::Yes);
    }
    else{
        ui->outputLabel->setText(saveFile);
    }
}

void MainWindow::on_startBtn_clicked()
{
    if(openFile != "" && saveFile!=""){
        sslPwd = ui->plainTextEdit->toPlainText();
        if(sslPwd!=""){
            finalCmd = sslUtils + sslCmd + sslCipher + sslMisc + " -in " + openFile +" -k " + sslPwd + " -out " + saveFile;
            //QMessageBox::information(this,"save",finalCmd);
            const char* system_command = finalCmd.toUtf8().constData() ;//解决macOS与Linux空格问题，但在Windows要换成QProcess
            system(system_command);
            //QProcess::execute(finalCmd);//不可在macOS与Linux处理带有空格的文件
        }
        else{
            QMessageBox::critical(this, "错误", "未指定密码", QMessageBox::Yes, QMessageBox::Yes);
        }
    }
    else{
        QMessageBox::critical(this, "错误", "未指定档案输入输出位置", QMessageBox::Yes, QMessageBox::Yes);
    }
}
