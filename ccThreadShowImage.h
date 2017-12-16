#ifndef CCTHREADSHOWIMAGE_H
#define CCTHREADSHOWIMAGE_H

#include <QThread>
#include <QLabel>
#include "common.h"

class ccThreadShowImage : public QThread
{
private:
    bool m_isStop;
    int m_idx;
    QStringList m_imageDirectoryList;
    QLabel *m_plblImageScreen;
private:
    void showImage();
protected:
    void run();
public:
    ccThreadShowImage();
    void setStop();
    void setImageList(QStringList imageDirectoryList, QLabel *lbl);
};

#endif // CCTHREADSHOWIMAGE_H
