// vim: set noexpandtab tabstop=2:

#pragma once

#include <spliced_aln/Word.hpp>
#include <spliced_aln/WordHit.hpp>
#include <spliced_aln/WordHitsChunk.hpp>
#include <spliced_aln/AlnSpliceOpt.hpp>
#include <util/GapAndMM.hpp>
#include <iostream>
#include <vector>

struct WordHitsGroup
{
	WordHitsGroup(int group_id) : id(group_id) {}

	void display()
	{
		std::cout << "Group ID: " << id << std::endl;
		std::cout << "Including Hit: ";
		for(auto iter = wordhits.begin(); iter != wordhits.end(); ++iter)
		{
			printf("%d, ", (*iter)->word_id);
		}
		printf("\n");
	}

	int id;
	double score;
	std::vector<WordHitPtr> wordhits;
	std::list<WordHitsChunkPtr> wordhitschunks;
	//list<jigsaw_junction_t*> *junctions;

	void group_wordHits_wordChunks(const AlnSpliceOpt& opt, int num_words);
};

typedef std::shared_ptr<WordHitsGroup> WordHitsGroupPtr;

//DEBUG
double calculate_wordhitsChunk_score(const WordHitsGroupPtr& group, const std::vector<WordPtr>& words, long ref_length, int num_words);
//END
