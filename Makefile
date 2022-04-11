#(CC) = gcc

graph:
	$(CC) main.c points.c bfs.c dijkstra.c -o graph

clean:
	rm *.o graph