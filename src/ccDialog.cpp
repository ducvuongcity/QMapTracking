#include "ccDialog.h"

ccDialog::ccDialog(QWidget *parent) : QDialog(parent)
{
    MACRO_THR_DLOG << "GUI Thread";
    ccDataManager::Instance();
    createScreen();
    signalMapping();
}

void ccDialog::createScreen()
{
    setWindowTitle("Map Tracking");
    setGeometry(
                QStyle::alignedRect(
                    Qt::LeftToRight,
                    Qt::AlignCenter,
                    QSize(640, 480),
                    qApp->desktop()->availableGeometry()
                    )
                );
    imgMap = new QImage();

    txtPath = new QLineEdit(this);
    btnLoadCoordinates = new QPushButton(this);
    btnLoadCoordinates->setText("Load Txt");
    btnLoadMap = new QPushButton(this);
    btnLoadMap->setText("Load Map");
    lblMap = new QLabel(this);

    scrMap = new QScrollArea(this);
    scrMap->setWidgetResizable(true);
    scrMap->setWidget(lblMap);

    horizontalLayout = new QHBoxLayout();
    verticalLayout = new QVBoxLayout(this);

    horizontalLayout->addWidget(txtPath);
    horizontalLayout->addWidget(btnLoadCoordinates);
    horizontalLayout->addWidget(btnLoadMap);

    verticalLayout->addLayout(horizontalLayout);
    verticalLayout->addWidget(scrMap);
}

void ccDialog::signalMapping()
{
    QObject::connect(btnLoadCoordinates, SIGNAL(clicked(bool)), this, SLOT(sltLoadCoordinates()), Qt::UniqueConnection);
    QObject::connect(btnLoadMap, SIGNAL(clicked(bool)), this, SLOT(sltLoadMap()), Qt::UniqueConnection);
    QObject::connect(this, SIGNAL(sgnRequestRead(const QString&, int)), ccDataManager::Instance(), SLOT(sltRequestReadHandle(const QString&, int)), Qt::UniqueConnection);
    QObject::connect(ccDataManager::Instance(), SIGNAL(sgnResponseReadFinished(int,bool)), this, SLOT(sltResponseHandle(int,bool)), Qt::UniqueConnection);
}

bool ccDialog::findFileTfw(QString &tfwFile)
{
    QFileInfo mapfile(mPathCurrentMap);
    if (!QString::compare(mapfile.suffix(), FILEFORMAT_TIF, Qt::CaseInsensitive)) {
        tfwFile = mapfile.absoluteFilePath().replace(mapfile.suffix(), FILEFORMAT_TFW);
        return true;
    }
    return false;
}

void ccDialog::sltLoadCoordinates()
{
    QString path = QFileDialog::getOpenFileName(this, "Open TXT File", QString::fromStdString(DEFAULD_PATH), "Text File(*.txt)");
    if (!path.isEmpty())
    {
        txtPath->setText(path);
        emit sgnRequestRead(path, CC_TYPE_MMS);
    }
}

void ccDialog::sltLoadMap()
{
    mPathCurrentMap = QFileDialog::getOpenFileName(this, "Open Map File", QString::fromStdString(DEFAULD_PATH), "Image File(*.tif)");
    if (!mPathCurrentMap.isEmpty())
    {
        QString tfwFile;
        if (findFileTfw(tfwFile)) {
            imgMap->load(mPathCurrentMap);
            lblMap->setPixmap(QPixmap::fromImage(*imgMap));
            emit sgnRequestRead(tfwFile, CC_TYPE_WORLDFILE);
        }
        else
            QMessageBox::critical(this, "Can't load map", "Can't load map because TFW file not found!");
    }
}

void ccDialog::sltResponseHandle(int type, bool state)
{
    switch (type) {
    case CC_TYPE_MMS:
        if (state)
            QtConcurrent::run(this, &ccDialog::renderMap);
        break;

    case CC_TYPE_WORLDFILE:
        if (state)
            QtConcurrent::run(this, &ccDialog::renderMap);
        break;

    default:
        break;
    }
}

bool ccDialog::renderMap()
{
    MACRO_THR_DLOG << ccDataManager::Instance()->isValidWorldFile() << ccDataManager::Instance()->getListMMS().size() << !imgMap->isNull();
    if(ccDataManager::Instance()->isValidWorldFile() && ccDataManager::Instance()->getListMMS().size() > 0 && !imgMap->isNull()) {
        MACRO_THR_DLOG << "Render start!";

        ccWorldFile worldFile = ccDataManager::Instance()->getWorldFile();

        for(int i = 0; i < ccDataManager::Instance()->getListMMS().size(); ++i) {
            double xMap = ccDataManager::Instance()->getListMMS().at(i).x;
            double yMap = ccDataManager::Instance()->getListMMS().at(i).y;
            int x = (int)(worldFile.E*xMap - worldFile.B*yMap + worldFile.B*worldFile.F - worldFile.E*worldFile.C)/(worldFile.A*worldFile.E - worldFile.D*worldFile.B);
            int y = (int)(-worldFile.D*xMap + worldFile.A*yMap + worldFile.D*worldFile.C - worldFile.A*worldFile.F)/(worldFile.A*worldFile.E - worldFile.D*worldFile.B);

            if(x >= imgMap->width() || y >= imgMap->height())
                break;

            imgMap->setPixel(x, y, COLOR_LINE);
        }
        MACRO_THR_DLOG << "Render done!";
        lblMap->setPixmap(QPixmap::fromImage(*imgMap));
        return true;
    }
    return false;
}
