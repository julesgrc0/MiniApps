#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include<iostream>
#include <filesystem>

using namespace std;

class Worker : public QObject
{
    Q_OBJECT
public:
     Worker(string path ,QObject *parent = nullptr,int MaxFilesCount=1);
     void FinderDir(std::filesystem::path path);
     void Stop();
public slots:
   void process();


signals:
    void finished();
    void error(QString err);
    void updateProcessBar(int value);
private:
    int MaxFilesCount = 1;
    int FilesCount = 0;
    string path;
    QObject *parent;
};

#endif // WORKER_H
