#pragma once
#include <stdio.h>
#include "assemble.h"

enum PageType
{
	Car,
	Engine,
	Brake,
	Steering,
	RunTest,
};

class IPage {
public:
	virtual void question(void) = 0;
	virtual bool isError(int answer) = 0;
	virtual int run(int answer) = 0;
};

class CarPage : public IPage {
public:
	void question(void) override {
		printf("        ______________\n");
		printf("       /|            | \n");
		printf("  ____/_|_____________|____\n");
		printf(" |                      O  |\n");
		printf(" '-(@)----------------(@)--'\n");
		printf("===============================\n");
		printf("어떤 차량 타입을 선택할까요?\n");
		printf("1. Sedan\n");
		printf("2. SUV\n");
		printf("3. Truck\n");
	}
	bool isError(int answer) override {
		if (!(answer >= 1 && answer <= 3))
		{
			printf("ERROR :: 차량 타입은 1 ~ 3 범위만 선택 가능\n");
			return true;
		}
		return false;
	}
	int run(int answer) override {
		selectCar(answer);
		delay(800);
		return Engine;
	}
};

class EnginePage : public IPage {
public:
	void question(void) override {
		printf("어떤 엔진을 탑재할까요?\n");
		printf("0. 뒤로가기\n");
		printf("1. GM\n");
		printf("2. TOYOTA\n");
		printf("3. WIA\n");
		printf("4. 고장난 엔진\n");
	}
	bool isError(int answer) override {
		if (!(answer >= 0 && answer <= 4))
		{
			printf("ERROR :: 엔진은 1 ~ 4 범위만 선택 가능\n");
			return true;
		}
		return false;
	}
	int run(int answer) override {
		selectEngine(answer);
		delay(800);
		return Brake;
	}
};

class BrakePage : public IPage {
public:
	void question(void) override {
		printf("어떤 제동장치를 선택할까요?\n");
		printf("0. 뒤로가기\n");
		printf("1. MANDO\n");
		printf("2. CONTINENTAL\n");
		printf("3. BOSCH\n");
	}
	bool isError(int answer) override {
		if (!(answer >= 0 && answer <= 3))
		{
			printf("ERROR :: 제동장치는 1 ~ 3 범위만 선택 가능\n");
			return true;
		}
		return false;
	}
	int run(int answer) override {
		selectBrake(answer);
		delay(800);
		return Steering;
	}
};

class SteeringPage : public IPage {
public:
	void question(void) override {
		printf("어떤 조향장치를 선택할까요?\n");
		printf("0. 뒤로가기\n");
		printf("1. BOSCH\n");
		printf("2. MOBIS\n");
	}
	bool isError(int answer) override {
		if (!(answer >= 0 && answer <= 2))
		{
			printf("ERROR :: 조향장치는 1 ~ 2 범위만 선택 가능\n");
			return true;
		}
		return false;
	}
	int run(int answer) override {
		selectSteering(answer);
		delay(800);
		return RunTest;
	}
};

class RunTestPage : public IPage {
public:
	void question(void) override {
		printf("멋진 차량이 완성되었습니다.\n");
		printf("어떤 동작을 할까요?\n");
		printf("0. 처음 화면으로 돌아가기\n");
		printf("1. RUN\n");
		printf("2. Test\n");
	}
	bool isError(int answer) override {
		if (!(answer >= 0 && answer <= 2))
		{
			printf("ERROR :: Run 또는 Test 중 하나를 선택 필요\n");
			return true;
		}
		return false;
	}
	int run(int answer) override {
		if (answer == RUN) {
			runProducedCar();
			delay(2000);
		}
		else if (answer == TEST) {
			printf("Test...\n");
			delay(1500);
			testProducedCar();
			delay(2000);
		}
		return RunTest;
	}
};