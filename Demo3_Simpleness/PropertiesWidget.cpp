#include "PropertiesWidget.h"
#include "ui_PropertiesWidget.h"
#include "PrismItem.h"
#include "PyramidItem.h"
#include "SphereItem.h"
#include "ModelItem.h"
#include <QDoubleSpinBox>
#include <QFileDialog>
#include <qdebug.h>
PropertiesWidget::PropertiesWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::PropertiesWidget),
    m_pSelectedItem(nullptr)
{
    ui->setupUi(this);
    {//导出控件
        ui->comboBox_type->setItemData(0,QVariant( Type::StlModel), Qt::UserRole + UserRole::Type);
        connect(ui->pushButton_export, &QPushButton::clicked, [=]() {
            QString selectedDir =
                QFileDialog::getExistingDirectory();
            if (selectedDir == "")
                return;
            if (ui->lineEdit_fileName->text() == "")
                return;
            selectedDir.append("/")
                .append(ui->lineEdit_fileName->text())
                .append(ui->comboBox_type->currentText());  
            if (QFile(selectedDir).exists())
                return;
            Q_EMIT modelExported(selectedDir,ui->comboBox_type->currentData(Qt::UserRole + UserRole::Type).toInt());
        });
    }
    {//通用属性控件
        //位置
        m_pSenderPosx = ui->doubleSpinBox_posx;
        m_pSenderPosy = ui->doubleSpinBox_posy;
        m_pSenderPosz = ui->doubleSpinBox_posz;

        m_pSenderPosx->setRange(-1.0, 1.0);
        m_pSenderPosy->setRange(-1.0, 1.0);
        m_pSenderPosz->setRange(-1.0, 1.0);

        m_pSenderPosx->setSingleStep(0.1);
        m_pSenderPosy->setSingleStep(0.1);
        m_pSenderPosz->setSingleStep(0.1);

        connect(m_pSenderPosx,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this,
            &PropertiesWidget::positionChanged);
        connect(m_pSenderPosy,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this,
            &PropertiesWidget::positionChanged);
        connect(m_pSenderPosz,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this,
            &PropertiesWidget::positionChanged);

        //角度
        m_pSenderRotx = ui->doubleSpinBox_rotx;
        m_pSenderRoty = ui->doubleSpinBox_roty;
        m_pSenderRotz = ui->doubleSpinBox_rotz;

        m_pSenderRotx->setRange(0, 360);
        m_pSenderRoty->setRange(0, 360);
        m_pSenderRotz->setRange(0, 360);

        m_pSenderRotx->setSingleStep(1);
        m_pSenderRoty->setSingleStep(1);
        m_pSenderRotz->setSingleStep(1);

        connect(m_pSenderRotx,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this,
            &PropertiesWidget::rotationChanged);
        connect(m_pSenderRoty,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this,
            &PropertiesWidget::rotationChanged);
        connect(m_pSenderRotz,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this,
            &PropertiesWidget::rotationChanged);

        //颜色
        m_pSenderColorR = ui->spinBox_colorR;
        m_pSenderColorG = ui->spinBox_colorG;
        m_pSenderColorB = ui->spinBox_colorB;
        m_pSenderColorA = ui->spinBox_colorA;

        m_pSenderColorR->setRange(0, 0xff);
        m_pSenderColorG->setRange(0, 0xff);
        m_pSenderColorB->setRange(0, 0xff);
        m_pSenderColorA->setRange(0, 0xff);


        m_pSenderColorR->setSingleStep(5);
        m_pSenderColorG->setSingleStep(5);
        m_pSenderColorB->setSingleStep(5);
        m_pSenderColorA->setSingleStep(5);

        connect(m_pSenderColorR,
            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this,
            &PropertiesWidget::colorChanged);
        connect(m_pSenderColorG,
            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this,
            &PropertiesWidget::colorChanged);
        connect(m_pSenderColorB,
            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this,
            &PropertiesWidget::colorChanged);
        connect(m_pSenderColorA,
            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this,
            &PropertiesWidget::colorChanged);
    }
    
    {//棱柱属性控件
        m_pSenderSideN = ui->spinBox_sideN;
        m_pSenderSideLen = ui->doubleSpinBox_sideLen;
        m_pSenderSideRadius = ui->doubleSpinBox_radius;

        m_pSenderSideN->setRange(3, (int)0x7fffffff);
        m_pSenderSideLen->setRange(0, 1);
        m_pSenderSideRadius->setRange(0, 1);

        m_pSenderSideN->setSingleStep(1);
        m_pSenderSideLen->setSingleStep(0.1);
        m_pSenderSideRadius->setSingleStep(0.1);

        connect(m_pSenderSideN,
            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this,
            static_cast<void (PropertiesWidget::*)(int)>(&PropertiesWidget::prismPropertiesChanged));
        connect(m_pSenderSideLen,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this,
            static_cast<void (PropertiesWidget::*)(double)>(&PropertiesWidget::prismPropertiesChanged));
        connect(m_pSenderSideRadius,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this,
            static_cast<void (PropertiesWidget::*)(double)>(&PropertiesWidget::prismPropertiesChanged));
    }

    {//棱锥属性控件

        m_pSenderPyramidSideN = ui->spinBox_PyramidSideN;
        m_pSenderPyramidHieght = ui->doubleSpinBox_PyramidHeight;
        m_pSenderPyramidRadius = ui->doubleSpinBox_PyramidRadius;

        m_pSenderPyramidSideN->setRange(3, (int)0x7fffffff);
        m_pSenderPyramidHieght->setRange(0, 1);
        m_pSenderPyramidRadius->setRange(0, 1);

        m_pSenderPyramidSideN->setSingleStep(1);
        m_pSenderPyramidHieght->setSingleStep(0.1);
        m_pSenderPyramidRadius->setSingleStep(0.1);

        connect(m_pSenderPyramidSideN,
            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this,
            static_cast<void (PropertiesWidget::*)(int)>(&PropertiesWidget::pyramidPropertiesChanged));
        connect(m_pSenderPyramidHieght,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this,
            static_cast<void (PropertiesWidget::*)(double)>(&PropertiesWidget::pyramidPropertiesChanged));
        connect(m_pSenderPyramidRadius,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this,
            static_cast<void (PropertiesWidget::*)(double)>(&PropertiesWidget::pyramidPropertiesChanged));
    }

    {//正多属性面体控件
        m_pSenderRegularPolyhedronTheta = ui->spinBox_ThetaResolution;
        m_pSenderRegularPolyhedronPhi = ui->spinBox_PhiResolution;
        m_pSenderRegularPolyhedronRadius = ui->doubleSpinBox_RegularPolyhedronRadius;

        m_pSenderRegularPolyhedronTheta->setRange(0, (int)0x7fffffff);
        m_pSenderRegularPolyhedronPhi->setRange(0, (int)0x7fffffff);
        m_pSenderRegularPolyhedronRadius->setRange(0, 1);

        m_pSenderRegularPolyhedronTheta->setSingleStep(1);
        m_pSenderRegularPolyhedronPhi->setSingleStep(1);
        m_pSenderRegularPolyhedronRadius->setSingleStep(0.1);

        connect(m_pSenderRegularPolyhedronTheta,
            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this,
            static_cast<void (PropertiesWidget::*)(int)>(&PropertiesWidget::RegularPolyhedronPropertiesChanged));
        connect(m_pSenderRegularPolyhedronPhi,
            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this,
            static_cast<void (PropertiesWidget::*)(int)>(&PropertiesWidget::RegularPolyhedronPropertiesChanged));
        connect(m_pSenderRegularPolyhedronRadius,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this,
            static_cast<void (PropertiesWidget::*)(double)>(&PropertiesWidget::RegularPolyhedronPropertiesChanged));
    }

    connect(ui->pushButton_remove, &QPushButton::clicked, [=]() {
        Q_EMIT removeItem(m_pSelectedItem);
    });
}

