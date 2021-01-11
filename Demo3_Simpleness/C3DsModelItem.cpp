#include "C3DsModelItem.h"

C3DsModelItem::C3DsModelItem()
{
	m_3DSModel = vtkSmartPointer<vtk3DSImporter>::New();
	setData(QVariant(Type::C3DsModel), Qt::UserRole + UserRole::Type);
}

C3DsModelItem::~C3DsModelItem()
{
}

vtkSmartPointer<vtk3DSImporter> C3DsModelItem::source()
{
	return vtkSmartPointer<vtk3DSImporter>(m_3DSModel);
}

void C3DsModelItem::loadFile(QString filePath)
{
	m_3DSModel->SetFileName(filePath.toStdString().c_str());
	m_3DSModel->ComputeNormalsOn();
}
