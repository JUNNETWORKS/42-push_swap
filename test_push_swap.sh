#!/bin/bash

set -euC

make

ARG_NUM="${1:-100}"
MAX=0
SUM=0
MIN=1000000000
TEST_NUM=100

for i in $(seq 1 "$TEST_NUM")
do
  ARG=$(seq 1 1000 | shuf | head -n "${ARG_NUM}")
  RESULT_OPS=$(./push_swap $ARG 2>/dev/null)

  # check if operations is correct
  echo "$RESULT_OPS" | ./checker_linux $ARG
  if [[ $? != 0 ]]
  then
    echo "operations isn't correct!"
    echo "ARG=\"${ARG}\""
    exit 1
  fi

  RESULT=$(echo "$RESULT_OPS" | wc -l)
  echo "${i}: RESULT: ${RESULT}"
  if (( RESULT > MAX ))
  then
    MAX=$RESULT
  fi
  if (( RESULT < MIN ))
  then
    MIN=$RESULT
  fi
  SUM=$(( SUM + RESULT ))
done

AVG=$(( SUM / TEST_NUM ))

echo "ARG: ${ARG_NUM}"
echo "MAX: ${MAX}"
echo "AVG: ${AVG}"
echo "MIN: ${MIN}"
