// vim: set noexpandtab tabstop=2:

#pragma once

#include <iostream>

struct GapAndMM
{
	int num_mismatch;
	int num_gapOpenRef;
	int num_gapOpenQuery;
	int num_gapExtRef;
	int num_gapExtQuery;

	GapAndMM()
		: num_mismatch(0), num_gapOpenRef(0), num_gapOpenQuery(0), num_gapExtRef(0), num_gapExtQuery(0) {}

	GapAndMM(int m, int gor, int goq, int ger, int geq)
		: num_mismatch(m), num_gapOpenRef(gor), num_gapOpenQuery(goq), num_gapExtRef(ger), num_gapExtQuery(geq) {}

	friend GapAndMM operator+(GapAndMM lhs, const GapAndMM& rhs)
	{
		lhs += rhs;
		return lhs;
	}

	GapAndMM& operator+=(const GapAndMM& rhs)
	{
		num_mismatch += rhs.num_mismatch;
		num_gapOpenRef += rhs.num_gapOpenRef;
		num_gapOpenQuery += rhs.num_gapOpenQuery;
		num_gapExtRef += rhs.num_gapExtRef;
		num_gapExtQuery += rhs.num_gapExtQuery;
		return *this;
	}

	int num_gapOpen()
	{
		return num_gapOpenRef + num_gapOpenQuery;
	}

	int num_gapExt()
	{
	 return num_gapExtRef + num_gapExtQuery;	
	}

	int total_diff()
	{
		return num_mismatch + num_gapExtRef + num_gapOpenRef + num_gapExtQuery + num_gapOpenQuery;
	}

	void display()
	{
		std::cout << "Mismatch: " << num_mismatch << std::endl;
		std::cout << " Ref  Open: " << num_gapOpenRef   << ", Ext: " << num_gapExtRef << std::endl;
		std::cout << "Query Open: " << num_gapOpenQuery << ", Ext: " << num_gapExtQuery << std::endl;
	}
};
