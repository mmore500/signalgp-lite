#!/bin/bash

TIME=$(date '+%F_%H-%M-%S')

mkdir "~/slurmscripts/${TIME}"

mkdir "./${TIME}"
cd "./${TIME}"


for point_rate in 0.0002 0.00006 0.00002; do
    for sequence_rate in 0.001 0.0003 0.0001; do
        for replicate in $(seq 1 10); do
            # JOB_SCRIPT="boolean_calculator+point_rate=${point_rate}+sequence_rate=${sequence_rate}+replicate=${replicate}+ext=.sh"
            JOB_SCRIPT="\$(mktemp)"

            j2 --format=yaml -o "${JOB_SCRIPT}" "../boolean-calculator.slurm.sh.jinja" << J2_HEREDOC_EOF
point_rate: "${point_rate}"
sequence_rate: "${sequence_rate}"
replicate: "${replicate}"
time: "${TIME}"
updates: "10000"
seed: "${replicate}"
J2_HEREDOC_EOF

            chmod +x ${JOB_SCRIPT}

            JOB_ID=$(sbatch --parsable ${JOB_SCRIPT})

            cp ${JOB_SCRIPT} "~/slurmscripts/${TIME}/${JOB_ID}.sh"
        done
    done
done
