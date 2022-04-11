#(CC) = gcc

graph:
	$(CC) main.c points.c bfs.c dijkstra.c gen.c -o graph

debug:
	$(CC) -g main.c points.c bfs.c dijkstra.c gen.c -o graph



clean:
	rm *.o graph