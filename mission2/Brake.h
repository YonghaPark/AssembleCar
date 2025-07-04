#pragma once
#include "stdio.h"

enum brakeSystem
{
	MANDO = 1,
	CONTINENTAL,
	BOSCH_B
};

class IBrake {
public:
	virtual int type(void) = 0;
	virtual void select(void) = 0;
	virtual void run(void) = 0;
};

class MANDO_Brake : public IBrake {
public:
	int type(void) override {
		return MANDO;
	}
	void select(void) override {
		printf("MANDO ������ġ�� �����ϼ̽��ϴ�.\n");
	}
	void run(void) override {
		printf("Brake System : Mando\n");
	}
};

class CONTINENTAL_Brake : public IBrake {
public:
	int type(void) override {
		return CONTINENTAL;
	}
	void select(void) override {
		printf("CONTINENTAL ������ġ�� �����ϼ̽��ϴ�.\n");
	}
	void run(void) override {
		printf("Brake System : Continental\n");
	}
};

class BOSCH_Brake : public IBrake {
public:
	int type(void) override {
		return BOSCH_B;
	}
	void select(void) override {
		printf("BOSCH ������ġ�� �����ϼ̽��ϴ�.\n");
	}
	void run(void) override {
		printf("Brake System : Bosch\n");
	}
};