#!/bin/bash

set -euC

make

ARG_NUM="${1:-100}"
MAX=0
SUM=0
MIN=1000000000
TEST_NUM="${2:-10}"

for i in $(seq 1 "$TEST_NUM")
do
  ARG=$(seq 1 1000 | shuf | head -n "${ARG_NUM}")

  # check if operations is correct
  set +e
  echo "${i}: $(echo $ARG | tr '\n' ' ')"
  CHEKCER_RESULT=$(./push_swap $ARG 2>/dev/null | ./checker_linux $ARG | tail -n 1)
  set -e
  echo "CHEKCER_RESULT: $CHEKCER_RESULT"
  if [[ "$CHEKCER_RESULT" != "OK" ]]
  then
    echo "operations isn't correct!"
    echo "ARG=\"${ARG}\""
    exit 1
  fi

  RESULT=$(./push_swap $ARG 2>/dev/null | wc -l)
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
