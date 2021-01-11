#include "PyramidItem.h"
#include <qdebug.h>
PyramidItem::PyramidItem() : GeometryItem(),
m_properties({ DefaultHeight, DefaultRadius, DefaultSide })
{
	m_cone = vtkSmartPointer<vtkConeSource>::New();
	setPyramidProperties( m_properties );
	mapper()->SetInputConnection( m_cone->GetOutputPort() );
	setData( QVariant(Type::Pyramid), Qt::UserRole + UserRole::Type );
}

PyramidItem::~PyramidItem()
{

}

vtkSmartPointer<vtkConeSource> PyramidItem::source()
{
	return vtkSmartPointer<vtkConeSource>(m_cone);
}

const PyramidProperties& PyramidItem::pyramidProperties()
{
	return m_properties;
}

void PyramidItem::setPyramidProperties(PyramidProperties& properties)
{
	memcpy(&m_properties, &properties, sizeof(PyramidProperties));
	m_cone->SetRadius(m_properties.lfRadius);
	m_cone->SetHeight(m_properties.lfHeight);
	m_cone->SetResolution(m_properties.lluSide);
}


