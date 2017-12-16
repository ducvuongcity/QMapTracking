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

#include <QTimer>
#include <QThread>

#include "ccQLabel.h"
#include "ccDataManager.h"
#include "common.h"
#include "ccThreadShowImage.h"

#define DEFAULD_PATH "../QMapTracking/document/qPlugin/SampleData/20171014"

class ccMapWidget : public QWidget
{
    Q_OBJECT

private:
    ccDataManager *m_model = nullptr;
    QString mPathCurrentMap;
    QImage *imgMap = nullptr;
    QImage *imgImage = nullptr;
    QLineEdit *txtPath = nullptr;
    QPushButton *btnLoadCoordinates = nullptr;
    QPushButton *btnLoadMap = nullptr;
    QPushButton *btnPlayPause = nullptr;
    QPushButton *btnLoad2DInfo = nullptr;
    ccQLabel *lblMap = nullptr;
    QScrollArea *scrMap = nullptr;
    ccQLabel *lblImage = nullptr;
    QVBoxLayout *verticalLayout = nullptr;
    QHBoxLayout *horizontalLayout = nullptr;
    QSplitter *spliter = nullptr;
    QTimer *timerShowImage = nullptr;

    bool determineMMSPointInsideSelectRegion(const QPoint &mmsPoint, const QPoint &firstPoint, const QPoint &secondPoint);

    bool m_isPlay;
    QList<QPoint> m_hightLightPoint;
    ccThreadShowImage threadShowImage;
private:
    void CreateRect(const QPoint &firstPoint, const QPoint &secondPoint, QRect &ret);
public:
    explicit ccMapWidget(ccDataManager *model, QWidget *parent = 0);
    ~ccMapWidget();

    void createScreen();
    void signalMapping();
    bool findWorldFile(QString &tfwFile);
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
    void sltResizeImageView(int pos, int index);

signals:
    void sgnEvent(EventList event, QString params);

};

#endif // ccMapWidget_H
