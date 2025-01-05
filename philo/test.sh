#!/bin/bash

# Path to the program
PROGRAM="./philo"

# Test cases and expected outcomes
declare -A TEST_CASES
TEST_CASES=(
  ["3 650 200 100 5"]="all_ate" #failed

  ["3 1000 200 700 5"]="no_death" #passed
  ["3 650 200 10000 2"]="early_exit" #passed
  ["3 650 20000 100 2"]="during_eating" #passed
  ["199 599 200 200 5"]="death_around_599" #passed
  ["199 650 200 100 10"]="timestamp_continuity" #passed #should not die?
  ["2 650 600 200 2"]="death_around_650" #passed
  ["1 800 200 200"]="single_philo_death" #passed
  ["5 800 200 200 7"]="all_ate_seven" #passed
  ["4 410 200 200 10"]="no_death_four_10" #passed
  ["4 310 200 100"]="one_death_four" #passed

  ["3 599 200 200 10"]="death_around_559_case1" #passed
  ["31 598 200 200 10"]="death_around_559_case2" #passed 50%
  ["131 596 200 200 10"]="death_around_596"  #passed

  ["5 610 200 200 10"]="no_death_610_small" #passed
  ["4 410 200 100 10"]="no_death_410_small" #passed

  ["199 610 200 200 10"]="no_death_610_large" #failed
  ["198 610 200 200 10"]="no_death_610_xlarge" #failed
  ["198 800 200 200 10"]="no_death_800_xlarge" # failed
)

# Base output file name
OUTPUT_BASE="philo_test"

# Number of runs for certain cases
RUNS=10

# Sleep time between runs (in seconds)
SLEEP_TIME=0.5

# Timeout for 'no_death' cases in seconds
TIMEOUT_DURATION=10

RESULTS_DIR="results"
mkdir -p "$RESULTS_DIR"

# Check if the program exists and is executable
if [[ ! -x "$PROGRAM" ]]; then
  echo "Error: $PROGRAM not found or is not executable."
  exit 1
fi

# Function to validate specific outcomes
validate_output() {
  local case="$1"
  local output_file="$2"
  local elapsed_time="$3"

  case $case in
    "all_ate")
      if grep -q "died" "$output_file"; then
        echo "Test failed: Philosopher died in 'all_ate' case."
        return 1
      fi
      ;;

    "no_death")
      if grep -q "died" "$output_file"; then
        echo "Test failed: Philosopher died in 'no_death' case."
        return 1
      fi
      if (( $(echo "$elapsed_time > $TIMEOUT_DURATION" | bc -l) )); then
        echo "Test failed: Program exceeded $TIMEOUT_DURATION seconds in 'no_death' case."
        return 1
      fi
      ;;

    "early_exit")
      if ! grep -q "died" "$output_file"; then
        echo "Test failed: No philosopher died in 'early_exit' case."
        return 1
      fi
      if (( $(echo "$elapsed_time > 3.0" | bc -l) )); then
        echo "Test failed: Program took too long to end in 'early_exit' case."
        return 1
      fi
      ;;

    "during_eating")
      if ! grep -q "died" "$output_file"; then
        echo "Test failed: No philosopher died in 'during_eating' case."
        return 1
      fi
      ;;

    "death_around_599")
      # Expect death around ~599ms
      if ! grep -qE "59[0-9]|6[0-0][0-9] .* died" "$output_file"; then
        echo "Test failed: No death within 590ms to 609ms in 'death_around_599' case."
        return 1
      fi
      ;;

    "timestamp_continuity")
      if grep -qE "timestamp .* <" "$output_file"; then
        echo "Test failed: Timestamp continuity error in 'timestamp_continuity' case."
        return 1
      fi
      ;;

    "death_around_650")
      if ! grep -qE "65[0-9]|66[0-0] .* died" "$output_file"; then
        echo "Test failed: No death within 650ms to 660ms in 'death_around_650' case."
        return 1
      fi
      ;;

    "single_philo_death")
      if ! grep -q "died" "$output_file"; then
        echo "Test failed: Single philosopher did not die in 'single_philo_death' case."
        return 1
      fi
      ;;

    "no_death_five")
      if grep -q "died" "$output_file"; then
        echo "Test failed: A philosopher died in 'no_death_five' case."
        return 1
      fi
      ;;

    "all_ate_seven")
      # Check if all philosophers ate at least 7 times
      for philo_id in $(seq 1 5); do
        count=$(grep -c " $philo_id is eating" "$output_file")
        echo "Philosopher $philo_id ate $count times" >> debug_log.txt
        if (( count < 7 )); then
          echo "Test failed: Philosopher $philo_id ate only $count times in 'all_ate_seven' case."
          return 1
        fi
      done
      ;;

    "no_death_four")
      if grep -q "died" "$output_file"; then
        echo "Test failed: A philosopher died in 'no_death_four' case."
        return 1
      fi
      ;;

    "one_death_four")
      if ! grep -q "died" "$output_file"; then
        echo "Test failed: No philosopher died in 'one_death_four' case."
        return 1
      fi
      ;;

    #
    # --- New cases (should die around a specific ms) ---
    #
    "die_around_559_small"|"die_around_559_medium")
      # Expect a death time between 559ms and 569ms
      if ! grep -qE "55[9]|56[0-9] .* died" "$output_file"; then
        echo "Test failed: No death within 559ms to 569ms in '$case' case."
        return 1
      fi
      ;;

    "die_around_596_large")
      # Expect a death time between 596ms and 606ms
      if ! grep -qE "59[6]|60[0-6] .* died" "$output_file"; then
        echo "Test failed: No death within 596ms to 606ms in '$case' case."
        return 1
      fi
      ;;

    #
    # --- New cases (should NOT die) ---
    #
    "no_death_610_small"|"no_death_610_large"|"no_death_410_small"|"no_death_610_xlarge"|"no_death_800_xlarge")
      if grep -q "died" "$output_file"; then
        echo "Test failed: A philosopher died in '$case' case."
        return 1
      fi
      ;;
  esac

  return 0
}

# Main loop to execute test cases
for params in "${!TEST_CASES[@]}"; do
  case_name="${TEST_CASES[$params]}"
  echo "Testing: $PROGRAM $params ($case_name)"

  for ((i = 1; i <= RUNS; i++)); do
    # === Зберігаємо у вказану теку
    OUTPUT_FILE="${RESULTS_DIR}/${OUTPUT_BASE}_${case_name}_${i}.txt"

    # Приклад з timeout
    if [[ "$case_name" == "no_death" ]]; then
      timeout $TIMEOUT_DURATION $PROGRAM $params > "$OUTPUT_FILE" &
      pid=$!
      wait $pid
      elapsed_time=$TIMEOUT_DURATION
    else
      start_time=$(date +%s.%N)
      $PROGRAM $params > "$OUTPUT_FILE"
      end_time=$(date +%s.%N)
      elapsed_time=$(echo "$end_time - $start_time" | bc -l)
    fi

    if ! validate_output "$case_name" "$OUTPUT_FILE" "$elapsed_time"; then
      echo "Run $i: Failed. Output saved to $OUTPUT_FILE."
    else
      rm "$OUTPUT_FILE"
      echo "Run $i: Passed. Output discarded."
    fi

    sleep $SLEEP_TIME
  done
done

echo "All tests completed."