PropertiesWidget::~PropertiesWidget()
{
    delete ui;
}

void PropertiesWidget::setSelectedItem(GeometryItem* item)
{
    m_pSelectedItem = item;
    if (m_pSelectedItem == nullptr)
    {
        setObjName( "" );
        return;
    }
    hideAllSpecificWidget();

    setObjName( item->text() );

    m_pSenderPosx->setValue( item->commonProperties().pos[0] );
    m_pSenderPosy->setValue( item->commonProperties().pos[1] );
    m_pSenderPosz->setValue( item->commonProperties().pos[2] );

    m_pSenderRotx->setValue( item->commonProperties().rot[0] );
    m_pSenderRoty->setValue( item->commonProperties().rot[1] );
    m_pSenderRotz->setValue( item->commonProperties().rot[2] );

    const unsigned char* rgb;
    rgb = (const unsigned char*)&( item->commonProperties().uColor );

    m_pSenderColorR->setValue(rgb[0]);
    m_pSenderColorG->setValue(rgb[1]);
    m_pSenderColorB->setValue(rgb[2]);
    m_pSenderColorA->setValue(rgb[3]);
    switch (item->data(Qt::UserRole + UserRole::Type).toInt())
    {
    case Type::Prism:
    {
        PrismItem* prism = (PrismItem*)item;
        m_pSenderSideLen->setValue(prism->prismProperties().lfHeight);
        m_pSenderSideRadius->setValue(prism->prismProperties().lfRadius);
        m_pSenderSideN->setValue(prism->prismProperties().lluSide);
    
        ui->groupBox_prism->show();
        break;
    }
    case Type::Pyramid:
    {
        PyramidItem* pyramid = (PyramidItem*)item;
        m_pSenderPyramidSideN->setValue(pyramid->pyramidProperties().lluSide);
        m_pSenderPyramidHieght->setValue(pyramid->pyramidProperties().lfHeight);
        m_pSenderPyramidRadius->setValue(pyramid->pyramidProperties().lfRadius);
        ui->groupBox_pyramid->show();
        break;
    }
    case Type::RegularPolyhedron:
    {
        SphereItem* sphereItem = (SphereItem*)item;
        m_pSenderRegularPolyhedronTheta->setValue(sphereItem->regularPolyhedronProperties().nThetaResolution);
        m_pSenderRegularPolyhedronPhi->setValue(sphereItem->regularPolyhedronProperties().nPhiResolution);
        m_pSenderRegularPolyhedronRadius->setValue(sphereItem->regularPolyhedronProperties().lfRadius);
        ui->groupBox_RegularPolyhedron->show();
        break;
    }
    case Type::StlModel:
    case Type::ObjModel:
    case Type::PlyModel:
    case Type::VtkModel:
    case Type::GModel:
    case Type::VtpModel:
    case Type::C3DsModel:
    {
        ModelItem* modelItem = (ModelItem*)item;
        ui->lineEdit_fileName->setText(modelItem->name());
        
        break;
    }
    default:
        break;
    }
    showCommonProperties();
}

