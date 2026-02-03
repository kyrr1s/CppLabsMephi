#include <gtest/gtest.h>
#include "archspiral.h"

////////////////////////conctructor///////////////////////////////

TEST(constructor, zero_value) {
	ASSERT_ANY_THROW(ArchimedeanSpiral a(0));
}

TEST(constructor, notzero_value) {
	ASSERT_NO_THROW(ArchimedeanSpiral a(1));
}

TEST(constructor, equal) {
	ArchimedeanSpiral a(1);
	ASSERT_DOUBLE_EQ(1, a.getRadianStep());
}

//////////////////////setRadianStep//////////////////////////////

TEST(setRadianStep, zero_value) {
	ArchimedeanSpiral a(1);
	ASSERT_ANY_THROW(a.setRadianStep(0));
}

TEST(setRadianStep, notzero_value) {
	ArchimedeanSpiral a(1);
	ASSERT_NO_THROW(a.setRadianStep(2));
}

TEST(setRadianStep, equal) {
	ArchimedeanSpiral a(1);
	a.setRadianStep(2);
	ASSERT_DOUBLE_EQ(2, a.getRadianStep());
}

///////////////////////distanceToCentre////////////////////////

TEST(distanceToCentre, negative_angle) {
	ArchimedeanSpiral a(1);
	ASSERT_ANY_THROW(a.distanceToCentre(-2));
}

TEST(distanceToCentre, normal_angle) {
 	ArchimedeanSpiral a(1);
 	ASSERT_NO_THROW(a.distanceToCentre(3.14));
}

TEST(distanceToCentre, equal) {
	ArchimedeanSpiral a(1);
	ASSERT_NEAR(0.5, a.distanceToCentre(3.14), 0.01);
}

//////////////////////areaOfSector////////////////////////////

TEST(areaOfSector, first_rad_negative) {
	ArchimedeanSpiral a(1);
	ASSERT_ANY_THROW(a.areaOfSector(-1, 1));
}

TEST(areaOfSector, second_rad_negative) {
	ArchimedeanSpiral a(1);
	ASSERT_ANY_THROW(a.areaOfSector(1, -1));
}

TEST(areaOfSector,normal_radiuses) {
	ArchimedeanSpiral a(1);
	ASSERT_NO_THROW(a.areaOfSector(1,2));
}

TEST(areaOfSector, wrong_angle) {
	ArchimedeanSpiral a(1);
	ASSERT_ANY_THROW(a.areaOfSector(5, 7));
}

TEST(areaOfSector, normal_angle) {
	ArchimedeanSpiral a(1);
	ASSERT_NO_THROW(a.areaOfSector(5, 6));
}

TEST(areaOfSector, equal) {
	ArchimedeanSpiral a(1);
	ASSERT_NEAR(a.areaOfSector(5,6), 95.3, 0.1);
}

///////////////////areaOfSectorIntegral/////////////////////

TEST(areaOfSectorIntegral, first_rad_negative) {
	ArchimedeanSpiral a(1);
	ASSERT_ANY_THROW(a.areaOfSectorIntegral(-1, 1));
}

TEST(areaOfSectorIntegral, second_rad_negative) {
	ArchimedeanSpiral a(1);
	ASSERT_ANY_THROW(a.areaOfSectorIntegral(1, -1));
}

TEST(areaOfSectorIntegral, normal_radiuses) {
	ArchimedeanSpiral a(1);
	ASSERT_NO_THROW(a.areaOfSectorIntegral(1,2));
}

TEST(areaOfSectorIntegral, wrong_angle) {
	ArchimedeanSpiral a(1);
	ASSERT_ANY_THROW(a.areaOfSectorIntegral(5, 7));
}

TEST(areaOfSectorIntegral, normal_angle) {
	ArchimedeanSpiral a(1);
	ASSERT_NO_THROW(a.areaOfSectorIntegral(5, 6));
}

TEST(areaOfSectorIntegral, equal) {
	ArchimedeanSpiral a(1);
	ASSERT_NEAR(a.areaOfSectorIntegral(5,6), a.areaOfSector(5,6), 0.01); 
}

//////////////////areaFigure/////////////////////////////////

TEST(areaFigure, negative_numTurn) {
	ArchimedeanSpiral a(1);
	ASSERT_ANY_THROW(a.areaFigure(-1));
}

TEST(areaFigure, normal_numTurn) {
	ArchimedeanSpiral a(1);
	ASSERT_NO_THROW(a.areaFigure(1));
}

TEST(areaFigure, equal) {
	ArchimedeanSpiral a(1);
	ASSERT_NEAR(a.areaFigure(5), 63.9, 0.1);
}

