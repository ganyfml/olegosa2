// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <spliced_aln/Word.hpp>

using namespace std;

int main(int argv, char** argc)
{
	int wordID1 = 1;
	Word word1 {wordID1};
	word1.ref_pos = atoi(argc[1]);
	WordPtr word1ptr = make_shared<Word>(word1);

	int wordID2 = 2;
	Word word2 {wordID2};
	word2.ref_pos = atoi(argc[2]);
	WordPtr word2ptr = make_shared<Word>(word2);

	word1ptr->display();
	word2ptr->display();
	cout << endl << "Result: " << compare_wordsByRefPos(word1ptr, word2ptr) << endl;
}
