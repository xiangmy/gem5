
NAME L2_SIZE #LINEAR READ/WRITE? ACCESS_SIZE ADDR-RANGE STATS_FILE

test1.cfg 512B 2  1READ/1WRITE 8B 0-2048 stats1.txt

test1.cfg 1kB 2  1READ/1WRITE 8B 0-2048 stats2.txt

test1.cfg 2kB 2  1READ/1WRITE 8B 0-8192 stats3.txt

test1.cfg 2kB 2  1READ/1WRITE 8B 0-8192 stats4.txt

test1.cfg 4kB 2  1READ/1WRITE 8B 0-2048 stats4_2.txt #no evicts, just warmup

test2.cfg 512B 2  1READ/1WRITE 16B 0-2048 stats5.txt

test6.cfg 512B 3 1READ/1READ/1READ 16B 0-511/0-127/512-1023 stats14.txt #LRU,read, re-reference,new reads
				       0-511/128-511/512-1023  stats15.txt 
				       0-511/128-511/512-1023  stats16.txt #FIFO
				       0-511/128-511/512-1023  stats17.txt #MRU
				       0-511/128-511/512-1023  stats18.txt #Random why are there tags greater than 8 when addresses till only 0x200 have been accessed
				       0-511/128-511/512-1023  stats19.txt #LFU good: no tag from 0-127(decimal) is being replaced, but a) why are there tags greater than 8 (same as above) 																	     b) what is the pattern in the tag access?
				       0-511/0-127/512-1023    stats_secondchance.txt #second chance
test7.cfg 512B 5 R/R/R/R/R 16B	       0-511/0-127/0-127/128-511/512-1023 stats20.txt #LFU (problems Same as above)
test8.cfg 512B 2 R/R 16B   0-511/512-575 stats_treeplru.txt #TreePLRU
test9.cfg 512B 5 R/R/R/R/R 64B 0-1023/0-1023/0-1023/0-1023/0-1023 stats_lip.txt #LIP working ok. Does not allow (b1, b2, ..., b8) to enter non-LRU position
																  stats_bip.txt #BIP working ok. Allows blocks in (b1, b2, ..., b8) to enter MRU position with a btp=3%.   








