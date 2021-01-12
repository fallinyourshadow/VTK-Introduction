#include "ModelItem.h"
#include <vtksys/SystemTools.hxx>
#include <vtkPLYReader.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkOBJReader.h>
#include <vtkPolyDataReader.h>
#include <vtkBYUReader.h>
#include <vtkSphereSource.h>
#include <qDebug>
ModelItem::ModelItem():GeometryItem()
{
	
}

ModelItem::~ModelItem()
{
}


int ModelItem::loadFile(const std::string &filePath)
{
    std::string extension =
        vtksys::SystemTools::GetFilenameExtension(filePath);
    std::string name =
        vtksys::SystemTools::GetFilenameName(filePath);
    m_name = QString(name.c_str());
    m_name.replace(QString(extension.c_str()), "");
    if (extension == ".ply")
    {
        vtkSmartPointer<vtkPLYReader> reader = vtkSmartPointer<vtkPLYReader>::New();
        reader->SetFileName(filePath.c_str());
        reader->Update();
        setPolyData(reader->GetOutputPort(0));
        setData(QVariant(Type::PlyModel), Qt::UserRole + UserRole::Type);
    }
    else if (extension == ".vtp")
    {
        vtkSmartPointer<vtkXMLPolyDataReader> reader = vtkSmartPointer<vtkXMLPolyDataReader>::New();
        reader->SetFileName(filePath.c_str());
        reader->Update();
        setPolyData(reader->GetOutputPort(0));
        setData(QVariant(Type::VtpModel), Qt::UserRole + UserRole::Type);
    }
    else if (extension == ".obj")
    {
        vtkSmartPointer<vtkOBJReader> reader = vtkSmartPointer<vtkOBJReader>::New();
        reader->SetFileName(filePath.c_str());
        reader->Update();
        setPolyData(reader->GetOutputPort(0));
        setData(QVariant(Type::ObjModel), Qt::UserRole + UserRole::Type);
    }
    else if (extension == ".stl"|| extension == ".STL")
    {
        vtkSTLReader * reader = vtkSTLReader::New();
        reader->SetFileName(filePath.c_str());
        reader->Update();

        setPolyData(reader->GetOutputPort(0));

        setData(QVariant(Type::StlModel), Qt::UserRole + UserRole::Type);
    }
    else if (extension == ".vtk")
    {
        vtkSmartPointer<vtkPolyDataReader> reader = vtkSmartPointer<vtkPolyDataReader>::New();
        reader->SetFileName(filePath.c_str());
        reader->Update();
        setPolyData(reader->GetOutputPort(0));
        setData(QVariant(Type::VtkModel), Qt::UserRole + UserRole::Type);
    }
    else if (extension == ".g")
    {
        vtkSmartPointer<vtkBYUReader> reader = vtkSmartPointer<vtkBYUReader>::New();
        reader->SetGeometryFileName(filePath.c_str());
        reader->Update();
        setPolyData(reader->GetOutputPort(0));
        setData(QVariant(Type::GModel), Qt::UserRole + UserRole::Type);
    }
    else 
    {
        vtkSmartPointer<vtkSphereSource> source = vtkSmartPointer<vtkSphereSource>::New();
        source->Update();
        setPolyData(source->GetOutputPort(0));
        setData(QVariant(Type::RegularPolyhedron), Qt::UserRole + UserRole::Type);
    }
    mapper()->SetInputConnection(0, polyData());
    qDebug() << "dasdasdas";
    return data(Qt::UserRole + UserRole::Type).toInt();
}

QString ModelItem::name() const
{
    return QString(m_name);
}

void ModelItem::setName(const QString& name)
{
    m_name = name;
}
