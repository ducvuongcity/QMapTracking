#include "ccDialog.h"

ccDialog::ccDialog(ccBridge &bridge, ccDataStore &data, QWidget *parent)
    : QDialog(parent)
    , m_bridge(&bridge)
    , m_dataStore(&data)
{
    MACRO_THR_DLOG << "GUI Thread";
    createScreen();
    signalMappingWidget();
    QObject::connect(m_bridge, SIGNAL(sgnEventToView(QString)), this, SLOT(sltEvenHandle(QString)));
}

void ccDialog::createScreen()
{
    setWindowTitle("Map Tracking");
    setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, QSize(640, 480), qApp->desktop()->availableGeometry()));
    imgMap = new QImage();

    txtPath = new QLineEdit(this);
    btnLoadCoordinates = new QPushButton(this);
    btnLoadCoordinates->setText("Load Txt");
    btnLoadMap = new QPushButton(this);
    btnLoadMap->setText("Load Map");
    lblMap = new QMapContainer(this);

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

//    progressDialog = new QProgressDialog(this);
//    progressDialog->setRange(0, 100);
//    progressDialog->hide();
}

void ccDialog::signalMappingWidget()
{
    QObject::connect(btnLoadCoordinates, SIGNAL(clicked(bool)), this, SLOT(sltLoadMMS()), Qt::UniqueConnection);
    QObject::connect(btnLoadMap, SIGNAL(clicked(bool)), this, SLOT(sltLoadMap()), Qt::UniqueConnection);
    QObject::connect(lblMap, SIGNAL(sgnMousePressEvent(QPoint,QPoint)), this, SLOT(sltMapMouseReceiver(QPoint,QPoint)));
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

void ccDialog::sltLoadMMS()
{
    QString path = QFileDialog::getOpenFileName(this, "Open TXT File", QString::fromStdString(DEFAULD_PATH), "Text File(*.txt)");
    if (!path.isEmpty())
    {
        txtPath->setText(path);
        m_bridge->sendEventToController(QString("evt_View_LoadMMS_Req(%1)").arg(path));
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
            m_bridge->sendEventToController(QString("evt_View_LoadWorldFile_Req(%1)").arg(tfwFile));
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
//    progressDialog->close();
}

void ccDialog::sltMapMouseReceiver(const QPoint &globalPoint, const QPoint &localPoint)
{
//    if(ccDataManager::Instance()->getListPixel().contains(localPoint))
//        QToolTip::showText(globalPoint, QString("%1, %2").arg(convertPixelToMMS(localPoint).x()).arg(convertPixelToMMS(localPoint).y()));
}

void ccDialog::sgnResponseReadStart(){
//    progressDialog->show();
}

bool ccDialog::renderMap()
{
//    MACRO_THR_DLOG << ccDataManager::Instance()->isValidWorldFile() << ccDataManager::Instance()->getListMMS().size() << !imgMap->isNull();
//    if(ccDataManager::Instance()->isValidWorldFile() && ccDataManager::Instance()->getListMMS().size() > 0 && !imgMap->isNull()) {
//        MACRO_THR_DLOG << "Render start!";

//        ccWorldFile worldFile = ccDataManager::Instance()->getWorldFile();
//        QList<QPoint> listPixel;

//        for(int i = 0; i < ccDataManager::Instance()->getListMMS().size(); ++i) {
//            double xMap = ccDataManager::Instance()->getListMMS().at(i).x;
//            double yMap = ccDataManager::Instance()->getListMMS().at(i).y;
//            int x = (int)(worldFile.E*xMap - worldFile.B*yMap + worldFile.B*worldFile.F - worldFile.E*worldFile.C)/(worldFile.A*worldFile.E - worldFile.D*worldFile.B);
//            int y = (int)(-worldFile.D*xMap + worldFile.A*yMap + worldFile.D*worldFile.C - worldFile.A*worldFile.F)/(worldFile.A*worldFile.E - worldFile.D*worldFile.B);

//            if(x >= imgMap->width() || y >= imgMap->height())
//                break;

//            imgMap->setPixel(x, y, COLOR_LINE);
//            listPixel.append(QPoint(x, y));
//        }
//        MACRO_THR_DLOG << "Render done!";
//        ccDataManager::Instance()->setListPixel(listPixel);
//        lblMap->setPixmap(QPixmap::fromImage(*imgMap));
//        return true;
//    }
//    return false;
}

QPointF ccDialog::convertPixelToMMS(const QPoint &pixel)
{
//    ccWorldFile worldFile = ccDataManager::Instance()->getWorldFile();
//    return QPoint(worldFile.A*pixel.x() + worldFile.B*pixel.y() + worldFile.C,
    //                  worldFile.D*pixel.x() + worldFile.E*pixel.y() + worldFile.F);
}

void ccDialog::sltEvenHandle(QString event)
{

}
