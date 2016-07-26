#!/usr/bin/env bash
# vim: set noexpandtab tabstop=2:

rpl -R 'refStart_pos' 'start_pos_in_ref' src/
rpl -R 'refEnd_pos' 'end_pos_in_ref' src/
rpl -R 'queryEnd_pos' 'end_pos_in_query' src/
rpl -R 'queryStart_pos' 'start_pos_in_query' src/
