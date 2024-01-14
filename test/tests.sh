#!/bin/bash

# Test1. Test Arithmetic operations
in_file="./test1.txt"
asm_file="./asm.txt"
out_file="./out.txt"
expected_out_file="./test1_expected.txt"
error_file="./error.txt"
name="arithmetic operations"
../compiler $in_file $asm_file 2>$error_file
echo -n "TEST: $name ..."
echo "654321 3" | ../vm/maszyna-wirtualna-cln $asm_file | sed 's/? //g' | grep ">" | sed 's/> //g' >$out_file
diff_res=$(diff $out_file $expected_out_file)
if [ -s $error_file ] || [ "$diff_res" ]; then
    echo -e " \033[0;31mFAILED\033[0m"
else
    echo -e " \033[0;32mPASSED\033[0m"
fi

rm -f $asm_file
rm -f $out_file
rm -f $error_file

# Test2. Array declaring and operations
in_file="./test2.txt"
asm_file="./asm.txt"
out_file="./out.txt"
expected_out_file="./test2_expected.txt"
error_file="./error.txt"
name="array declaring and operations"
../compiler $in_file $asm_file 2>$error_file
echo -n "TEST: $name ..."
echo "654321 3" | ../vm/maszyna-wirtualna-cln $asm_file | sed 's/? //g' | grep ">" | sed 's/> //g' >$out_file
diff_res=$(diff $out_file $expected_out_file)
if [ -s $error_file ] || [ "$diff_res" ]; then
    echo -e " \033[0;31mFAILED\033[0m"
else
    echo -e " \033[0;32mPASSED\033[0m"
fi

rm -f $asm_file
rm -f $out_file
rm -f $error_file

# Test3. Conditions
in_file="./test3.txt"
asm_file="./asm.txt"
out_file="./out.txt"
expected_out_file="./test3_expected.txt"
error_file="./error.txt"
name="conditions"
../compiler $in_file $asm_file 2>$error_file
echo -n "TEST: $name ..."
echo "654321 3" | ../vm/maszyna-wirtualna-cln $asm_file | sed 's/? //g' | grep ">" | sed 's/> //g' >$out_file
diff_res=$(diff $out_file $expected_out_file)
if [ -s $error_file ] || [ "$diff_res" ]; then
    echo -e " \033[0;31mFAILED\033[0m"
else
    echo -e " \033[0;32mPASSED\033[0m"
fi

rm -f $asm_file
rm -f $out_file
rm -f $error_file

# Test4. Loops
in_file="./test4.txt"
asm_file="./asm.txt"
out_file="./out.txt"
expected_out_file="./test4_expected.txt"
error_file="./error.txt"
name="loops"
../compiler $in_file $asm_file 2>$error_file
echo -n "TEST: $name ..."
echo "654321 3" | ../vm/maszyna-wirtualna-cln $asm_file | sed 's/? //g' | grep ">" | sed 's/> //g' >$out_file
diff_res=$(diff $out_file $expected_out_file)
if [ -s $error_file ] || [ "$diff_res" ]; then
    echo -e " \033[0;31mFAILED\033[0m"
else
    echo -e " \033[0;32mPASSED\033[0m"
fi

rm -f $asm_file
rm -f $out_file
rm -f $error_file

# Test5. TBN
in_file="./test5.txt"
asm_file="./asm.txt"
out_file="./out.txt"
expected_out_file="./test5_expected.txt"
error_file="./error.txt"
name="TBN"
../compiler $in_file $asm_file 2>$error_file
echo -n "TEST: $name ..."
echo "654321 3" | ../vm/maszyna-wirtualna-cln $asm_file | sed 's/? //g' | grep ">" | sed 's/> //g' >$out_file
diff_res=$(diff $out_file $expected_out_file)
if [ -s $error_file ] || [ "$diff_res" ]; then
    echo -e " \033[0;31mFAILED\033[0m"
else
    echo -e " \033[0;32mPASSED\033[0m"
fi

rm -f $asm_file
rm -f $out_file
rm -f $error_file

# Test6. TBN
in_file="./test6.txt"
asm_file="./asm.txt"
out_file="./out.txt"
expected_out_file="./test6_expected.txt"
error_file="./error.txt"
name="TBN"
../compiler $in_file $asm_file 2>$error_file
echo -n "TEST: $name ..."
echo "654321 3" | ../vm/maszyna-wirtualna-cln $asm_file | sed 's/? //g' | grep ">" | sed 's/> //g' >$out_file
diff_res=$(diff $out_file $expected_out_file)
if [ -s $error_file ] || [ "$diff_res" ]; then
    echo -e " \033[0;31mFAILED\033[0m"
else
    echo -e " \033[0;32mPASSED\033[0m"
fi

rm -f $asm_file
rm -f $out_file
rm -f $error_file

