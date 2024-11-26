mergeHeap: main.cpp
	g++ main.cpp -o mergeHeap

clean:
	rm ./mergeHeap

run: mergeHeap
	./mergeHeap
