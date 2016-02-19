// vim: set noexpandtab tabstop=2:

#pragma once

#include <iostream>

class SeqSegmentPrefix
{
	public:
		SeqSegmentPrefix(const void *);
		~SeqSegmentPrefix();
		void* get_pointer() const { return impl_; }
	private:
		void* impl_; 
};

std::ostream& operator<<(std::ostream& os, const SeqSegmentPrefix& obj);
