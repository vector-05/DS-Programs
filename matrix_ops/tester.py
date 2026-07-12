import subprocess

# 1. Compile the C code once before running the tests
print("Compiling matrix.c...")
compile_result = subprocess.run(["gcc", "matrix_ops.c", "-o", "matrix_ops"], capture_output=True, text=True)

if compile_result.returncode != 0:
    print("Compilation Failed!")
    print(compile_result.stderr)
    exit(1)

test_inputs = {
    # ==========================================
    # GROUP 1: ADDITION & SUBTRACTION IDENTITY TESTS (1-10)
    # ==========================================
    "Test 1: Basic Addition": ("2 2\n2 2\n1 2\n3 4\n1 2\n3 4\n1", "2 4\n6 8"),
    "Test 2: Basic Subtraction": ("2 2\n2 2\n1 2\n3 4\n1 2\n3 4\n2", "0 0\n0 0"),
    "Test 3: Zero Matrix Identity (Add)": ("2 2\n2 2\n5 6\n7 8\n0 0\n0 0\n1", "5 6\n7 8"),
    "Test 4: Zero Matrix Identity (Sub)": ("2 2\n2 2\n5 6\n7 8\n0 0\n0 0\n2", "5 6\n7 8"),
    "Test 5: Subtract from Zero Matrix": ("2 2\n2 2\n0 0\n0 0\n1 2\n3 4\n2", "-1 -2\n-3 -4"),
    "Test 6: Add Large Values": ("2 2\n2 2\n1000 2000\n3000 4000\n500 500\n500 500\n1", "1500 2500\n3500 4500"),
    "Test 7: Subtraction resulting in Negatives": ("2 2\n2 2\n1 1\n1 1\n5 5\n5 5\n2", "-4 -4\n-4 -4"),
    "Test 8: Mixed Sign Addition": ("2 2\n2 2\n-1 2\n-3 4\n1 -2\n3 -4\n1", "0 0\n0 0"),
    "Test 9: Addition of Rectangular Matrices": ("2 3\n2 3\n1 1 1\n2 2 2\n3 3 3\n4 4 4\n1", "4 4 4\n6 6 6"),
    "Test 10: Subtraction of Rectangular Matrices": ("3 2\n3 2\n5 5\n5 5\n5 5\n1 2\n3 4\n5 6\n2", "4 3\n2 1\n0 -1"),

    # ==========================================
    # GROUP 2: MULTIPLICATION FUNCTIONALITY TESTS (11-20)
    # ==========================================
    "Test 11: Square Matrix Multiplication": ("2 2\n2 2\n1 2\n3 4\n1 2\n3 4\n3", "7 10\n15 22"),
    "Test 12: Multiply by Zero Matrix": ("2 2\n2 2\n1 2\n3 4\n0 0\n0 0\n3", "0 0\n0 0"),
    "Test 13: Multiply by Identity Matrix": ("2 2\n2 2\n4 5\n6 7\n1 0\n0 1\n3", "4 5\n6 7"),
    "Test 14: Rectangular Multiplication (2x3 by 3x2)": ("2 3\n3 2\n1 2 3\n4 5 6\n7 8\n9 10\n11 12\n3", "58 64\n139 154"),
    "Test 15: Rectangular Multiplication (3x2 by 2x3)": ("3 2\n2 3\n1 2\n3 4\n5 6\n1 2 3\n4 5 6\n3", "9 12 15\n19 26 33\n29 40 51"),
    "Test 16: Column Vector times Row Vector (Inner Product)": ("1 3\n3 1\n2 3 4\n5\n6\n7\n3", "56"),
    "Test 17: Row Vector times Column Vector (Outer Product)": ("3 1\n1 3\n2\n3\n4\n5 6 7\n3", "10 12 14\n15 18 21\n20 24 28"),
    "Test 18: Multiplication with Negative Elements": ("2 2\n2 2\n-1 2\n3 -4\n5 -6\n-7 8\n3", "-19 22\n43 -50"),
    "Test 19: Multiplication Scalar-like Single Elements": ("1 1\n1 1\n6\n7\n3", "42"),
    "Test 20: Large Product Computations": ("2 2\n2 2\n100 200\n300 400\n5 2\n1 3\n3", "700 800\n1900 1800"),

    # ==========================================
    # GROUP 3: TRANSPOSE TESTS (21-27)
    # ==========================================
    "Test 21: Transpose Square Matrices": ("2 2\n2 2\n1 2\n3 4\n5 6\n7 8\n4", "1 3\n2 4\n5 7\n6 8"),
    "Test 22: Transpose Rectangular A and B (Wide)": ("2 3\n2 3\n1 2 3\n4 5 6\n7 8 9\n1 2 3\n4", "1 4\n2 5\n3 6\n7 1\n8 2\n9 3"),
    "Test 23: Transpose Rectangular A and B (Tall)": ("3 2\n3 2\n1 2\n3 4\n5 6\n7 8\n9 0\n1 2\n4", "1 3 5\n2 4 6\n7 9 1\n8 0 2"),
    "Test 24: Transpose Symmetric Matrix (Should match input)": ("2 2\n2 2\n1 5\n5 2\n9 3\n3 9\n4", "1 5\n5 2\n9 3\n3 9"),
    "Test 25: Transpose Row Vector to Column": ("1 4\n1 4\n1 2 3 4\n5 6 7 8\n4", "1\n2\n3\n4\n5\n6\n7\n8"),
    "Test 26: Transpose Column Vector to Row": ("4 1\n4 1\n1\n2\n3\n4\n5\n6\n7\n8\n4", "1 2 3 4\n5 6 7 8"),
    "Test 27: Transpose Single Element Matrices": ("1 1\n1 1\n99\n11\n4", "99\n11"),

    # ==========================================
    # GROUP 4: STRUCTURAL EDGE CASES & DIMENSIONS (28-36)
    # ==========================================
    "Test 28: Smallest Valid Size (1x1 Operations - Add)": ("1 1\n1 1\n5\n10\n1", "15"),
    "Test 29: Smallest Valid Size (1x1 Operations - Sub)": ("1 1\n1 1\n5\n10\n2", "-5"),
    "Test 30: Smallest Valid Size (1x1 Operations - Mul)": ("1 1\n1 1\n5\n10\n3", "50"),
    "Test 31: Highly Symmetric Data Pattern Multiplications": ("3 3\n3 3\n1 1 1\n1 1 1\n1 1 1\n1 1 1\n1 1 1\n1 1 1\n3", "3 3 3\n3 3 3\n3 3 3"),
    "Test 32: Asymmetric Dimensions Matrix Multiplication": ("1 4\n4 2\n1 2 3 4\n1 2\n3 4\n5 6\n7 8\n3", "50 60"),
    "Test 33: Non-Square Flat Row Alternating Signs": ("1 5\n1 5\n1 -1 1 -1 1\n2 -2 2 -2 2\n1", "3 -3 3 -3 3"),
    "Test 34: 4x4 Large Dimension Addition": ("4 4\n4 4\n1 1 1 1\n1 1 1 1\n1 1 1 1\n1 1 1 1\n2 2 2 2\n2 2 2 2\n2 2 2 2\n2 2 2 2\n1", "3 3 3 3\n3 3 3 3\n3 3 3 3\n3 3 3 3"),
    "Test 35: 4x4 Large Dimension Subtraction": ("4 4\n4 4\n3 3 3 3\n3 3 3 3\n3 3 3 3\n3 3 3 3\n1 1 1 1\n1 1 1 1\n1 1 1 1\n1 1 1 1\n2", "2 2 2 2\n2 2 2 2\n2 2 2 2\n2 2 2 2"),
    "Test 36: 4x1 Column Vector Subtraction": ("4 1\n4 1\n1\n2\n3\n4\n4\n3\n2\n1\n2", "-3\n-1\n1\n3"),

    # ==========================================
    # GROUP 5: COMPATIBILITY EXCEPTION/ERROR BOUNDARIES (37-50)
    # ==========================================
    "Test 37: Incompatible Addition (Row Mismatch)": ("2 2\n3 2\n1 2\n3 4\n1 2\n3 4\n5 6\n1", "Matrix Incompatible"),
    "Test 38: Incompatible Addition (Col Mismatch)": ("2 2\n2 3\n1 2\n3 4\n1 2 3\n4 5 6\n1", "Matrix Incompatible"),
    "Test 39: Incompatible Subtraction (Row Mismatch)": ("3 2\n2 2\n1 2\n3 4\n5 6\n1 2\n3 4\n2", "Matrix Incompatible"),
    "Test 40: Incompatible Subtraction (Col Mismatch)": ("2 3\n2 2\n1 2 3\n4 5 6\n1 2\n3 4\n2", "Matrix Incompatible"),
    "Test 41: Incompatible Multiplication (Inner Dim Mismatch)": ("2 3\n2 3\n1 2 3\n4 5 6\n1 2 3\n4 5 6\n3", "Matrix Incompatible"),
    "Test 42: Incompatible Multiplication Vector Boundary": ("1 4\n1 4\n1 2 3 4\n5 6 7 8\n3", "Matrix Incompatible"),
    "Test 43: Incompatible Subtraction Deep Mismatch": ("1 1\n4 4\n5\n1 1 1 1\n1 1 1 1\n1 1 1 1\n1 1 1 1\n2", "Matrix Incompatible"),
    "Test 44: Incompatible Addition Swapped Shapes": ("4 2\n2 4\n1 1\n1 1\n1 1\n1 1\n2 2 2 2\n2 2 2 2\n1", "Matrix Incompatible"),
    "Test 45: Incompatible Multiplication Swapped Shapes": ("4 1\n4 1\n1\n1\n1\n1\n2\n2\n2\n2\n3", "Matrix Incompatible"),
    "Test 46: Row Count Extreme Incompatibility": ("1 2\n5 2\n1 2\n1 2\n1 2\n1 2\n1 2\n1 2\n1", "Matrix Incompatible"),
    "Test 47: Column Count Extreme Incompatibility": ("2 1\n2 5\n1\n2\n1 2 3 4 5\n6 7 8 9 0\n1", "Matrix Incompatible"),
    "Test 48: Addition Identity Check Matrix Shape": ("3 1\n1 3\n1\n2\n3\n1 2 3\n1", "Matrix Incompatible"),
    "Test 49: Vector Multiplication Structural Orientation Mismatch": ("4 1\n4 1\n1\n2\n3\n4\n5\n6\n7\n8\n3", "Matrix Incompatible"),
    "Test 50: Non-Matching Multiplications Dimensions Check": ("3 2\n4 3\n1 2\n3 4\n5 6\n1 2 3\n4 5 6\n7 8 9\n0 1 2\n3", "Matrix Incompatible"),
    
    # ==========================================
    # GROUP 6: ADVANCED ALGEBRAIC & MATRIX IDENTITIES (51-65)
    # ==========================================
    "Test 51: Nilpotent Matrix Multiplication (A^2 = 0)": ("2 2\n2 2\n0 1\n0 0\n0 1\n0 0\n3", "0 0\n0 0"),
    "Test 52: Idempotent Matrix Multiplication (A^2 = A)": ("2 2\n2 2\n1 0\n0 0\n1 0\n0 0\n3", "1 0\n0 0"),
    "Test 53: Involutory Matrix Multiplication (A^2 = I)": ("2 2\n2 2\n0 1\n1 0\n0 1\n1 0\n3", "1 0\n0 1"),
    "Test 54: Orthogonal Vector Multiplication (Product = 0)": ("1 3\n3 1\n1 -2 1\n2\n1\n0\n3", "0"),
    "Test 55: Skew-Symmetric Matrix Transpose": ("3 3\n3 3\n0 1 -2\n-1 0 3\n2 -3 0\n0 1 -2\n-1 0 3\n2 -3 0\n4", "0 -1 2\n1 0 -3\n-2 3 0\n0 -1 2\n1 0 -3\n-2 3 0"),
    "Test 56: Identity Matrix Multiplication (Alternative Sizes)": ("3 3\n3 3\n1 2 3\n4 5 6\n7 8 9\n1 0 0\n0 1 0\n0 0 1\n3", "1 2 3\n4 5 6\n7 8 9"),
    "Test 57: Zero Matrix Multiplication Absorption Property": ("3 3\n3 3\n0 0 0\n0 0 0\n0 0 0\n9 8 7\n6 5 4\n3 2 1\n3", "0 0 0\n0 0 0\n0 0 0"),
    "Test 58: Repeated Identity Matrix Addition": ("2 2\n2 2\n1 0\n0 1\n1 0\n0 1\n1", "2 0\n0 2"),
    "Test 59: Matrix Self-Subtraction (Yields Zero)": ("3 3\n3 3\n14 15 16\n17 18 19\n20 21 22\n14 15 16\n17 18 19\n20 21 22\n2", "0 0 0\n0 0 0\n0 0 0"),
    "Test 60: Double Negative Addition Logic": ("2 2\n2 2\n-5 -10\n-15 -20\n-5 -10\n-15 -20\n1", "-10 -20\n-30 -40"),
    "Test 61: Alternating Row Sign Subtraction": ("2 2\n2 2\n1 -1\n1 -1\n-1 1\n-1 1\n2", "2 -2\n2 -2"),
    "Test 62: Single Row Scalar Vector Scaling Addition": ("1 4\n1 4\n10 20 30 40\n1 2 3 4\n1", "11 22 33 44"),
    "Test 63: Diagonal Matrix Multiplication Extraction": ("3 3\n3 3\n2 0 0\n0 3 0\n0 0 4\n1 2 3\n4 5 6\n7 8 9\n3", "2 4 6\n12 15 18\n28 32 36"),
    "Test 64: Non-Commutative Multiplication Verification (A*B != B*A)": ("2 2\n2 2\n1 2\n3 4\n2 0\n1 2\n3", "4 4\n10 8"),
    "Test 65: Permutation Matrix Swap Row Execution": ("2 2\n2 2\n0 1\n1 0\n5 6\n7 8\n3", "7 8\n5 6"),

    # ==========================================
    # GROUP 7: COMPLEX NEGATIVE & SIGN COMBINATIONS (66-75)
    # ==========================================
    "Test 66: Subtraction of Inverse Sign Matrix": ("2 2\n2 2\n4 4\n4 4\n-4 -4\n-4 -4\n2", "8 8\n8 8"),
    "Test 67: Multiplication completely populated by Negative Ones": ("2 2\n2 2\n-1 -1\n-1 -1\n-1 -1\n-1 -1\n3", "2 2\n2 2"),
    "Test 68: Multiplicative Signs Cancellation Cascade": ("2 2\n2 2\n-1 2\n-3 4\n-5 -6\n7 -8\n3", "19 -10\n43 -14"),
    "Test 69: Mixed Elements Single Value Zero-Crossing (Sub)": ("1 1\n1 1\n-5\n-12\n2", "7"),
    "Test 70: Asymmetric Sign Column Matrix Addition": ("3 1\n3 1\n-1\n2\n-3\n1\n-2\n3\n1", "0\n0\n0"),
    "Test 71: Checkerboard Pattern Matrix Addition": ("3 3\n3 3\n1 -1 1\n-1 1 -1\n1 -1 1\n-1 1 -1\n1 -1 1\n-1 1 -1\n1", "0 0 0\n0 0 0\n0 0 0"),
    "Test 72: Checkerboard Pattern Matrix Subtraction": ("3 3\n3 3\n1 -1 1\n-1 1 -1\n1 -1 1\n1 -1 1\n-1 1 -1\n1 -1 1\n2", "0 0 0\n0 0 0\n0 0 0"),
    "Test 73: Highly Negative Elements Rectangular Multiplication": ("2 3\n3 2\n-1 -2 -3\n-4 -5 -6\n-1 -2\n-3 -4\n-5 -6\n3", "22 28\n49 64"),
    "Test 74: Flat Matrix Subtraction Drop to Negative Value": ("1 5\n1 5\n0 0 0 0 0\n5 10 15 20 25\n2", "-5 -10 -15 -20 -25"),
    "Test 75: Large Single Digits Multiplication Verification": ("1 1\n1 1\n-9\n-9\n3", "81"),

    # ==========================================
    # GROUP 8: TALL, WIDE & EXTREME ASYMMETRIC VISUAl LAYOUTS (76-85)
    # ==========================================
    "Test 76: Multi-Row Horizontal Strip Addition": ("1 6\n1 6\n1 1 1 1 1 1\n2 2 2 2 2 2\n1", "3 3 3 3 3 3"),
    "Test 77: Multi-Row Horizontal Strip Subtraction": ("1 6\n1 6\n5 5 5 5 5 5\n2 2 2 2 2 2\n2", "3 3 3 3 3 3"),
    "Test 78: Multi-Column Vertical Long Strip Addition": ("6 1\n6 1\n2\n2\n2\n2\n2\n2\n3\n3\n3\n3\n3\n3\n1", "5\n5\n5\n5\n5\n5"),
    "Test 79: Multi-Column Vertical Long Strip Subtraction": ("6 1\n6 1\n10\n10\n10\n10\n10\n10\n4\n4\n4\n4\n4\n4\n2", "6\n6\n6\n6\n6\n6"),
    "Test 80: Multi-Column Vertical Long Strip Transpose": ("5 1\n5 1\n1\n2\n3\n4\n5\n6\n7\n8\n9\n0\n4", "1 2 3 4 5\n6 7 8 9 0"),
    "Test 81: High Aspect Ratio Multiplication (1x5 by 5x1)": ("1 5\n5 1\n1 2 3 4 5\n5\n4\n3\n2\n1\n3", "35"),
    "Test 82: High Aspect Ratio Multiplication (5x1 by 1x5)": ("5 1\n1 5\n1\n2\n3\n4\n5\n2 2 2 2 2\n3", "2 2 2 2 2\n4 4 4 4 4\n6 6 6 6 6\n8 8 8 8 8\n10 10 10 10 10"),
    "Test 83: Asymmetric Rectangular Addition Structure": ("3 4\n3 4\n1 1 1 1\n2 2 2 2\n3 3 3 3\n1 1 1 1\n1 1 1 1\n1 1 1 1\n1", "2 2 2 2\n3 3 3 3\n4 4 4 4"),
    "Test 84: Asymmetric Rectangular Subtraction Structure": ("4 3\n4 3\n5 5 5\n5 5 5\n5 5 5\n5 5 5\n1 2 3\n1 2 3\n1 2 3\n1 2 3\n2", "4 3 2\n4 3 2\n4 3 2\n4 3 2"),
    "Test 85: Interlocking Non-Square Rectangular Shapes Multiplication": ("3 4\n4 2\n1 0 1 0\n0 1 0 1\n1 1 1 1\n2 1\n3 2\n4 3\n5 4\n3", "6 4\n8 6\n14 10"),

    # ==========================================
    # GROUP 9: FURTHER COMPATIBILITY EXCEPTION CHANNELS (86-100)
    # ==========================================
    "Test 86: Comp-Exception: Radical Square Matrix Addition Mismatch": ("2 2\n3 3\n1 2\n3 4\n1 2 3\n4 5 6\n7 8 9\n1", "Matrix Incompatible"),
    "Test 87: Comp-Exception: Radical Square Matrix Subtraction Mismatch": ("3 3\n2 2\n1 2 3\n4 5 6\n7 8 9\n1 2\n3 4\n2", "Matrix Incompatible"),
    "Test 88: Comp-Exception: Addition Transposed Shapes Error Flow": ("2 5\n5 2\n1 1 1 1 1\n1 1 1 1 1\n2 2\n2 2\n2 2\n2 2\n2 2\n1", "Matrix Incompatible"),
    "Test 89: Comp-Exception: Subtraction Transposed Shapes Error Flow": ("5 2\n2 5\n2 2\n2 2\n2 2\n2 2\n2 2\n1 1 1 1 1\n1 1 1 1 1\n2", "Matrix Incompatible"),
    "Test 90: Comp-Exception: Empty Structural Mismatch Multiplication Inner Gap": ("3 1\n3 1\n1\n2\n3\n4\n5\n6\n3", "Matrix Incompatible"),
    "Test 91: Comp-Exception: Multiplication Wide-Wide Outer Boundary Clash": ("1 4\n1 4\n1 2 3 4\n5 6 7 8\n3", "Matrix Incompatible"),
    "Test 92: Comp-Exception: Multiplication Tall-Tall Side Border Clash": ("4 1\n4 1\n1\n2\n3\n4\n5\n6\n7\n8\n3", "Matrix Incompatible"),
    "Test 93: Comp-Exception: Complex Asymmetric Rectangular Multiplicative Failure": ("4 3\n2 4\n1 2 3\n4 5 6\n7 8 9\n1 2 3\n1 2 3 4\n5 6 7 8\n3", "Matrix Incompatible"),
    "Test 94: Comp-Exception: Row Dominated Grid Addition Clash": ("5 2\n1 2\n1 2\n1 2\n1 2\n1 2\n1 2\n1 2\n1", "Matrix Incompatible"),
    "Test 95: Comp-Exception: Column Dominated Grid Subtraction Clash": ("2 5\n2 1\n1 2 3 4 5\n6 7 8 9 0\n1\n2\n2", "Matrix Incompatible"),
    "Test 96: Comp-Exception: 1x1 to 2x2 Scaling Vector Space Mismatch (Add)": ("1 1\n2 2\n5\n1 2\n3 4\n1", "Matrix Incompatible"),
    "Test 97: Comp-Exception: 1x1 to 2x2 Scaling Vector Space Mismatch (Sub)": ("2 2\n1 1\n1 2\n3 4\n5\n2", "Matrix Incompatible"),
    "Test 98: Comp-Exception: 1x1 to 2x2 Scaling Vector Space Mismatch (Mul)": ("1 1\n2 2\n5\n1 2\n3 4\n3", "Matrix Incompatible"),
    "Test 99: Comp-Exception: Extreme Sizing Matrix Addition Overflow Incompatibility": ("1 4\n4 1\n1 2 3 4\n1\n2\n3\n4\n1", "Matrix Incompatible"),
    "Test 100: Comp-Exception: Complex Intertwined Dimensions Structural Drop": ("3 2\n2 1\n1 2\n3 4\n5 6\n1\n2\n1", "Matrix Incompatible")
}

