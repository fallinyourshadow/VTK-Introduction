#include "PyramidItem.h"
#include <qdebug.h>
PyramidItem::PyramidItem() : GeometryItem(),
m_properties({ DefaultHeight, DefaultRadius, DefaultSide })
{
	m_cone = vtkSmartPointer<vtkConeSource>::New();
	setPyramidProperties( m_properties );

	mapper()->SetInputConnection(0, m_cone->GetOutputPort(0) );
	setPolyData(m_cone->GetOutputPort(0));
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


