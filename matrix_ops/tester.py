import subprocess

# 1. Compile the C code once before running the tests
print("Compiling matrix.c...")
compile_result = subprocess.run(["gcc", "matrix_ops.c", "-o", "matrix_ops"], capture_output=True, text=True)

if compile_result.returncode != 0:
    print("Compilation Failed!")
    print(compile_result.stderr)
    exit(1)

test_input_1 = """2\n2\n2\n2\n1\n2\n3\n4\n1\n2\n3\n4\n1"""
test_input_2 = """2\n2\n2\n2\n1\n2\n3\n4\n1\n2\n3\n4\n2"""
test_input_3 = """2\n2\n2\n2\n1\n2\n3\n4\n1\n2\n3\n4\n3"""
test_input_4 = """2\n2\n2\n2\n1\n2\n3\n4\n1\n2\n3\n4\n4"""

test_inputs = {
    "Test 1: Addition": test_input_1, 
    "Test 2: Subtraction": test_input_2, 
    "Test 3: Multiplication": test_input_3, 
    "Test 4: transpose": test_input_4
}

# 3. Loop through each test case dynamically
print("\n=== STARTING AUTOMATED TESTS ===\n")

for test_name, input_stream in test_inputs.items():
    print(f"Running: {test_name}")
    print("-" * 40)
    
    # Run the program with the current input stream
    result = subprocess.run(
        ["./matrix_ops"], 
        input=input_stream, 
        text=True, 
        capture_output=True
    )
    
    # Check if the C program crashed (return code != 0 means something went wrong, like a SegFault)
    if result.returncode != 0:
        print(f"CRASHED with exit code {result.returncode}!")
        print(f"Error Output:\n{result.stderr}")
    else:
        print(" Program Output:")
        print(result.stdout.strip()) # .strip() cleans up empty whitespace at the end
        
    print("=" * 40 + "\n")

print("All tests completed.")