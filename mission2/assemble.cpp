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

	// ���� ���๮�� ����
	char* context = nullptr;
	strtok_s(buf, "\r", &context);
	strtok_s(buf, "\n", &context);

	if (!strcmp(buf, "exit"))
	{
		printf("���̹���\n");
		return false;
	}

	return true;
}

int isError(char buf[100], int page) {
	// ���ڷ� �� ������� Ȯ��
	char* checkNumber;
	int answer = strtol(buf, &checkNumber, 10); // ���ڿ��� 10������ ��ȯ

	// �Է¹��� ���ڰ� ���ڰ� �ƴ϶��
	if (*checkNumber != '\0')
	{
		printf("ERROR :: ���ڸ� �Է� ����\n");
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
			printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
			printf("Sedan���� Continental������ġ ��� �Ұ�\n");
		}
		return false;
	}
	if (assemble.car->type() == SUV && assemble.engine->type() == TOYOTA)
	{
		if (test) {
			printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
			printf("SUV���� TOYOTA���� ��� �Ұ�\n");
		}
		return false;
	}
	if (assemble.car->type() == TRUCK && assemble.engine->type() == WIA)
	{
		if (test) {
			printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
			printf("Truck���� WIA���� ��� �Ұ�\n");
		}
		return false;
	}
	if (assemble.car->type() == TRUCK && assemble.brake->type() == MANDO)
	{
		if (test) {
			printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
			printf("Truck���� Mando������ġ ��� �Ұ�\n");
		}
		return false;
	}
	if (assemble.brake->type() == BOSCH_B && assemble.steering->type() != BOSCH_S)
	{
		if (test) {
			printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
			printf("Bosch������ġ���� Bosch������ġ �̿� ��� �Ұ�\n");
		}
		return false;
	}
	return true;
}

void runProducedCar()
{
	if (isValidCheck() == false)
	{
		printf("�ڵ����� ���۵��� �ʽ��ϴ�\n");
		return;
	}

	if (!assemble.engine)
	{
		printf("������ ���峪�ֽ��ϴ�.\n");
		printf("�ڵ����� �������� �ʽ��ϴ�.\n");
		return;
	}

	assemble.car->run();
	assemble.engine->run();
	assemble.brake->run();
	assemble.steering->run();

	printf("�ڵ����� ���۵˴ϴ�.\n");
}

void testProducedCar()
{
	if (!isValidCheck(true))
	{
		return;
	}

	printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : PASS\n");
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

		// ó������ ���ư���
		if (answer == BACK && page == RunTest)
		{
			page = Car;
			continue;
		}

		// �������� ���ư���
		if (answer == BACK)
		{
			page -= 1;
			continue;
		}

		page = runPage(page, answer);
	}
}

#endif