all: KeyValBSTNode.h
	g++ priority_queue.cpp -o pq
	g++ priority_queue2.cpp -o pq2 -std=c++11
	g++ test.cpp -o test --std=c++11

clean:
	rm -rf pq pq2 bst
