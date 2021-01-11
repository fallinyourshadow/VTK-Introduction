#include "QtWidgetsVTKTest.h"

#include "vtkSmartPointer.h"
#include "vtkRenderWindow.h"

#include "vtkRenderWindowInteractor.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkCylinderSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkRendererCollection.h"
#include "vtkCamera.h"

#include <vtkAutoInit.h>
#include "PreDefine.h"

#include "PrismItem.h"
#include "PyramidItem.h"
#include "SphereItem.h"
#include "STLModelItem.h"
#include "C3DsModelItem.h"

#include "vtkNamedColors.h"
#include <vtkProperty.h>
#include "PropertiesWidget.h"
#include "ListView.h"

#include <QDebug>
#include <QFileDialog>
#include <qmessagebox.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle)

QtWidgetsVTKTest::QtWidgetsVTKTest(QWidget* parent) : QMainWindow(parent)
{
	m_renderer = vtkSmartPointer<vtkRenderer>::New();//renderer对象
	m_renderer->SetBackground( 0.1, 0.2, 0.4 );
	m_renderer->GradientBackgroundOn();
	ui.setupUi( this );
	QStandardItemModel* model = new QStandardItemModel(ui.listView);
	ui.listView->setModel(model);
	model->setHorizontalHeaderItem(0, new QStandardItem(StrActerObj));
	ui.listView->setMaximumWidth(100);
	ui.widget->GetRenderWindow()->AddRenderer(m_renderer);//将renderer放到vtk widget中
	
	QAction * actionLoadStlFile = new QAction(ToLocal8Bit("加载.stl文件"));
	ui.menu->addAction(actionLoadStlFile);
	connect(actionLoadStlFile, &QAction::triggered, [=]() {
		static quint32 counter = 1;
		QFileDialog file(0, QString::fromLocal8Bit("选择stl文件"), "C:\\Users\\Administrator\\Desktop\\", "*.stl");
		file.setFileMode(QFileDialog::ExistingFile);
		if (file.exec() != 1)
			return;
		QStringList fileList = file.selectedFiles();
		if (fileList.size() != 1)
			return;
		STLModelItem* item = new STLModelItem;
		item->loadFile(fileList.at(0));
		m_renderer->AddActor(item->actor());
		ui.widget->GetRenderWindow()->Render();
		QString str = QString("%1%2").arg(QString::fromLocal8Bit("stl模型")).arg(counter++);
		item->setText(str);
		model->appendRow(item);
	});
	QAction* actionLoad3DSFile = new QAction(ToLocal8Bit("加载.3ds文件"));
	ui.menu->addAction(actionLoad3DSFile);
	connect(actionLoad3DSFile, &QAction::triggered, [=]() {
		static quint32 counter = 1;
		QFileDialog file(0, QString::fromLocal8Bit("选择3ds文件"), "C:\\Users\\Administrator\\Desktop\\", "*.3ds");
		file.setFileMode(QFileDialog::ExistingFile);
		if (file.exec() != 1)
			return;
		QStringList fileList = file.selectedFiles();
		qDebug() << fileList.size();
		if (fileList.size() != 1)
			return;
		C3DsModelItem* item = new C3DsModelItem;
		item->source()->SetRenderWindow(ui.widget->GetRenderWindow());
		
		item->loadFile(fileList.at(0));
		item->source()->Update();
		//m_renderer->AddActor(item->actor());

		ui.widget->GetRenderWindow()->Render();
		QString str = QString("%1%2").arg(QString::fromLocal8Bit("3ds模型")).arg(counter++);
		item->setText(str);
		model->appendRow(item);

		//vtkNew<vtkCamera> camera;
		//camera->SetPosition(0, -1, 0);
		//camera->SetFocalPoint(0, 0, 0);
		//camera->SetViewUp(0, 0, 1);
		//camera->Azimuth(150);
		//camera->Elevation(30);

		//m_renderer->SetActiveCamera(camera);
		//m_renderer->ResetCamera();
		//m_renderer->ResetCameraClippingRange();
		});
	//绑定创建按钮的槽函数
	connect( ui.pushButton, &QPushButton::clicked, this, &QtWidgetsVTKTest::onCreateButtonClicked );
	connect( ui.pushButton_2, &QPushButton::clicked, this, &QtWidgetsVTKTest::onCreateButtonClicked );
	connect( ui.pushButton_3, &QPushButton::clicked, this, &QtWidgetsVTKTest::onCreateButtonClicked );

	//
	connect(ui.listView, &ListView::itemClicked,this, &QtWidgetsVTKTest::onItemClicked);

	
	//ui.widget->GetRenderWindow()->AddRenderer(renderer2);
	//ui.widget->GetRenderWindow()->GetRenderers()->RemoveItem(1);

	QWidget* center = new QWidget( this );
	center->setLayout(ui.horizontalLayout );
	center->setWindowTitle( "Render Window" );
	setCentralWidget( center );



	PropertiesWidget* propertiesWidget = new PropertiesWidget(this);
	ui.dockWidget->setWidget(propertiesWidget);
	propertiesWidget->hide();
	//属性改变
	connect( propertiesWidget, &PropertiesWidget::propertiesChanged, this, &QtWidgetsVTKTest::onPropertiesChanged );
	//删除对象
	connect( propertiesWidget, &PropertiesWidget::removeItem, [=]( GeometryItem* item ) {
		if ( item == nullptr )
			return;
		m_renderer->RemoveActor(item->actor());
		propertiesWidget->hide();
		model->removeRow(item->row());
		ui.widget->GetRenderWindow()->Render();
	});

	vtkSmartPointer<vtkRenderWindowInteractor> iren =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	iren->SetRenderWindow(ui.widget->GetRenderWindow());
	vtkSmartPointer<vtkInteractorStyleTrackballCamera> style =
		vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
	iren->SetInteractorStyle(style);
}

