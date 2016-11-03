NAME=inball

echo "Running tests"
for input in testsets/*.in ; do
    echo $input
    time ./$NAME.o < $input > $input.tmp ;
done
for output in testsets/*.out ; do
    echo $output
    diff $output ${output%.out}.in.tmp ;
done
rm testsets/*.in.tmp
