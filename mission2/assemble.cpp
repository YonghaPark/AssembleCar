#include "assemble.h"
#include "Page.h"

#define CLEAR_SCREEN "\033[H\033[2J"

unique_ptr<IPage> pages[] = {
	make_unique<CarPage>(),
	make_unique<EnginePage>(),
	make_unique<BrakePage>(),
	make_unique<SteeringPage>(),
	make_unique<RunTestPage>()
};

unique_ptr<ICar> car[] = {
	NULL,
	make_unique<Sedan_Car>(),
	make_unique<SUV_Car>(),
	make_unique<Truck_Car>(),
};

unique_ptr<IEngine> engine[] = {
	NULL,
	make_unique<GM_Engine>(),
	make_unique<TOYOTA_Engine>(),
	make_unique<WIA_Engine>(),
};

unique_ptr<IBrake> brake[] = {
	NULL,
	make_unique<MANDO_Brake>(),
	make_unique<CONTINENTAL_Brake>(),
	make_unique<BOSCH_Brake>(),
};

unique_ptr<ISteering> steering[] = {
	NULL,
	make_unique<BOSCH_Steering>(),
	make_unique<MOBIS_Steering>(),
};

Assemble assemble;

void delay(int ms)
{
	volatile int sum = 0;
	for (int i = 0; i < 1000; i++)
	{
		for (int j = 0; j < 1000; j++)
		{
			for (int t = 0; t < ms; t++)
			{
				sum++;
			}
		}
	}
}

void printQuestion(int page) {
	printf(CLEAR_SCREEN);
	pages[page]->question();
	printf("===============================\n");
}

bool enterInput(char (*pbuf)[100], int size, FILE* input) {
	char* buf = *pbuf;

	printf("INPUT > ");
	fgets(buf, size, input);

	// 엔터 개행문자 제거
	char* context = nullptr;
	strtok_s(buf, "\r", &context);
	strtok_s(buf, "\n", &context);

	if (!strcmp(buf, "exit"))
	{
		printf("바이바이\n");
		return false;
	}

	return true;
}

int isError(char buf[100], int page) {
	// 숫자로 된 대답인지 확인
	char* checkNumber;
	int answer = strtol(buf, &checkNumber, 10); // 문자열을 10진수로 변환

	// 입력받은 문자가 숫자가 아니라면
	if (*checkNumber != '\0')
	{
		printf("ERROR :: 숫자만 입력 가능\n");
		delay(800);
		return ERROR;
	}

	if (pages[page]->isError(answer))
	{
		delay(800);
		return ERROR;
	}

	return answer;
}

int runPage(int page, int answer) {
	return pages[page]->run(answer);
}

void selectCar(int answer)
{
	assemble.car = car[answer].get();
	assemble.car->select();
}

void selectEngine(int answer)
{
	assemble.engine = engine[answer].get();
	if (assemble.engine)
		assemble.engine->select();
}

void selectBrake(int answer)
{
	assemble.brake = brake[answer].get();
	assemble.brake->select();
}

void selectSteering(int answer)
{
	assemble.steering = steering[answer].get();
	assemble.steering->select();
}

int isValidCheck(bool test)
{
	if (assemble.car->type() == SEDAN && assemble.brake->type() == CONTINENTAL)
	{
		if (test) {
			printf("자동차 부품 조합 테스트 결과 : FAIL\n");
			printf("Sedan에는 Continental제동장치 사용 불가\n");
		}
		return false;
	}
	if (assemble.car->type() == SUV && assemble.engine->type() == TOYOTA)
	{
		if (test) {
			printf("자동차 부품 조합 테스트 결과 : FAIL\n");
			printf("SUV에는 TOYOTA엔진 사용 불가\n");
		}
		return false;
	}
	if (assemble.car->type() == TRUCK && assemble.engine->type() == WIA)
	{
		if (test) {
			printf("자동차 부품 조합 테스트 결과 : FAIL\n");
			printf("Truck에는 WIA엔진 사용 불가\n");
		}
		return false;
	}
	if (assemble.car->type() == TRUCK && assemble.brake->type() == MANDO)
	{
		if (test) {
			printf("자동차 부품 조합 테스트 결과 : FAIL\n");
			printf("Truck에는 Mando제동장치 사용 불가\n");
		}
		return false;
	}
	if (assemble.brake->type() == BOSCH_B && assemble.steering->type() != BOSCH_S)
	{
		if (test) {
			printf("자동차 부품 조합 테스트 결과 : FAIL\n");
			printf("Bosch제동장치에는 Bosch조향장치 이외 사용 불가\n");
		}
		return false;
	}
	return true;
}

void runProducedCar()
{
	if (isValidCheck() == false)
	{
		printf("자동차가 동작되지 않습니다\n");
		return;
	}

	if (!assemble.engine)
	{
		printf("엔진이 고장나있습니다.\n");
		printf("자동차가 움직이지 않습니다.\n");
		return;
	}

	assemble.car->run();
	assemble.engine->run();
	assemble.brake->run();
	assemble.steering->run();

	printf("자동차가 동작됩니다.\n");
}

void testProducedCar()
{
	if (!isValidCheck(true))
	{
		return;
	}

	printf("자동차 부품 조합 테스트 결과 : PASS\n");
}

#ifdef _DEBUG

#include "gmock/gmock.h"

int main()
{
	testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}

#else

int main()
{
	char buf[100];
	int page = Car;

	while (1)
	{
		printQuestion(page);

		if (!enterInput(&buf, sizeof(buf)))
		{
			break;
		}

		int answer = isError(buf, page);

		if (answer == ERROR)
		{
			continue;
		}

		// 처음으로 돌아가기
		if (answer == BACK && page == RunTest)
		{
			page = Car;
			continue;
		}

		// 이전으로 돌아가기
		if (answer == BACK)
		{
			page -= 1;
			continue;
		}

		page = runPage(page, answer);
	}
}

#endif