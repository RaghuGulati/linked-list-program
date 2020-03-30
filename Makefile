.PHONY: solution1 run_solution1 1a solution1/1a build clean

build: solution1

solution1: 1a

1a: solution1/1a

solution1/1a: solution1/1a/a4q1aint solution1/1a/a4q1achar

solution1/1a/a4q1aint: solution1/1a/a4q1a_int.c
	gcc $^ -o $@

solution1/1a/a4q1achar: solution1/1a/a4q1a_char.c
	gcc $^ -o $@

run_solution1:
<<<<<<< HEAD
<<<<<<< HEAD
	@cd solution1/1a && chmod +x a4q1aint && ./a4q1aint cmd1.txt
	@cd solution1/1a && chmod +x a4q1achar && ./a4q1achar cmd2.txt
=======
	@cd solution1/1a && chmod +x a4q1aint && ./a4q1aint cmd.txt
	@cd solution1/1a && chmod +x a4q1achar && ./a4q1achar cmd.txt
>>>>>>> fd32115b154c7854c5d4555f8b15a669fa33fd94
=======
	@cd solution1/1a && chmod +x a4q1aint && ./a4q1aint cmd1.txt
	@cd solution1/1a && chmod +x a4q1achar && ./a4q1achar cmd2.txt
>>>>>>> dcd3ced3ac321b7105a6c5aae6a164354d18248b

clean:
	rm solution1/1a/a4q1aint solution1/1a/a4q1achar
