#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsVTKTest.h"

class QtWidgetsVTKTest : public QMainWindow
{
    Q_OBJECT
public:
    QtWidgetsVTKTest(QWidget *parent = Q_NULLPTR);

private:
    Ui::QtWidgetsVTKTestClass ui;
};
