#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <QFileDialog>
#include <QtGlobal>
#include <QProcess>
#include <cstdlib>

QString openFile="";
QString saveFile="";
QString sslUtils=".\\lhn4crypt.exe";
QString sslCmd=" enc ";
QString sslCipher=" -aes-256-cbc ";
QString sslMisc=" -pbkdf2";
QString sslPwd="";
QString finalCmd="";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
    setFixedSize(this->width(), this->height());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_inputBtn_clicked()
{
    openFile=QFileDialog::getOpenFileName(this,"打开","～./","");
    openFile=openFile.replace("/","\\");
    openFile=openFile.replace(" ","\" \"");
    if(openFile == ""){
        QMessageBox::critical(this, "错误", "请先打开一个档案", QMessageBox::Yes, QMessageBox::Yes);
    }
    else{
        ui->inputLabel->setText(openFile);
    }
}

void MainWindow::on_outputBtn_clicked()
{
    saveFile=QFileDialog::getSaveFileName(this,"保存","~./","*.lhn");
    saveFile=saveFile.replace("/","\\");
    saveFile=saveFile.replace(" ","\" \"");
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
            finalCmd = sslUtils + sslCmd + sslCipher + sslMisc + " -in " + openFile + " -out " + saveFile + " -k " + sslPwd;
            //QMessageBox::information(this,"save",finalCmd);
            //以下代码
            //std::string str = finalCmd.toStdString();
            //const char* system_command = str.c_str();
            //system(system_command);
            //会导致中文乱码
            QProcess::execute(finalCmd);
        }
        else{
            QMessageBox::critical(this, "错误", "未指定密码", QMessageBox::Yes, QMessageBox::Yes);
        }
    }
    else{
        QMessageBox::critical(this, "错误", "未指定档案输入输出位置", QMessageBox::Yes, QMessageBox::Yes);
    }
}
