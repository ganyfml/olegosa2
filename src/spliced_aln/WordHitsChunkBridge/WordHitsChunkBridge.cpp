#include <spliced_aln/WordHitsChunkBridge.hpp>

bool compare_wordHitsChunkBridgeByRefAndStrand(const WordHitsChunkBridgePtr bridge1, const WordHitsChunkBridgePtr& bridge2)
{
	if(bridge1->head_chunk->strand != bridge2->head_chunk->strand)
	{
		return bridge1->head_chunk->strand < bridge2->head_chunk->strand;
	}
	else if(bridge1->spliced_strand != bridge1->spliced_strand)
	{
		return bridge1->spliced_strand < bridge2->spliced_strand;
	}
	else if(bridge1->head_chunk->start_pos_in_ref != bridge2->head_chunk->start_pos_in_ref)
	{
		return bridge1->head_chunk->start_pos_in_ref < bridge2->head_chunk->start_pos_in_ref;
	}
	else if(bridge1->start_pos_in_ref != bridge2->start_pos_in_ref)
	{
		return bridge1->start_pos_in_ref < bridge2->start_pos_in_ref;
	}
	else
	{
		return bridge1->end_pos_in_ref < bridge2->end_pos_in_ref;
	}
}

//void uniq_wordHitsChunkBridge(std::list<WordHitsChunkBridgePtr>& bridges)
//{
//	auto head = ++bridges.begin();
//	while(head != bridges.end())
//	{
//		auto tail = head;
//		--tail;
//		if((*head)->head_chunk == (*tail)->head_chunk && (*head)->tail_chunk == (*tail)->tail_chunk
//				&& (*head)->start_pos_in_ref == (*tail)->start_pos_in_ref && (*head)->end_pos_in_ref == (*tail)->end_pos_in_ref)
//		{
//			head = bridges.erase(head);
//		}
//		else
//		{
//			++head;
//		}
//	}
//}
