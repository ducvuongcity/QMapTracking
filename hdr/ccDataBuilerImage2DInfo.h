#ifndef CCDATABUILERIMAGE2DINFO_H
#define CCDATABUILERIMAGE2DINFO_H

// ADD-START QMapTracking 2017.11.18 dhthong
#include <QVector>
#include <QFile>
#include <QStringList>
#include <QTextStream>
#include <QDir>
#include <QFile>

#define CC_FILE_IMAGE_COLUM                 6           /// number of colums in file 2D.txt
#define CC_FILE_IMAGE_FOLDER_NAME           "IMAGE"
#define CC_FILE_IMAGE_FILE_INFO_NAME        "2D.txt"

typedef struct
{
    unsigned char arDirecInfo[CC_FILE_IMAGE_COLUM];
    double dbTime;
}image2DInfo;

class ccDataBuilerImage2DInfo
{
private:
    QVector<image2DInfo> m_Images;
    QStringList *m_pRows;
    QString m_strRootPath;
    bool set2DImageFile(QString &);
private:
    void addImageInfo(QStringList &);
    bool InitialRowInfo();
public:
    ccDataBuilerImage2DInfo();

    virtual ~ccDataBuilerImage2DInfo();

    bool setRootPath(QString &);

    void findPathByTime(double, QString &);
};
// ADD-END QMapTracking 2017.11.18 dhthong
#endif // CCDATABUILERIMAGE2DINFO_H
