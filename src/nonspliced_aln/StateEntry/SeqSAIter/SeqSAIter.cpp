// vim: set noexpandtab tabstop=2:

#include <nonspliced_aln/SeqSAIter.hpp>

using namespace seqan;

SeqSAIter::SeqSAIter(SeqanSA& seqan_sa)
	: seqan_sa_iter_(new SeqanSAIter(seqan_sa)), extra_steps_(0) {}

SeqSAIter::~SeqSAIter()
{
	delete seqan_sa_iter_;
}

bool SeqSAIter::godown_char(const char x)
{
	int original_length = length(representative(*seqan_sa_iter_));
	if(this->extra_steps_ == 0)
	{
		if(goDown(*seqan_sa_iter_, x))
		{
			this->extra_steps_ = length(representative(*seqan_sa_iter_)) - original_length - 1;
			return true;
		}
	}
	else
	{
		if(representative(*seqan_sa_iter_)[original_length - this->extra_steps_] == x)
		{
			--this->extra_steps_;
			return true;
		}
	}
	return false;
}

SeqString SeqSAIter::get_prefix() const
{
	SeqanString original_seq = representative(*seqan_sa_iter_);
	SeqString ret;
	ret.set_pointer(new SeqanString(prefix(original_seq, (length(original_seq) - this->extra_steps_))));
	return ret;
}
