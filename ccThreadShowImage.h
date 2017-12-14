#ifndef CCTHREADSHOWIMAGE_H
#define CCTHREADSHOWIMAGE_H

#include <QThread>
#include "common.h"

class ccThreadShowImage : public QThread
{
private:
    bool m_isStop;
    int m_idx;
    QStringList m_imageDirectoryList;
private:
    void setStop();
    void showImage();
protected:
    void run();
public:
    ccThreadShowImage();

    void setImageList(QStringList imageDirectoryList);
};

#endif // CCTHREADSHOWIMAGE_H
