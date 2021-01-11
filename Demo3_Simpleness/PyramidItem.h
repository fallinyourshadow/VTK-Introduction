#pragma once
#include "GeometryItem.h"
#include "vtkConeSource.h"

class PyramidItem :
    public GeometryItem
{
public:
    PyramidItem();
    virtual ~PyramidItem();
    vtkSmartPointer<vtkConeSource> source();
    const PyramidProperties& pyramidProperties();
    void setPyramidProperties(PyramidProperties&);

private:
    vtkSmartPointer<vtkConeSource> m_cone;//Source∂‘œÛ
    PyramidProperties m_properties;
};