void QtWidgetsVTKTest::onCreateButtonClicked()
{
	static quint32 counter = 1;
	QPushButton* pOrigin = qobject_cast<QPushButton*>(sender());
	QStandardItemModel* model = qobject_cast<QStandardItemModel*>(ui.listView->model());
	GeometryItem* pItem = nullptr;
	PropertiesWidget* propertiesWidget = qobject_cast<PropertiesWidget*>(ui.dockWidget->widget());
	QString str;

	if ( pOrigin->text() == StrPrism )
	{
		pItem = new PrismItem();
		str = QString( "%1%2" ).arg( StrPrism ).arg( counter++ );
	}
	else if ( pOrigin->text() == StrPyramid )
	{
		pItem = new PyramidItem();
		str = QString( "%1%2" ).arg( StrPyramid ).arg( counter++ );
	}
	else if ( pOrigin->text() == StrRegularPolyhedron )
	{
		pItem = new SphereItem();
		str = QString( "%1%2" ).arg( StrRegularPolyhedron ).arg(counter++);
	}

	if ( pItem )
	{
		pItem->setText( str );
		model->appendRow( pItem );
		m_renderer->AddActor( pItem->actor() );
		ui.widget->GetRenderWindow()->Render();
	}
}

void QtWidgetsVTKTest::onItemClicked(QStandardItem* item)
{
	PropertiesWidget* propertiesWidget = qobject_cast<PropertiesWidget*>(ui.dockWidget->widget());
	
	if (item == nullptr)
	{
		ui.dockWidget->widget()->hide();
		propertiesWidget->setSelectedItem(nullptr);
	}
	else
	{
		propertiesWidget->show();
		propertiesWidget->setSelectedItem((GeometryItem*)item);
	}
}

void QtWidgetsVTKTest::onPropertiesChanged()
{
	ui.widget->GetRenderWindow()->Render();
}
