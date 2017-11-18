#ifndef CCDIALOG_H
#define CCDIALOG_H

#include <QApplication>
#include <QWidget>
#include <QDialog>
#include <QImage>
#include <QPushButton>
#include <QLineEdit>
#include <QGraphicsView>
#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollBar>

#include <QStyle>
#include <QDesktopWidget>

#include "QMapContainer.h"
#include "ccDataManager.h"
#include "common.h"

#define DEFAULD_PATH "../QMapTracking/document/qPlugin/SampleData"

class ccDialog : public QDialog
{
    Q_OBJECT

private:
    ccDataManager *m_model = nullptr;
    QString mPathCurrentMap;
    QImage *imgMap = nullptr;

    QLineEdit *txtPath = nullptr;
    QPushButton *btnLoadCoordinates = nullptr;
    QPushButton *btnLoadMap = nullptr;
    QPushButton *btnPlayPause = nullptr;
// ADD-START QMapTracking 2017.11.18 dhthong
    QPushButton *btnLoad2DInfo = nullptr;
// ADD-END QMapTracking 2017,11.18 dhthong
    QMapContainer *lblMap = nullptr;
    QScrollArea *scrMap = nullptr;

    QLabel *lblImage = nullptr;
    QScrollArea *scrImage = nullptr;

    QVBoxLayout *verticalLayout = nullptr;
    QHBoxLayout *horizontalLayout = nullptr;

public:
    explicit ccDialog(ccDataManager &model, QWidget *parent = 0);
    ~ccDialog();

public:
    void createScreen();
    void signalMapping();
    bool findFileTfw(QString &tfwFile);
    bool renderMap();
    QPointF convertPixelToMMS(const QPoint &pixel);
    void sendEvent(EventList event, QString params);

private slots:
    void sltLoadCoordinates();
    void sltLoadMap();
    void sltPlayPause();
    void sltMapMouseReceiver(const QPoint &globalPoint, const QPoint &localPoint);
// ADD-START QMapTracking 2017.11.18 dhthong
    void sltSet2DImageInfo();
// ADD-END QMapTracking 2017,11.18 dhthong
signals:
    void sgnEvent(EventList event, QString params);

};

#endif // CCDIALOG_H
