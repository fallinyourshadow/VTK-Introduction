#pragma once
#include "GeometryItem.h"
#include "vtk3DSImporter.h"

class C3DsModelItem :
    public GeometryItem
{
public:
    C3DsModelItem();
    virtual ~C3DsModelItem();
    vtkSmartPointer<vtk3DSImporter> source();
    void loadFile(QString filePath);

private:
    vtkSmartPointer<vtk3DSImporter> m_3DSModel;//Source∂‘œÛ

};

