// vim: set noexpandtab tabstop=2:

#pragma once

#include <seqan/index.h>
#include <seqan/seq_io.h>

typedef seqan::Dna5String SeqString;
typedef seqan::StringSet<SeqString> SeqStringSet;

SeqString get_reverseComplement(const SeqString& target);
SeqString change_stringInsert(const SeqString& target, int index, char value);
SeqString change_stringRemove(const SeqString& target, int index);
SeqString get_stringPrefix(const SeqString& target, int index);
SeqString get_stringInfix(const SeqString& target, int start, int end);
SeqString get_stringSuffix(const SeqString& target, int index);
int get_seqLength(const SeqString& target);
void erase_seqBack(SeqString& str);

class Seq
{
	friend class SeqFinder;
	public:
		Seq(const std::string& ref_file, const std::string& index_file);
		bool create_SA(int chr_index);
		bool load_SA();
		bool find_exist(const SeqString& target) const;
		char operator[](unsigned long idx) const { return rawtextAt(idx, *search_index_); }
		//May not be useful
		//long get_length() const { return get_seqLength(sequence); }

	private:
		std::string ref_file_;
		std::string index_file_;
		std::shared_ptr<seqan::Index<SeqString, seqan::IndexEsa<> > >search_index_;
};

class SeqFinder
{
	public:
	SeqFinder(Seq ref, SeqString& query)
	{
		finder_ = seqan::Finder< seqan::Index<SeqString, seqan::IndexEsa<> > > (*ref.search_index_);	
		query_ = query;
		has_next_ = find(finder_, query_);
	}

	bool has_next()
	{
		return has_next_;
	}

	unsigned long next()
	{
		unsigned long ret = position(finder_); 
		has_next_ = find(finder_, query_);
		return ret;	
	}

	private:
	seqan::Finder< seqan::Index<SeqString, seqan::IndexEsa<> > > finder_;
	SeqString query_;
	bool has_next_;
};
