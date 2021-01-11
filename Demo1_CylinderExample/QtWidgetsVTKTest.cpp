#include "QtWidgetsVTKTest.h"

#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkCylinderSource.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkPlane.h>
#include <vtkAutoInit.h>
#include <vtkFloatingPointExceptions.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle)

QtWidgetsVTKTest::QtWidgetsVTKTest(QWidget* parent) : QMainWindow(parent)
{
	vtkNew<vtkNamedColors> colors;
	// Set the background color.
	//std::array<unsigned char, 4> bkg= {26, 51, 102, 255} ;
	unsigned char bkg[4] = { 26, 51, 102, 255 };
	colors->SetColor( "BkgColor", bkg);

	// This creates a polygonal cylinder model with eight circumferential facets
	// (i.e, in practice an octagonal prism).
	vtkNew<vtkCylinderSource> cylinder;
	cylinder->SetResolution(8);

	// The mapper is responsible for pushing the geometry into the graphics
	// library. It may also do color mapping, if scalars or other attributes are
	// defined.
	vtkNew<vtkPolyDataMapper> cylinderMapper;
	cylinderMapper->SetInputConnection(cylinder->GetOutputPort());

	// The actor is a grouping mechanism: besides the geometry (mapper), it
	// also has a property, transformation matrix, and/or texture map.
	// Here we set its color and rotate it around the X and Y axes.
	vtkNew<vtkActor> cylinderActor;
	cylinderActor->SetMapper(cylinderMapper);
	cylinderActor->GetProperty()->SetColor(
		colors->GetColor4d("Orange").GetData());
	cylinderActor->RotateX(60);
	cylinderActor->RotateY(60);
	cylinderActor->RotateZ(90);
	
	vtkNew<vtkActor> cylinderActor2;
	cylinderActor2->SetMapper(cylinderMapper);
	cylinderActor2->GetProperty()->SetColor(
		colors->GetColor4d("Red").GetData());
	cylinderActor2->RotateX(45);
	cylinderActor2->RotateY(45);
	cylinderActor2->RotateZ(0);
	// The renderer generates the image
	// which is then displayed on the render window.
	// It can be thought of as a scene to which the actor is added

	vtkNew<vtkRenderer> renderer;
	//double pos[3];
	//memcpy(pos, renderer->GetCenter(), sizeof(double) * 3);
	//cylinderActor->SetPosition(pos);
	//renderer->AddActor(cylinderActor);

	renderer->AddActor(cylinderActor);
	renderer->AddActor(cylinderActor2);
	//pos[0] += 500;
	//pos[1] += 500;
	//pos[2] += 500;
	//cylinderActor->SetPosition(pos);
	renderer->SetBackground(colors->GetColor4d("Green").GetData());
	//Zoom in a little by accessing the camera and invoking its "Zoom" method.
	renderer->ResetCamera();
	renderer->GetActiveCamera()->Zoom(1.0);

	ui.setupUi(this);
	ui.widget->GetRenderWindow()->AddRenderer(renderer);//将renderer放到vtk widget中显示
}
