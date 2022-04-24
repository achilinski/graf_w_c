#(CC) = gcc

graph:
	$(CC) main.c points.c bfs.c dijkstra.c gen.c -o graph

debug:
	$(CC) -g main.c points.c bfs.c dijkstra.c gen.c -o graph

test:
	./graph --input graf_test_1 --route 1 10 --int > tests/test_1_result 2>&1
	@res=$$(diff -w tests/test_1_exp_result tests/test_1_result);\
	if [ -z "$$res" ];\
		then\
			echo "Test 1 OK";\
		else\
			echo "Test1 BLAD:";\
			echo $$res ;\
		fi\



clean:
	rm *.o graph