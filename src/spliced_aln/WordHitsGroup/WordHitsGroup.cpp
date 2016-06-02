// vim: set noexpandtab tabstop=2:

#include <cmath>
#include <spliced_aln/WordHitsGroup.hpp>

using namespace std;

void WordHitsGroup::group_wordHits_wordChunks(const AlnSpliceOpt& opt, int num_words)
{
	vector<int> words_occ(num_words);
	for (auto iter = wordhits.begin(); iter != wordhits.end(); ++iter)
	{
		++words_occ[(*iter)->word_id];
	}

	int prev_strand = -1;
	long prev_hit_diag = -1;
	int local_wordChunk_diff = (opt.wordChunk_max_diff > 2) ? 2 : opt.wordChunk_max_diff;

	int curr_wordChunk_id = 0;
	WordHitsChunkPtr curr_chunk;
	for (auto iter = wordhits.begin(); iter != wordhits.end(); ++iter)
	{
		if(words_occ[(*iter)->word_id] > 1)
			continue;

		long curr_hit_diag = (*iter)->ref_pos - (*iter)->query_pos;
		if ((*iter)->strand != prev_strand || curr_hit_diag - prev_hit_diag > local_wordChunk_diff)
		{
			curr_chunk = make_shared<WordHitsChunk>(curr_wordChunk_id++);
			wordhitschunks.push_back(curr_chunk);
		}

		curr_chunk->wordHitList.push_back(*iter);
		prev_hit_diag = curr_hit_diag;
		prev_strand = (*iter)->strand;
	}
}

double calculate_wordhitsChunk_score(const WordHitsGroupPtr& group, const vector<WordPtr>& words, long ref_length, int num_words)
{
	double log_occ = 0;
	bool word_uniqueness[num_words];
	int num_wordHits_uniq = 0;

	for (auto iter = group->wordhits.begin(); iter != group->wordhits.end(); ++iter)
	{
		int word_id = (*iter)->word_id;
		if (word_uniqueness[word_id])
			continue;

		word_uniqueness[word_id] = true;
		++num_wordHits_uniq;
		log_occ += log10((double)words[word_id]->num_occ);
	}
	return log_occ - (num_wordHits_uniq - 1) * log10((double)ref_length);
}

bool can_pair(const WordHitsChunkPtr head_chunk, const WordHitsChunkPtr tail_chunk, const AlnSpliceOpt& opt)
{
	if(!(head_chunk->colinearity) || !(tail_chunk->colinearity))
		return false;
	if(head_chunk->gapMM.total_diff() > opt.wordChunk_max_diff || tail_chunk->gapMM.total_diff() > opt.wordChunk_max_diff)
		return false;
	if(head_chunk->strand != tail_chunk->strand)
		return false;
	if(head_chunk->wordHitList.back()->word_id >= tail_chunk->wordHitList.front()->word_id)
		return false;
	if(head_chunk->refEnd_pos >= tail_chunk->refStart_pos)
		return false;
	return true;
}

void WordHitsGroup::pair_wordChunks(const SeqString& query, const SeqSuffixArray& ref_SAIndex, const AlnSpliceOpt& opt)
{
	for(auto head_chunk_iter = wordhitschunks.begin(); head_chunk_iter != wordhitschunks.end(); ++head_chunk_iter)
	{
		WordHitsChunkPtr head_chunk = *head_chunk_iter;

		for(auto tail_chunk_iter = next(head_chunk_iter); tail_chunk_iter != wordhitschunks.end(); ++tail_chunk_iter)
		{
			WordHitsChunkPtr tail_chunk = *tail_chunk_iter;
			if(!can_pair(head_chunk, tail_chunk, opt))
			{
				continue;
			}

			/***************** If annotation exist, use annotation search first ***************/
			int gap_length = tail_chunk->queryStart_pos - head_chunk->queryEnd_pos;
			/* For annotation search
				 int wordID_diff = tail_chunk->get_wordList().front()->id - head_chunk->get_wordList().back()->id;
				 int gap_length = tail_chunk->queryStart_pos - head_chunk->queryEnd_pos - 1;
				 */

			//DEBUG
			//locate_junc_two_anchors(head_chunk, tail_chunk, query, ref_SAIndex);
			//END
		}
	}
}

