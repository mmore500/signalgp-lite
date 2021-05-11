TEST_NAMES += changing-enviroment

EXPECTED_FITNESS := 256

TO_ROOT := $(shell git rev-parse --show-cdup)

include $(TO_ROOT)/tests/MaketemplateRunning

test-%: %.cpp ../third-party/Catch/single_include/catch2/catch.hpp
	$(CXX) $(FLAGS) $< -o $@.out
	# execute test
	./$@.out -LOGGING 1 -UPDATES 501
	python3 ../check_csv.py $(EXPECTED_FITNESS)
