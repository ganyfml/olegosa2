// vim: set noexpandtab tabstop=2:

#pragma once

#include <memory>
#include <string>
#include <seqan_api/SeqString.hpp>
#include <seqan_api/CharString.hpp>

class CharStringSet
{
	public:
		CharStringSet();
		CharStringSet(const CharStringSet& that);
		~CharStringSet();
		long get_length() const;
		const void* get_pointer() const { return impl_; }
		void set_pointer(void* ptr) { impl_ = ptr; }

		CharString operator[](long idx) const;

		CharStringSet& operator=(const CharStringSet& other);

	private:
		void* impl_;
};

typedef std::shared_ptr<CharStringSet> CharStringSetPtr;
