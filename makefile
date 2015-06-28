all: KeyValBSTNode.h
	g++ priority_queue.cpp -o pq
	g++ priority_queue2.cpp -o pq2 -std=gnu++11
	g++ BST.cpp -o bst

clean:
	rm -rf pq pq2 bst
