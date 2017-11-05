#include "ccReaderManager.h"

ccReaderManager::ccReaderManager(QObject *parent) : QObject(parent)
{
}

ccReaderManager *ccReaderManager::Instance()
{
    static ccReaderManager *s_textReader = nullptr;
    if (!s_textReader)
        s_textReader = new ccReaderManager();
    return s_textReader;
}

void ccReaderManager::sltReadFileMMS(const QString &path)
{
    QFuture<void> func = QtConcurrent::run(this, &ccReaderManager::analysisMMS, path);
    func.waitForFinished();
}

void ccReaderManager::analysisMMS(QString path)
{
    MACRO_THREAD_DLOG << "Read MMS";
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
              MACRO_THREAD_DLOG << "MMS File incorrect";
              return;
          }
          tempPoint.x = list.at(0).toDouble();
          tempPoint.y = list.at(1).toDouble();
          tempPoint.z = list.at(2).toDouble();
          tempPoint.t = list.at(3).toDouble();
          mListMMS.append(tempPoint);
       }
       txtFile.close();
       emit sgnReadFinish(CC_FINISHED_MMS);
       qDebug() << "List MMS size = " << mListMMS.size();
       qDebug() << "List at " << 1234 << QString::number(mListMMS.at(1234).x, 'f', 6) << ", "
                                      << QString::number(mListMMS.at(1234).y, 'f', 6) << ", "
                                      << QString::number(mListMMS.at(1234).z, 'f', 6) << ", "
                                      << QString::number(mListMMS.at(1234).t, 'f', 6);
    }
}

QList<ccPoint4D> ccReaderManager::getListMMS()
{
    return mListMMS;
}

