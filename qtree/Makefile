all: qtree qtree-sol test

qtree: qtree.cc
	g++ qtree.cc -o qtree

qtree-sol: qtree-sol.cc
	g++ qtree-sol.cc -o qtree-sol

gen: gen.cc
	g++ gen.cc -o gen

.PHONY: test
test:
	cp 1.inp input
	./qtree <input >output
	./qtree-sol <input >solution
	diff output solution
	cp 2.inp input
	./qtree <input >output
	./qtree-sol <input >solution
	diff output solution
	cp 3.inp input
	./qtree <input >output
	./qtree-sol <input >solution
	diff output solution
	cp 4.inp input
	./qtree <input >output
	./qtree-sol <input >solution
	diff output solution
	cp 5.inp input
	./qtree <input >output
	./qtree-sol <input >solution
	diff output solution
	cp 6.inp input
	./qtree <input >output
	./qtree-sol <input >solution
	diff output solution
	cp 7.inp input
	./qtree <input >output
	./qtree-sol <input >solution
	diff output solution
	cp 8.inp input
	./qtree <input >output
	./qtree-sol <input >solution
	diff output solution
	cp 9.inp input
	./qtree <input >output
	./qtree-sol <input >solution
	diff output solution
	cp 27.inp input
	./qtree <input >output
	./qtree-sol <input >solution
	diff output solution

.PHONY: run
run: qtree
	./qtree <input >output

.PHONY: gen-and-test
gen-and-test: gen qtree qtree-sol
	./gen >input
	./qtree <input >output
	./qtree-sol <input >solution
	diff output solution
