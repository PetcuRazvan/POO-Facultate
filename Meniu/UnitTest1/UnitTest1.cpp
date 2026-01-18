#include "pch.h"
#include "CppUnitTest.h"
#include "../Meniu/FileName.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestMancare
{
	TEST_CLASS(TestMancare)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Mancare m1(60, "Mici", 0.5, 2, new string[2]{ "porc", "vita" }, Tip::NORMAL_LA_CAP);
			double pret = m1.getPret();
			Assert::AreEqual(60.0, pret);
		}
	};
}
