#pragma once
#include <iostream>
#include <string>

#ifndef RW_main_H
#define RW_main_H

class RW_Classification
{
public:
	void winning(RW_Classification arr[], int num);
	void result(RW_Classification arr[], int num);
	//void betmaking(RW_Classification arr[], int color, int num_);
	void assign_color(RW_Classification arr[], int i);
	void num_init(RW_Classification arr[]);
private:
	int number;
	std::string color;
};

class Result
{
public:
	int result_number;
	std::string result_color;
	std::string result_hl;
	std::string result_eo;
};

#endif