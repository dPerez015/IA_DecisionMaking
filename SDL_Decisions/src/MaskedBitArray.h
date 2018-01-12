#pragma once

struct MaskedBitArray{
	int bits;
	int mask;

public:
	void add(int position, bool value) {
		mask = mask | position;
		bits = bits | (position*value);
	}
};