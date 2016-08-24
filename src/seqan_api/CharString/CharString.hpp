// vim: set noexpandtab tabstop=2:

#pragma once

#include <memory>
#include <string>

class CharString
{
	public:
		CharString();
		CharString(const CharString& that);
		CharString(const std::string& id);
		~CharString();
		const void* get_pointer() const { return impl_; }
		void set_pointer(void* ptr) { impl_ = ptr; }

		CharString& operator=(const CharString& other);

	private:
		void* impl_;
};

std::ostream& operator<<(std::ostream& os, const CharString& obj);

typedef std::shared_ptr<CharString> CharStringPtr;
