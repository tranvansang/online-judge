mkdir -p build
g++ gen.cpp -o build/gen
g++ bf.cpp -o build/bf
g++ main.cpp -o build/main

for ((i=0;i<100;i++)); do
  inp=$(./build/gen)
  out=$(echo "${inp}" | ./build/bf)
  ans=$(echo "${inp}" | ./build/main)
#  echo "${out}"
#  echo "${ans}"
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
