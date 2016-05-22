// vim: set noexpandtab tabstop=2:

#pragma once

#include <seqan_api/SeqString.hpp>
#include <seqan_api/SeqSuffixArray.hpp>
#include <iostream>

struct AlnResult
{
	unsigned long SA_index_high;
	unsigned long SA_index_low;
	long num_hits;
	int seq_length;

	void display(const SeqSuffixArray& seq_SA) const
	{
		printf("Seq len: %d, SA index low: %lu, high: %li\n, num of hit: %ld\n", seq_length, SA_index_low, SA_index_high, num_hits);
		std::cout << "Hit in pos: ";
		for(unsigned long i = SA_index_low; i < SA_index_high; ++i)
		{
			std::cout << seq_SA.SAIndex2SeqPos(i) << " ";
		}
		printf("\n");
		std::cout << std::endl << "Seq: " << seq_SA.getSeq_bySAIndex(SA_index_low, seq_length) << std::endl;
	}
};


