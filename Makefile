#(CC) = gcc

graph:
	$(CC) main.c points.c bfs.c dijkstra.c gen.c -o graph

debug:
	$(CC) -g main.c points.c bfs.c dijkstra.c gen.c -o graph
test: test-bfs test-n-spoj test-dijkstra
test-bfs:
	@./graph --input tests/graf_test_1 --int > tests/test_1_result 2>&1
	@res=$$(diff -w tests/test_1_exp_result tests/test_1_result);\
	if [ -z "$$res" ];\
		then\
			echo "test bfs ok";\
		else\
			echo "test bfs blad:";\
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

test-dijkstra:
	@./graph --input tests/graf_test_3 --route 1 24 > tests/test_3_result 2>&1
	@res=$$(diff -w tests/test_3_exp_result tests/test_3_result);\
	if [ -z "$$res" ];\
		then\
			echo "test dijkstra ok";\
		else\
			echo "test dijkstra blad:";\
			echo $$res ;\
		fi\



clean:
	rm *.o graph
