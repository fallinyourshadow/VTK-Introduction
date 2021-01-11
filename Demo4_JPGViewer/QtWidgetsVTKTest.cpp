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
#include <QDir>
#include <QFileDialog>
#include <vtkImageViewer2.h>
#include <vtkSmartPointer.h>
#include <vtkImageViewer2.h>
#include <vtkJPEGReader.h>
#include <vtkImageActor.h>
#include <qdebug.h>

VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle)

QtWidgetsVTKTest::QtWidgetsVTKTest(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
    m_pImageViewer = vtkSmartPointer< vtkImageViewer2 >::New();
    m_pRenderder = vtkSmartPointer< vtkRenderer >::New();

    // 设置m_QVTKWidget的渲染器
    ui.widget->GetRenderWindow()->AddRenderer(m_pRenderder);

    connect(ui.action_JPG, &QAction::triggered,
        this, &QtWidgetsVTKTest::onOpenSlot);
}

void QtWidgetsVTKTest::onOpenSlot()
{
    QString filter;
    filter = "JPEG image file (*.jpg *.jpeg)";

    QDir dir;
    QString fileName = QFileDialog::getOpenFileName(this,
        QString::fromLocal8Bit("打开图像"), dir.absolutePath(), filter);
    if (fileName.isEmpty() == true) return;

    // 支持带中文路径的读取
    QByteArray ba = fileName.toLocal8Bit();
    const char* fileName_str = ba.data();
    qDebug() << fileName_str;
    // printf("%s", fileName_str);
    // 用vtkJPEGReader读取JPG图像
    vtkSmartPointer<vtkJPEGReader> reader = vtkSmartPointer<vtkJPEGReader>::New();
    reader->SetFileName(fileName_str);
    reader->Update();
    // 将reader的输出作为m_pImageViewer的输入，并设置m_pImageViewer与渲染器m_pRenderer的关联
    m_pImageViewer->SetInputData(reader->GetOutput());
    m_pImageViewer->UpdateDisplayExtent();
    m_pImageViewer->SetRenderWindow(ui.widget->GetRenderWindow());
    m_pImageViewer->SetRenderer(m_pRenderder);
    //m_pImageViewer->SetupInteractor(ui.widget->GetRenderWindow()->GetInteractor());
    m_pImageViewer->SetSliceOrientationToXY();//默认就是这个方向的
    m_pImageViewer->GetImageActor()->InterpolateOff();
    m_pRenderder->ResetCamera();
    m_pRenderder->DrawOn();
    m_pRenderder->SetBackground(1.0, 1.0, 1.0);
    ui.widget->GetRenderWindow()->Render(); 
}
