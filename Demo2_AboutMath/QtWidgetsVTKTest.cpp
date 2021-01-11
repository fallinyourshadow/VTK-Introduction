#include "QtWidgetsVTKTest.h"

#include <vtkNew.h>
#include <vtkMath.h>
#include <vtkLine.h>
#include <vtkPoints.h>
#include <vtkAutoInit.h>
#include <vtkMatrix4x4.h>
#include <vtkPerspectiveTransform.h>
#include <vtkTransform.h>
#include <vtkMinimalStandardRandomSequence.h>
//ȡ�����
#include <time.h>

//����
#include <vtkFloatingPointExceptions.h>



// Avoid the "potential divide by 0" warning from the Microsoft
// compiler, since this example intentionally divides by 0


VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle)

//ƽ��
#include <vtkPlane.h>
#ifdef _MSC_VER
#pragma warning(disable : 4723)
#endif
QtWidgetsVTKTest::QtWidgetsVTKTest(QWidget* parent) : QMainWindow(parent)
{
	//��������֮��ľ�
	{
		std::cout << "-------------------------��������֮��ľ���-----------------------" << std::endl;
		double p0[3] = { 0.0, 0.0, 0.0 };
		double p1[3] = { 1.0, 1.0, 1.0 };

		// Find the squared distance between the points.
		double squaredDistance = vtkMath::Distance2BetweenPoints(p0, p1);//�����ƽ��

		// Take the square root to get the Euclidean distance between the points.
		double distance = std::sqrt(squaredDistance);//������

		// Output the results.
		std::cout << "��������ƽ�� = " << squaredDistance << std::endl;
		std::cout << "������� = " << distance << std::endl;
		std::cout << "------------------------------------------------------------------" << std::endl;

		
	}
	
	{
		//����㵽�ߵĴ�ֱ����
		std::cout << "-------------------------����㵽�ߵľ���-----------------------" << std::endl;
		double lineP0[3] = { 1.0, 0.0, 0.0 };
		double lineP1[3] = { 1.0,1.0, 0.0 };

		double p0[3] = { 0.0, 0, 0 };
		double p1[3] = { 0.0, 3.0, 0 };

		/*
		vtkNew<vtkLine> line;
		line->GetPoints()->SetPoint(0, lineP0);
		line->GetPoints()->SetPoint(0, lineP1);
		*/
		{
			double dist0 = vtkLine::DistanceToLine(p0, lineP0, lineP1);//��lineP0��lineP1���ɵ����޳�ֱ��
			std::cout << "����㵽ֱ�ߵľ���Dist0: " << std::sqrt(dist0) << std::endl;

			double dist1 = vtkLine::DistanceToLine(p1, lineP0, lineP1);
			std::cout << "����㵽ֱ�ߵľ���Dist1: " << std::sqrt(dist1) << std::endl;
		}

		{
			double t;
			double closest[3];
			double dist0 = vtkLine::DistanceToLine(p0, lineP0, lineP1 ,   t, closest);
			std::cout << "Dist0: " << std::sqrt(dist0) << " closest point: " << closest[0] << " "
				<< closest[1] << " " << closest[2] << " t = " << t << std::endl;

			double dist1 = vtkLine::DistanceToLine(p1, lineP0 , lineP1, t, closest);
			std::cout << "Dist1: " << std::sqrt(dist1) << " closest point: " << closest[0] << " "
				<< closest[1] << " " << closest[2] << "  t = " << t <<std::endl;
			std::cout << "���t��[0,1]��ͶӰλ�����߶���,��t��(-��, 0)��(1, +��)��ͶӰλ�����߶��ӳ�����" << std::endl;
			
		}
		std::cout << "------------------------------------------------------------------" << std::endl;
	}

	{
		std::cout << "----vtkFloatingPointExceptions::Enable���0�������ᵼ���쳣�˳�---" << std::endl;
		vtkFloatingPointExceptions::Disable();//vtkFloatingPointExceptions::Enable���0�������ᵼ���쳣�˳�
		double x = 0.0;
		double y = 1.0 / x; // floating-point exception
		std::cout << "x: " << x << " x/0: " << y << std::endl;
		std::cout << "------------------------------------------------------------------" << std::endl;
	}

	{
		std::cout << "------------------��̬�ֲ�(��˹�ֲ�)����3����0Ϊ��׼����׼ƫ��Ϊ2�������--------------------" << std::endl;
		// The number of random numbers we wish to produce
		unsigned int numRand = 3;

		// without this line, the random numbers will be the same every iteration
		vtkMath::RandomSeed(time(NULL));

		// Generate numRand random numbers from a Gaussian distribution with mean 0.0
		// and standard deviation 2.0
		std::vector<double> randNums;
		for (unsigned int i = 0; i < numRand; i++)
		{
			double a = vtkMath::Gaussian(0.0, 2.0);
			randNums.push_back(a);
			std::cout << a << std::endl;
		}
		//std::sort(randNums.begin(), randNums.end());
		//for (size_t i = 0; i < randNums.size(); i++)
		//{
		//	std::cout << randNums.at(i) << std::endl;
		//}
		
		std::cout << "------------------------------------------------------------------" << std::endl;
	}

	{

		std::cout << "-------------------------------͸���任---------------------------" << std::endl;
		//The perspective transform automatically appends the "homogeneous 1" to the point before it is multiplied by the matrix.
		//It then divides the first 3 coordinates of the result by the 4th coordinate of the result.For comparison, 
		//the standard projection vtkTransform) is also performed with the same 
		//matrixand the same point.Note that the results are much different.
		vtkNew<vtkMatrix4x4> m;
		
		
		double mxtrix[4][4] = 
		{ 
		   //0  1  2  3
		  	{1, 2, 3, 4},// 0
			{2, 2, 3, 4},// 1
			{3, 2, 3, 4},// 2
			{4, 2, 3, 4} // 3
		};
		m->SetElement(0, 0, mxtrix[0][0]);
		m->SetElement(0, 1, mxtrix[0][1]);
		m->SetElement(0, 2, mxtrix[0][2]);
		m->SetElement(0, 3, mxtrix[0][3]);
		m->SetElement(1, 0, mxtrix[1][0]);
		m->SetElement(1, 1, mxtrix[1][1]);
		m->SetElement(1, 2, mxtrix[1][2]);
		m->SetElement(1, 3, mxtrix[1][3]);
		m->SetElement(2, 0, mxtrix[2][0]);
		m->SetElement(2, 1, mxtrix[2][1]);
		m->SetElement(2, 2, mxtrix[2][2]);
		m->SetElement(2, 3, mxtrix[2][3]);
		m->SetElement(3, 0, mxtrix[3][0]);
		m->SetElement(3, 1, mxtrix[3][1]);
		m->SetElement(3, 2, mxtrix[3][2]);
		m->SetElement(3, 3, mxtrix[3][3]);

		vtkNew<vtkPerspectiveTransform> perspectiveTransform;//͸��
		perspectiveTransform->SetMatrix(m);//���þ���

		vtkNew<vtkTransform> transform;
		transform->SetMatrix(m);

		double p[3];
		p[0] = 1.0;
		p[1] = 2.0;
		p[2] = 3.0;

		double normalProjection[3];
		transform->TransformPoint(p, normalProjection);

		std::cout << "Standard projection: " << normalProjection[0] << " "
			<< normalProjection[1] << " " << normalProjection[2] << std::endl;

		double perspectiveProjection[3];
		perspectiveTransform->TransformPoint(p, perspectiveProjection);
		std::cout << "Perspective projection: " << perspectiveProjection[0] << " "
			<< perspectiveProjection[1] << " " << perspectiveProjection[2]
			<< std::endl;
		std::cout << "------------------------------------------------------------------" << std::endl;
	}

	{
		std::cout << "--------------------����ƽ���ϵ�ͶӰ-----------------------------" << std::endl;
		vtkNew<vtkPlane> plane;
		plane->SetOrigin(0.0, 0.0, 0.0);//ԭ��
		plane->SetNormal(0.0, 0.0, 1.0);//

		double p[3] = { 23.1, 54.6, 9.2 };
		double origin[3] = { 0.0, 0.0, 0.0 };
		double normal[3] = { 0.0, 0.0, 1.0 };
		double projected[3];

		plane->ProjectPoint(p, origin, normal, projected);

		std::cout << "Projected: " << projected[0] << " " << projected[1] << " "
			<< projected[2] << std::endl;

		std::cout << "------------------------------------------------------------------" << std::endl;
	}
	{
		std::cout << "--------------------------�������--------------------------------" << std::endl;
		vtkNew<vtkMinimalStandardRandomSequence> sequence;

		// initialize the sequence
		sequence->SetSeed(time(NULL));

		// Get 3 random numbers.
		double x = sequence->GetValue();
		sequence->Next();
		double y = sequence->GetValue();
		sequence->Next();
		double z = sequence->GetValue();

		// You can also use seq->GetRangeValue(-1.0,1.0);
		// to set a range on the random values.

		// Output the resulting random numbersl
		std::cout << "x: " << x << " y: " << y << " z: " << z << std::endl;
		std::cout << "------------------------------------------------------------------" << std::endl;
	}

	{
		std::cout << "--------------------------����ͳһ�����--------------------------------" << std::endl;
		// Set the number of random numbers we wish to produce to 3.
		unsigned int numRand = 3;

		// Without this line, the random numbers will be the same every iteration.
		vtkMath::RandomSeed(time(NULL));

		// Generate numRand random numbers from a uniform distribution between 0.0
		// and 2.0
		for (unsigned int i = 0; i < numRand; i++)
		{
			double a = vtkMath::Random(0.0, 2.0);
			std::cout << a << std::endl;
		}
		std::cout << "------------------------------------------------------------------" << std::endl;
	}
	ui.setupUi(this);
}
