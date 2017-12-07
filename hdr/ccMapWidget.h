#ifndef ccMapWidget_H
#define ccMapWidget_H

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
#include <QSplitter>

#include <QStyle>
#include <QDesktopWidget>

#include "QMapContainer.h"
#include "ccDataManager.h"
#include "common.h"

#define DEFAULD_PATH "../QMapTracking/document/qPlugin/SampleData"

class ccMapWidget : public QWidget
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
    QPushButton *btnLoad2DInfo = nullptr;
    QMapContainer *lblMap = nullptr;
    QScrollArea *scrMap = nullptr;
    QLabel *lblImage = nullptr;
    QScrollArea *scrImage = nullptr;
    QVBoxLayout *verticalLayout = nullptr;
    QHBoxLayout *horizontalLayout = nullptr;
    QSplitter *spliter = nullptr;
    QThread *showImgThread = nullptr;

    bool determineMMSPointInsideSelectRegion(const QPoint &mmsPoint, const QPoint &firstPoint, const QPoint &secondPoint);

public:
    explicit ccMapWidget(ccDataManager *model, QWidget *parent = 0);
    ~ccMapWidget();

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
    void sltSet2DImageInfo();
    void sltMapMouseReleaseEvent(const QPoint &, const QPoint &);

signals:
    void sgnEvent(EventList event, QString params);

};

#endif // ccMapWidget_H
