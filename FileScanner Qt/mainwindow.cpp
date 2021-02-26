#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "worker.h"
#include<iostream>
#include <filesystem>
#include <chrono>
#include <thread>
#include<QThread>


namespace fs = std::filesystem;
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
    ui->setupUi(this);
    this->GenerateFiles("C:/");
}

void MainWindow::on_processBar_recieveUpdate(int value)
{
    this->ui->progressBar->setValue(value);
}

void MainWindow::GenerateFiles(string path)
{
    this->thread = new QThread;
    this->worker = new Worker(path,this,1000000);
    worker->moveToThread(thread);
    connect(this->thread, SIGNAL (started()), this->worker, SLOT (process()));
    connect(worker, SIGNAL (finished()), thread, SLOT (quit()));
    connect(worker, SIGNAL (finished()), this->worker, SLOT (deleteLater()));
    connect(this->thread, SIGNAL (finished()), thread, SLOT (deleteLater()));
    connect(worker, SIGNAL (updateProcessBar(int)),this, SLOT (on_processBar_recieveUpdate(int)));
    this->thread->start();
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    if(this->HaveStop)
    {
        qApp->exit(0);
    }
    try{
        this->worker->Stop();
        this->ui->pushButton->setText("exit");
        this->HaveStop = true;
        this->ui->progressBar->setValue(0);
        disconnect(this->worker, SIGNAL (updateProcessBar(int)),this, SLOT (on_processBar_recieveUpdate(int)));
    }catch(exception e)
    {
        cout << e.what() << endl;
    }
}
