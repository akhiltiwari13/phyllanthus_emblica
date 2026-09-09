# Each problem builds twice: practice_* is the stub you solve against the clock
# (it compiles, and prints TESTS FAILED until you finish it), solution_* is the
# worked reference. Both run the same test block.
set(PE_PRACTICE_PROBLEMS
	order_book
	feed_arbitrator
	object_pool
	timer_wheel
	fixed_point_price
	lru_cache)

foreach(problem ${PE_PRACTICE_PROBLEMS})
	add_executable(practice_${problem} ${problem}.cpp)
	add_executable(solution_${problem} solutions/${problem}.cpp)
endforeach()
