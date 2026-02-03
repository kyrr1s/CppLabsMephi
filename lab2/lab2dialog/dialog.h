#include "archspiral.h"

namespace dialog {
	int change(ArchimedeanSpiral&);
	int distanceToCentre(ArchimedeanSpiral&);
	int areaOfSector(ArchimedeanSpiral&);
	int areaFigure(ArchimedeanSpiral&);
	int areaCircle(ArchimedeanSpiral&);
	int lenghtArc(ArchimedeanSpiral&);
	int radiusOfCurvature(ArchimedeanSpiral&);

	int dialog(const char* msgs[], int Nmsgs);
};

namespace io {
	void getType(int& value);
	void getType(double& value);
	void setRadiuses(double& radius1, double& radius2);
};