# Test7. TBN
in_file="./test7.txt"
asm_file="./asm.txt"
out_file="./out.txt"
expected_out_file="./test7_expected.txt"
error_file="./error.txt"
name="TBN"
../compiler $in_file $asm_file 2>$error_file
echo -n "TEST: $name ..."
echo "654321 3" | ../vm/maszyna-wirtualna-cln $asm_file | sed 's/? //g' | grep ">" | sed 's/> //g' >$out_file
diff_res=$(diff $out_file $expected_out_file)
if [ -s $error_file ] || [ "$diff_res" ]; then
    echo -e " \033[0;31mFAILED\033[0m"
else
    echo -e " \033[0;32mPASSED\033[0m"
fi

rm -f $asm_file
rm -f $out_file
rm -f $error_file

# Test8. TBN
in_file="./test8.txt"
asm_file="./asm.txt"
out_file="./out.txt"
expected_out_file="./test8_expected.txt"
error_file="./error.txt"
name="TBN"
../compiler $in_file $asm_file 2>$error_file
echo -n "TEST: $name ..."
echo "654321 3" | ../vm/maszyna-wirtualna-cln $asm_file | sed 's/? //g' | grep ">" | sed 's/> //g' >$out_file
diff_res=$(diff $out_file $expected_out_file)
if [ -s $error_file ] || [ "$diff_res" ]; then
    echo -e " \033[0;31mFAILED\033[0m"
else
    echo -e " \033[0;32mPASSED\033[0m"
fi

rm -f $asm_file
rm -f $out_file
rm -f $error_file

# Test9. TBN
in_file="./test9.txt"
asm_file="./asm.txt"
out_file="./out.txt"
expected_out_file="./test9_expected.txt"
error_file="./error.txt"
name="TBN"
../compiler $in_file $asm_file 2>$error_file
echo -n "TEST: $name ..."
echo "654321 3" | ../vm/maszyna-wirtualna-cln $asm_file | sed 's/? //g' | grep ">" | sed 's/> //g' >$out_file
diff_res=$(diff $out_file $expected_out_file)
if [ -s $error_file ] || [ "$diff_res" ]; then
    echo -e " \033[0;31mFAILED\033[0m"
else
    echo -e " \033[0;32mPASSED\033[0m"
fi

rm -f $asm_file
rm -f $out_file
rm -f $error_file

# Test10. TBN
in_file="./test10.txt"
asm_file="./asm.txt"
out_file="./out.txt"
expected_out_file="./test10_expected.txt"
error_file="./error.txt"
name="TBN"
../compiler $in_file $asm_file 2>$error_file
echo -n "TEST: $name ..."
echo "654321 3" | ../vm/maszyna-wirtualna-cln $asm_file | sed 's/? //g' | grep ">" | sed 's/> //g' >$out_file
diff_res=$(diff $out_file $expected_out_file)
if [ -s $error_file ] || [ "$diff_res" ]; then
    echo -e " \033[0;31mFAILED\033[0m"
else
    echo -e " \033[0;32mPASSED\033[0m"
fi

rm -f $asm_file
rm -f $out_file
rm -f $error_file

# Test11. TBN
in_file="./test11.txt"
asm_file="./asm.txt"
out_file="./out.txt"
expected_out_file="./test11_expected.txt"
error_file="./error.txt"
name="TBN"
../compiler $in_file $asm_file 2>$error_file
echo -n "TEST: $name ..."
echo "654321 3" | ../vm/maszyna-wirtualna-cln $asm_file | sed 's/? //g' | grep ">" | sed 's/> //g' >$out_file
diff_res=$(diff $out_file $expected_out_file)
if [ -s $error_file ] || [ "$diff_res" ]; then
    echo -e " \033[0;31mFAILED\033[0m"
else
    echo -e " \033[0;32mPASSED\033[0m"
fi

rm -f $asm_file
rm -f $out_file
rm -f $error_file

# Test12. TBN
in_file="./test12.txt"
asm_file="./asm.txt"
out_file="./out.txt"
expected_out_file="./test12_expected.txt"
error_file="./error.txt"
name="TBN"
../compiler $in_file $asm_file 2>$error_file
echo -n "TEST: $name ..."
echo "654321 3" | ../vm/maszyna-wirtualna-cln $asm_file | sed 's/? //g' | grep ">" | sed 's/> //g' >$out_file
diff_res=$(diff $out_file $expected_out_file)
if [ -s $error_file ] || [ "$diff_res" ]; then
    echo -e " \033[0;31mFAILED\033[0m"
else
    echo -e " \033[0;32mPASSED\033[0m"
fi

rm -f $asm_file
rm -f $out_file
rm -f $error_file

# Test13. TBN
in_file="./test13.txt"
asm_file="./asm.txt"
out_file="./out.txt"
expected_out_file="./test13_expected.txt"
error_file="./error.txt"
name="TBN"
../compiler $in_file $asm_file 2>$error_file
echo -n "TEST: $name ..."
echo "654321 3" | ../vm/maszyna-wirtualna-cln $asm_file | sed 's/? //g' | grep ">" | sed 's/> //g' >$out_file
diff_res=$(diff $out_file $expected_out_file)
if [ -s $error_file ] || [ "$diff_res" ]; then
    echo -e " \033[0;31mFAILED\033[0m"
else
    echo -e " \033[0;32mPASSED\033[0m"
fi

rm -f $asm_file
rm -f $out_file
rm -f $error_file

