#include "ccDataBuilerImage2DInfo.h"

ccDataBuilerImage2DInfo::ccDataBuilerImage2DInfo()
{
    m_Images.clear();
}
ccDataBuilerImage2DInfo::~ccDataBuilerImage2DInfo()
{
}

bool ccDataBuilerImage2DInfo::InitialRowInfo()
{
    // clean m_Rows
    for(uint8_t i = 0; i < CC_FILE_IMAGE_COLUM; i++)
    {
        m_Rows[i].clear();
    }
}

bool ccDataBuilerImage2DInfo::setRootPath(QString &rootPath)
{
    bool bRet = false;
    if(!QDir(rootPath).exists())
    {
        return bRet;
    }
    QString path2dInfo(rootPath);
    path2dInfo.append(QDir::separator());
    path2dInfo.append(CC_FILE_IMAGE_FILE_INFO_NAME);
    QString pathImageFolder(rootPath);
    pathImageFolder.append(QDir::separator());
    pathImageFolder.append(CC_FILE_IMAGE_FOLDER_NAME);
    // check if the folder and file 2D.txt exist in the new root directory
    if(!(QDir(pathImageFolder).exists() && QFile(path2dInfo).exists()))
    {
        return bRet;
    }
    m_strRootPath.clear();
    m_strRootPath.append(rootPath);
    bRet = InitialRowInfo();
    if(true == bRet)
    {
        bRet = set2DImageFile(path2dInfo);
    }
    // return false if error occours
    return bRet;
}

bool ccDataBuilerImage2DInfo::set2DImageFile(QString &str2DfilePath)
{
    bool bRet = true;
    QFile txtFile(str2DfilePath);
    QRegExp rx(",");
    if (txtFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&txtFile);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            QStringList list = line.split(rx, QString::SkipEmptyParts);
            if (list.size() < CC_FILE_IMAGE_COLUM) {
                // debug log: wrong fomat
                bRet = false;
                break;
            }
            addImageInfo(list);
        }
    }
    txtFile.close();
    return bRet;
}

void ccDataBuilerImage2DInfo::addImageInfo(QStringList &strListInfo)
{
    image2DInfo NewElement;
    uint32_t i = 0;
    for( ; i < (CC_FILE_IMAGE_COLUM - 1); i++)
    {
        QString FolderName(strListInfo.at(i));
        QStringList *pRow = &(m_Rows[i]);
        uint32_t j = 0;
        for( ; j < pRow->size(); j++)
        {
            QString value(pRow->at(j));
            if(value == FolderName)
            {
                break;
            }
        }
        if(pRow->size() == j)
        {
            pRow->push_back(FolderName);
        }
        NewElement.arDirecInfo[i] = j;
    }
    QString GPSTime(strListInfo.at(i));
    NewElement.dbTime = GPSTime.toDouble();
    m_Images.push_back(NewElement);
}
void ccDataBuilerImage2DInfo::findPathByTime(double gpsTime, QString &resultPath)
{
    resultPath.clear();                     // output empty string if can not find a corresponding path
    uint32_t idx = 0;
    for( ; idx < m_Images.size(); idx++)
    {
        if(gpsTime == m_Images.at(idx).dbTime)
        {
            break;
        }
    }
    if(idx == m_Images.size())
    {
        //MACRO_THR_DLOG << "Error: not image match with time "<< gpsTime;
        return;
    }
    image2DInfo targetImageInfo = m_Images.at(idx);
    resultPath.append(m_strRootPath);
    resultPath.append(QDir::separator());
    resultPath.append(CC_FILE_IMAGE_FOLDER_NAME);
    for(uint32_t i = 0; i < (CC_FILE_IMAGE_COLUM - 1); i++)
    {
        QStringList *pRow = &(m_Rows[i]);
        resultPath.append(QDir::separator());
        resultPath.append(pRow->at(targetImageInfo.arDirecInfo[i]));
    }
    if(!(QFileInfo(resultPath).exists() && QFileInfo(resultPath).isFile()))
    {
        resultPath.clear();
    }
    //MACRO_THR_DLOG << "path from 2D.txt:" << resultPath;
    //MACRO_THR_DLOG << "exist: " << QFileInfo(resultPath).exists();
    //MACRO_THR_DLOG << "is File: " << QFileInfo(resultPath).isFile();
}
