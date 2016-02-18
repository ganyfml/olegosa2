// vim: set noexpandtab tabstop=2:

#pragma once

#include <iostream>

class SeqSegmentInfix
{
	public:
		SeqSegmentInfix(const void *);
		~SeqSegmentInfix();
		const void* get_pointer() const { return impl_; }
	private:
		void * impl_; 
};

std::ostream& operator<<(std::ostream& os, const SeqSegmentInfix& obj);
