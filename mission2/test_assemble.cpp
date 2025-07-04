#ifdef _DEBUG

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "assemble.h"
#include <iostream>
#include "Page.h"

using namespace testing;
using namespace std;

extern unique_ptr<IPage> pages[];
extern unique_ptr<ICar> car[];
extern unique_ptr<IEngine> engine[];
extern unique_ptr<IBrake> brake[];
extern unique_ptr<ISteering> steering[];
extern Assemble assemble;

class TestAssemble : public Test {
public:
	void SetUp(void) override {
		assemble.car = car[SEDAN].get();
		assemble.engine = engine[GM].get();
		assemble.brake = brake[MANDO].get();
		assemble.steering = steering[BOSCH_S].get();
	}
	void TearDown(void) override {

	}
};

TEST(Assemble, printQuestion)
{
	internal::CaptureStdout();

	printQuestion(Car);

	string output = internal::GetCapturedStdout();

	EXPECT_EQ(output, "\033[H\033[2J"
		"        ______________\n"
		"       /|            | \n"
		"  ____/_|_____________|____\n"
		" |                      O  |\n"
		" '-(@)----------------(@)--'\n"
		"===============================\n"
		"� ���� Ÿ���� �����ұ��?\n"
		"1. Sedan\n"
		"2. SUV\n"
		"3. Truck\n"
		"===============================\n");
}

TEST(Assemble, runPage)
{
	internal::CaptureStdout();

	runPage(Car, SEDAN);

	string output = internal::GetCapturedStdout();

	EXPECT_EQ(output, "���� Ÿ������ Sedan�� �����ϼ̽��ϴ�.\n");
}

TEST(Assemble, enterInput1) {
	char buffer[100] = { 0 };

	FILE* fp = nullptr;
	errno_t err = tmpfile_s(&fp);
	ASSERT_EQ(err, 0);
	ASSERT_NE(fp, nullptr);

	fputs("exit\n", fp);
	rewind(fp);

	bool result = enterInput(&buffer, sizeof(buffer), fp);

	EXPECT_FALSE(result);
	EXPECT_STREQ(buffer, "exit");

	fclose(fp);
}

TEST(Assemble, enterInput2) {
	char buffer[100] = { 0 };

	FILE* fp = nullptr;
	errno_t err = tmpfile_s(&fp);
	ASSERT_EQ(err, 0);
	ASSERT_NE(fp, nullptr);

	fputs("1\n", fp);
	rewind(fp);

	bool result = enterInput(&buffer, sizeof(buffer), fp);

	EXPECT_TRUE(result);
	EXPECT_STREQ(buffer, "1");

	fclose(fp);
}

TEST(Assemble, isError_1_Car)
{
	char buffer[100] = { '1', };

	int ret = isError(buffer, Car);

	EXPECT_EQ(1, ret);
}

TEST(Assemble, isError_a_Car)
{
	char buffer[100] = { 'a', };

	int ret = isError(buffer, Car);

	EXPECT_EQ(ERROR, ret);
}

TEST(Assemble, isError_0_Car)
{
	char buffer[100] = { '0', };

	int ret = isError(buffer, Car);

	EXPECT_EQ(ERROR, ret);
}

TEST(Assemble, selectCar)
{
	internal::CaptureStdout();

	selectCar(SEDAN);

	string output = internal::GetCapturedStdout();

	EXPECT_EQ(output, "���� Ÿ������ Sedan�� �����ϼ̽��ϴ�.\n");
}

TEST(Assemble, selectEngine)
{
	internal::CaptureStdout();

	selectEngine(GM);

	string output = internal::GetCapturedStdout();

	EXPECT_EQ(output, "GM ������ �����ϼ̽��ϴ�.\n");
}

TEST(Assemble, selectBrake)
{
	internal::CaptureStdout();

	selectBrake(MANDO);

	string output = internal::GetCapturedStdout();

	EXPECT_EQ(output, "MANDO ������ġ�� �����ϼ̽��ϴ�.\n");
}

TEST(Assemble, selectSteering)
{
	internal::CaptureStdout();

	selectSteering(BOSCH_S);

	string output = internal::GetCapturedStdout();

	EXPECT_EQ(output, "BOSCH ������ġ�� �����ϼ̽��ϴ�.\n");
}

TEST_F(TestAssemble, runProducedCar1)
{
	internal::CaptureStdout();

	assemble.car = car[SEDAN].get();
	assemble.brake = brake[CONTINENTAL].get();

	runProducedCar();

	string output = internal::GetCapturedStdout();

	EXPECT_EQ(output, "�ڵ����� ���۵��� �ʽ��ϴ�\n");
}

