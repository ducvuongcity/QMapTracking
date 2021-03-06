#include "ccDataManager.h"

ccDataManager::ccDataManager(QObject *parent) : QObject(parent) {
    resetWorldFile();
    m_pDBImage2DInfo = new ccDataBuilerImage2DInfo();
}

ccDataManager::~ccDataManager()
{
    MACRO_DEL_PTR(m_pDBImage2DInfo);
}

void ccDataManager::analysisMMS(QString &path)
{
    MACRO_THR_DLOG << "Read MMS";
    mListMMS.clear();
    ccPoint4D tempPoint;
    QFile txtFile(path);
    QStringList list;
    QRegExp rx("(\\s+|\\,)");
    if (txtFile.open(QIODevice::ReadOnly))
    {
        uint32_t sizeOfFile = txtFile.size();
        MACRO_THR_DLOG << "Size of file " << sizeOfFile;
        uint32_t countSize = 0;
        QTextStream in(&txtFile);
        emit sgnResponseReadStart();
        while (!in.atEnd())
        {
            QString line = in.readLine();
            countSize += line.size();
//            MACRO_THR_DLOG << "Size count " << countSize;
//            sendEvent(QString("evt_Model_UpdateProgress_Res(%1)").arg(100*countSize/sizeOfFile));
            list = line.split(rx, QString::SkipEmptyParts);
            if (list.size() != 4) {
                MACRO_THR_DLOG << "MMS File incorrect";
                sendEvent(CC_EVT_MODEL_READMMS_RESPONSE ,QString::number(0));
                return;
            }
            tempPoint.x = list.at(0).toDouble();
            tempPoint.y = list.at(1).toDouble();
            tempPoint.z = list.at(2).toDouble();
            tempPoint.t = list.at(3).toDouble();
            mListMMS.append(tempPoint);
        }
        txtFile.close();
        sendEvent(CC_EVT_MODEL_READMMS_RESPONSE ,QString::number(1));
    }
}

void ccDataManager::analysisWorldFile(QString &path)
{
    MACRO_THR_DLOG << "Read World File";
    resetWorldFile();
    QFile txtFile(path);;
    if (txtFile.open(QIODevice::ReadOnly))
    {
        uint8_t lineCount = 0;
        QTextStream in(&txtFile);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            if (0 == lineCount)
                mWorldFile.A = line.toDouble();
            else if (1 == lineCount)
                mWorldFile.D = line.toDouble();
            else if (2 == lineCount)
                mWorldFile.B = line.toDouble();
            else if (3 == lineCount)
                mWorldFile.E = line.toDouble();
            else if (4 == lineCount)
                mWorldFile.C = line.toDouble();
            else if (5 == lineCount)
                mWorldFile.F = line.toDouble();
            else
                break;

            ++lineCount;
        }
        txtFile.close();
        sendEvent(CC_EVT_MODEL_READWORLDFILE_RESPONSE, QString::number(isValidWorldFile() && (lineCount == 6) ? 1 : 0));
    }
    else {
        MACRO_THR_DLOG << "Can't open file " << path;
    }
}

void ccDataManager::resetWorldFile()
{
    mWorldFile.A = 0;
    mWorldFile.E = 0;
    mWorldFile.B = 0;
    mWorldFile.D = 0;
    mWorldFile.C = 0;
    mWorldFile.F = 0;
}

void ccDataManager::sendEvent(EventList event, QString params)
{
    emit sgnEvent(event, params);
}

QList<ccPoint4D> &ccDataManager::getListMMS()
{
    return mListMMS;
}

ccWorldFile &ccDataManager::getWorldFile()
{
    return mWorldFile;
}

QList<QPoint> &ccDataManager::getListPixel()
{
    return mListPixel;
}

QStringList &ccDataManager::getListPathImage()
{
    return mListPathImage;
}

void ccDataManager::setListPixel(const QList<QPoint> &list)
{
    if (mListPixel.size() > 0)
        mListPixel.clear();
    for (uint32_t i = 0; i < list.size(); ++i)
        mListPixel.append(list.at(i));
}

void ccDataManager::setListPathImage(const QStringList &list)
{
    if (mListPathImage.size() > 0)
        mListPathImage.clear();
    for (uint32_t i = 0; i < list.size(); ++i) {
        mListPathImage.append(list.at(i));
    }
}

bool ccDataManager::isValidWorldFile()
{
    return (mWorldFile.A != 0.0f) && (mWorldFile.E != 0.0f);
}

bool ccDataManager::notifyChange2DImageInfo(QString &path)
{
    MACRO_THR_DLOG << path;
    bool bRet = false;
    if(nullptr != m_pDBImage2DInfo)
    {
        bRet = m_pDBImage2DInfo->setRootPath(path);
    }
    else
    {
        MACRO_THR_DLOG << "m_pDBImage2DInfo is null";
    }
    return bRet;
}

bool ccDataManager::requestFindImagePathByTime(double time, QString &strResult)
{
    bool bRet = false;
    if(nullptr != m_pDBImage2DInfo)
    {
        // before searching, round down time. eg: 12345.xxx -> 12345
        m_pDBImage2DInfo->findPathByTime(floor(time), strResult);
    }
    return bRet;
}
