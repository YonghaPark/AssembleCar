#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include "Car.h"
#include "Engine.h"
#include "Brake.h"
#include "Steering.h"

using namespace std;

void printQuestion(int step);
bool enterInput(char (*pbuf)[100], int size, FILE* input = stdin);
int isError(char buf[100], int step);
int runPage(int page, int answer);

void selectCar(int answer);
void selectEngine(int answer);
void selectBrake(int answer);
void selectSteering(int answer);
int isValidCheck(bool test = false);
void runProducedCar();
void testProducedCar();
void delay(int ms);

enum Answer
{
	ERROR = -1,
	BACK,
	RUN,
	TEST
};

struct Assemble {
	ICar* car;
	IEngine* engine;
	IBrake* brake;
	ISteering* steering;
};