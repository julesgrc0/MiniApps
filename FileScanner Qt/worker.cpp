#include "worker.h"
#include<iostream>
#include<thread>
#include<filesystem>

using namespace std;
namespace fs = std::filesystem;

Worker::Worker(string path ,QObject *parent,int MaxFilesCount)
{
    this->path = path;
    this->MaxFilesCount = MaxFilesCount;
    this->parent= parent;
}

int GetValue(int val,int total)
{
    return  (int)((100 * val) / total);
}

void ShowProcess(int value)
{
        cout << "[";
        int pos = value;
        for (int i = 0; i < 100;i++) {
            if (i < pos)
            {
                cout << "=";
            }
            else if (i == pos)
            {
                cout << ">";
            }
            else
            {
                cout << " ";
            }
        }

        cout << "] " << int(value) << " %\r";
        cout.flush();
}

int CountFiles(fs::path path)
{
    int i = 0;
    fs::directory_iterator end_iter;
    for (fs::directory_iterator iter(path); iter != end_iter; ++iter)
    {
        i++;
    }
    return i;
}

void Worker::Stop()
{
     this->MaxFilesCount = 1;
     emit finished();
}

void Worker::FinderDir(fs::path lastPath)
{
    try{
        this->MaxFilesCount += CountFiles(lastPath);
        for (const auto & entry : fs::directory_iterator(lastPath))
        {
            this->FilesCount++;
            if(this->FilesCount>=this->MaxFilesCount)
            {
                break;
            }

            if(entry.is_directory() && this->FilesCount <= this->MaxFilesCount)
            {
                int value = GetValue(this->FilesCount,this->MaxFilesCount);
                emit updateProcessBar(value);
                this->FinderDir(entry.path());
            }
        }
    }catch(exception _){}
}

void Worker::process()
{
    for (const auto & entry : fs::directory_iterator(path))
    {
        this->FilesCount++;
        int value = GetValue(this->FilesCount,this->MaxFilesCount);
        if(entry.is_directory() && entry.exists() &&!entry.is_block_file())
        {
            this->FinderDir(entry.path());
        }
        value = GetValue(this->FilesCount,this->MaxFilesCount);
        ShowProcess(value);
        emit updateProcessBar(value);
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    emit finished();
}
