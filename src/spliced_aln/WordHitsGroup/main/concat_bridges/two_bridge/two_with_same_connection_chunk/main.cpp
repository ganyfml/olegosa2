#include <../../../../WordHitsGroup.hpp>
#include <list>

using namespace std;

int main()
{
  WordHitsGroupPtr group = make_shared<WordHitsGroup>(0);

  WordHitsChunkPtr bridge_head = make_shared<WordHitsChunk>(0);
  bridge_head->strand = 1;
  bridge_head->refStart_pos = 0;
  bridge_head->refEnd_pos = 5;
  bridge_head->queryStart_pos = 1;
  bridge_head->queryEnd_pos = 6;
  bridge_head->gapMM.num_mismatch = 6;
  bridge_head->gapMM.num_gapOpenRef = 1;
  bridge_head->gapMM.num_gapExtRef = 2;
  bridge_head->gapMM.num_gapOpenQuery = 3;
  bridge_head->gapMM.num_gapExtQuery = 4;

  WordHitsChunkPtr bridge_connection = make_shared<WordHitsChunk>(1);
  bridge_connection->strand = 1;
  bridge_connection->refStart_pos = 10;
  bridge_connection->refEnd_pos = 15;
  bridge_connection->queryStart_pos = 11;
  bridge_connection->queryEnd_pos = 16;
  bridge_connection->gapMM.num_mismatch = 5;
  bridge_connection->gapMM.num_gapOpenRef = 1;
  bridge_connection->gapMM.num_gapExtRef = 2;
  bridge_connection->gapMM.num_gapOpenQuery = 3;
  bridge_connection->gapMM.num_gapExtQuery = 4;

  WordHitsChunkPtr bridge_tail = make_shared<WordHitsChunk>(2);
  bridge_tail->strand = 1;
  bridge_tail->refStart_pos = 20;
  bridge_tail->refEnd_pos = 25;
  bridge_tail->queryStart_pos = 21;
  bridge_tail->queryEnd_pos = 26;
  bridge_tail->gapMM.num_mismatch = 5;
  bridge_tail->gapMM.num_gapOpenRef = 1;
  bridge_tail->gapMM.num_gapExtRef = 2;
  bridge_tail->gapMM.num_gapOpenQuery = 3;
  bridge_tail->gapMM.num_gapExtQuery = 4;

  WordHitsChunkBridgePtr group_bridge_head = make_shared<WordHitsChunkBridge>();
  group_bridge_head->sense_strand = 1;
  group_bridge_head->head_chunk = bridge_head;
  group_bridge_head->tail_chunk = bridge_connection;
  group_bridge_head->refStart_pos = 5;
  group_bridge_head->refEnd_pos = 10;
  group_bridge_head->queryStart_pos = 6;
  group_bridge_head->queryEnd_pos= 11;
  group_bridge_head->gap_mm.num_mismatch = 6;
  group_bridge_head->gap_mm.num_gapOpenRef = 2;
  group_bridge_head->gap_mm.num_gapExtRef = 3;
  group_bridge_head->gap_mm.num_gapOpenQuery = 4;

  WordHitsChunkBridgePtr group_bridge_tail = make_shared<WordHitsChunkBridge>();
  group_bridge_tail->sense_strand = 1;
  group_bridge_tail->head_chunk = bridge_connection;
  group_bridge_tail->tail_chunk = bridge_tail;
  group_bridge_tail->refStart_pos = 15;
  group_bridge_tail->refEnd_pos = 20;
  group_bridge_tail->queryStart_pos = 16;
  group_bridge_tail->queryEnd_pos= 21;
  group_bridge_tail->gap_mm.num_mismatch = 7;
  group_bridge_tail->gap_mm.num_gapOpenRef = 3;
  group_bridge_tail->gap_mm.num_gapExtRef = 4;
  group_bridge_tail->gap_mm.num_gapOpenQuery = 5;

  group->wordhitschunkbridge.push_back(group_bridge_head);
  group->wordhitschunkbridge.push_back(group_bridge_tail);

  list<SplicedAlnResultPtr> results;
  int query_length = 100;
  bool global = false;
  group->concat_bridges(results, query_length, global);
  printf("Num of results: %lu\n", results.size());
  for(auto iter = results.begin(); iter != results.end(); ++iter)
  {
    (*iter)->display();
  }
}
