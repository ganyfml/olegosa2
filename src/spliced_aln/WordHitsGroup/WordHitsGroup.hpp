// vim: set noexpandtab tabstop=2:

#pragma once

#include <spliced_aln/Word.hpp>
#include <spliced_aln/WordHit.hpp>
#include <iostream>
#include <list>

struct WordHitsGroup
{
	WordHitsGroup(int group_id) : id(group_id) {}

	void display()
	{
		std::cout << "Group ID: " << id << ", score: " << score << std::endl;
		std::cout << "Including Hit: ";
		for(auto iter = wordhits.begin(); iter != wordhits.end(); ++iter)
		{
			printf("%d, ", (*iter)->word_id);
		}
		printf("\n");
	}

	int id;
	double score;
	std::list<WordHitPtr> wordhits;
};

typedef std::shared_ptr<WordHitsGroup> WordHitsGroupPtr;

bool compare_wordHitsGroupByScore(const WordHitsGroupPtr group1, const WordHitsGroupPtr group2);
