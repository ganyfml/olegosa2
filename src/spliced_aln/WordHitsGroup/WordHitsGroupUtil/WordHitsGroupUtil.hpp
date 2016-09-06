// vim: set noexpandtab tabstop=2:

#include <vector>
#include <queue>
#include <seqan_api/SeqString.hpp>
#include <seqan_api/SeqSuffixArray.hpp>
#include <spliced_aln/WordHitsChunk.hpp>
#include <spliced_aln/WordHitsGroup.hpp>
#include <spliced_aln/WordHitsChunkBridgeChain.hpp>
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

SeqString get_partner_splice_site(SpliceType::Value splice_type, Strand::Value splice_strand);

int locate_bridge_within_two_chunks_with_inner_exon_denovo(WordHitsChunkPtr& head_chunk, WordHitsChunkPtr& tail_chunk, std::list<WordHitsChunkBridgePtr>& wordhitschunkbridges, std::list<WordHitsChunkPtr>& wordhitschunks, int num_backSearch, const SeqString& query, const SeqSuffixArray& ref_SAIndex, const AlnSpliceOpt& opt);

int locate_bridge_by_one_chunk_denovo_downstream(WordHitsChunkPtr& head_chunk, std::list<WordHitsChunkBridgePtr>& wordhitschunkbridges, std::list<WordHitsChunkPtr>& wordhitschunks, int num_backSearch, const SeqString& query, const SeqSuffixArray& ref_SAIndex, const AlnSpliceOpt& opt);

int locate_bridge_by_one_chunk_denovo_upstream(WordHitsChunkPtr& tail_chunk, std::list<WordHitsChunkBridgePtr>& wordhitschunkbridges, std::list<WordHitsChunkPtr>& wordhitschunks, int num_backSearch, const SeqString& query, const SeqSuffixArray& ref_SAIndex, const AlnSpliceOpt& opt);

void concat_bridges(std::list<WordHitsChunkBridgePtr>& wordhitschunkbridges, std::list<WordHitsChunkBridgeChainPtr>& results, int query_length, bool global);

void locate_bridge_two_chunks(WordHitsChunkPtr& head_chunk, WordHitsChunkPtr& tail_chunk, std::list<WordHitsChunkBridgePtr>& wordhitschunkbridges, std::list<WordHitsChunkPtr>& wordhitschunks, const SeqString& query, const SeqSuffixArray& ref_SAIndex, const AlnSpliceOpt& opt);
void locate_bridge_one_chunk(WordHitsChunkPtr& chunk, std::list<WordHitsChunkBridgePtr>& wordhitschunkbridges, std::list<WordHitsChunkPtr>& wordhitschunks, const SeqString& query, const SeqSuffixArray& ref_SAIndex, const AlnSpliceOpt& opt);
void search_exonic_aln(const std::list<WordHitsChunkPtr>& wordhitschunks, const SeqString query, std::list<WordHitsChunkBridgeChainPtr>& results);

//In hpp due to debug
bool is_donor_splice_site_forward(const SeqSuffixArray& ref, long ref_pos);
bool is_donor_splice_site_reverse(const SeqSuffixArray& ref, long ref_pos);
bool is_acceptor_splice_site_forward(const SeqSuffixArray& ref, long ref_pos);
bool is_acceptor_splice_site_reverse(const SeqSuffixArray& ref, long ref_pos);
void cal_two_wordchunks_backsearch_area_mm(const WordHitsChunkPtr head_chunk, const WordHitsChunkPtr tail_chunk, std::vector<int>& head_chunk_adjust_diff, std::vector<int>& tail_chunk_adjust_diff, const SeqString query, const SeqSuffixArray& ref_SAIndex, int num_backSearch);
void update_aln_list(std::list<WordHitsChunkBridgeChainPtr>& results, std::vector<bool>& destroy_flag, int& aln_length);
