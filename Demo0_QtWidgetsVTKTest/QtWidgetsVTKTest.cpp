#include "QtWidgetsVTKTest.h"

#include "vtkSmartPointer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderer.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkCylinderSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"

#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle)

QtWidgetsVTKTest::QtWidgetsVTKTest(QWidget* parent) : QMainWindow(parent)
{




	vtkSmartPointer<vtkCylinderSource> cylinder = vtkSmartPointer<vtkCylinderSource>::New();//Source对象
	cylinder->SetHeight(5.0);//高
	cylinder->SetRadius(5.0);//半径
	cylinder->SetResolution(1000);//一千条棱

	vtkSmartPointer<vtkPolyDataMapper> cylinderMapper = vtkSmartPointer<vtkPolyDataMapper>::New();//mapper对象
	cylinderMapper->SetInputConnection(cylinder->GetOutputPort());

	vtkSmartPointer<vtkActor> cylinderActor = vtkSmartPointer<vtkActor>::New();//actor对象
	cylinderActor->SetMapper(cylinderMapper);

	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();//renderer对象
	renderer->AddActor(cylinderActor);
	renderer->SetBackground(0.1, 0.2, 0.4);

	ui.setupUi(this);
	ui.widget->GetRenderWindow()->AddRenderer(renderer);//将renderer放到vtk widget中显示
}