GeometryItem* PropertiesWidget::selectedItem()
{
    return m_pSelectedItem;
}


void PropertiesWidget::positionChanged(double value)
{
    CommonProperties prop;
    memcpy(&prop, &(m_pSelectedItem->commonProperties()), sizeof(CommonProperties));
    if ((quint64)sender() == (quint64)m_pSenderPosx)
    {
        prop.pos[0] = value;
    }
    else if ((quint64)sender() == (quint64)m_pSenderPosy)
    {
        prop.pos[1] = value;
    }
    else if ((quint64)sender() == (quint64)m_pSenderPosz)
    {
        prop.pos[2] = value;
    }

    if (m_pSelectedItem)
    {
        m_pSelectedItem->setCommonProperties(prop);
        Q_EMIT propertiesChanged();
    }
}

void PropertiesWidget::rotationChanged(double value)
{
    CommonProperties prop;
    memcpy(&prop, &(m_pSelectedItem->commonProperties()), sizeof( CommonProperties ));
    if ((quint64)sender() == (quint64)m_pSenderRotx)
    {
        prop.rot[0] = value;
    }
    else if ((quint64)sender() == (quint64)m_pSenderRoty)
    {
        prop.rot[1] = value;
    }
    else if ((quint64)sender() == (quint64)m_pSenderRotz)
    {
        prop.rot[2] = value;
    }

    if (m_pSelectedItem)
    {
        m_pSelectedItem->setCommonProperties(prop);
        Q_EMIT propertiesChanged();
    }
}

void PropertiesWidget::colorChanged(int value)
{
    CommonProperties prop;
    memcpy(&prop, &(m_pSelectedItem->commonProperties()), sizeof(CommonProperties));
    unsigned char* color = (unsigned char*)&prop.uColor;
    if ((quint64)sender() == (quint64)m_pSenderColorR)
    {
        color[0] = value;
    }
    else if ((quint64)sender() == (quint64)m_pSenderColorG)
    {
        color[1] = value;
    }
    else if ((quint64)sender() == (quint64)m_pSenderColorB)
    {
        color[2] = value;
    }
    else if ((quint64)sender() == (quint64)m_pSenderColorA)
    {
        color[3] = value;
    }
    if (m_pSelectedItem)
    {
        m_pSelectedItem->setCommonProperties(prop);
        Q_EMIT propertiesChanged();
    }
}

