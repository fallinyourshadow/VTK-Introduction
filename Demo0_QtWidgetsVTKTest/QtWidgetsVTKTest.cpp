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




	vtkSmartPointer<vtkCylinderSource> cylinder = vtkSmartPointer<vtkCylinderSource>::New();//Source����
	cylinder->SetHeight(5.0);//��
	cylinder->SetRadius(5.0);//�뾶
	cylinder->SetResolution(1000);//һǧ����

	vtkSmartPointer<vtkPolyDataMapper> cylinderMapper = vtkSmartPointer<vtkPolyDataMapper>::New();//mapper����
	cylinderMapper->SetInputConnection(cylinder->GetOutputPort());

	vtkSmartPointer<vtkActor> cylinderActor = vtkSmartPointer<vtkActor>::New();//actor����
	cylinderActor->SetMapper(cylinderMapper);

	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();//renderer����
	renderer->AddActor(cylinderActor);
	renderer->SetBackground(0.1, 0.2, 0.4);

	ui.setupUi(this);
	ui.widget->GetRenderWindow()->AddRenderer(renderer);//��renderer�ŵ�vtk widget����ʾ
}
