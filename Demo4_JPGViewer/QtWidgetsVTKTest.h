#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsVTKTest.h"

class vtkImageViewer2;
class vtkRenderer;

class QtWidgetsVTKTest : public QMainWindow
{
    Q_OBJECT
public:
    QtWidgetsVTKTest(QWidget *parent = Q_NULLPTR);
private slots:
    //响应打开图像文件的槽函数
    void onOpenSlot();
private:
    Ui::QtWidgetsVTKTestClass ui;
    vtkSmartPointer< vtkImageViewer2 > m_pImageViewer;
    vtkSmartPointer< vtkRenderer > m_pRenderder;
};