void PropertiesWidget::prismPropertiesChanged(int value)
{
    if (m_pSelectedItem->data(Qt::UserRole + UserRole::Type) != Type::Prism)
        return;
    PrismItem* prism = (PrismItem*)m_pSelectedItem;
    PrismProperties prop;
    memcpy(&prop, &(prism->prismProperties()),sizeof(PrismProperties));
    prop.lluSide = value;
    prism->setPrismProperties(prop);
    Q_EMIT propertiesChanged();
}

void PropertiesWidget::prismPropertiesChanged(double value)
{
    if (m_pSelectedItem->data(Qt::UserRole + UserRole::Type) != Type::Prism)
        return;
    PrismItem* prism = (PrismItem*)m_pSelectedItem;
    PrismProperties prop;
    memcpy(&prop, &(prism->prismProperties()), sizeof(PrismProperties));
    if ((quint64)sender() == (quint64)m_pSenderSideLen)
    {
        prop.lfHeight = value;
    }
    else if((quint64)sender() == (quint64)m_pSenderSideRadius)
    {
        prop.lfRadius = value;
    }
    prism->setPrismProperties(prop);
    Q_EMIT propertiesChanged();
}

void PropertiesWidget::pyramidPropertiesChanged(int value)
{
    if (m_pSelectedItem->data(Qt::UserRole + UserRole::Type) != Type::Pyramid)
        return;
    PyramidItem* pyramid = (PyramidItem*)m_pSelectedItem;
    PyramidProperties prop;
    memcpy(&prop, &(pyramid->pyramidProperties()), sizeof(PrismProperties));
    prop.lluSide = value;
    pyramid->setPyramidProperties(prop);
    Q_EMIT propertiesChanged();
}

void PropertiesWidget::pyramidPropertiesChanged(double value)
{
    if (m_pSelectedItem->data(Qt::UserRole + UserRole::Type) != Type::Pyramid)
        return;
    PyramidItem* pyramid = (PyramidItem*)m_pSelectedItem;
    PyramidProperties prop;
    memcpy(&prop, &(pyramid->pyramidProperties()), sizeof(PyramidProperties));
    if ((quint64)sender() == (quint64)m_pSenderPyramidHieght)
    {
        prop.lfHeight = value;
    }
    else if ((quint64)sender() == (quint64)m_pSenderPyramidRadius)
    {
        prop.lfRadius = value;
    }
    pyramid->setPyramidProperties(prop);
    Q_EMIT propertiesChanged();
}

void PropertiesWidget::RegularPolyhedronPropertiesChanged(int value)
{
    if (m_pSelectedItem->data(Qt::UserRole + UserRole::Type) != Type::RegularPolyhedron)
        return;
    SphereItem* regularPolyhedron = (SphereItem*)m_pSelectedItem;
    RegularPolyhedronProperties prop;
    memcpy(&prop, &(regularPolyhedron->regularPolyhedronProperties()), sizeof(RegularPolyhedronProperties));
    if ((quint64)sender() == (quint64)m_pSenderRegularPolyhedronTheta)
    {
        prop.nThetaResolution = value;
    }
    else if ((quint64)sender() == (quint64)m_pSenderRegularPolyhedronPhi)
    {
        prop.nPhiResolution = value;
    }
    regularPolyhedron->setRegularPolyhedronProperties(prop);
    Q_EMIT propertiesChanged();
}

void PropertiesWidget::RegularPolyhedronPropertiesChanged(double value)
{
    if (m_pSelectedItem->data(Qt::UserRole + UserRole::Type) != Type::RegularPolyhedron)
        return;
    SphereItem* regularPolyhedron = (SphereItem*)m_pSelectedItem;
    RegularPolyhedronProperties prop;
    memcpy(&prop, &(regularPolyhedron->regularPolyhedronProperties()), sizeof(RegularPolyhedronProperties));

    prop.lfRadius = value;


    regularPolyhedron->setRegularPolyhedronProperties(prop);
    Q_EMIT propertiesChanged();
}

void PropertiesWidget::hideAllSpecificWidget()
{
    ui->groupBox_pyramid->hide();
    ui->groupBox_prism->hide();
    ui->groupBox_RegularPolyhedron->hide();
    ui->groupBox_export->hide();
}

void PropertiesWidget::showCommonProperties()
{

    ui->groupBox_export->show();
}

void PropertiesWidget::setObjName(const QString& name)
{
    ui->label_objName->setText(name);
}
