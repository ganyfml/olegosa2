// vim: set noexpandtab tabstop=2:

#include<spliced_aln/WordHitsChunkBridgeChain.hpp>

using namespace std;

//bool is_identical(const WordHitsChunkBridgeChainPtr& first, const WordHitsChunkBridgeChainPtr& second)
//{
//  if(first->bridges.size() == second->bridges.size())
//  {
//    for (auto first_bridge_iter = first->bridges.begin(), second_bride_iter = second->bridges.begin()
//        ; second_bride_iter != second->bridges.end();
//        ++first_bridge_iter, ++second_bride_iter)
//    {
//      if((*first_bridge_iter)->start_pos_in_ref != (*second_bride_iter)->start_pos_in_ref
//          || (*first_bridge_iter)->end_pos_in_ref != (*second_bride_iter)->end_pos_in_ref
//          || (*first_bridge_iter)->head_chunk->strand != (*second_bride_iter)->head_chunk->strand)
//      {
//        return false;
//      }
//    }
//    return true;
//  }
//  else
//  {
//    return false;
//  }
//}

void WordHitsChunkBridgeChain::summarize(bool global, int query_length)
{
	WordHitsChunkBridgePtr first_bridge = bridges.front();
	WordHitsChunkBridgePtr last_bridge = bridges.back();

	strand = first_bridge->head_chunk->strand;
	spliced_strand = first_bridge->spliced_strand;

	start_pos_in_ref = first_bridge->head_chunk->start_pos_in_ref;
	start_pos_in_query = first_bridge->head_chunk->start_pos_in_query;
	end_pos_in_ref = last_bridge->tail_chunk->end_pos_in_ref;
	end_pos_in_query = last_bridge->tail_chunk->end_pos_in_query;

	gap_mm = first_bridge->head_chunk->gapMM;
	num_diff = 0;
	logistic_prob = 0.0;
	num_diff = 0;

	//  for (auto bridge_iter = bridges.begin(); bridge_iter != bridges.end(); ++bridge_iter)
	//  {
	//    auto curr_bridge = *bridge_iter;
	//    gap_mm += (*bridge_iter)->gap_mm;
	//
	//    // n_mm might be overestimated since there redundant mm counts between junction and de ue
	//    gap_mm += (*bridge_iter)->tail_chunk->gapMM;
	//    gap_mm.num_mismatch -= curr_bridge->original_search_area_diff;
	//
	//    logistic_prob += (*bridge_iter)->score; 
	//  }
	//
	//  num_diff = gap_mm.sum();
	//  logistic_prob = logistic_prob / bridges.size();
	//
	//  if(global)
	//  {
	//    num_diff += start_pos_in_query;
	//    num_diff += (query_length - 1 - end_pos_in_query);
	//
	//    start_pos_in_ref -= start_pos_in_query;
	//    end_pos_in_ref+= (query_length - 1 - end_pos_in_query);
	//    start_pos_in_query = 0;
	//    end_pos_in_query = query_length - 1;
	//  }
}

void summarize_WordHitsChunkBridgeChains(list<WordHitsChunkBridgeChainPtr>& results, int query_length, bool global)
{
	for(auto aln_iter = results.begin(); aln_iter != results.end(); ++aln_iter)
	{
		//    if(aln_iter != results.begin())
		//    {
		//      auto prev_aln_iter = aln_iter;
		//      --prev_aln_iter;
		//      if(is_identical(*prev_aln_iter, *aln_iter))
		//      {
		//        aln_iter = results.erase(aln_iter);
		//        --aln_iter;
		//      }
		//    }
		(*aln_iter)->summarize(global, query_length);
	}
}
