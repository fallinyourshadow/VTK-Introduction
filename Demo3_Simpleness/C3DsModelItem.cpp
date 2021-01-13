#include "C3DsModelItem.h"
#include <vtksys/SystemTools.hxx>
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

void C3DsModelItem::loadFile(const std::string &filePath)
{
	std::string extension =
		vtksys::SystemTools::GetFilenameExtension(filePath);
	std::string name =
		vtksys::SystemTools::GetFilenameName(filePath);
	m_name = QString(name.c_str());

	m_name.replace(QString(extension.c_str()), "");
	m_3DSModel->SetFileName(filePath.c_str());
	m_3DSModel->ComputeNormalsOn();

	
}

QString C3DsModelItem::name() const
{
	return QString(m_name);
}
