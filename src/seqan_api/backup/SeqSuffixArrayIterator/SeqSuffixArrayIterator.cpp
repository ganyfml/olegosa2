// vim: set noexpandtab tabstop=2:

#include <seqan/index.h>
#include <seqan_api/SeqanAPIUtil.hpp>
#include <SeqSuffixArrayIterator.hpp>

typedef seqan::Dna5String SeqanString;
typedef seqan::Index<SeqanString, seqan::IndexEsa<>> Dna5SuffixArray;
typedef seqan::Iterator<Dna5SuffixArray, seqan::TopDown<>>::Type T;

inline T* voidPtr2TPtr(void* original_ptr)
{
	return static_cast<T*>(original_ptr);
}

SeqSuffixArrayIterator::SeqSuffixArrayIterator(const SeqSuffixArray& sa)
	: impl_(new T(*constVoid2localType<Dna5SuffixArray>(sa.get_pointer()))), extra_steps_(0) {}

SeqSuffixArrayIterator::~SeqSuffixArrayIterator()
{
	delete static_cast<T*>(impl_);
}

bool SeqSuffixArrayIterator::godown_char(const char& godown_char)
{
	T* seqan_iter = voidPtr2TPtr(impl_);
	int original_length = length(representative(*seqan_iter));
	if(this->extra_steps_ == 0)
	{
		if(seqan::goDown(*seqan_iter, godown_char))
		{
			this->extra_steps_ = length(representative(*seqan_iter)) - original_length - 1;
			return true;
		}
	}
	else
	{
		if(representative(*seqan_iter)[original_length - this->extra_steps_] == godown_char)
		{
			--this->extra_steps_;
			return true;
		}
	}
	return false;
}

SeqString SeqSuffixArrayIterator::get_seq()
{
	T seqan_iter = *voidPtr2TPtr(impl_);
	return SeqString(std::string(seqanString(prefix(representative(seqan_iter), length(seqan_iter) - this->extra_steps_)));
			}
