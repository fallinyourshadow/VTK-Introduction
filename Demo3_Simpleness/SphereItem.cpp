#include "SphereItem.h"

SphereItem::SphereItem() : GeometryItem(),
m_properties({ DefaultThetaResolution, DefaultPhiResolution,DefaultRadius })
{
	m_sphere = vtkSmartPointer<vtkSphereSource>::New();
	setRegularPolyhedronProperties(m_properties);
	mapper()->SetInputConnection(m_sphere->GetOutputPort());
	setData(QVariant(Type::RegularPolyhedron), Qt::UserRole + UserRole::Type);
}

SphereItem::~SphereItem()
{

}

vtkSmartPointer<vtkSphereSource> SphereItem::source()
{
	return vtkSmartPointer<vtkSphereSource>(m_sphere);
}

const RegularPolyhedronProperties& SphereItem::regularPolyhedronProperties()
{
	return m_properties;
}

void SphereItem::setRegularPolyhedronProperties(RegularPolyhedronProperties& properties)
{
	memcpy(&m_properties, &properties, sizeof(RegularPolyhedronProperties));
	m_sphere->SetThetaResolution(m_properties.nThetaResolution);
	m_sphere->SetPhiResolution(m_properties.nPhiResolution);
	m_sphere->SetRadius(m_properties.lfRadius);
}
