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

  WordHitsChunkPtr bridge_tail1 = make_shared<WordHitsChunk>(1);
  bridge_tail1->refStart_pos = 10;
  bridge_tail1->refEnd_pos = 15;
  bridge_tail1->queryStart_pos = 11;
  bridge_tail1->queryEnd_pos = 16;
  bridge_tail1->gapMM.num_mismatch = 5;
  bridge_tail1->gapMM.num_gapOpenRef = 1;
  bridge_tail1->gapMM.num_gapExtRef = 2;
  bridge_tail1->gapMM.num_gapOpenQuery = 3;
  bridge_tail1->gapMM.num_gapExtQuery = 4;

  WordHitsChunkPtr bridge_tail2 = make_shared<WordHitsChunk>(2);
  bridge_tail2->refStart_pos = 20;
  bridge_tail2->refEnd_pos = 25;
  bridge_tail2->queryStart_pos = 21;
  bridge_tail2->queryEnd_pos = 26;
  bridge_tail2->gapMM.num_mismatch = 5;
  bridge_tail2->gapMM.num_gapOpenRef = 1;
  bridge_tail2->gapMM.num_gapExtRef = 2;
  bridge_tail2->gapMM.num_gapOpenQuery = 3;
  bridge_tail2->gapMM.num_gapExtQuery = 4;

  WordHitsChunkBridgePtr group_bridge1 = make_shared<WordHitsChunkBridge>();
  group_bridge1->sense_strand = 1;
  group_bridge1->head_chunk = bridge_head;
  group_bridge1->tail_chunk = bridge_tail1;
  group_bridge1->refStart_pos = 5;
  group_bridge1->refEnd_pos = 10;
  group_bridge1->gap_mm.num_mismatch = 6;
  group_bridge1->gap_mm.num_gapOpenRef = 2;
  group_bridge1->gap_mm.num_gapExtRef = 3;
  group_bridge1->gap_mm.num_gapOpenQuery = 4;
  group_bridge1->gap_mm.num_gapExtQuery = 5;

  WordHitsChunkBridgePtr group_bridge2 = make_shared<WordHitsChunkBridge>();
  group_bridge2->sense_strand = 1;
  group_bridge2->head_chunk = bridge_head;
  group_bridge2->tail_chunk = bridge_tail2;
  group_bridge2->refStart_pos = 5;
  group_bridge2->refEnd_pos = 20;
  group_bridge2->gap_mm.num_mismatch = 7;
  group_bridge2->gap_mm.num_gapOpenRef = 3;
  group_bridge2->gap_mm.num_gapExtRef = 4;
  group_bridge2->gap_mm.num_gapOpenQuery = 5;
  group_bridge2->gap_mm.num_gapExtQuery = 6;

  group->wordhitschunkbridge.push_back(group_bridge1);
  group->wordhitschunkbridge.push_back(group_bridge2);

  list<SplicedAlnResultPtr> results;
  int query_length = 100;
  bool global = false;
  group->concat_bridges(results, query_length, global);
  printf("Num of results: %lu\n", results.size());
  for(auto iter = results.begin(); iter != results.end(); ++iter)
  {
    (*iter)->display();
    cout << "\n\n";
  }
}
