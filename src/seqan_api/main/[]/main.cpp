// vim: set noexpandtab tabstop=2:
#include <seqan_api.hpp>

using namespace std;

int main(int argc, char ** argv)
{
	string ref_file = argv[1];
	string index_file = argv[2];
	Seq ref(ref_file, index_file);

	int chr_num = 0;
	ref.create_SA(chr_num);
	ref.load_SA();

	char one = ref[3];

	cout << one << endl;
}
