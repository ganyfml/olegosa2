// vim: set noexpandtab tabstop=2:

#pragma once

#include <spliced_aln/Word.hpp>
#include <spliced_aln/WordHit.hpp>
#include <spliced_aln/WordHitsChunk.hpp>
#include <spliced_aln/WordHitsChunkBridge.hpp>
#include <spliced_aln/AlnSpliceOpt.hpp>
#include <iostream>
#include <list>

struct WordHitsGroup
{
	WordHitsGroup(int group_id) : id(group_id) {}

	void display()
	{
		std::cout << "Group ID: " << id << ", score: " << score << std::endl;
		std::cout << "Including Hit: ";
		for(auto iter = wordhits.begin(); iter != wordhits.end(); ++iter)
		{
			printf("%d, ", (*iter)->word_id);
		}
		printf("\n");
	}

	int id;
	double score;
	std::list<WordHitPtr> wordhits;
	std::list<WordHitsChunkPtr> wordhitschunks;
	std::list<WordHitsChunkBridgePtr> wordhitschunkbridges;
	void group_wordHits_wordChunks(const AlnSpliceOpt& opt, int num_words);
	int locate_bridge_within_two_chunks_denovo(WordHitsChunkPtr& head_chunk, WordHitsChunkPtr& tail_chunk, int min_headChunk_refEnd, int max_headChunk_refEnd, int gap_length, int num_backSearch, const SeqString& query, const SeqSuffixArray& ref_SAIndex, const AlnSpliceOpt& opt);
};

typedef std::shared_ptr<WordHitsGroup> WordHitsGroupPtr;

bool compare_wordHitsGroupByScore(const WordHitsGroupPtr group1, const WordHitsGroupPtr group2);
