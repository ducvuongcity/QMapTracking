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

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollBar>

#include <QLabel>

#include <QStyle>
#include <QDesktopWidget>
#include <QProgressDialog>

#include "QMapContainer.h"
#include "ccDataManager.h"
#include "common.h"

#define DEFAULD_PATH "../QMapTracking/document/qPlugin/SampleData"

class ccDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ccDialog(ccBridge &bridge, ccDataStore &data, QWidget *parent = 0);

private:
    void createScreen();
    void signalMapping();
    bool findFileTfw(QString &tfwFile);
    bool renderMap();
    QPointF convertPixelToMMS(const QPoint &pixel);

public slots:
    void sltEvenHandle(QString event);
    void sltLoadCoordinates();
    void sltLoadMap();
    void sltResponseHandle(int type, bool state);
    void sltMapMouseReceiver(const QPoint &globalPoint, const QPoint &localPoint);
    void sgnResponseReadStart();

private:
    ccBridge *m_bridge;
    ccDataStore *m_dataStore;

    QString mPathCurrentMap;
    QImage *imgMap = nullptr;

    QLineEdit *txtPath = nullptr;
    QPushButton *btnLoadCoordinates = nullptr;
    QPushButton *btnLoadMap = nullptr;
    QMapContainer *lblMap = nullptr;
    QScrollArea *scrMap = nullptr;

    QVBoxLayout *verticalLayout = nullptr;
    QHBoxLayout *horizontalLayout = nullptr;

    QProgressDialog *progressDialog;

};

#endif // CCDIALOG_H
