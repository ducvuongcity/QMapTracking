#include "ccMapWidget.h"

ccMapWidget::ccMapWidget(ccDataManager *model, QWidget *parent)
    : QWidget(parent)
    , m_model(model)
{
    MACRO_THR_DLOG << "GUI Thread";
    showImgThread = new QThread(parent);
    createScreen();
    signalMapping();
}

ccMapWidget::~ccMapWidget()
{
    MACRO_DEL_PTR(m_model);
}

void ccMapWidget::createScreen()
{
    imgMap = new QImage();
    txtPath = new QLineEdit(this);
    btnLoadCoordinates = new QPushButton(this);
    btnLoadCoordinates->setText("Load Txt");
    btnLoadMap = new QPushButton(this);
    btnLoadMap->setText("Load Map");
    lblMap = new QMapContainer(this);
    btnPlayPause = new QPushButton(this);
    btnPlayPause->setText("Play");
    btnPlayPause->setEnabled(false);
    btnLoad2DInfo = new QPushButton(this);
    btnLoad2DInfo->setText("Image 2D");
    scrMap = new QScrollArea(this);
    scrMap->setWidgetResizable(true);
    scrMap->setWidget(lblMap);

    lblImage = new QLabel(this);
    scrImage = new QScrollArea(this);
    scrImage->setWidgetResizable(true);
    scrImage->setWidget(lblImage);

    horizontalLayout = new QHBoxLayout();
    verticalLayout = new QVBoxLayout(this);

    spliter = new QSplitter(Qt::Vertical);
    spliter->addWidget(scrMap);
    spliter->addWidget(scrImage);

    horizontalLayout->addWidget(txtPath);
    horizontalLayout->addWidget(btnLoadCoordinates);
    horizontalLayout->addWidget(btnLoadMap);
    horizontalLayout->addWidget(btnLoad2DInfo);
    horizontalLayout->addWidget(btnPlayPause);

    verticalLayout->addLayout(horizontalLayout);
    verticalLayout->addWidget(spliter);
}

//mapping signal slot
void ccMapWidget::signalMapping()
{
    QObject::connect(btnLoadCoordinates, SIGNAL(clicked(bool)), this, SLOT(sltLoadCoordinates()), Qt::UniqueConnection);
    QObject::connect(btnLoadMap, SIGNAL(clicked(bool)), this, SLOT(sltLoadMap()), Qt::UniqueConnection);
    QObject::connect(lblMap, SIGNAL(sgnMousePressEvent(QPoint,QPoint)), this, SLOT(sltMapMouseReceiver(QPoint,QPoint)));
    QObject::connect(btnPlayPause, SIGNAL(clicked(bool)), this, SLOT(sltPlayPause()));
    QObject::connect(lblMap, SIGNAL(sgnmouseReleaseEvent(const QPoint &, const QPoint &)), this, SLOT(sltMapMouseReleaseEvent(const QPoint &, const QPoint &)));
    QObject::connect(btnLoad2DInfo, SIGNAL(clicked(bool)), this, SLOT(sltSet2DImageInfo()));
}

//find world file
bool ccMapWidget::findFileTfw(QString &tfwFile)
{
    QFileInfo mapfile(mPathCurrentMap);
    if (!QString::compare(mapfile.suffix(), FILEFORMAT_TIF, Qt::CaseInsensitive)) {
        tfwFile = mapfile.absoluteFilePath().replace(mapfile.suffix(), FILEFORMAT_TFW);
        return true;
    }
    return false;
}

//load gps file
void ccMapWidget::sltLoadCoordinates()
{
    QString path = QFileDialog::getOpenFileName(this, "Open TXT File", QString::fromStdString(DEFAULD_PATH), "Text File(*.txt)");
    if (!path.isEmpty())
    {
        txtPath->setText(path);
        sendEvent(CC_EVT_HMI_READMMS_REQUEST, path);
    }
}

//load map tif
void ccMapWidget::sltLoadMap()
{
    mPathCurrentMap = QFileDialog::getOpenFileName(this, "Open Map File", QString::fromStdString(DEFAULD_PATH), "Image File(*.tif)");
    if (!mPathCurrentMap.isEmpty())
    {
        QString tfwFile;
        if (findFileTfw(tfwFile)) {
            imgMap->load(mPathCurrentMap);
            lblMap->setPixmap(QPixmap::fromImage(*imgMap));
            sendEvent(CC_EVT_HMI_READWORLDFILE_REQUEST, tfwFile);
        }
        else
            QMessageBox::critical(this, "Can't load map", "Can't load map because TFW file not found!");
    }
}

void ccMapWidget::sltPlayPause()
{

}

//rev & show mouse position
void ccMapWidget::sltMapMouseReceiver(const QPoint &globalPoint, const QPoint &localPoint)
{
    if(m_model->getListPixel().contains(localPoint))
        QToolTip::showText(globalPoint, QString("%1, %2").arg(convertPixelToMMS(localPoint).x()).arg(convertPixelToMMS(localPoint).y()));
}

