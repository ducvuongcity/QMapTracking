#include "ccDialog.h"

ccDialog::ccDialog(QWidget *parent) : QDialog(parent)
{
    createScreen();
    ccReaderManager::Instance();
    MACRO_THREAD_DLOG << "Main Thread";
}

ccDialog::~ccDialog()
{

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

    QObject::connect(btnLoadCoordinates, SIGNAL(clicked(bool)), this, SLOT(sltLoadCoordinates()), Qt::UniqueConnection);
    QObject::connect(btnLoadMap, SIGNAL(clicked(bool)), this, SLOT(sltLoadMap()), Qt::UniqueConnection);
    QObject::connect(this, SIGNAL(sgnRequestReadMMS(const QString&)), ccReaderManager::Instance(), SLOT(sltReadFileMMS(const QString&)), Qt::UniqueConnection);
}

void ccDialog::sltLoadCoordinates()
{
    QString path = QFileDialog::getOpenFileName(this, "Open TXT File", QString::fromStdString(DEFAULD_PATH), "Text File(*.txt)");
    if (!path.isEmpty())
    {
        txtPath->setText(path);
        emit sgnRequestReadMMS(path);
    }
}

void ccDialog::sltLoadMap()
{
    QString path = QFileDialog::getOpenFileName(this, "Open Map File", QString::fromStdString(DEFAULD_PATH), "Image File(*.*)");
    if (!path.isEmpty())
    {
        imgMap->load(path);
        //----------------------Test render---------------------------
        for(int w = imgMap->size().width() / 3; w < imgMap->size().width() / 2; w++)
            for (int h = imgMap->size().width() / 3; h < imgMap->size().width() / 2; h++)
                imgMap->setPixel(w, h, qRgb(0,255,0));
        //------------------------------------------------------------
        lblMap->setPixmap(QPixmap::fromImage(*imgMap));
    }
}
