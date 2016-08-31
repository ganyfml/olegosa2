// vim: set noexpandtab tabstop=2:

#pragma once

#include <nonspliced_aln/StateEntry.hpp>
#include <nonspliced_aln/alnNonspliceOpt.hpp>

class priority_StateEntry_array
{
	public:
		priority_StateEntry_array(const alnNonspliceOpt& opt)
		{
			int max_score = opt.max_gapOpen * opt.score_gapOpen
				+ opt.max_gapExt * opt.score_gapExt
				+ opt.max_mismatch * opt.score_mismatch;

			stateEntry_array = std::vector<std::list<StateEntry>>(max_score + 1);
		}

		bool pop_best(StateEntry& best_entry, int max_score)
		{
			for(int i = 0; i <= max_score && i < (int)stateEntry_array.size(); ++i)
			{
				if(stateEntry_array[i].size() != 0)
				{
					best_entry = stateEntry_array[i].front();
					stateEntry_array[i].pop_front();
					return true;
				}
			}
			return false;
		}

		void push(const StateEntry& new_entry, const alnNonspliceOpt& opt)
		{
			stateEntry_array[new_entry.get_score(opt)].push_front(new_entry);
		}

		void display() const
		{
			std::cout << "priority_StateEntry_array with the size of " << stateEntry_array.size() << std::endl;
			printf("Entry in score: \n");
			for(unsigned i = 0; i < stateEntry_array.size(); ++i)
			{
				if(stateEntry_array[i].size())
					printf("%u, ", i);
			}
			printf("\n");
		}

	private:
		std::vector<std::list<StateEntry>> stateEntry_array;
};
