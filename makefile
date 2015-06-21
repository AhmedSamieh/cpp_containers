all: BSTNode.h
	g++ priority_queue.cpp -o pq

clean:
	rm -rf pq
