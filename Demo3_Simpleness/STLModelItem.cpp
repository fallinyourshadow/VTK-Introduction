#include "STLModelItem.h"

STLModelItem::STLModelItem():GeometryItem()
{
	m_stlModel = vtkSmartPointer<vtkSTLReader>::New();
	mapper()->SetInputConnection(m_stlModel->GetOutputPort());
	setData(QVariant(Type::StlModel), Qt::UserRole + UserRole::Type);
}

STLModelItem::~STLModelItem()
{
}

vtkSmartPointer<vtkSTLReader> STLModelItem::source()
{
	return vtkSmartPointer<vtkSTLReader>(m_stlModel);
}

void STLModelItem::loadFile(QString filePath)
{
	m_stlModel->SetFileName(filePath.toStdString().c_str());
	m_stlModel->Update();
}
