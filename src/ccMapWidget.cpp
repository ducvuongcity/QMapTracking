#include "ccMapWidget.h"

ccMapWidget::ccMapWidget(ccDataManager *model, QWidget *parent)
    : QWidget(parent)
    , m_model(model)
{
    MACRO_THR_DLOG << "GUI Thread";
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
// ADD-START QMapTracking 2017.11.18 dhthong
    btnLoad2DInfo = new QPushButton(this);
    btnLoad2DInfo->setText("Image 2D");
// ADD-END QMapTracking 2017.11.18 dhthong
    scrMap = new QScrollArea(this);
    scrMap->setWidgetResizable(true);
    scrMap->setWidget(lblMap);

    lblImage = new QLabel(this);
    scrImage = new QScrollArea(this);
    scrImage->setWidgetResizable(true);
    scrImage->setWidget(lblImage);

    horizontalLayout = new QHBoxLayout();
    verticalLayout = new QVBoxLayout(this);

    horizontalLayout->addWidget(txtPath);
    horizontalLayout->addWidget(btnLoadCoordinates);
    horizontalLayout->addWidget(btnLoadMap);
// ADD-START QMapTracking 2017.11.18 dhthong
    horizontalLayout->addWidget(btnLoad2DInfo);
// ADD-END QMapTracking 2017.11.18 dhthong
    horizontalLayout->addWidget(btnPlayPause);

    verticalLayout->addLayout(horizontalLayout);
    verticalLayout->addWidget(scrMap);
    verticalLayout->addWidget(scrImage);
}

void ccMapWidget::signalMapping()
{
    QObject::connect(btnLoadCoordinates, SIGNAL(clicked(bool)), this, SLOT(sltLoadCoordinates()), Qt::UniqueConnection);
    QObject::connect(btnLoadMap, SIGNAL(clicked(bool)), this, SLOT(sltLoadMap()), Qt::UniqueConnection);
    QObject::connect(lblMap, SIGNAL(sgnMousePressEvent(QPoint,QPoint)), this, SLOT(sltMapMouseReceiver(QPoint,QPoint)));
    QObject::connect(btnPlayPause, SIGNAL(clicked(bool)), this, SLOT(sltPlayPause()));
// ADD-START QMapTracking 2017.11.18 dhthong
    QObject::connect(lblMap, SIGNAL(sgnmouseReleaseEvent(const QPoint &, const QPoint &)), this, SLOT(sltMapMouseReleaseEvent(const QPoint &, const QPoint &)));
    QObject::connect(btnLoad2DInfo, SIGNAL(clicked(bool)), this, SLOT(sltSet2DImageInfo()));
// ADD-END QMapTracking 2017.11.18 dhthong
}

bool ccMapWidget::findFileTfw(QString &tfwFile)
{
    QFileInfo mapfile(mPathCurrentMap);
    if (!QString::compare(mapfile.suffix(), FILEFORMAT_TIF, Qt::CaseInsensitive)) {
        tfwFile = mapfile.absoluteFilePath().replace(mapfile.suffix(), FILEFORMAT_TFW);
        return true;
    }
    return false;
}

void ccMapWidget::sltLoadCoordinates()
{
    QString path = QFileDialog::getOpenFileName(this, "Open TXT File", QString::fromStdString(DEFAULD_PATH), "Text File(*.txt)");
    if (!path.isEmpty())
    {
        txtPath->setText(path);
        sendEvent(CC_EVT_HMI_READMMS_REQUEST, path);
    }
}

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

void ccMapWidget::sltMapMouseReceiver(const QPoint &globalPoint, const QPoint &localPoint)
{
    if(m_model->getListPixel().contains(localPoint))
        QToolTip::showText(globalPoint, QString("%1, %2").arg(convertPixelToMMS(localPoint).x()).arg(convertPixelToMMS(localPoint).y()));
}

bool ccMapWidget::renderMap()
{
    MACRO_THR_DLOG << m_model->isValidWorldFile() << m_model->getListMMS().size() << !imgMap->isNull();
    if(m_model->isValidWorldFile() && m_model->getListMMS().size() > 0 && !imgMap->isNull()) {
        MACRO_THR_DLOG << "Render start!";

        ccWorldFile worldFile = m_model->getWorldFile();
        QList<QPoint> listPixel;

        for(int i = 0; i < m_model->getListMMS().size(); ++i) {
            double xMap = m_model->getListMMS().at(i).x;
            double yMap = m_model->getListMMS().at(i).y;
            int x = (int)(worldFile.E*xMap - worldFile.B*yMap + worldFile.B*worldFile.F - worldFile.E*worldFile.C)/(worldFile.A*worldFile.E - worldFile.D*worldFile.B);
            int y = (int)(-worldFile.D*xMap + worldFile.A*yMap + worldFile.D*worldFile.C - worldFile.A*worldFile.F)/(worldFile.A*worldFile.E - worldFile.D*worldFile.B);

            if(x >= imgMap->width() || y >= imgMap->height())
                break;

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

void ccMapWidget::sendEvent(EventList event, QString params)
{
    MACRO_THR_DLOG << "Send event " << event;
    emit sgnEvent(event, params);
}
// ADD-START QMapTracking 2017.11.18 dhthong
void ccMapWidget::sltSet2DImageInfo()
{
    QString path = QFileDialog::getExistingDirectory(this,
                                                     tr("Select folder contain 2D images and info"),
                                                     QDir::currentPath(),
                                                     QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
                                                     );
    if (!path.isEmpty())
    {

        if( nullptr != m_model )
        {
            m_model->notifyChange2DImageInfo(path);
        }
        else
        {
//            QMessageBox::critical(this, "abc");
        }
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
    quint32 idx = 0;
    QVector<quint32> StartEndPoint;
    quint32 pathNum = 0;
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
        quint32 start = StartEndPoint.at(idx << 1);
        quint32 end = StartEndPoint.at((idx << 1) + 1);
        for(int i = start; i < end; i++)
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
        quint32 start = StartEndPoint.at(idx << 1);
        quint32 end = StartEndPoint.at((idx << 1) + 1);
        quint32 step = (end - start) / CC_SELECT_REGION_DIVIDE;
        while(start <= end)
        {
            QString imageDir;
            m_model->requestFindImagePathByTime(m_model->getListMMS().at(start).t, imageDir);
            imageDirectoryList.append(imageDir);

            start += step;
        }
    }
    //
    return;
}

bool ccMapWidget::determineMMSPointInsideSelectRegion(const QPoint &mmsPoint, const QPoint &firstPoint, const QPoint &secondPoint)
{
    bool isNotLeftFirstPoint, isNotLeftSecondPoint;
    bool isNotBelowFirstPoint, isNotBelowSecondPoint;

    isNotLeftFirstPoint = (mmsPoint.x() > firstPoint.x())?true:false;
    isNotLeftSecondPoint = (mmsPoint.x() > secondPoint.x())?true:false;

    isNotBelowFirstPoint = (mmsPoint.y() > firstPoint.y())?true:false;
    isNotBelowSecondPoint = (mmsPoint.y() > secondPoint.y())?true:false;

    if( (isNotLeftFirstPoint ^ isNotLeftSecondPoint) &&
        (isNotBelowFirstPoint ^ isNotBelowSecondPoint) )
    {
        return true;
    }
    return false;
}
// ADD-END QMapTracking 2017.11.18 dhthong