TEST_F(TestAssemble, runProducedCar2)
{
	internal::CaptureStdout();

	assemble.car = car[SUV].get();
	assemble.engine = engine[TOYOTA].get();

	runProducedCar();

	string output = internal::GetCapturedStdout();

	EXPECT_EQ(output, "�ڵ����� ���۵��� �ʽ��ϴ�\n");
}

TEST_F(TestAssemble, runProducedCar3)
{
	internal::CaptureStdout();

	assemble.car = car[TRUCK].get();
	assemble.engine = engine[WIA].get();

	runProducedCar();

	string output = internal::GetCapturedStdout();

	EXPECT_EQ(output, "�ڵ����� ���۵��� �ʽ��ϴ�\n");
}

TEST_F(TestAssemble, runProducedCar4)
{
	internal::CaptureStdout();

	assemble.car = car[TRUCK].get();
	assemble.brake = brake[MANDO].get();

	runProducedCar();

	string output = internal::GetCapturedStdout();

	EXPECT_EQ(output, "�ڵ����� ���۵��� �ʽ��ϴ�\n");
}

TEST_F(TestAssemble, runProducedCar5)
{
	internal::CaptureStdout();

	assemble.brake = brake[BOSCH_B].get();
	assemble.steering = steering[MOBIS].get();

	runProducedCar();

	string output = internal::GetCapturedStdout();

	EXPECT_EQ(output, "�ڵ����� ���۵��� �ʽ��ϴ�\n");
}

TEST_F(TestAssemble, runProducedCar6)
{
	internal::CaptureStdout();

	assemble.brake = brake[BOSCH_B].get();
	assemble.steering = steering[BOSCH_S].get();

	runProducedCar();

	string output = internal::GetCapturedStdout();

	EXPECT_EQ(output, "Car Type : Sedan\n"
		"Engine : GM\n"
		"Brake System : Bosch\n"
		"SteeringSystem : Bosch\n"
		"�ڵ����� ���۵˴ϴ�.\n");
}

TEST_F(TestAssemble, runProducedCar7)
{
	internal::CaptureStdout();

	assemble.engine = NULL;

	runProducedCar();

	string output = internal::GetCapturedStdout();

	EXPECT_EQ(output, "������ ���峪�ֽ��ϴ�.\n"
		"�ڵ����� �������� �ʽ��ϴ�.\n");
}

TEST_F(TestAssemble, testProducedCar1)
{
	internal::CaptureStdout();

	assemble.car = car[SEDAN].get();
	assemble.brake = brake[CONTINENTAL].get();

	testProducedCar();

	string output = internal::GetCapturedStdout();

	EXPECT_EQ(output, "�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n"
		"Sedan���� Continental������ġ ��� �Ұ�\n");
}

TEST_F(TestAssemble, testProducedCar2)
{
	internal::CaptureStdout();

	assemble.car = car[SUV].get();
	assemble.engine = engine[TOYOTA].get();

	testProducedCar();

	string output = internal::GetCapturedStdout();

	EXPECT_EQ(output, "�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n"
		"SUV���� TOYOTA���� ��� �Ұ�\n");
}

TEST_F(TestAssemble, testProducedCar3)
{
	internal::CaptureStdout();

	assemble.car = car[TRUCK].get();
	assemble.engine = engine[WIA].get();

	testProducedCar();

	string output = internal::GetCapturedStdout();

	EXPECT_EQ(output, "�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n"
		"Truck���� WIA���� ��� �Ұ�\n");
}

TEST_F(TestAssemble, testProducedCar4)
{
	internal::CaptureStdout();

	assemble.car = car[TRUCK].get();
	assemble.brake = brake[MANDO].get();

	testProducedCar();

	string output = internal::GetCapturedStdout();

	EXPECT_EQ(output, "�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n"
		"Truck���� Mando������ġ ��� �Ұ�\n");
}

TEST_F(TestAssemble, testProducedCar5)
{
	internal::CaptureStdout();

	assemble.brake = brake[BOSCH_B].get();
	assemble.steering = steering[MOBIS].get();

	testProducedCar();

	string output = internal::GetCapturedStdout();

	EXPECT_EQ(output, "�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n"
		"Bosch������ġ���� Bosch������ġ �̿� ��� �Ұ�\n");
}

TEST_F(TestAssemble, testProducedCar6)
{
	internal::CaptureStdout();

	assemble.brake = brake[BOSCH_B].get();
	assemble.steering = steering[BOSCH_S].get();

	testProducedCar();

	string output = internal::GetCapturedStdout();

	EXPECT_EQ(output, "�ڵ��� ��ǰ ���� �׽�Ʈ ��� : PASS\n");
}

TEST_F(TestAssemble, testProducedCar7)
{
	internal::CaptureStdout();

	assemble.engine = NULL;

	testProducedCar();

	string output = internal::GetCapturedStdout();

	EXPECT_EQ(output, "�ڵ��� ��ǰ ���� �׽�Ʈ ��� : PASS\n");
}

#endif