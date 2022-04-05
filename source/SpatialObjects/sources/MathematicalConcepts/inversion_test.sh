#!/bin/bash
# NOTE : Quote it else use array to avoid problems #

#create logging file
if test -f "results.log"; then
    echo "Error: results.log already exists."
    exit
fi
# create result log file
touch results.log

for f in ~/input_examples/*.lgc;
do
  # write problem name
  echo "Processing $f" >> results.log
  echo "">> results.log
  # run LGC with the lgc input file
  ./LGC -i "$f" >> results.log
  echo "">> results.log
done
