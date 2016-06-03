// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <WordChunk.hpp>

using namespace std;

int main(int, char** argc)
{
	int wordID = 0;
	Word word1 {wordID};
	word1.word_length = 5;
	word1.strand = 1;
	word1.query_index = 7;
	word1.ref_index = 80;
	WordPtr word1ptr = make_shared<Word>(word1);

	Word word2 {1};
	word2.word_length = 5;
	word2.strand = 1;
	word2.query_index = 3;
	word2.ref_index = 80;
	WordPtr word2ptr = make_shared<Word>(word2);

	Word word3 {3};
	word3.word_length = 5;
	word3.strand = 1;
	word3.query_index = 32;
	word3.ref_index = 82;
	WordPtr word3ptr = make_shared<Word>(word3);

	int wordChunkID = 1;
	WordChunk wordChunk(wordChunkID);
	wordChunk.add_word(word3ptr);
	wordChunk.add_word(word2ptr);
	wordChunk.add_word(word1ptr);

	wordChunk.eval();
	wordChunk.display();
}
