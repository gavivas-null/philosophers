#!/bin/sh

GREEN="\033[0;32m"
RED="\033[0;31m"
BLUE="\033[1;34m"
BROWN="\033[0;33m"
RESET="\033[0m"

run_awk_check() {
	condition="$1"

	awk -v red="$RED" -v green="$GREEN" -v reset="$RESET" "$condition"' {err=1}
	END {
		if (err)
			print red "❌ FAIL" reset "\n";
		else
			print green "✅ OK" reset "\n";
	}'
}

echo "${BROWN}Test 01: 2 800 200 200 10${RESET}"
./philo 2 800 200 200 10 | grep eating | cut -d' ' -f2 | sort | uniq -c | run_awk_check '$1 != 10'


echo "${BROWN}Test 02: 1 800 200 200${RESET}"
./philo 1 800 200 200 10 | grep died | cut -d' ' -f2 | sort | uniq -c | run_awk_check '$1 != 1'

echo "${BROWN}Test 03: 5 1000 200 200 7${RESET}"
./philo 5 1000 200 200 7 | grep eating | cut -d' ' -f2 | sort | uniq -c | run_awk_check '$1 != 7'

echo "${BROWN}Test 04: ${RESET}"

echo "${BROWN}Test 05: ${RESET}"

echo "${BROWN}Test 06: ${RESET}"

echo "${BROWN}Test 07: ${RESET}"

echo "${BROWN}Test 08: ${RESET}"

echo "${BROWN}Test 09: ${RESET}"

echo "${BROWN}Test 10: ${RESET}"

echo "${BROWN}Test 11: ${RESET}"

echo "${BROWN}Test 12: ${RESET}"