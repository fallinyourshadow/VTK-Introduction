#pragma once
#include "GeometryItem.h"
#include "vtk3DSImporter.h"
//��ʱ�޷�����3ds�ļ���ԭ�򣺼������̺�����ģ�͵����̲�һ��
class C3DsModelItem :
    public GeometryItem
{
public:
    C3DsModelItem();
    virtual ~C3DsModelItem();

    vtkSmartPointer<vtk3DSImporter> source();
    void loadFile(const std::string& filePath);
    QString name() const;
private:
    vtkSmartPointer<vtk3DSImporter> m_3DSModel;//Source����
    QString m_name;
};

