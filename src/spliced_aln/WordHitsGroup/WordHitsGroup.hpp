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
	//std::list<WordHitsChunkBridgePtr> wordhitschunkbridge;

	void group_wordHits_wordChunks(const AlnSpliceOpt& opt, int num_words);
	void pair_wordChunks(const SeqString& query, const SeqSuffixArray& ref_SAIndex, const AlnSpliceOpt& opt);
	void locate_junc_two_chunks(const WordHitsChunkPtr& head_chunk, const WordHitsChunkPtr& tail_chunk, const SeqString& query, const SeqSuffixArray& ref_SAIndex, const AlnSpliceOpt& opt);
	int locate_junc_two_chunks_denovo(WordHitsChunkPtr& head_chunk, WordHitsChunkPtr& tail_chunk, int min_headChunk_refEnd, int max_headChunk_refEnd, int gap_length, int num_backSearch, const SeqString& query, const SeqSuffixArray& ref_SAIndex, const AlnSpliceOpt& opt);
};

typedef std::shared_ptr<WordHitsGroup> WordHitsGroupPtr;

//DEBUG
double calculate_wordhitsChunk_score(const WordHitsGroupPtr& group, const std::vector<WordPtr>& words, long ref_length, int num_words);
bool can_pair(const WordHitsChunkPtr head_chunk, const WordHitsChunkPtr tail_chunk, const AlnSpliceOpt& opt);
void cal_wordChunk_adjust_diff(const WordHitsChunkPtr head_chunk, const WordHitsChunkPtr tail_chunk, std::vector<int>& head_chunk_adjust_diff, std::vector<int>& tail_chunk_adjust_diff, const SeqString query, const SeqSuffixArray& ref_SAIndex, int num_backSearch);
//END
