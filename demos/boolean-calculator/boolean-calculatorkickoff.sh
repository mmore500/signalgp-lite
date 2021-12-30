#!/bin/bash

TIME=$(date '+%F_%H-%M-%S')

mkdir "./${TIME}"
cd "./${TIME}"


for point_rate in 0.0002 0.00006 0.00002; do
    for sequence_rate in 0.001 0.0003 0.0001; do
        for replicate in $(seq 1 10); do
            JOB_SCRIPT="boolean_calculator+point_rate=${point_rate}+sequence_rate=${sequence_rate}+replicate=${replicate}+ext=.sh"

            echo $JOB_SCRIPT

            j2 --format=yaml -o "${JOB_SCRIPT}" "boolean-calculator.slurm.sh.jinja" << J2_HEREDOC_EOF
point_rate: "${point_rate}"
sequence_rate: "${sequence_rate}"
replicate: "${replicate}"
time: "${TIME}"
updates: "10000"
J2_HEREDOC_EOF

            chmod +x ${JOB_SCRIPT}


        done
    done
done
