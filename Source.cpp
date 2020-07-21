/*
* /File: Source.cpp /
* /Brief: BigInt and BigReal
* /Creator: Leonid Artemev | Leartiz /
* /Date: 2020 /
*/

#include <iostream>
#include <cstdlib>

#include "BigInt.h"
#include "BigReal.h"


int main()
{
	lez::BigInt bi_f(2147483647);
	lez::BigInt bi_s(-2147483547);

	std::cout << bi_f + bi_s << std::endl;
	std::cout << bi_f - bi_s << std::endl;
	std::cout << bi_f * bi_s << std::endl;
	std::cout << bi_f / bi_s << std::endl;
	std::cout << bi_f % bi_s << std::endl;
	std::cout << -bi_f << std::endl;
	//...

	std::cout << std::endl;

	lez::BigReal::start_amount_digits_after_comma() = 25U; // can be edited, default = 25U
	lez::BigReal br_f(2147483647.123456);
	lez::BigReal br_s(-2147483547.123356);

	std::cout << br_f + br_s << std::endl;
	std::cout << br_f - br_s << std::endl;
	std::cout << br_f * br_s << std::endl;
	std::cout << br_f / br_s << std::endl;
	std::cout << br_f % br_s << std::endl;
	std::cout << -br_f << std::endl;
	//...
	
	system("PAUSE");
	return 0;
}