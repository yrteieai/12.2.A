#include "pch.h"
#include "CppUnitTest.h"
#include <fstream>
#include "../12.2.A/12.2.A.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest122A
{
	TEST_CLASS(UnitTest122A)
	{
	public:
		TEST_METHOD(TestCalculatePercentage)
		{
			const char* testFile = "test_percentage.dat";

			{
				ofstream fout(testFile, ios::binary);
				Assert::IsTrue(fout.is_open(), L"Не вдалося створити тестовий файл.");

				Student s1 = { "Ostapyshyn", 1, KN, 4, 4, 5 };
				Student s2 = { "Peruta", 2, INF, 3, 4, 4 };
				Student s3 = { "Sidr", 3, FI, 5, 5, 3 };
				Student s4 = { "Stas", 4, ME, 2, 2, 5 };

				fout.write(reinterpret_cast<char*>(&s1), sizeof(Student));
				fout.write(reinterpret_cast<char*>(&s2), sizeof(Student));
				fout.write(reinterpret_cast<char*>(&s3), sizeof(Student));
				fout.write(reinterpret_cast<char*>(&s4), sizeof(Student));
				fout.close();
			}

			{
				double percent = calculate_percentage(testFile);

				Assert::AreEqual(50.0, percent, L"Відсоток студентів із високими оцінками неправильний.");
			}

			remove(testFile);
		}
	};
}
