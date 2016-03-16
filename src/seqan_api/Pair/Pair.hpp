// vim: set noexpandtab tabstop=2:

#pragma once

class Pair
{
	public:
		Pair(unsigned first, unsigned second);
		~Pair();
		unsigned first() const;
		unsigned second() const;

	private:
		void* impl_;
};
