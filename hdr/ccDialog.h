#ifndef CCDIALOG_H
#define CCDIALOG_H

#include <QApplication>
#include <QString>
#include <QWidget>
#include <QObject>
#include <QDialog>
#include <QImage>
#include <QPushButton>
#include <QLineEdit>
#include <QGraphicsView>
#include <QFileDialog>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollBar>

#include <QLabel>

#include <QStyle>
#include <QDesktopWidget>

#include "ccReaderManager.h"
#include "common.h"

#define DEFAULD_PATH ""

class ccDialog : public QDialog
{
    Q_OBJECT

private:
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

private slots:
    void sltLoadCoordinates();
    void sltLoadMap();

signals:
    void sgnRequestReadMMS(const QString &path);

};

#endif // CCDIALOG_H
