#include "stdafx.h"
//#include "/Users/Covton/Documents/Visual Studio 2015/std_lib_facilities.h"
#include <vector>
#include <iostream>
#include <string>

std::vector<int> convertStringToIntVector(std::string input)
{
	std::vector<int> result;
	for (int j = 0; j < input.size(); j++)
	{
		result.push_back(input.at(j) - '0');
	}
	return result;
}

std::string addThousands(int input)
{
	return std::to_string(input) + " thousand";
}

std::string addHundreds(int input)
{
	return std::to_string(input) + " hundred";
} 

std::string addTens(int input)
{
	return std::to_string(input) + " tens";
}

std::string returnWord(int input)
{
	switch (input)
	{
	case 0:
		return "zero";
	case 1:
		return "one";
	case 2:
		return "two";
	case 3:
		return "three";
	case 4:
		return "four";
	case 5:
		return "five";
	case 6:
		return "six";
	case 7:
		return "seven";
	case 8:
		return "eight";
	case 9:
		return "nine";
	}
}

int combineInts(int firstInt, int secondInt)
{
	int timesToMultiply;
	timesToMultiply = 1;
	while (timesToMultiply < secondInt)
	{
		timesToMultiply *= 10;
	}
	return firstInt * timesToMultiply + secondInt;
}

std::string numInWords(std::vector<int> input)
{
	std::string result;

	if (input.size() == 5)
	{
		result = addThousands(combineInts(input.at(0),input.at(1))) + ", " + addHundreds(input.at(2)) + ", " + addTens(input.at(3)) + " and " + returnWord(input.at(4));
	}
	else if (input.size() == 4)
	{
		result = addThousands(input.at(0)) + ", " + addHundreds(input.at(1)) + ", " + addTens(input.at(2)) + " and " + returnWord(input.at(3));
	}
	else if (input.size() == 3)
	{
		result = addHundreds(input.at(0)) + ", " + addTens(input.at(1)) + " and " + returnWord(input.at(2));
	}
	else if (input.size() == 2)
	{
		result = addTens(input.at(0)) + " and " + returnWord(input.at(1));
	}
	else if (input.size() == 1)
	{
		result = returnWord(input.at(0));
	}
	return result;
}


//int main()
//{
//	std::cout << "Please input a number: ";
//	std::string input;
//	std::cin >> input;
//	std::string output;
//	output = numInWords(convertStringToIntVector(input));
//	std::cout << output << '\n';
//
//	system("PAUSE");
//
//}