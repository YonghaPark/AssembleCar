#pragma once
#include <stdio.h>

enum CarType
{
	SEDAN = 1,
	SUV,
	TRUCK
};

class ICar {
public:
	virtual int type(void) = 0;
	virtual void select(void) = 0;
	virtual void run(void) = 0;
};

class Sedan_Car : public ICar {
public:
	int type(void) override {
		return SEDAN;
	}
	void select(void) override {
		printf("차량 타입으로 Sedan을 선택하셨습니다.\n");
	}
	void run(void) override {
		printf("Car Type : Sedan\n");
	}
};

class SUV_Car : public ICar {
public:
	int type(void) override {
		return SUV;
	}
	void select(void) override {
		printf("차량 타입으로 SUV을 선택하셨습니다.\n");
	}
	void run(void) override {
		printf("Car Type : SUV\n");
	}
};

class Truck_Car : public ICar {
public:
	int type(void) override {
		return TRUCK;
	}
	void select(void) override {
		printf("차량 타입으로 Truck을 선택하셨습니다.\n");
	}
	void run(void) override {
		printf("Car Type : Truck\n");
	}
};