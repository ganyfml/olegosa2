// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <WordChunk.hpp>

using namespace std;

int main(int, char** argc)
{
	int wordChunkID1 = 1;
	WordChunk w1 {wordChunkID1};
	w1.set_colinearity(atoi(argc[1]));
	w1.set_refStartIndex(atoi(argc[2]));
	WordChunkPtr w1ptr = make_shared<WordChunk>(w1);

	int wordChunkID2 = 2;
	WordChunk w2 {wordChunkID2};
	w2.set_colinearity(atoi(argc[3]));
	w2.set_refStartIndex(atoi(argc[4]));
	WordChunkPtr w2ptr = make_shared<WordChunk>(w2);
	
	cout << compare_wordChunks(w1ptr, w2ptr) << endl;
}
