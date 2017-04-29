#include "stdafx.h"
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

bool isPrime(long input, std::vector<long> listToCheck)
{
	//since all numbers are either prime, or composite of primes smaller than itself,
	//we only need to check if the number is divisible by those primes we have already found
	//also note we need only check to the square root of the number in question

	double sqrtOfInput;
	sqrtOfInput = std::sqrt(input);

	for (long j = 0; j < listToCheck.size(); j++)
	{
		if (listToCheck.at(j) > sqrtOfInput)
		{
			return true;
		}
		else if (input % listToCheck.at(j) == 0)
		{
			return false;
		}
	}
	return true;
}

std::vector<long> generatePrimes(long limit)
{
	std::vector<long> result;
	if (limit < 2)
	{
		throw std::out_of_range("No primes exist below the number two");
	}
	else
	{
		result.push_back(2);
		for (long j = 3; j <= limit; j++)
		{
			if (isPrime(j, result) == true)
			{
				result.push_back(j);
			}
		}
	}
	return result;
}

void printPrimes(std::vector<long> input)
{
	for (long j = 0; j < input.size(); j++)
	{
		std::cout << input.at(j) << '\n';
	}
}

long getLongFromUser(std::string strPrompt, long minNum, long maxNum) {

	long result = 0;

	while (true || (result >= minNum && result <= maxNum))
	{

		std::string strinput = "";
		//use getline to avoid errors with inputs
		std::cout << strPrompt;
		std::getline(std::cin, strinput);

		// this line defines a stringstream called 'mystream' and gives it the value of strinput
		std::stringstream myStream(strinput);
		//this line looks for result (i.e. a signed long) and stores it. If it can't, it returns false
		if (myStream >> result) {
			if (result < minNum || result > maxNum)
			{
				std::cout << "Please enter a number between " << minNum << " and " << maxNum << ".\n";
			}
			else
			{
				break;
			}
		}
		else
		{
			std::cout << "That's not a number. Please enter a number.\n";
		}
	}
	return result;
}

int main()
{
	long limit;
	limit = getLongFromUser("Find all primes up to which number? ", 0, 10000);
	try
	{
		std::vector<long> listOfPrimes = generatePrimes(limit);
		printPrimes(listOfPrimes);
	}
	catch (...)
	{
		std::cout << "No primes exist below " << limit << '\n';
	}
	system("PAUSE"); //know this is not ideal, but does for now
}
