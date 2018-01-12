#pragma once
#include "MaskedBitArray.h"
#include <string>

struct Action{
	MaskedBitArray preConditions;
	MaskedBitArray reaction;
	float cost;
	std::string definition;
};