# Test14. TBN
in_file="./test14.txt"
asm_file="./asm.txt"
out_file="./out.txt"
expected_out_file="./test14_expected.txt"
error_file="./error.txt"
name="TBN"
../compiler $in_file $asm_file 2>$error_file
echo -n "TEST: $name ..."
echo "654321 3" | ../vm/maszyna-wirtualna-cln $asm_file | sed 's/? //g' | grep ">" | sed 's/> //g' >$out_file
diff_res=$(diff $out_file $expected_out_file)
if [ -s $error_file ] || [ "$diff_res" ]; then
    echo -e " \033[0;31mFAILED\033[0m"
else
    echo -e " \033[0;32mPASSED\033[0m"
fi

rm -f $asm_file
rm -f $out_file
rm -f $error_file

# Test15. TBN
in_file="./test15.txt"
asm_file="./asm.txt"
out_file="./out.txt"
expected_out_file="./test15_expected.txt"
error_file="./error.txt"
name="TBN"
../compiler $in_file $asm_file 2>$error_file
echo -n "TEST: $name ..."
echo "654321 3" | ../vm/maszyna-wirtualna-cln $asm_file | sed 's/? //g' | grep ">" | sed 's/> //g' >$out_file
diff_res=$(diff $out_file $expected_out_file)
if [ -s $error_file ] || [ "$diff_res" ]; then
    echo -e " \033[0;31mFAILED\033[0m"
else
    echo -e " \033[0;32mPASSED\033[0m"
fi

rm -f $asm_file
rm -f $out_file
rm -f $error_file

# Test16. TBN
in_file="./test16.txt"
asm_file="./asm.txt"
out_file="./out.txt"
expected_out_file="./test16_expected.txt"
error_file="./error.txt"
name="TBN"
../compiler $in_file $asm_file 2>$error_file
echo -n "TEST: $name ..."
echo "654321 3" | ../vm/maszyna-wirtualna-cln $asm_file | sed 's/? //g' | grep ">" | sed 's/> //g' >$out_file
diff_res=$(diff $out_file $expected_out_file)
if [ -s $error_file ] || [ "$diff_res" ]; then
    echo -e " \033[0;31mFAILED\033[0m"
else
    echo -e " \033[0;32mPASSED\033[0m"
fi

rm -f $asm_file
rm -f $out_file
rm -f $error_file

# Test17. TBN
in_file="./test17.txt"
asm_file="./asm.txt"
out_file="./out.txt"
expected_out_file="./test17_expected.txt"
error_file="./error.txt"
name="TBN"
../compiler $in_file $asm_file 2>$error_file
echo -n "TEST: $name ..."
echo "654321 3" | ../vm/maszyna-wirtualna-cln $asm_file | sed 's/? //g' | grep ">" | sed 's/> //g' >$out_file
diff_res=$(diff $out_file $expected_out_file)
if [ -s $error_file ] || [ "$diff_res" ]; then
    echo -e " \033[0;31mFAILED\033[0m"
else
    echo -e " \033[0;32mPASSED\033[0m"
fi

rm -f $asm_file
rm -f $out_file
rm -f $error_file

# Test18. TBN
in_file="./test18.txt"
asm_file="./asm.txt"
out_file="./out.txt"
expected_out_file="./test18_expected.txt"
error_file="./error.txt"
name="TBN"
../compiler $in_file $asm_file 2>$error_file
echo -n "TEST: $name ..."
echo "654321 3" | ../vm/maszyna-wirtualna-cln $asm_file | sed 's/? //g' | grep ">" | sed 's/> //g' >$out_file
diff_res=$(diff $out_file $expected_out_file)
if [ -s $error_file ] || [ "$diff_res" ]; then
    echo -e " \033[0;31mFAILED\033[0m"
else
    echo -e " \033[0;32mPASSED\033[0m"
fi

rm -f $asm_file
rm -f $out_file
rm -f $error_file

# Error1. Error: Undeclared variable
in_file="./error1.txt"
out_file="./out.txt"
error_file="./error.txt"
expected_error_file="./error1_expected.txt"
name="Undeclared variable"
echo -n "TEST: $name ..."
../compiler $in_file $out_file 2>$error_file
diff_res=$(diff $error_file $expected_error_file)
if [ $? -eq 1 ] || [ "$diff_res" ]; then
    echo -e " \033[0;31mFAILED\033[0m"
else
    echo -e " \033[0;32mPASSED\033[0m"
fi

rm -f $out_file
rm -f $error_file

# Error2. Error: Unitialized variable
in_file="./error2.txt"
out_file="./out.txt"
error_file="./error.txt"
expected_error_file="./error2_expected.txt"
name="Uninitialized variable"
echo -n "TEST: $name ..."
../compiler $in_file $out_file 2>$error_file
diff_res=$(diff $error_file $expected_error_file)
if [ $? -eq 1 ] || [ "$diff_res" ]; then
    echo -e " \033[0;31mFAILED\033[0m"
else
    echo -e " \033[0;32mPASSED\033[0m"
fi

rm -f $out_file
rm -f $error_file
