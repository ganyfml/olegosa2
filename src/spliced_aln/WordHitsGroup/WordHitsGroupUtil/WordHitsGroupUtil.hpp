// vim: set noexpandtab tabstop=2:

#include <vector>
#include <queue>
#include <seqan_api/SeqString.hpp>
#include <seqan_api/SeqSuffixArray.hpp>
#include <spliced_aln/WordHitsChunk.hpp>
#include <spliced_aln/WordHitsGroup.hpp>
#include <spliced_aln/Util.hpp>
#include <nonspliced_aln/alnNonspliceOpt.hpp>

namespace SpliceType
{
	enum Value {splice_donor = 0, splice_acceptor = 1, splice_noncanonical = 2};
}

int cal_two_wordchunks_backsearch_area_diff_sum(const WordHitsChunkPtr head_chunk, const WordHitsChunkPtr tail_chunk, const SeqString query, const SeqSuffixArray& ref_SAIndex, int num_backSearch);

int locate_bridge_within_two_chunks_denovo(WordHitsChunkPtr& head_chunk, WordHitsChunkPtr& tail_chunk, std::list<WordHitsChunkBridgePtr>& wordhitschunkbridges, int num_backSearch, const SeqString& query, const SeqSuffixArray& ref_SAIndex, const AlnSpliceOpt& opt);

void collect_anchor_hits_within_bound(const SeqString& anchor_seq, std::list<long>& anchor_hit_list, const SeqSuffixArray& ref_SAIndex, long hit_left_bound, long hit_right_bound, const alnNonspliceOpt& anchor_search_opt);

Strand::Value determin_strand_by_canonical_spliceSite(const SeqSuffixArray& ref_SAIndex, long donor_pos, long acceptor_pos);

bool is_splice_site_by_refPos(const SeqSuffixArray& ref, long ref_pos, SpliceType::Value splice_type, Strand::Value splice_strand);

//In hpp due to debug
bool is_donor_splice_site(const SeqSuffixArray& ref, long ref_pos, bool revcomp);
bool is_acceptor_splice_site(const SeqSuffixArray& ref, long ref_pos, bool revcomp);
