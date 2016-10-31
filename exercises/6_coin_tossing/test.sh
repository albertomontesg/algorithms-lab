NAME=coin_tossing

echo "Running tests"
for input in testsets/*.in ; do
    echo $input
    time ./bin/$NAME < $input > $input.tmp ;
done
for output in testsets/*.out ; do
    echo $output
    diff $output ${output%.out}.in.tmp ;
done
rm testsets/*.in.tmp
