#include <../../../../WordHitsGroupUtil.hpp>
#include <list>

using namespace std;

int main()
{
  WordHitsGroupPtr group = make_shared<WordHitsGroup>(0);

  WordHitsChunkPtr bridge_head = make_shared<WordHitsChunk>(0);
  bridge_head->strand = Strand::forward;
  bridge_head->start_pos_in_ref = 0;
  bridge_head->end_pos_in_ref = 5;
  bridge_head->start_pos_in_query = 1;
  bridge_head->end_pos_in_query = 6;
  bridge_head->gapMM.num_mismatch = 6;
  bridge_head->gapMM.num_gapOpenRef = 1;
  bridge_head->gapMM.num_gapExtRef = 2;
  bridge_head->gapMM.num_gapOpenQuery = 3;
  bridge_head->gapMM.num_gapExtQuery = 4;

  WordHitsChunkPtr bridge_connection = make_shared<WordHitsChunk>(1);
  bridge_connection->strand = Strand::forward;
  bridge_connection->start_pos_in_ref = 10;
  bridge_connection->end_pos_in_ref = 15;
  bridge_connection->start_pos_in_query = 11;
  bridge_connection->end_pos_in_query = 16;
  bridge_connection->gapMM.num_mismatch = 5;
  bridge_connection->gapMM.num_gapOpenRef = 1;
  bridge_connection->gapMM.num_gapExtRef = 2;
  bridge_connection->gapMM.num_gapOpenQuery = 3;
  bridge_connection->gapMM.num_gapExtQuery = 4;

  WordHitsChunkPtr bridge_tail = make_shared<WordHitsChunk>(2);
  bridge_tail->strand = Strand::forward;
  bridge_tail->start_pos_in_ref = 20;
  bridge_tail->end_pos_in_ref = 25;
  bridge_tail->start_pos_in_query = 21;
  bridge_tail->end_pos_in_query = 26;
  bridge_tail->gapMM.num_mismatch = 5;
  bridge_tail->gapMM.num_gapOpenRef = 1;
  bridge_tail->gapMM.num_gapExtRef = 2;
  bridge_tail->gapMM.num_gapOpenQuery = 3;
  bridge_tail->gapMM.num_gapExtQuery = 4;

  WordHitsChunkBridgePtr group_bridge_head = make_shared<WordHitsChunkBridge>(
      bridge_head, bridge_connection,
      5, 10,
      6, 11,
      Strand::forward, 1);

  WordHitsChunkBridgePtr group_bridge_tail = make_shared<WordHitsChunkBridge>(
      bridge_connection, bridge_tail,
      11, 13,
      12, 14,
      Strand::reverse, 1);

  group->wordhitschunkbridges.push_back(group_bridge_head);
  group->wordhitschunkbridges.push_back(group_bridge_tail);

  list<SplicedAlnResultPtr> results;
  int query_length = 100;
  bool global = false;
  concat_bridges(group->wordhitschunkbridges, results, query_length, global);
  printf("Num of results: %lu\n", results.size());
  for(auto iter = results.begin(); iter != results.end(); ++iter)
  {
    (*iter)->display();
    printf("\n");
  }
}
