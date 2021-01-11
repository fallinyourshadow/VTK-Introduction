#pragma once
#include "GeometryItem.h"
#include "vtkCylinderSource.h"

class PrismItem :
    public GeometryItem
{
public:
    PrismItem();
    virtual ~PrismItem();
    vtkSmartPointer<vtkCylinderSource> source();
    const PrismProperties& prismProperties();
    void setPrismProperties(PrismProperties&);

private:
	vtkSmartPointer<vtkCylinderSource> m_cylinder;//Source∂‘œÛ
    PrismProperties m_properties;
};

