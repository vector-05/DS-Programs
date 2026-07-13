import subprocess
import os
import datetime
import pandas as pd

# 1. Compile the C code once before running the test cases
print("Compiling matrix.c...")
compile_result = subprocess.run(["gcc", "matrix_ops.c", "-o", "matrix_ops"], capture_output=True, text=True)

if compile_result.returncode != 0:
    print("❌ Compilation Failed!")
    print(compile_result.stderr)
    exit(1)

# Load test cases using pandas
if not os.path.exists("tests.csv"):
    print("❌ Error: matrix_tests.csv file not found! Please create it first.")
    exit(1)

df_tests = pd.read_csv("tests.csv")
df_tests.columns = df_tests.columns.str.strip()

df_tests = pd.read_csv("tests.csv")

print(f"Loaded {len(df_tests)} test cases from matrix_tests.csv.")
print("\n=== STARTING AUTOMATED TESTS ===\n")

passed_count = 0
log_entries = []

# 3. Loop through each test case from the DataFrame
for index, row in df_tests.iterrows():
    test_id = row['test_id']
    test_name = f"Test {test_id}: {row['test_name']}"
    input_stream = str(row['input_stream'])
    expected_output = str(row['expected_output']).strip()
    
    print(f"Running: {test_name}")
    print("-" * 40)
    
    # Initialize execution metrics
    status = "FAILED"
    error_message = ""
    actual_output = ""
    
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
        status = "CRASHED"
        error_message = result.stderr.strip()
        print("=" * 40 + "\n")
    else:
        # --- PARSE THE OUTPUT USING [DATA] ---
        filtered_lines = []
        for line in result.stdout.splitlines():
            if line.startswith("[DATA]"):
                cleaned_line = line.replace("[DATA]", "").strip()
                filtered_lines.append(cleaned_line)
                
        actual_output = "\n".join(filtered_lines)
        
        # --- VALIDATE THE OUTPUT ---
        if actual_output == expected_output:
            print("✅ PASSED")
            status = "PASSED"
            passed_count += 1
        else:
            print("❌ FAILED")
            print(f"   Expected:\n{expected_output}")
            print(f"   Got (Cleaned Data):\n{actual_output}")
            error_message = "Output mismatch"
            
        print("=" * 40 + "\n")
        
    # Collect tracking metrics for logs
    log_entries.append({
        "timestamp": datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S"),
        "test_id": test_id,
        "test_name": row['test_name'],
        "status": status,
        "error_details": error_message
    })

print(f"All tests completed. Summary: {passed_count}/{len(df_tests)} passed.")

# 4. Log the execution metrics directly to logs.csv using pandas
df_new_logs = pd.DataFrame(log_entries)

# Append to existing log file or create a brand new one if it doesn't exist
if os.path.exists("logs.csv"):
    df_new_logs.to_csv("logs.csv", mode='a', header=False, index=False)
else:
    df_new_logs.to_csv("logs.csv", mode='w', header=True, index=False)

print("Execution metrics successfully captured and added to logs.csv.")