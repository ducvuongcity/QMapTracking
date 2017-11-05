#include "ccDialog.h"

ccDialog::ccDialog(QWidget *parent) : QDialog(parent)
{
    MACRO_THR_DLOG << "GUI Thread";
    ccReaderManager::Instance();
    createScreen();
    signalMapping();
}

ccDialog::~ccDialog()
{
    MACRO_DEL_PTR(imgMap);
    MACRO_DEL_PTR(txtPath);
    MACRO_DEL_PTR(btnLoadCoordinates);
    MACRO_DEL_PTR(btnLoadMap);
    MACRO_DEL_PTR(lblMap);
    MACRO_DEL_PTR(scrMap);
    MACRO_DEL_PTR(verticalLayout);
    MACRO_DEL_PTR(horizontalLayout);
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
    QObject::connect(this, SIGNAL(sgnRequestRead(const QString&, int)), ccReaderManager::Instance(), SLOT(sltRequestReadHandle(const QString&, int)), Qt::UniqueConnection);
    QObject::connect(ccReaderManager::Instance(), SIGNAL(sgnResponseReadFinished(int,bool)), this, SLOT(sltResponseHandle(int,bool)), Qt::UniqueConnection);
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
    mPathCurrentMap = QFileDialog::getOpenFileName(this, "Open Map File", QString::fromStdString(DEFAULD_PATH), "Image File(*.*)");
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
    this->metaObject()->className();
    MACRO_THR_DLOG << ccReaderManager::Instance()->isValidWorldFile() << ccReaderManager::Instance()->getListMMS().size() << !imgMap->isNull();
    if(ccReaderManager::Instance()->isValidWorldFile() && ccReaderManager::Instance()->getListMMS().size() > 0 && !imgMap->isNull()) {
        MACRO_THR_DLOG << "Render start!";
        double A = ccReaderManager::Instance()->getWorldFile().xPixelSize;
        double B = ccReaderManager::Instance()->getWorldFile().xAxis;
        double C = ccReaderManager::Instance()->getWorldFile().xCoordinate;
        double D = ccReaderManager::Instance()->getWorldFile().yAxis;
        double E = ccReaderManager::Instance()->getWorldFile().yPixelSize;
        double F = ccReaderManager::Instance()->getWorldFile().yCoordinate;

        for(int i = 0; i < ccReaderManager::Instance()->getListMMS().size(); ++i) {
            double xMap = ccReaderManager::Instance()->getListMMS().at(i).x;
            double yMap = ccReaderManager::Instance()->getListMMS().at(i).y;
            int x = (int)(E*xMap - B*yMap + B*F - E*C)/(A*E - D*B);
            int y = (int)(-D*xMap + A*yMap + D*C - A*F)/(A*E - D*B);

            imgMap->setPixel(x, y, COLOR_LINE);
        }
        MACRO_THR_DLOG << "Render done!";
        lblMap->setPixmap(QPixmap::fromImage(*imgMap));
        return true;
    }
    return false;
}
