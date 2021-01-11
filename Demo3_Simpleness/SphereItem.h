#pragma once
#include "GeometryItem.h"
#include "vtkSphereSource.h"
class SphereItem :
    public GeometryItem
{
public:
    SphereItem();
    virtual ~SphereItem();
    vtkSmartPointer<vtkSphereSource> source();
    const RegularPolyhedronProperties& regularPolyhedronProperties();
    void setRegularPolyhedronProperties(RegularPolyhedronProperties&);
private:
    vtkSmartPointer<vtkSphereSource> m_sphere;//Source∂‘œÛ
    RegularPolyhedronProperties m_properties;
};