# 3. Loop through each test case dynamically
print("\n=== STARTING AUTOMATED TESTS ===\n")
passed_count = 0

# FIX: Unpack both variables from the tuple here
for test_name, (input_stream, expected_output) in test_inputs.items():
    print(f"Running: {test_name}")
    print("-" * 40)
    
    # Run the program with the current input stream
    result = subprocess.run(
        ["./matrix_ops"], 
        input=input_stream, 
        text=True, 
        capture_output=True
    )
    
    # Check if the C program crashed
    if result.returncode != 0:
        print(f"❌ CRASHED with exit code {result.returncode}!")
        print(f"Error Output:\n{result.stderr}")
        print("=" * 40 + "\n")
        continue
        
    # --- PARSE THE OUTPUT USING [DATA] TAGS ---
    filtered_lines = []
    for line in result.stdout.splitlines():
        if line.startswith("[DATA]"):
            # Remove the prefix tag and clean up any trailing whitespace
            cleaned_line = line.replace("[DATA]", "").replace("\r", "").strip()
            filtered_lines.append(cleaned_line)
            
    actual_output = "\n".join(filtered_lines)

    # --- VALIDATE THE OUTPUT ---
    if actual_output == expected_output.strip():
        print("✅ PASSED")
        passed_count += 1
    else:
        print("❌ FAILED")
        print(f"   Expected:\n{expected_output}")
        print(f"   Got (Cleaned Data):\n{actual_output}")
        
    print("=" * 40 + "\n")

print(f"All tests completed. Summary: {passed_count}/{len(test_inputs)} passed.")