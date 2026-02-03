#pragma once
#include <iostream>
#include <math.h>
#include <limits>
#include <numbers>

class ArchimedeanSpiral {
	private:
		constexpr static double delta = 0.0001;
		double radian_step;

		double integral(const double& angle, const double& radius) const;
		double integral(const int& num) const;

	public:
		explicit ArchimedeanSpiral(double value):radian_step(value) {
			if (value == 0)
				throw std::invalid_argument("Invalid coefficient");	
		}

		~ArchimedeanSpiral() {
			radian_step = 0;
		}

		ArchimedeanSpiral& setRadianStep(double value);

		double getRadianStep() const;

		double distanceToCentre(const double& angle) const;

		double areaOfSector(const double& radius1, const double& radius2) const;

		double areaOfSectorIntegral(const double& radius1, const double& radius2) const;

		double areaFigure(const int& numTurn) const;

		double areaFigureIntegral(const int& numTurn) const;

		double areaCircle(const int& numCircle) const;

		double areaCircleIntegral(const int& numCircle) const;

		double lenghtArc(const double& angle) const;

		double radiusOfCurvature(const double& angle) const;
};