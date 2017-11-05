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

#include "ccReaderManager.h"
#include "common.h"

#define DEFAULD_PATH "../QMapTracking/document/qPlugin/SampleData"

class ccDialog : public QDialog
{
    Q_OBJECT

private:
    QString mPathCurrentMap;
    QImage *imgMap = nullptr;

    QLineEdit *txtPath = nullptr;
    QPushButton *btnLoadCoordinates = nullptr;
    QPushButton *btnLoadMap = nullptr;
    QLabel *lblMap = nullptr;
    QScrollArea *scrMap = nullptr;

    QVBoxLayout *verticalLayout = nullptr;
    QHBoxLayout *horizontalLayout = nullptr;

public:
    explicit ccDialog(QWidget *parent = 0);
    ~ccDialog();

private:
    void createScreen();
    void signalMapping();
    bool findFileTfw(QString &tfwFile);
    bool renderMap();

private slots:
    void sltLoadCoordinates();
    void sltLoadMap();
    void sltResponseHandle(int type, bool state);

signals:
    void sgnRequestRead(const QString &path, int type);

};

#endif // CCDIALOG_H