//render path
bool ccMapWidget::renderMap()
{
    MACRO_THR_DLOG << m_model->isValidWorldFile() << m_model->getListMMS().size() << !imgMap->isNull();
    if(m_model->isValidWorldFile() && m_model->getListMMS().size() > 0 && !imgMap->isNull()) {
        MACRO_THR_DLOG << "Render start!";

        ccWorldFile worldFile = m_model->getWorldFile();
        QList<QPoint> listPixel;

        for(uint32_t i = 0; i < m_model->getListMMS().size(); ++i) {
            double xMap = m_model->getListMMS().at(i).x;
            double yMap = m_model->getListMMS().at(i).y;
            int32_t x = (int32_t)(worldFile.E*xMap - worldFile.B*yMap + worldFile.B*worldFile.F - worldFile.E*worldFile.C)/(worldFile.A*worldFile.E - worldFile.D*worldFile.B);
            int32_t y = (int32_t)(-worldFile.D*xMap + worldFile.A*yMap + worldFile.D*worldFile.C - worldFile.A*worldFile.F)/(worldFile.A*worldFile.E - worldFile.D*worldFile.B);

            if(x < 0 || x >= imgMap->width() || y < 0 || y >= imgMap->height()) {
                MACRO_THR_DLOG << "Pixel out map";
                break;
            }

            imgMap->setPixel(x, y, COLOR_LINE);
            listPixel.append(QPoint(x, y));
        }
        MACRO_THR_DLOG << "Render done!";
        m_model->setListPixel(listPixel);
        lblMap->setPixmap(QPixmap::fromImage(*imgMap));
        return true;
    }
    return false;
}

QPointF ccMapWidget::convertPixelToMMS(const QPoint &pixel)
{
    ccWorldFile worldFile = m_model->getWorldFile();
    return QPoint(worldFile.A*pixel.x() + worldFile.B*pixel.y() + worldFile.C,
                  worldFile.D*pixel.x() + worldFile.E*pixel.y() + worldFile.F);
}

//send event to controller
void ccMapWidget::sendEvent(EventList event, QString params)
{
    MACRO_THR_DLOG << "Send event " << event;
    emit sgnEvent(event, params);
}

void ccMapWidget::sltSet2DImageInfo()
{
    QString path = QFileDialog::getExistingDirectory(this,
                                                     tr("Select folder contain 2D images and info"),
                                                     QDir::currentPath(),
                                                     QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
                                                     );
    if (!path.isEmpty())
    {
        sendEvent(CC_EVT_HMI_READ_2D_IMAGE_INFO, path);
    }
}

void ccMapWidget::sltMapMouseReleaseEvent(const QPoint &firstPoint, const QPoint &secondPoint)
{
    if(nullptr == imgMap || nullptr == m_model)
    {
        return;
    }
    // select some mms points and hightlight it
    // 1: Select
    QList<QPoint> &ListPixel = m_model->getListPixel();
    uint32_t idx = 0;
    QVector<uint32_t> StartEndPoint;
    uint32_t pathNum = 0;
    bool flag = false;
    for( ; idx < ListPixel.size(); idx++)
    {
        if(determineMMSPointInsideSelectRegion(ListPixel.at(idx), firstPoint, secondPoint))
        {
            // stat new path
            if(!flag)
            {
                StartEndPoint.append(idx);
                flag = true;
                pathNum++;
            }
        }
        else if(flag)
        {
            // end of path
            StartEndPoint.append(idx);
            flag = false;
        }
    }
    StartEndPoint.append(idx);
    if(0 == pathNum)
    {
        // debug log: there is no mms point inside select region
        return;
    }
    if( StartEndPoint.size() < (pathNum << 1) )
    {
        // debug log: ambigous error
        return;
    }
    // 2: HightLight
    for(idx = 0; idx < pathNum; idx++)
    {
        uint32_t start = StartEndPoint.at(idx << 1);
        uint32_t end = StartEndPoint.at((idx << 1) + 1);
        for(uint32_t i = start; i < end; i++)
        {
            imgMap->setPixel(ListPixel.at(i).x(), ListPixel.at(i).y(), COLOR_GREEN);
        }
    }
    lblMap->setPixmap(QPixmap::fromImage(*imgMap));
    // 3: show 2Dimage
    // find direc and store in imageDirectoryList
    QStringList imageDirectoryList;
    for(idx = 0; idx < pathNum; idx++)
    {
        uint32_t start = StartEndPoint.at(idx << 1);
        uint32_t end = StartEndPoint.at((idx << 1) + 1);
        uint32_t step = (end - start) / CC_SELECT_REGION_DIVIDE;
        QString imageDir;
        while(start < end)
        {
            m_model->requestFindImagePathByTime(m_model->getListMMS().at(start).t, imageDir);
            imageDirectoryList.append(imageDir);
            start += step;
        }
        m_model->requestFindImagePathByTime(m_model->getListMMS().at(end).t, imageDir);
        imageDirectoryList.append(imageDir);
    }
}

bool ccMapWidget::determineMMSPointInsideSelectRegion(const QPoint &mmsPoint, const QPoint &firstPoint, const QPoint &secondPoint)
{
    bool isRightFirstPoint, isRightSecondPoint;
    bool isAboveFirstPoint, isAboveSecondPoint;

    int BotLeftX = (firstPoint.x() > secondPoint.x()) ? firstPoint.x() : secondPoint.x();
    int BotLeftY = (firstPoint.y() > secondPoint.y()) ? firstPoint.y() : secondPoint.y();

    isRightFirstPoint = (mmsPoint.x() > firstPoint.x());
    isRightSecondPoint = (mmsPoint.x() > secondPoint.x());

    isAboveFirstPoint = (mmsPoint.y() > firstPoint.y());
    isAboveSecondPoint = (mmsPoint.y() > secondPoint.y());

    return ((isRightFirstPoint ^ isRightSecondPoint) && (isAboveFirstPoint ^ isAboveSecondPoint))
            || ((mmsPoint.x() == BotLeftX) && (isAboveFirstPoint ^ isAboveSecondPoint))
            || ((mmsPoint.y() == BotLeftY) && (isRightFirstPoint ^ isRightSecondPoint));
}
