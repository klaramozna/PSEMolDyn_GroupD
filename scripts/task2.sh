#!/bin/bash

# Output file
output_file="output.txt"

# Your command template
command_template="../build/src/MolSim -p ../input/fallingdrop_Wall.xml -t true"

# Loop over values of X
for X in 1 2 4 8 14 16; do
    # Set the environment variable before running the command
    export OMP_NUM_THREADS=$X

    # Run the command and append output to the file
    {
        $command_template
        echo ""
    } >> "$output_file" 2>&1
done

echo "Commands executed and output written to $output_file."

