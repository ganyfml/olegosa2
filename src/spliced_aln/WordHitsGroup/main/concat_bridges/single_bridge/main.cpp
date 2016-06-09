#include <../../../WordHitsGroup.hpp>
#include <list>

using namespace std;

int main()
{
  WordHitsGroupPtr group = make_shared<WordHitsGroup>(0);

  WordHitsChunkBridgePtr group_bridge = make_shared<WordHitsChunkBridge>();
  group_bridge->sense_strand = 2;

  WordHitsChunkPtr bridge_head = make_shared<WordHitsChunk>(0);
  bridge_head->strand = 1;
  bridge_head->refStart_pos = 0;
  bridge_head->refEnd_pos = 5;
  bridge_head->queryStart_pos = 1;
  bridge_head->queryEnd_pos = 6;
  bridge_head->gapMM.num_mismatch = 5;
  bridge_head->gapMM.num_gapOpenRef = 1;
  bridge_head->gapMM.num_gapExtRef = 2;
  bridge_head->gapMM.num_gapOpenQuery = 3;
  bridge_head->gapMM.num_gapExtQuery = 4;

  WordHitsChunkPtr bridge_tail = make_shared<WordHitsChunk>(1);
  bridge_tail->refStart_pos = 10;
  bridge_tail->refEnd_pos = 15;
  bridge_tail->queryStart_pos = 11;
  bridge_tail->queryEnd_pos = 16;
  bridge_tail->gapMM.num_mismatch = 5;
  bridge_tail->gapMM.num_gapOpenRef = 1;
  bridge_tail->gapMM.num_gapExtRef = 2;
  bridge_tail->gapMM.num_gapOpenQuery = 3;
  bridge_tail->gapMM.num_gapExtQuery = 4;

  group_bridge->head_chunk = bridge_head;
  group_bridge->tail_chunk = bridge_tail;
  group->wordhitschunkbridge.push_back(group_bridge);

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