void WordHitsGroup::locate_junc_two_chunks(const WordHitsChunkPtr& head_chunk, const WordHitsChunkPtr& tail_chunk, const SeqString& query, const SeqSuffixArray& ref_SAIndex, const AlnSpliceOpt& opt)
{
	//Determin Number of BackSearch
	int num_backSearch = opt.max_overhang;

	int query_gap = head_chunk->queryEnd_pos - tail_chunk->queryStart_pos + 1;
	num_backSearch = num_backSearch < query_gap ? query_gap : num_backSearch;

	int head_max_backSearch = head_chunk->queryEnd_pos - head_chunk->queryStart_pos - 4 + 1; //TODO Why 4?
	num_backSearch = num_backSearch > head_max_backSearch ? head_max_backSearch : num_backSearch;

	int query_gapStart =  head_chunk->queryEnd_pos - num_backSearch + 1;

	//Determin Gap Length
	int gap_length = tail_chunk->queryStart_pos - head_chunk->queryEnd_pos + 2 * num_backSearch + 1;
	if(gap_length <= 0)
	{
		return;
	}

	if(gap_length >= query.get_length() - query_gapStart)
	{
		gap_length = query.get_length() - query_gapStart;
	}

	//Negative intron length
	if(tail_chunk->refStart_pos - head_chunk->refEnd_pos - gap_length - 2 * num_backSearch <= 0 )
	{
		return;
	}

	long min_headChunk_refEnd = head_chunk->refEnd_pos - num_backSearch;
	long max_headChunk_refEnd = min_headChunk_refEnd + gap_length - 1;

	//TODO
	/***************** If annotation exist, use annotation search first ***************/

	if(opt.denovo_search && 
			(tail_chunk->refStart_pos - 1 - head_chunk->refEnd_pos < opt.max_intron_size))
	{
		//int result = locate_junc_two_anchors_denovo(head_chunk, tail_chunk, min_headChunk_refEnd, max_headChunk_refEnd, gap_length, num_backSearch, query, ref);
	}
}

void cal_wordChunk_adjust_diff(const WordHitsChunkPtr head_chunk, const WordHitsChunkPtr tail_chunk, vector<int>& head_chunk_adjust_diff, vector<int>& tail_chunk_adjust_diff, const SeqString query, const SeqSuffixArray& ref_SAIndex, int num_backSearch)
{
	head_chunk_adjust_diff = vector<int>(num_backSearch + 1);
	tail_chunk_adjust_diff = vector<int>(num_backSearch + 1);
	int head_chunk_diff = 0;
	int tail_chunk_diff = 0;
	for(int i = 0; i < num_backSearch + 1; ++i)
	{
		long head_chunk_refEnd = head_chunk->refEnd_pos - i;
		long head_chunk_queryEnd = head_chunk->queryEnd_pos - i;
		if(query[head_chunk_queryEnd] != ref_SAIndex.char_at(head_chunk_refEnd))
		{
			++head_chunk_diff;
		}
		head_chunk_adjust_diff[i] = head_chunk_diff;

		long tail_chunk_refEnd = tail_chunk->refStart_pos + i;
		long tail_chunk_queryEnd = tail_chunk->queryStart_pos + i;
		if(query[tail_chunk_queryEnd] != ref_SAIndex.char_at(tail_chunk_refEnd))
		{
			++tail_chunk_diff;
		}
		tail_chunk_adjust_diff[i] = tail_chunk_diff;
	}
}

