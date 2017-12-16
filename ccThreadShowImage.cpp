#include "ccThreadShowImage.h"

void ccThreadShowImage::setStop()
{
    m_isStop = true;
}

void ccThreadShowImage::showImage()
{
    if(m_imageDirectoryList.isEmpty() || NULL == m_plblImageScreen)
    {
        MACRO_THR_DLOG << "List empty or Label null";
        return;
    }
    m_isStop = false;
    MACRO_THR_DLOG << "m_imageDirectoryList.size: " << m_imageDirectoryList.size();
    for(; m_idx < m_imageDirectoryList.size(); m_idx++)
    {
        if(m_isStop)
        {
            MACRO_THR_DLOG << "isStop";
            return;
        }
        MACRO_THR_DLOG << "Image: " << m_idx;
        // set Image to lblImage
        QPixmap image(m_imageDirectoryList.at(0));
        image = image.scaledToWidth(m_plblImageScreen->width());
        m_plblImageScreen->setPixmap(image);
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

void ccThreadShowImage::setImageList(QStringList imageDirectoryList, QLabel *lbl)
{
    m_isStop = true;
    m_idx = 0;
    m_plblImageScreen = lbl;
    m_imageDirectoryList.clear();
    m_imageDirectoryList = imageDirectoryList;
}
