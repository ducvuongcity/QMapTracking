#include "ccReaderManager.h"

ccReaderManager *ccReaderManager::s_textReader = nullptr;

ccReaderManager::ccReaderManager(QObject *parent) : QObject(parent) {
    resetWorldFile();
}

ccReaderManager::~ccReaderManager()
{
    MACRO_DEL_PTR(s_textReader);
}

ccReaderManager *ccReaderManager::Instance()
{
    if (!s_textReader)
        s_textReader = new ccReaderManager();
    return s_textReader;
}

void ccReaderManager::sltRequestReadHandle(const QString &path, int type)
{
    switch (type) {
    case CC_TYPE_MMS:
        QtConcurrent::run(this, &ccReaderManager::analysisMMS, path);
        break;

    case CC_TYPE_WORLDFILE:
        QtConcurrent::run(this, &ccReaderManager::analysisWorldFile, path);
        break;

    default:
        break;
    }
}

void ccReaderManager::analysisMMS(QString &path)
{
    MACRO_THR_DLOG << "Read MMS";
    mListMMS.clear();
    ccPoint4D tempPoint;
    QFile txtFile(path);
    QStringList list;
    QRegExp rx("\\s+");
    if (txtFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&txtFile);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            list = line.split(rx, QString::SkipEmptyParts);
            if (list.size() < 4) {
                MACRO_THR_DLOG << "MMS File incorrect";
                emit sgnResponseReadFinished(CC_TYPE_MMS, false);
                return;
            }
            tempPoint.x = list.at(0).toDouble();
            tempPoint.y = list.at(1).toDouble();
            tempPoint.z = list.at(2).toDouble();
            tempPoint.t = list.at(3).toDouble();
            mListMMS.append(tempPoint);
        }
        txtFile.close();
        emit sgnResponseReadFinished(CC_TYPE_MMS, true);
    }
}

void ccReaderManager::analysisWorldFile(QString &path)
{
    MACRO_THR_DLOG << "Read World File";
    resetWorldFile();
    QFile txtFile(path);;
    if (txtFile.open(QIODevice::ReadOnly))
    {
        uint8_t lineCount = 0;
        bool isCastSuccess = false;
        QTextStream in(&txtFile);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            if (0 == lineCount)
                mWorldFile.xPixelSize = line.toDouble(&isCastSuccess);
            else if (1 == lineCount)
                mWorldFile.yAxis = line.toDouble(&isCastSuccess);
            else if (2 == lineCount)
                mWorldFile.xAxis = line.toDouble(&isCastSuccess);
            else if (3 == lineCount)
                mWorldFile.yPixelSize = line.toDouble(&isCastSuccess);
            else if (4 == lineCount)
                mWorldFile.xCoordinate = line.toDouble(&isCastSuccess);
            else if (5 == lineCount)
                mWorldFile.yCoordinate = line.toDouble(&isCastSuccess);
            else {}

            ++lineCount;
        }
        txtFile.close();
        if (!isCastSuccess)
            MACRO_DLOG << "Load error, please check WorldFile " << path;

        emit sgnResponseReadFinished(CC_TYPE_WORLDFILE, (lineCount >= 6) && isCastSuccess ? true : false);
    }
    else {
        MACRO_DLOG << "Can't open file " << path;
    }
}

void ccReaderManager::resetWorldFile()
{
    mWorldFile.xPixelSize = 0;
    mWorldFile.yPixelSize = 0;
    mWorldFile.xAxis = 0;
    mWorldFile.yAxis = 0;
    mWorldFile.xCoordinate = 0;
    mWorldFile.yCoordinate = 0;
}

QList<ccPoint4D> &ccReaderManager::getListMMS()
{
    return mListMMS;
}

ccWorldFile &ccReaderManager::getWorldFile()
{
    return mWorldFile;
}

bool ccReaderManager::isValidWorldFile()
{
    return (mWorldFile.xPixelSize != 0.0f) && (mWorldFile.yPixelSize != 0.0f);
}