//////////////////areaFigureIntegral///////////////////////////////

TEST(areaFigureIntegral, negative_numTurn){
	ArchimedeanSpiral a(1);
	ASSERT_ANY_THROW(a.areaFigureIntegral(-1));	
}

TEST(areaFigureIntegral, normal_numTurn){
	ArchimedeanSpiral a(1);
	ASSERT_NO_THROW(a.areaFigureIntegral(1));		
}

TEST(areaFigureIntegral, equal){
	ArchimedeanSpiral a(1);
	ASSERT_NEAR(a.areaFigureIntegral(5), a.areaFigure(5), 0.01); 		
}

///////////////////areaCircle////////////////////////////////

TEST(areaCircle, negative_numTurn) {
	ArchimedeanSpiral a(1);
	ASSERT_ANY_THROW(a.areaCircle(-1));
}

TEST(areaCircle, normal_numTurn) {
	ArchimedeanSpiral a(1);
	ASSERT_NO_THROW(a.areaCircle(1));
}

TEST(areaCircle, equal) {
	ArchimedeanSpiral a(1);
	ASSERT_NEAR(a.areaCircle(5), 78.5, 0.1);
}

/////////////////areaCircleIntegral//////////////////////

TEST(areaCircleIntegral, negative_numTurn){
	ArchimedeanSpiral a(1);
	ASSERT_ANY_THROW(a.areaCircleIntegral(-1));	
}

TEST(areaCircleIntegral, normal_numTurn){
	ArchimedeanSpiral a(1);
	ASSERT_NO_THROW(a.areaCircleIntegral(1));		
}

TEST(areaCircleIntegral, equal){
	ArchimedeanSpiral a(1);
	ASSERT_NEAR(a.areaCircleIntegral(5), a.areaCircle(5), 0.01); 		
}

//////////////////lenghtArc////////////////////////////////

TEST(lenghtArc, negative_angle) {
	ArchimedeanSpiral a(1);
	ASSERT_ANY_THROW(a.lenghtArc(-1));
}

TEST(lenghtArc, normal_angle) {
	ArchimedeanSpiral a(1);
	ASSERT_NO_THROW(a.lenghtArc(1));
}

TEST(lenghtArc, equal) {
	ArchimedeanSpiral a(1);
	ASSERT_NEAR(a.lenghtArc(3.14), 1, 0.1);
}

/////////////////radiusOfCurvature/////////////////////////////

TEST(radiusOfCurvature, negative_angle) {
	ArchimedeanSpiral a(1);
	ASSERT_ANY_THROW(a.radiusOfCurvature(-1));
}

TEST(radiusOfCurvature, normal_angle) {
	ArchimedeanSpiral a(1);
	ASSERT_NO_THROW(a.radiusOfCurvature(1));
}

TEST(radiusOfCurvature, equal) {
	ArchimedeanSpiral a(1);
	ASSERT_NEAR(a.radiusOfCurvature(3.14), 0.08, 0.1);
}

////////////////////////////////////////////////////////

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

/* TEST (группа тестов, вид теста)
Утверждения, порождающие в случае их ложности критические отказы начинаются с ASSERT_
Утверждения, порождающие в случае их ложности некритические отказы начинаются с EXPECT_

Простейшие логические

ASSERT_TRUE(condition);
ASSERT_FALSE(condition);


Сравнение

ASSERT_EQ(expected, actual); — =
ASSERT_NE(val1, val2); — !=
ASSERT_LT(val1, val2); — <
ASSERT_LE(val1, val2); — <=
ASSERT_GT(val1, val2); — >
ASSERT_GE(val1, val2); — >=

Сравнение строк

ASSERT_STREQ(expected_str, actual_str);
ASSERT_STRNE(str1, str2);
ASSERT_STRCASEEQ(expected_str, actual_str); — регистронезависимо
ASSERT_STRCASENE(str1, str2); — регистронезависимо

Проверка на исключения

ASSERT_THROW(statement, exception_type);
ASSERT_ANY_THROW(statement);
ASSERT_NO_THROW(statement);


Сравнение чисел с плавающей точкой

ASSERT_FLOAT_EQ(expected, actual); — неточное сравнение float
ASSERT_DOUBLE_EQ(expected, actual); — неточное сравнение double
ASSERT_NEAR(val1, val2, abs_error); — разница между val1 и val2 не превышает погрешность abs_error


Вызов отказа или успеха

SUCCEED();
FAIL();
ADD_FAILURE();
ADD_FAILURE_AT(«file_path», line_number);
 */