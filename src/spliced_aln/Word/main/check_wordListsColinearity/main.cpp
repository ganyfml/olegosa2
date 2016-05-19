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
	
	int wordID3 = 3;
	Word word3 {wordID3};
	word3.ref_pos = atoi(argc[3]);
	WordPtr word3ptr = make_shared<Word>(word3);
	
	int wordID4 = 4;
	Word word4 {wordID4};
	word4.ref_pos = atoi(argc[4]);
	WordPtr word4ptr = make_shared<Word>(word4);

	list<WordPtr> wordptr_list;
	wordptr_list.push_back(word1ptr);	
	wordptr_list.push_back(word2ptr);	
	wordptr_list.push_back(word3ptr);	
	wordptr_list.push_back(word4ptr);	

	cout << check_wordListsColinearity(wordptr_list) << endl;
}
