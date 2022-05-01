.PHONY: main

main: main.cpp
	g++ main.cpp
	./a.out <0.inp

ans: ans.cpp
	g++ ans.cpp
	./a.out <0.inp

gen: gen.cpp
	g++ gen.cpp
	./a.out

test: gen.cpp ans.cpp main.cpp
	mkdir -p build
	g++ gen.cpp -o build/gen
	g++ ans.cpp -o build/ans
	g++ main.cpp -o build/main

	for ((i=0;i<100;i++)); do
	  inp=$(./build/gen)
	  out=$(echo "${inp}" | ./build/ans)
	  ans=$(echo "${inp}" | ./build/main)
	  if [[ ${out} != ${ans} ]]; then
		echo "${i}: failed"
		echo "out: ${out}"
		echo "ans: ${ans}"
		echo "${inp}" > gen.inp
		break
	  else
		echo "${i}: ok"
	  fi
	done
