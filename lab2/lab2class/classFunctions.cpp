#include "archspiral.h"

ArchimedeanSpiral& ArchimedeanSpiral::setRadianStep(double value) {
	if (value == 0)
		throw std::invalid_argument("Invalid coefficient");
	radian_step = value;
	return *this;
} 

double ArchimedeanSpiral::getRadianStep() const {
	return radian_step;
}

double ArchimedeanSpiral::distanceToCentre(const double& angle) const {
	if (angle < 0)
		throw std::invalid_argument("Negative angle");
	return angle*radian_step/(2*M_PI);
}

double ArchimedeanSpiral::areaOfSector(const double& radius1, const double& radius2) const {
	if (radius1 < 0 || radius2 < 0)
		throw std::invalid_argument("Negative polar radius");
	double difference = abs(radius2-radius1)/radian_step;
	if (difference > 1)
		throw std::invalid_argument("The angle between two polar radiuses is greater thar 2*PI");
	else return (radius1*radius1 + radius1*radius2 + radius2*radius2)*difference*2*M_PI/6;
}

double ArchimedeanSpiral::integral(const double& angle, const double& radius) const {
	if (angle < 0)
		throw std::invalid_argument("Negative angle");
	if (radius < 0) 
		throw std::invalid_argument("Negative radius");
	double result = 0;
	for (double start = 0; start < angle; start += delta)
		result += delta*pow(radius, 2);
	return result/2;	
}

double ArchimedeanSpiral::integral(const int& num) const {
	if (num < 0) 
		throw std::invalid_argument("Negative radius");
	double result = 0;
	for (double start = delta; start < 2*M_PI; start += delta)
		result += delta*pow(radian_step*num, 2);
	return result/2;	
}

double ArchimedeanSpiral::areaOfSectorIntegral(const double& radius1, const double& radius2) const {
	if (radius1 < 0 || radius2 < 0)
		throw std::invalid_argument("Negative polar radius");
	double difference = abs(radius2-radius1)/radian_step;
	if (difference > 1)
		throw std::invalid_argument("The angle between two polar radiuses is greater thar 2*PI");
	double angle = difference*2*M_PI;
	return (this->integral(angle, radius1) + this->integral(angle, radius2) + this->integral(angle, sqrt(radius1*radius2)))/3;
}

double ArchimedeanSpiral::areaFigure(const int& numTurn) const {
	if (numTurn <= 0)
		throw std::invalid_argument("Invalid coefficient");
	return radian_step*radian_step*(pow(numTurn, 3) - pow(numTurn - 1, 3))*M_PI/3;
}

double ArchimedeanSpiral::areaFigureIntegral(const int& numTurn) const {
	if (numTurn <= 0)
		throw std::invalid_argument("Invalid coefficient");
	return (pow(numTurn, 3) - pow(numTurn - 1, 3))*(this->integral(numTurn))/(3*pow(numTurn, 2));			
}

double ArchimedeanSpiral::areaCircle(const int& numCircle) const {
	if (numCircle <= 0)
		throw std::invalid_argument("Invalid coefficient");
	return pow(radian_step*numCircle,2)*M_PI; 
}

double ArchimedeanSpiral::areaCircleIntegral(const int& numCircle) const {
	if (numCircle <= 0)
		throw std::invalid_argument("Invalid coefficient");
	return this->integral(numCircle);
}

double ArchimedeanSpiral::lenghtArc(const double& angle) const {
	if (angle < 0)
		throw std::invalid_argument("Negative angle");
	return radian_step*((angle*sqrt(1+pow(angle,2))) + log(angle+sqrt(1+pow(angle,2))))/(2*2*M_PI);
}

double ArchimedeanSpiral::radiusOfCurvature(const double& angle) const {
	if (angle < 0)
		throw std::invalid_argument("Negative angle");
	return radian_step*pow((tan(angle)*tan(angle) + 1),3/2)/((1/(cos(angle)*cos(angle))+1)*2*M_PI);
}