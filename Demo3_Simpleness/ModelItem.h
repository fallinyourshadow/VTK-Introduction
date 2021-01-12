#pragma once
#include "GeometryItem.h"
#include <vtkSTLReader.h>
class ModelItem :
    public GeometryItem
{
public:
    ModelItem();
    virtual ~ModelItem();
    int loadFile(const std::string& filePath);
    QString name() const;
    void setName(const QString &name);
private:
    QString m_name;
 
};