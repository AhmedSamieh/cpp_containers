all: KeyValBSTNode.h
	g++ priority_queue.cpp -o pq --std=c++14
	g++ test.cpp -o test --std=c++14

clean:
	rm -rf pq bst