int WordHitsGroup::locate_junc_two_chunks_denovo(WordHitsChunkPtr& head_chunk, WordHitsChunkPtr& tail_chunk, int min_headChunk_refEnd, int max_headChunk_refEnd, int gap_length, int num_backSearch, const SeqString& query, const SeqSuffixArray& ref_SAIndex, const AlnSpliceOpt& opt)
{
	int num_foundInDenovoSearch = 0;

	vector<int> head_chunk_adjust_diff;
	vector<int> tail_chunk_adjust_diff;
	cal_wordChunk_adjust_diff(head_chunk, tail_chunk, head_chunk_adjust_diff, tail_chunk_adjust_diff, query, ref_SAIndex, num_backSearch);

	int local_max_diff = opt.max_diff > 2 ? 2 : opt.max_diff;
	int best_diff = local_max_diff + 1;

	WordChunkBridge new_jun;

	for(long headChunk_refEnd = min_headChunk_refEnd; headChunk_refEnd <= max_headChunk_refEnd; ++headChunk_refEnd)
	{
		long tailChunk_refStart = tail_chunk->refStart_pos + num_backSearch - (gap_length - (headChunk_refEnd - min_headChunk_refEnd));

		if((tailChunk_refStart - headChunk_refEnd) < opt.min_intron_size)
		{
			continue;
		}

		long index_gap_refStart = headChunk_refEnd + 1;
		long index_gap_refEnd = tailChunk_refStart - 1;

		//TODO WHY?
		long breakpoint_index_query_tmp = head_chunk->queryEnd_pos - num_backSearch + headChunk_refEnd - min_headChunk_refEnd;
		if(breakpoint_index_query_tmp + 1 < opt.min_anchor || (get_seqLength(query)- breakpoint_index_query_tmp) < opt.min_anchor)
			continue;
		//TODO END

		int splice_strand;
		if(ref_SAIndex.char_at(index_refStart) == 'G' && ref_SAIndex.char_at(index_refStart + 1) == 'T'
				&& ref_SAIndex.char_at(index_refEnd - 1) == 'A' && ref_SAIndex(index_refEnd) == 'G')
		{
			splice_strand = 0;
		}
		else if((int)ref_SAIndex.char_at(index_refStart) == 'C' && (int)ref_SAIndex.char_at(index_refStart + 1) == 'T'
				&& (int)ref_SAIndex.char_at(index_refEnd - 2) == 'A' && (int)ref_SAIndex.char_at(index_refEnd) == 'C')
		{
			splice_strand = 1;
		}
		else continue;

		/*
			 if(opt.strand_mode != Strand_mode::reverse && splice_strand != head_chunk->strand)
			 continue;
			 if(opt.strand_mode != Strand_mode::forward && splice_strand == head_chunk->strand)
			 continue;
			 */

		//TODO FIX
		SeqString ref_seq = get_stringInfix(ref, min_headChunk_refEnd, headChunk_refEnd);
		SeqString ref_seq2 = get_stringInfix(ref, tailChunk_refStart, tailChunk_refStart + num_backSearch);
		ref_seq += ref_seq2;
		SeqString gap_seq = query.get_infixSeq(head_chunk->queryEnd_pos - num_backSearch + 1);

		GapAndMM gap_mm;
		get_alnPath(ref_seq, gap_seq, gap_mm);

		int adjuest_mm = 0;
		adjuest_mm += begin_wordChunk_adjustDiff[num_backSearch - 1]; // note the -1
		adjuest_mm += end_wordChunk_adjustDiff[num_backSearch - 1];
		int diff = gap_mm.total_diff() - adjuest_mm;
		//TODO END

		//Only choose the best one
		if (diff <= local_max_diff && diff < best_diff)
		{
			new_jun.spliced_strand = splice_strand;
			new_jun.head_chunk = head_chunk;
			new_jun.tail_chunk = end_wordChunk;
			new_jun.gap_mm = gap_mm;
			new_jun.index_refStart = headChunk_refEnd;
			new_jun.index_refEnd = tailChunk_refStart;
			new_jun.index_queryStart = head_chunk->queryEnd_pos - num_backSearch + headChunk_refEnd  - min_headChunk_refEnd;
			new_jun.index_queryEnd = new_jun.index_queryStart + 1;

			//p.logistic_prob = get_splice_score(pacseq, ue_end_t, de_start_t);
			best_diff = diff;
			head_chunk->set_isFirst(false);
			head_chunk->set_isFirst(false);

			num_foundInDenovoSearch++;
		}
	}

	wordChunkBridgeList_.emplace(make_shared<WordChunkBridge>(new_jun));
	return num_foundInDenovoSearch;
}
