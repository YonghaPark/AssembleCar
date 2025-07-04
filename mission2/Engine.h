#pragma once
#include "stdio.h"

enum Engine
{
	GM = 1,
	TOYOTA,
	WIA
};

class IEngine {
public:
	virtual int type(void) = 0;
	virtual void select(void) = 0;
	virtual void run(void) = 0;
};

class GM_Engine : public IEngine {
public:
	int type(void) override {
		return GM;
	}
	void select(void) override {
		printf("GM 엔진을 선택하셨습니다.\n");
	}
	void run(void) override {
		printf("Engine : GM\n");
	}
};

class TOYOTA_Engine : public IEngine {
public:
	int type(void) override {
		return TOYOTA;
	}
	void select(void) override {
		printf("TOYOTA 엔진을 선택하셨습니다.\n");
	}
	void run(void) override {
		printf("Engine : TOYOTA\n");
	}
};

class WIA_Engine : public IEngine {
public:
	int type(void) override {
		return WIA;
	}
	void select(void) override {
		printf("WIA 엔진을 선택하셨습니다.\n");
	}
	void run(void) override {
		printf("Engine : WIA\n");
	}
};

class Broken_Engine : public IEngine {
public:
	void select(void) override {
		printf("WIA 엔진을 선택하셨습니다.\n");
	}
};