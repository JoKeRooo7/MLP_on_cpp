COMPILATOR = gcc
COMPILATOR_FLAGS = -Wall -Werror -Wextra -g
STANDART = -std=c++17
LIBS = -lstdc++ -lgtest -lgtest_main
LINUX_FLAGS = -lrt -lm -lsubunit -lpthread
OUTPUT_FILE = test_back.out

PERCEPTRON_PATH = ../src/model/perceptron/graph_model/*.cc
LAYERS_PATH = ../src/model/perceptron/graph_model/layers/*.cc
NEURON_PATH = ../src/model/perceptron/graph_model/layers/neurons/*.cc
READ_FILE_PATH = ../src/model/csv_reader/*.cc

OS := $(shell uname)
ifeq ($(OS), Linux)
	NEED_LIBS = $(LIBS) $(LINUX_FLAGS)
else
	NEED_LIBS = $(LIBS)
endif

ACTION = $(COMPILATOR) $(COMPILATOR_FLAGS) $(STANDART)

all: rebuild

test:
# git lfs pull -I ../datasets/ --include="*.zip" --xargs="unzip -d ../datasets/"
	git lfs pull ../datasets 
	unzip ../datasets/emnist-letters.zip -d ../../datasets
	$(ACTION) test_perceptron/*.cc test_read_file/*.cc test_neurons/*.cc  test_layers/*.cc $(PERCEPTRON_PATH) $(READ_FILE_PATH) $(NEURON_PATH) $(LAYERS_PATH)  -o $(OUTPUT_FILE) $(NEED_LIBS)
	chmod +x $(OUTPUT_FILE)
	make clean_other_test
	./$(OUTPUT_FILE)

testing_read_file:
	$(ACTION) test_read_file/*.cc $(READ_FILE_PATH) -o test_r $(NEED_LIBS)
	./test_r

testing_neurons:
	$(ACTION) test_neurons/*.cc  $(NEURON_PATH) -o test_n $(NEED_LIBS)
	./test_n

testing_layers:
	$(ACTION) test_layers/*.cc $(LAYERS_PATH) $(NEURON_PATH) -o test_l $(NEED_LIBS)
	./test_l

testing_perceptron:
	$(ACTION) test_perceptron/*.cc $(READ_FILE_PATH) $(PERCEPTRON_PATH) $(LAYERS_PATH) $(NEURON_PATH) -o test_p $(NEED_LIBS)
	./test_p

clean_other_test:
	rm -rf test_n test_r test_l test_p

clear: clean_other_test
	rm -rf *.dSYM
	rm -rf $(OUTPUT_FILE)

clean: clear

rebuild: clean test
 
