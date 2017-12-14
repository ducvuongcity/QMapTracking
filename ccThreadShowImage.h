#ifndef CCTHREADSHOWIMAGE_H
#define CCTHREADSHOWIMAGE_H

#include <QThread>

class ccThreadShowImage : public QThread
{
private:
    QStringList imageDirectoryList;
protected:
    void run();

public:
    ccThreadShowImage();
};

#endif // CCTHREADSHOWIMAGE_H
