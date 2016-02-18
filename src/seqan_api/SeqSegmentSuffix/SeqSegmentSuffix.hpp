// vim: set noexpandtab tabstop=2:

#pragma once

#include <iostream>

class SeqSegmentSuffix
{
	public:
		SeqSegmentSuffix(const void *);
		~SeqSegmentSuffix();
		const void* get_pointer() const { return impl_; }
	private:
		void * impl_; 
};

std::ostream& operator<<(std::ostream& os, const SeqSegmentSuffix& obj);
