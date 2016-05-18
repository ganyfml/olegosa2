// vim: set noexpandtab tabstop=2:

#pragma once

#include <seqan/index.h>
#include <seqan/seq_io.h>

class SeqSAIter
{
	typedef seqan::Dna5String SeqanString;
	typedef seqan::Index<SeqanString, seqan::IndexEsa<>> SeqanSA;
	typedef seqan::Iterator<SeqanSA, seqan::TopDown<seqan::ParentLinks<>>>::Type SeqanSAIter;

	public:
	SeqSAIter(SeqanSA& seqan_sa);
	SeqSAIter()
		: seqan_sa_iter(new SeqanSAIter()), extra_steps_(0) {}
	SeqSAIter(const SeqSAIter& other)
		: seqan_sa_iter(new SeqanSAIter(*other.seqan_sa_iter)), extra_steps_(other.extra_steps_) {}
	SeqSAIter& operator=(const SeqSAIter& other)
	{
		extra_steps_ = other.extra_steps_;
		seqan_sa_iter = new SeqanSAIter(*other.seqan_sa_iter);
		return *this;
	}

	~SeqSAIter();
	bool godown_char(const char x);
	seqan::Dna5String get_prefix() const;

	void display()
	{
		printf("Extra step: %d\n", extra_steps_);
		std::cout << "Prefix: " << this->get_prefix() << '\n';
	}

	private:
	SeqanSAIter* seqan_sa_iter;
	int extra_steps_;
};
