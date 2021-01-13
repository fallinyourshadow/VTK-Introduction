#pragma once
#include "GeometryItem.h"
#include "vtk3DSImporter.h"
//暂时无法导出3ds文件，原因：加载流程和其他模型的流程不一致
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
    vtkSmartPointer<vtk3DSImporter> m_3DSModel;//Source对象
    QString m_name;
};

