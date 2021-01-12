#include "PrismItem.h"



PrismItem::PrismItem(): GeometryItem(),
	m_properties({ DefaultHeight, DefaultRadius, DefaultSide })
{
	m_cylinder = vtkSmartPointer<vtkCylinderSource>::New();
	setPrismProperties(m_properties);
	setPolyData(m_cylinder->GetOutputPort(0));
	mapper()->SetInputConnection(0, m_cylinder->GetOutputPort(0) );
	setData( QVariant(Type::Prism), Qt::UserRole + UserRole::Type );
}

PrismItem::~PrismItem()
{
}

vtkSmartPointer<vtkCylinderSource> PrismItem::source()
{
	return vtkSmartPointer<vtkCylinderSource>(m_cylinder);
}

const PrismProperties& PrismItem::prismProperties( )
{
	return m_properties;
}

void PrismItem::setPrismProperties(PrismProperties& properties)
{
	memcpy( &m_properties, &properties , sizeof( PrismProperties ) );
	m_cylinder->SetRadius(m_properties.lfRadius);
	m_cylinder->SetHeight(m_properties.lfHeight);
	m_cylinder->SetResolution(m_properties.lluSide);
	//setPolyData(m_cylinder->GetOutputPort(0));
}
