#pragma once

#include <qobject.h>
#include <QStandardItem>
#include "vtkSmartPointer.h"
#include "vtkActor.h"
#include "vtkNamedColors.h"
#include "vtkProperty.h"
#include "vtkPolyDataMapper.h"
#include "PreDefine.h"

class GeometryItem : public QStandardItem
{
public:
    explicit GeometryItem();
	virtual ~GeometryItem();
	vtkSmartPointer<vtkPolyDataMapper> mapper();
	vtkSmartPointer<vtkActor> actor();
	const CommonProperties& commonProperties();
	void setCommonProperties(CommonProperties&);
protected:

private:
	vtkSmartPointer<vtkPolyDataMapper> m_cylinderMapper;//mapper����
	vtkSmartPointer<vtkActor> m_cylinderActor;//actor����
	CommonProperties m_properties;
};

