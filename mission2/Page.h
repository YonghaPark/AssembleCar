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
		printf("� ���� Ÿ���� �����ұ��?\n");
		printf("1. Sedan\n");
		printf("2. SUV\n");
		printf("3. Truck\n");
	}
	bool isError(int answer) override {
		if (!(answer >= 1 && answer <= 3))
		{
			printf("ERROR :: ���� Ÿ���� 1 ~ 3 ������ ���� ����\n");
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
		printf("� ������ ž���ұ��?\n");
		printf("0. �ڷΰ���\n");
		printf("1. GM\n");
		printf("2. TOYOTA\n");
		printf("3. WIA\n");
		printf("4. ���峭 ����\n");
	}
	bool isError(int answer) override {
		if (!(answer >= 0 && answer <= 4))
		{
			printf("ERROR :: ������ 1 ~ 4 ������ ���� ����\n");
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
		printf("� ������ġ�� �����ұ��?\n");
		printf("0. �ڷΰ���\n");
		printf("1. MANDO\n");
		printf("2. CONTINENTAL\n");
		printf("3. BOSCH\n");
	}
	bool isError(int answer) override {
		if (!(answer >= 0 && answer <= 3))
		{
			printf("ERROR :: ������ġ�� 1 ~ 3 ������ ���� ����\n");
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
		printf("� ������ġ�� �����ұ��?\n");
		printf("0. �ڷΰ���\n");
		printf("1. BOSCH\n");
		printf("2. MOBIS\n");
	}
	bool isError(int answer) override {
		if (!(answer >= 0 && answer <= 2))
		{
			printf("ERROR :: ������ġ�� 1 ~ 2 ������ ���� ����\n");
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
		printf("���� ������ �ϼ��Ǿ����ϴ�.\n");
		printf("� ������ �ұ��?\n");
		printf("0. ó�� ȭ������ ���ư���\n");
		printf("1. RUN\n");
		printf("2. Test\n");
	}
	bool isError(int answer) override {
		if (!(answer >= 0 && answer <= 2))
		{
			printf("ERROR :: Run �Ǵ� Test �� �ϳ��� ���� �ʿ�\n");
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