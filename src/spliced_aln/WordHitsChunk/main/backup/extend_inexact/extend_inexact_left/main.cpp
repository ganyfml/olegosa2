// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <WordChunk.hpp>

using namespace std;

int main(int, char** argc)
{
	SeqString query = "TTTTTTTTTTTTT";
	SeqString ref = "GTGTTTTGTG";
	int wordID = 0;
	Word word_test {wordID};
	word_test.sequence = "TT";
	word_test.query_index = 5;
	word_test.ref_index = 4;
	word_test.word_length = 2;

	int wordChunkID = 1;
	WordChunk wordChunk_test { wordChunkID };
	wordChunk_test.add_word(make_shared<Word>(word_test));	
	wordChunk_test.eval();
	wordChunk_test.display();
	bool stop_atNegativeScore = true;
	long lpca = 100;
	wordChunk_test.extend_inexact_left(query, ref, stop_atNegativeScore, lpca);
	wordChunk_test.display();
}
