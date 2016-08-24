// vim: set noexpandtab tabstop=2:

#pragma once

#include <memory>
#include <string>
#include <seqan_api/SeqString.hpp>
#include <seqan_api/CharString.hpp>
#include <seqan_api/CharStringSet.hpp>

class SeqStringSet
{
	public:
		SeqStringSet();
		SeqStringSet(const SeqStringSet& that);
		~SeqStringSet();
		long get_length() const;
		const void* get_pointer() const { return impl_; }
		void set_pointer(void* ptr) { impl_ = ptr; }

		SeqString operator[](long idx) const;

		SeqStringSet& operator=(const SeqStringSet& other);

	private:
		void* impl_;
};

void load_seqs(std::string seqFilePath, SeqStringSet& seq, CharStringSet& id);
void load_seqs_with_qual(std::string seqFilePath, SeqStringSet& seq, CharStringSet& id, CharStringSet& qual);

typedef std::shared_ptr<SeqStringSet> SeqStringSetPtr;
