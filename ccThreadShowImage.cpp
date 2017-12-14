#include "ccThreadShowImage.h"

void ccThreadShowImage::setStop()
{
    m_isStop = true;
}

void ccThreadShowImage::showImage()
{
    if(m_imageDirectoryList.isEmpty())
    {
        return;
    }
    for(; m_idx < m_imageDirectoryList.size(); m_idx++)
    {
        if(m_isStop)
        {
            return;
        }
        // set Image to lblImage

        // show time
        msleep(CC_TIMER_SHOW_IMAGE);
    }
    m_isStop = true;
    m_idx = 0;
}

void ccThreadShowImage::run()
{
    showImage();
}

ccThreadShowImage::ccThreadShowImage()
{
    m_isStop = true;
    m_idx = 0;
    m_imageDirectoryList.clear();
}

void ccThreadShowImage::setImageList(QStringList imageDirectoryList)
{
    m_isStop = true;
    m_idx = 0;
    m_imageDirectoryList.clear();
    m_imageDirectoryList = imageDirectoryList;
}
