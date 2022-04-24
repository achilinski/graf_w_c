#(CC) = gcc

graph:
	$(CC) main.c points.c bfs.c dijkstra.c gen.c -o graph

debug:
	$(CC) -g main.c points.c bfs.c dijkstra.c gen.c -o graph
test-all: test test-n-spoj
test:
	@./graph --input tests/graf_test_1 --route 1 10 --int > tests/test_1_result 2>&1
	@res=$$(diff -w tests/test_1_exp_result tests/test_1_result);\
	if [ -z "$$res" ];\
		then\
			echo "test 1 ok";\
		else\
			echo "test 1 blad:";\
			echo $$res ;\
		fi\

test-n-spoj:
	@./graph --input tests/graf_test_2 --int > tests/test_2_result 2>&1
	@res=$$(diff -w tests/test_2_exp_result tests/test_2_result);\
	if [ -z "$$res" ];\
		then\
			echo "test graf nie spojny ok";\
		else\
			echo "test graf nie spojny blad:";\
			echo $$res ;\
		fi\




clean:
	rm *.o graph
