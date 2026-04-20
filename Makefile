CXX = g++
CXXFLAGS = -std=c++17 -Wall -I.

SRCS = main.cpp parser/parser.cpp core/warp_simulator.cpp analyzer/performance_analyzer.cpp analyzer/suggestion_engine.cpp
OBJS = $(SRCS:.cpp=.o)

TARGET = gpu_simulator

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
	rm -rf output/*.json output/*.png

run-good: $(TARGET)
	mkdir -p output
	./$(TARGET) input/vector_add.txt
	python3 ai/analyze_metrics.py

run-bad: $(TARGET)
	mkdir -p output
	./$(TARGET) input/divergent_kernel.txt
	python3 ai/analyze_metrics.py
