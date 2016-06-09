#include<spliced_aln/SplicedAlnResult.hpp>

bool is_identical(const SplicedAlnResultPtr& first, const SplicedAlnResultPtr& second)
{
  if(first->bridges.size() == second->bridges.size())
  {
    for (auto first_bridge_iter = first->bridges.begin(), second_bride_iter = second->bridges.begin()
        ; second_bride_iter != second->bridges.end();
        ++first_bridge_iter, ++second_bride_iter)
    {
      if((*first_bridge_iter)->refStart_pos != (*second_bride_iter)->refStart_pos
          || (*first_bridge_iter)->refEnd_pos != (*second_bride_iter)->refEnd_pos
          || (*first_bridge_iter)->head_chunk->strand != (*second_bride_iter)->head_chunk->strand)
      {
        return false;
      }
    }
    return true;
  }
  else
  {
    return false;
  }
}

void SplicedAlnResult::evaluate(bool global, int query_length)
{
  WordHitsChunkBridgePtr first_bridge = bridges.front();
  WordHitsChunkBridgePtr last_bridge = bridges.back();

  strand = first_bridge->head_chunk->strand;
  sense_strand = first_bridge->sense_strand;

  refStart_pos = first_bridge->head_chunk->refStart_pos;
  queryStart_pos = first_bridge->head_chunk->queryStart_pos;
  refEnd_pos = last_bridge->tail_chunk->refEnd_pos;
  queryEnd_pos = last_bridge->tail_chunk->queryEnd_pos;

  gap_mm = first_bridge->head_chunk->gapMM;
  num_diff = 0;
  logistic_prob = 0.0;
  num_diff = 0;

  for (auto bridge_iter = bridges.begin(); bridge_iter != bridges.end(); ++bridge_iter)
  {
    auto curr_bridge = *bridge_iter;
    gap_mm += (*bridge_iter)->gap_mm;

    // n_mm might be overestimated since there redundant mm counts between junction and de ue
    gap_mm += (*bridge_iter)->tail_chunk->gapMM;
    gap_mm.num_mismatch -= curr_bridge->adjust_diff;

    logistic_prob += (*bridge_iter)->score; 
  }

  num_diff = gap_mm.total_diff();
  logistic_prob = logistic_prob / bridges.size();

  if(global)
  {
    num_diff += queryStart_pos;
    num_diff += (query_length - 1 - queryEnd_pos);

    refStart_pos -= queryStart_pos;
    refEnd_pos+= (query_length - 1 - queryEnd_pos);
    queryStart_pos = 0;
    queryEnd_pos = query_length - 1;
  }
}
