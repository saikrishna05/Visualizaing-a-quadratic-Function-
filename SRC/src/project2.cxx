#include <vtkStructuredPointsReader.h>
#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkWidgetEvent.h>
#include <vtkRenderer.h>
#include <vtkPolyData.h>
#include <vtkPlane.h>
#include <vtkCutter.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyDataNormals.h>
#include <vtkContourFilter.h>
#include <vtkSliderWidget.h>
#include <vtkCommand.h>
#include <vtkProperty.h>
#include <vtkCleanPolyData.h>
#include <vtkSliderRepresentation3D.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkQuadric.h>
#include <vtkContourFilter.h>
#include <vtkSampleFunction.h>


int main(int, char *argv[])
{
	// Sample quadric function
	vtkSmartPointer<vtkQuadric> quadric = vtkSmartPointer<vtkQuadric>::New();
	quadric->SetCoefficients(1, 0.5, 0.2, 0.1, 0, 0, 0.2, 0, 0, 0);

	vtkSmartPointer<vtkSampleFunction> sample = vtkSmartPointer<vtkSampleFunction>::New();
	sample->SetSampleDimensions(40, 40, 40);
	sample->SetImplicitFunction(quadric);

	// Generate implicit surface
	vtkSmartPointer<vtkContourFilter> contour = vtkSmartPointer<vtkContourFilter>::New();
	contour->SetInputConnection(sample->GetOutputPort());
	contour->GenerateValues(4, 0.0, 1.0);

	// Map contour
	vtkSmartPointer<vtkPolyDataMapper> contourMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	contourMapper->SetInputConnection(contour->GetOutputPort());
	contourMapper->SetScalarRange(0.0, 1.2);

	vtkSmartPointer<vtkActor> contourActor = vtkSmartPointer<vtkActor>::New();
	contourActor->SetMapper(contourMapper);

	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);
	renderer->AddActor(contourActor);
	renderWindow->Render();
	renderWindowInteractor->Start();

	return EXIT_SUCCESS;
}