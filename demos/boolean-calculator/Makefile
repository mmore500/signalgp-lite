TEST_NAMES += boolean-calculator

EXPECTED_FITNESS := 3

TO_ROOT := $(shell git rev-parse --show-cdup)

include $(TO_ROOT)/tests/MaketemplateRunning

test-%: %.cpp ../third-party/Catch/single_include/catch2/catch.hpp
	$(CXX) $(FLAGS) -Ithird-party/ $< -o $@.out
	# execute test
	./$@.out -LOGGING 1 -UPDATES 501 -ENVIROMENT_STATES 2 -NUMBER_RESPONSES 2
	python3 ../check_csv.py $(EXPECTED_FITNESS) 1.csv
