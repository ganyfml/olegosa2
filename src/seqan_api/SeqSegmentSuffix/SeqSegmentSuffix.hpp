// vim: set noexpandtab tabstop=2:

#pragma once

class SeqSegmentSuffix
{
	public:
		SeqSegmentSuffix(const void *);
		~SeqSegmentSuffix();
		void display();
	private:
		void * impl_; 
};
