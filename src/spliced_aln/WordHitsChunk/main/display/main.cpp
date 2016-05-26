// vim: set noexpandtab tabstop=2:

#include <iostream>
#include "../../WordHitsChunk.hpp"

using namespace std;

int main(int, char** argc)
{
	int chunk_id = 0;
	WordHitsChunk w1(chunk_id);
	w1.display();
}
