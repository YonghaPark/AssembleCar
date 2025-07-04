#pragma once
#include "stdio.h"

enum SteeringSystem
{
	BOSCH_S = 1,
	MOBIS
};

class ISteering {
public:
	virtual int type(void) = 0;
	virtual void select(void) = 0;
	virtual void run(void) = 0;
};

class BOSCH_Steering : public ISteering {
public:
	int type(void) override {
		return BOSCH_S;
	}
	void select(void) override {
		printf("BOSCH 조향장치를 선택하셨습니다.\n");
	}
	void run(void) override {
		printf("SteeringSystem : Bosch\n");
	}
};

class MOBIS_Steering : public ISteering {
public:
	int type(void) override {
		return MOBIS;
	}
	void select(void) override {
		printf("MOBIS 조향장치를 선택하셨습니다.\n");
	}
	void run(void) override {
		printf("SteeringSystem : Mobis\n");
	}
};