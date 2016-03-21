// vim: set noexpandtab tabstop=2:

#pragma once

class SARange
{
	public:
		SARange(unsigned first, unsigned second);
		~SARange();
		unsigned low() const;
		unsigned high() const;

	private:
		void* impl_;
};
