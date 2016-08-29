// vim: set noexpandtab tabstop=2:

#include "../../../OutputWriter.hpp"

int main()
{
	SAMWritter sam_writter("./test.sam");
	sam_writter.write_header();
}
