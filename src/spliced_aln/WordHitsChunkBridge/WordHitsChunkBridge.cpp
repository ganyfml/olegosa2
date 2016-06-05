#include <spliced_aln/WordHitsChunkBridge.hpp>

bool compare_wordHitsChunkBridgeByRefAndStrand(const WordHitsChunkBridgePtr bridge1, const WordHitsChunkBridgePtr& bridge2)
{
  if(bridge1->head_chunk->strand != bridge2->head_chunk->strand)
  {
    return bridge1->head_chunk->strand < bridge2->head_chunk->strand;
  }
  else if(bridge1->sense_strand != bridge1->sense_strand)
  {
    return bridge1->sense_strand < bridge2->sense_strand;
  }
  else if(bridge1->head_chunk->refStart_pos != bridge2->head_chunk->refStart_pos)
  {
    return bridge1->head_chunk->refStart_pos < bridge2->head_chunk->refStart_pos;
  }
  else if(bridge1->refStart_pos != bridge2->refStart_pos)
  {
    return bridge1->refStart_pos < bridge2->refStart_pos;
  }
  else
  {
    return bridge1->refEnd_pos < bridge2->refEnd_pos;
  }
}

void uniq_wordHitsChunkBridge(std::list<WordHitsChunkBridgePtr>& bridges)
{
  auto head = ++bridges.begin();
  while(head != bridges.end())
  {
    auto tail = head;
    --tail;
    if((*head)->head_chunk == (*tail)->head_chunk && (*head)->tail_chunk == (*tail)->tail_chunk
        && (*head)->refStart_pos == (*tail)->refStart_pos && (*head)->refEnd_pos == (*tail)->refEnd_pos)
      {
        tail = bridges.erase(tail);
      }
    else
    {
      ++tail;
    }
  }
}
