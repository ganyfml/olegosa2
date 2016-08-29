// vim: set noexpandtab tabstop=2:

#include "../../OutputWriter.hpp"

using namespace std;

int main()
{
	SAMWritter sam_writter;

	CharString ref_name_1(string("chr1"));
	long ref_length_1 = 12345;
	sam_writter.append_header_ref_info(ref_name_1, ref_length_1);
	CharString ref_name_2(string("chr2"));
	long ref_length_2 = 123456;
	sam_writter.append_header_ref_info(ref_name_2, ref_length_2);

	sam_writter.write_header();
}
