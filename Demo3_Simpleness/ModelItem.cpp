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
    if (m_pVtkAlgorithmOutput == nullptr)
        return;
    switch (data(Qt::UserRole + UserRole::Type).toInt())
    {
    case Type::StlModel:
    {
        vtkSTLReader* reader = (vtkSTLReader*)m_pVtkAlgorithmOutput;
        reader->Delete();
        break; 
    }
    case Type::PlyModel:
    {
        vtkPLYReader* reader = (vtkPLYReader*)m_pVtkAlgorithmOutput;
        reader->Delete();
        break;
    }
    case Type::ObjModel:
    {
        vtkOBJReader* reader = (vtkOBJReader*)m_pVtkAlgorithmOutput;
        reader->Delete();
        break;
    }
    case Type::VtkModel:
    {
        vtkPolyDataReader* reader = (vtkPolyDataReader*)m_pVtkAlgorithmOutput;
        reader->Delete();
        break;
    }
    case Type::VtpModel:
    {
        vtkXMLPolyDataReader* reader = (vtkXMLPolyDataReader*)m_pVtkAlgorithmOutput;
        reader->Delete();
        break;
    }
    case Type::GModel:
    {
        vtkBYUReader* reader = (vtkBYUReader*)m_pVtkAlgorithmOutput;
        reader->Delete();
        break;
    }
    case Type::RegularPolyhedron:
    {
        vtkSphereSource* reader = (vtkSphereSource*)m_pVtkAlgorithmOutput;
        reader->Delete();
        break;
    }
    default:
        break;
    }
}


int ModelItem::loadFile(const QString &filePath)
{
    QTextCodec* code = QTextCodec::codecForName("GB2312");//解决中文路径问题
    std::string fileName = code->fromUnicode(filePath).data();
    std::string extension =
        vtksys::SystemTools::GetFilenameExtension(fileName);
    std::string name =
        vtksys::SystemTools::GetFilenameName(filePath.toStdString().c_str());
    m_name = QString(name.c_str());
    m_name.replace(QString(extension.c_str()), "");
    if (extension == ".ply")
    {
        vtkPLYReader * reader = vtkPLYReader::New();
        reader->SetFileName(fileName.c_str());
        reader->Update();
        setPolyData(reader->GetOutputPort(0));
        setData(QVariant(Type::PlyModel), Qt::UserRole + UserRole::Type);
        m_pVtkAlgorithmOutput = reader;
    }
    else if (extension == ".vtp")
    {
        vtkXMLPolyDataReader * reader = vtkXMLPolyDataReader::New();
        reader->SetFileName(fileName.c_str());
        reader->Update();
        setPolyData(reader->GetOutputPort(0));
        setData(QVariant(Type::VtpModel), Qt::UserRole + UserRole::Type);
        m_pVtkAlgorithmOutput = reader;
    }
    else if (extension == ".obj")
    {
        vtkOBJReader * reader = vtkOBJReader::New();
        reader->SetFileName(fileName.c_str());
        reader->Update();
        setPolyData(reader->GetOutputPort(0));
        setData(QVariant(Type::ObjModel), Qt::UserRole + UserRole::Type);
        m_pVtkAlgorithmOutput = reader;
    }
    else if (extension == ".stl" || extension == ".STL")
    {
        vtkSTLReader * reader = vtkSTLReader::New();
        reader->SetFileName(fileName.c_str());
        reader->Update();

        setPolyData(reader->GetOutputPort(0));

        setData(QVariant(Type::StlModel), Qt::UserRole + UserRole::Type);
        m_pVtkAlgorithmOutput = reader;
    }
    else if (extension == ".vtk")
    {
        vtkPolyDataReader * reader = vtkPolyDataReader::New();
        reader->SetFileName(fileName.c_str());
        reader->Update();
        setPolyData(reader->GetOutputPort(0));
        setData(QVariant(Type::VtkModel), Qt::UserRole + UserRole::Type);
        m_pVtkAlgorithmOutput = reader;
    }
    else if (extension == ".g")
    {
        vtkBYUReader * reader = vtkBYUReader::New();
        reader->SetGeometryFileName(fileName.c_str());
        reader->Update();
        setPolyData(reader->GetOutputPort(0));
        setData(QVariant(Type::GModel), Qt::UserRole + UserRole::Type);
        m_pVtkAlgorithmOutput = reader;
    }
    else 
    {
        vtkSphereSource * source = vtkSphereSource::New();
        source->Update();
        setPolyData(source->GetOutputPort(0));
        setData(QVariant(Type::RegularPolyhedron), Qt::UserRole + UserRole::Type);
        m_pVtkAlgorithmOutput = source;
    }
    mapper()->SetInputConnection(0, polyData());
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
