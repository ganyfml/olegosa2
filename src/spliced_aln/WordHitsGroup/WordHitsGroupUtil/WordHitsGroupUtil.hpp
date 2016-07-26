// vim: set noexpandtab tabstop=2:

#include <vector>
#include <seqan_api/SeqString.hpp>
#include <seqan_api/SeqSuffixArray.hpp>
#include <spliced_aln/WordHitsChunk.hpp>
#include <spliced_aln/Util.hpp>

Strand::Value determin_strand_by_canonical_spliceSite(const SeqSuffixArray& ref_SAIndex, long donor_pos, long acceptor_pos);

std::pair<int, int> cal_two_wordchunks_backsearch_area_diff(const WordHitsChunkPtr head_chunk, const WordHitsChunkPtr tail_chunk, const SeqString query, const SeqSuffixArray& ref_SAIndex, int num_backSearch);
