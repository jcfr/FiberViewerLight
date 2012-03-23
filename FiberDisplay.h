#ifndef FIBERDISPLAY_H
#define FIBERDISPLAY_H

#include <QWidget>
#include <QGridLayout>
#include "QVTKWidget.h"
#include <QMouseEvent>

#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>
#include <vtkRenderWindow.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkPolyDataReader.h>
#include <vtkRendererCollection.h>
#include <vtkProperty.h>
#include <vtkPolyLine.h>
#include <vtkLookupTable.h>
#include <vtkPointData.h>
#include <vtkPolyDataWriter.h>
#include <vtkInteractorStyleSwitch.h>
#include <vtkImplicitPlaneWidget.h>

#include <itkImage.h>
#include <itkContinuousIndex.h>
#include <itkVectorLinearInterpolateImageFunction.h>
#include <itkDanielssonDistanceMapImageFilter.h>
#include <vnl/vnl_math.h>

#include <time.h>
#include <algorithm>

typedef itk::Image<unsigned short, 3> IntImageType;
typedef itk::Image<double, 3> RealImageType;
typedef itk::Vector<double, 3> InterpolatePixelType;
typedef itk::Image<InterpolatePixelType, 3> InterpolateImageType;
typedef itk::VectorLinearInterpolateImageFunction<InterpolateImageType, double> InterpolateType;
typedef InterpolateType::ContinuousIndexType ContinuousIndexType;

class FiberDisplay: public QWidget
{
	Q_OBJECT
	
	public:
		enum AlphasType{Next,Previous};
		
		FiberDisplay(QWidget* parent);
		void InitRenderer();
		void InitAlphas();
		void InitDTVector();
		
		vtkSmartPointer<vtkPolyData> GetOriginalPolyData();
		vtkSmartPointer<vtkRenderer> GetRenderer();
		vtkSmartPointer<vtkActor> GetActor();
		std::vector<int> GetLastAlpha(AlphasType Type);
		int GetAlphasSize(AlphasType Type);
		void GetFiberColor(double coef, double color[]);
		void GetSpacing(double[]);
		RealImageType::Pointer GetDTVector(int Id);
		void GetBounds(double[]);
		
		void SetOriginalPolyData(vtkSmartPointer<vtkPolyData> PolyData);
		void SetLookupTable(vtkSmartPointer<vtkLookupTable> RedMap);
		void SetLastAlpha(std::vector<int> Alpha, AlphasType Type);
		void SetSpacing(double Spacing[]);
		
		void ClearAlphas(AlphasType Type);
		void PushBackAlpha(std::vector<int> Alpha, AlphasType Type);
		void PopBackAlpha(AlphasType Type);
		int GetNbModifiedFibers();
		std::vector<int> GenerateRandomIds();
		void StartRenderer(vtkSmartPointer<vtkPolyData> PolyData);
		void Render();
		void UpdateCells();
		IntImageType::Pointer Voxelize(int Id);
		void InitBounds();
		vtkSmartPointer<vtkImplicitPlaneWidget> GetPlan();
		void InitPlan();
		bool IsUnchanged();
		void SetNbFibersDisplayed(int value);
		void FillDisplayedId(std::vector<int> RandomIds);
		void UpdateDT();
		
	signals:
		void NbFibersChanged(int);
		void Progress(int);
	
	private:
		vtkSmartPointer<QVTKInteractor> iren;
		vtkSmartPointer<vtkImplicitPlaneWidget> m_Plane;
		QVTKWidget* m_VTKW_RenderWin;
		vtkSmartPointer<vtkPolyData> m_OriginalPolyData;
		vtkSmartPointer<vtkPolyData> m_DisplayedPolyData;
		std::vector<std::vector<int> > m_PreviousAlphas;
		std::vector<std::vector<int> > m_NextAlphas;
		int m_NbFibersDisplayed;
		double m_Spacing[3];
		double m_Bounds[6];
		std::vector<int> m_DisplayedId;
		std::vector<RealImageType::Pointer> m_DTVector;
		
};

#endif
