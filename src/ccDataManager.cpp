#include "ccDataManager.h"

ccDataManager *ccDataManager::s_dataManager = nullptr;

ccDataManager::ccDataManager(QObject *parent) : QObject(parent) {
    resetWorldFile();
}

ccDataManager::~ccDataManager()
{
    MACRO_DEL_PTR(s_dataManager);
}

ccDataManager *ccDataManager::Instance()
{
    if (!s_dataManager)
        s_dataManager = new ccDataManager();
    return s_dataManager;
}

void ccDataManager::sltRequestReadHandle(const QString &path, int type)
{
    switch (type) {
    case CC_TYPE_MMS:
        QtConcurrent::run(this, &ccDataManager::analysisMMS, path);
        break;

    case CC_TYPE_WORLDFILE:
        QtConcurrent::run(this, &ccDataManager::analysisWorldFile, path);
        break;

    default:
        break;
    }
}

void ccDataManager::analysisMMS(QString &path)
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
            if (list.size() != 4) {
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
        emit sgnResponseReadFinished(CC_TYPE_WORLDFILE, isValidWorldFile() && (lineCount == 6));
    }
    else {
        MACRO_DLOG << "Can't open file " << path;
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

QList<ccPoint4D> &ccDataManager::getListMMS()
{
    return mListMMS;
}

ccWorldFile &ccDataManager::getWorldFile()
{
    return mWorldFile;
}

bool ccDataManager::isValidWorldFile()
{
    return (mWorldFile.A != 0.0f) && (mWorldFile.E != 0.0f);
}
