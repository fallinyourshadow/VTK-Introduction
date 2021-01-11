#include "GeometryItem.h"


GeometryItem::GeometryItem():QStandardItem(),
m_properties({ {0,0,0},{0,0,0},0xffffffff})
{
	m_cylinderMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	m_cylinderActor = vtkSmartPointer<vtkActor>::New();
	m_cylinderActor->SetMapper(m_cylinderMapper);

	quint32 col = 0xffff0000;// PrismDefaultParameter::PrismDefaultColor;
	double color[3];
	UInt32ToRGBDouble(col, color);
	actor()->GetProperty()->SetColor(color);
	setCommonProperties(m_properties);
}

GeometryItem::~GeometryItem()
{
}

vtkSmartPointer<vtkPolyDataMapper> GeometryItem::mapper() 
{
	return m_cylinderMapper;
}

vtkSmartPointer<vtkActor> GeometryItem::actor() 
{
	return m_cylinderActor;
}

const CommonProperties& GeometryItem::commonProperties()
{
	return m_properties;
}

void GeometryItem::setCommonProperties(CommonProperties& properties)
{
	actor()->SetPosition( properties.pos );
	double color[3];
	UInt32ToRGBDouble( properties.uColor, color );
	unsigned char* rgba = (unsigned char*)&(properties.uColor);
	actor()->GetProperty()->SetColor( color );
	actor()->GetProperty()->SetOpacity((double)rgba[3] / (double)0xff);

	actor()->RotateX( properties.rot[0] - m_properties.rot[0] );
	actor()->RotateY( properties.rot[1] - m_properties.rot[1] );
	actor()->RotateZ( properties.rot[2] - m_properties.rot[2] );
	
	memcpy(&m_properties, &properties, sizeof(CommonProperties));
}
