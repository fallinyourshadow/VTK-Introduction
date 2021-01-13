#include "QtWidgetsVTKTest.h"

#include "vtkSmartPointer.h"

#include "vtkActor.h"

#include <vtkAutoInit.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkOBJImporter.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkTexture.h>
#include <vtkOBJReader.h>
#include <vtkImageReader2.h>
#include <vtkImageReader2Factory.h>
#include <vtkImageData.h>
#include <vtkCamera.h>
#include <vtkProjectedTexture.h>
#include <vtkPlanes.h>
#include <vtkFrustumSource.h>
#include <vtkProperty.h>

VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle)

QtWidgetsVTKTest::QtWidgetsVTKTest(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
    /*
    vtkNew<vtkOBJImporter> importer;
    importer->SetFileName("../model/citysd1231.obj");
    importer->SetFileNameMTL("../model/backpack.mtl");
    importer->SetTexturePath("../model/diffuse.jpg");

    vtkNew<vtkNamedColors> colors;
    vtkNew<vtkRenderer> renderer;
    vtkNew<vtkRenderWindow> renWin;
    vtkNew<vtkRenderWindowInteractor> iren;

    renderer->SetBackground2(colors->GetColor3d("Silver").GetData());
    renderer->SetBackground(colors->GetColor3d("Gold").GetData());
    renderer->GradientBackgroundOn();

    renderer->UseHiddenLineRemovalOn();



    importer->SetRenderWindow(renWin);
    importer->Update();

    auto actors = renderer->GetActors();
    actors->InitTraversal();
    std::cout << "There are " << actors->GetNumberOfItems() << " actors"
        << std::endl;
    */
   
    vtkNew<vtkOBJReader> reader;
    reader->SetFileName("../model/backpack.obj");//模型文件
    reader->Update();

    vtkNew<vtkImageReader2Factory> readerFactory;
    vtkSmartPointer<vtkImageReader2> textureFile;
    textureFile.TakeReference(readerFactory->CreateImageReader2(
        "../model/chest.jpg"));
    textureFile->SetFileName(
        "../model/chest.jpg");
    textureFile->Update();

    vtkNew<vtkTexture> texture;
    texture->SetInputData(textureFile->GetOutput());

    vtkNew<vtkNamedColors> colors;
    vtkNew<vtkRenderer> renderer;
    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputConnection(reader->GetOutputPort());
    vtkNew<vtkActor> actor;
    actor->SetMapper(mapper);
    actor->SetTexture(texture);
  
    renderer->AddActor(actor);
    renderer->SetBackground2(colors->GetColor3d("Silver").GetData());
    renderer->SetBackground(colors->GetColor3d("Gold").GetData());
    renderer->GradientBackgroundOn();
    renderer->UseHiddenLineRemovalOn();

    ui.widget->GetRenderWindow()->AddRenderer(renderer);//将renderer放到vtk widget中显示
       /*  */


}
