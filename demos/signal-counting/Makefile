TEST_NAMES += signal-counting

EXPECTED_FITNESS := 4

TO_ROOT := $(shell git rev-parse --show-cdup)

include $(TO_ROOT)/tests/MaketemplateRunning

test-%: %.cpp ../third-party/Catch/single_include/catch2/catch.hpp
	$(CXX) $(FLAGS) $< -o $@.out
	# execute test
	./$@.out -LOGGING 1 -UPDATES 250 -ENVIROMENT_STATES 2 -NUMBER_RESPONSES 2
	python ../check_csv.py $(EXPECTED_FITNESS)