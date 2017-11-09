#include "ccDataManager.h"

ccDataManager::ccDataManager(ccBridge &bridge, ccDataStore &store, QObject *parent)
    : QObject(parent)
    , m_bridge(&bridge)
    , m_dataStore(&store)
{
    QObject::connect(m_bridge, SIGNAL(sgnEventToModel(QString)), this, SLOT(sltEvenHandle(QString)));
}

ccDataManager::~ccDataManager()
{

}

void ccDataManager::sltEvenHandle(QString event)
{

}

//void ccDataManager::sltRequestReadHandle(const QString &path, int type)
//{
//    switch (type) {
//    case CC_TYPE_MMS:
//        QtConcurrent::run(this, &ccDataManager::analysisMMS, path);
//        break;

//    case CC_TYPE_WORLDFILE:
//        QtConcurrent::run(this, &ccDataManager::analysisWorldFile, path);
//        break;

//    default:
//        break;
//    }
//}

void ccDataManager::analysisMMS(QString &path)
{
    MACRO_THR_DLOG << "Read MMS";
//    mListMMS.clear();
//    ccPoint4D tempPoint;
//    QFile txtFile(path);
//    QStringList list;
//    QRegExp rx("\\s+");
//    if (txtFile.open(QIODevice::ReadOnly))
//    {
//        int sizeOfFile = txtFile.size();
//        MACRO_THR_DLOG << "Size of file " << sizeOfFile;
//        int countSize = 0;
//        QTextStream in(&txtFile);

//        m_bridge->sendEventToController(QString("evt_ReadMMS_Start()"));

//        while (!in.atEnd())
//        {
//            QString line = in.readLine();
//            countSize += line.size();
//            m_bridge->sendEventToController(QString("evt_ReadMMS_Inprogress_UpdateValue(%1)").arg(100*countSize/sizeOfFile));
//            list = line.split(rx, QString::SkipEmptyParts);
//            if (list.size() != 4) {
//                MACRO_THR_DLOG << "MMS File incorrect";
//                m_bridge->sendEventToController(QString("evt_ReadMMS_Finished(0)"));
//                return;
//            }
//            tempPoint.x = list.at(0).toDouble();
//            tempPoint.y = list.at(1).toDouble();
//            tempPoint.z = list.at(2).toDouble();
//            tempPoint.t = list.at(3).toDouble();
//            mListMMS.append(tempPoint);
//        }
//        txtFile.close();
//        m_bridge->sendEventToController(QString("evt_ReadMMS_Finished(1)"));
//    }
}

void ccDataManager::analysisWorldFile(QString &path)
{
    MACRO_THR_DLOG << "Read World File";
//    resetWorldFile();
//    QFile txtFile(path);;
//    if (txtFile.open(QIODevice::ReadOnly))
//    {
//        m_bridge->sendEventToController(QString("evt_ReadWorldFile_Start()"));

//        uint8_t lineCount = 0;
//        QTextStream in(&txtFile);
//        while (!in.atEnd())
//        {
//            QString line = in.readLine();
//            if (0 == lineCount)
//                mWorldFile.A = line.toDouble();
//            else if (1 == lineCount)
//                mWorldFile.D = line.toDouble();
//            else if (2 == lineCount)
//                mWorldFile.B = line.toDouble();
//            else if (3 == lineCount)
//                mWorldFile.E = line.toDouble();
//            else if (4 == lineCount)
//                mWorldFile.C = line.toDouble();
//            else if (5 == lineCount)
//                mWorldFile.F = line.toDouble();
//            else
//                break;

//            ++lineCount;
//        }
//        txtFile.close();
//        m_bridge->sendEventToController(QString("evt_ReadWorldFile_Finish()"));
//    }
//    else {
//        MACRO_DLOG << "Can't open file " << path;
//    }
}

//void ccDataManager::resetWorldFile()
//{
//    mWorldFile.A = 0;
//    mWorldFile.E = 0;
//    mWorldFile.B = 0;
//    mWorldFile.D = 0;
//    mWorldFile.C = 0;
//    mWorldFile.F = 0;
//}

void ccDataManager::setListPixel(const QList<QPoint> &list)
{
//    mListPixel.clear();
//    for (int i = 0; i < list.size(); ++i)
//        mListPixel.append(list.at(i));
}
