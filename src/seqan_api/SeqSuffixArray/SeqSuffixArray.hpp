// vim: set noexpandtab tabstop=3:

#pragma once

#include <string>
#include <seqan_api/SeqString.hpp>

class SeqSuffixArray
{
  public:
	 SeqSuffixArray(const SeqString& seq);
	 SeqSuffixArray(const std::string& index_file_name);
	 ~SeqSuffixArray();
	 void saveSA(const std::string& index_file_name) const;
	 unsigned long SAIndex2SeqPos(unsigned long SAIndex) const;
	 SeqString getSeq_bySAIndex(unsigned long SAIndex, int seq_length) const;
	 char char_at(int index) const;
	 long seq_length() const;
	 const void* get_pointer() const { return impl_; }
  private:
	 void* impl_;
};
