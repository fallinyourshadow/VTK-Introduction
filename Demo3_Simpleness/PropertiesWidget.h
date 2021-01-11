#ifndef PRISM_H
#define PRISM_H

#include <QWidget>
#include <QStandardItem>
#include "PreDefine.h"
#include "GeometryItem.h"
#include <QDoubleSpinBox>
#include <QSpinBox>
namespace Ui {
class PropertiesWidget;
}

class PropertiesWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PropertiesWidget(QWidget *parent = nullptr);
    ~PropertiesWidget();
    void setSelectedItem(GeometryItem* item);
signals:
    void propertiesChanged();
    void removeItem(GeometryItem*);
private slots:
    
    void positionChanged(double);
    void rotationChanged(double);
    void colorChanged(int);
    
    void prismPropertiesChanged(int);
    void prismPropertiesChanged(double);

    void pyramidPropertiesChanged(int);
    void pyramidPropertiesChanged(double);

    void RegularPolyhedronPropertiesChanged(int);
    void RegularPolyhedronPropertiesChanged(double);
private:
    void hideAllSpecificWidget();
    void setObjName(const QString& name);
    GeometryItem* m_pSelectedItem;


    Ui::PropertiesWidget *ui;

    //ͨ�����Կؼ�ָ��
    QDoubleSpinBox* m_pSenderPosx;
    QDoubleSpinBox* m_pSenderPosy;
    QDoubleSpinBox* m_pSenderPosz;

    QDoubleSpinBox* m_pSenderRotx;
    QDoubleSpinBox* m_pSenderRoty;
    QDoubleSpinBox* m_pSenderRotz;

    QSpinBox* m_pSenderColorR;
    QSpinBox* m_pSenderColorG;
    QSpinBox* m_pSenderColorB;
    QSpinBox* m_pSenderColorA;
    //�������Կؼ�
    QSpinBox* m_pSenderSideN;
    QDoubleSpinBox* m_pSenderSideLen;
    QDoubleSpinBox* m_pSenderSideRadius;

    //��׶���Կؼ�
    QSpinBox* m_pSenderPyramidSideN;
    QDoubleSpinBox* m_pSenderPyramidHieght;
    QDoubleSpinBox* m_pSenderPyramidRadius;

    //�����������Կؼ�
    QSpinBox* m_pSenderRegularPolyhedronTheta;
    QSpinBox* m_pSenderRegularPolyhedronPhi;
    QDoubleSpinBox* m_pSenderRegularPolyhedronRadius;
};

#endif // PRISM_H
