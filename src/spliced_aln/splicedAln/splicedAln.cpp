// vim: set noexpandtab tabstop=2:

#include <spliced_aln/splicedAln.hpp>

using namespace std;

void generate_words(const SeqString& query, list<WordPtr>& wordList, const SeqSuffixArray& ref_SAIndex)
{
	opt_.num_words = (get_seqLength(query_) - opt_.word_max_overlap ) / (opt_.word_size - opt_.word_max_overlap);

	std::list<WordPtr> raw_subSeq;
	for (int i = 0; i != opt_.num_words; ++i)
	{
		Word subSeq {i};
		subSeq.query_index = opt_.word_size * i + (get_seqLength(query_) - opt_.num_words * opt_.word_size) * i / ( opt_.num_words - 1);
		subSeq.word_length = opt_.word_size;
		subSeq.sequence = get_stringInfix(query_, subSeq.query_index, subSeq.query_index + subSeq.word_length);
		raw_subSeq.push_back(std::make_shared<Word> (subSeq));	
	}
/*
	for(auto index = raw_subSeq.begin(); index != raw_subSeq.end(); ++index)
	{
		std::list<long> hits = ref_.find_all((*index)->sequence);
		for(auto hit_index = hits.begin(); hit_index != hits.end(); ++hit_index)
		{
			Word word {(*index)->id};
			word.sequence = (*index)->sequence;
			word.query_index = (*index)->query_index;
			word.word_length = (*index)->word_length;
			word.ref_index = *hit_index;
			wordList.push_back(std::make_shared<Word>(word));
		}
	}
	*/
}

