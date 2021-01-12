#pragma once

#include <QtWidgets/QMainWindow>
#include <QStandardItemModel>
#include "ui_QtWidgetsVTKTest.h"
#include "vtkRenderer.h"

class QtWidgetsVTKTest : public QMainWindow
{
    Q_OBJECT

public:
    QtWidgetsVTKTest(QWidget *parent = Q_NULLPTR);
protected slots:
    void onCreateButtonClicked();
    void onItemClicked(QStandardItem* item);
    void onPropertiesChanged();
    void onModelExported(QString dirPath,int type);
private:
    Ui::QtWidgetsVTKTestClass ui;

    vtkSmartPointer<vtkRenderer> m_renderer;
};
