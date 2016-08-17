#include <../../../WordHitsGroupUtil.hpp>
#include <list>

using namespace std;

int main()
{
  WordHitsChunkPtr bridge_head = make_shared<WordHitsChunk>(0);
  bridge_head->strand = Strand::forward;

  WordHitsChunkPtr bridge_tail = make_shared<WordHitsChunk>(1);
  bridge_tail->strand = Strand::forward;

  WordHitsChunkBridgePtr group_bridge = make_shared<WordHitsChunkBridge>(
      bridge_head, bridge_tail
      , 0, 15
      , 1, 16
      , Strand::forward, 1);

  WordHitsGroupPtr group = make_shared<WordHitsGroup>(0);
  group->wordhitschunkbridges.push_back(group_bridge);

  list<SplicedAlnResultPtr> results;
  int query_length = 100;
  bool global = false;
  concat_bridges(group->wordhitschunkbridges, results, query_length, global);

  printf("Num of results: %lu\n", results.size());
  for(auto iter = results.begin(); iter != results.end(); ++iter)
  {
    (*iter)->display();
  }
}
