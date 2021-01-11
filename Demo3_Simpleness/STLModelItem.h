#pragma once
#include "GeometryItem.h"
#include <vtkSTLReader.h>
class STLModelItem :
    public GeometryItem
{
public:
    STLModelItem();
    virtual ~STLModelItem();
    vtkSmartPointer<vtkSTLReader> source();
    void loadFile(QString filePath);

private:
    vtkSmartPointer<vtkSTLReader> m_stlModel;//Source∂‘œÛ

};