#!/bin/bash

TIME=$(date '+%F_%H-%M-%S')
echo "TIME ${TIME}"

SCRIPTS_DIR=~/slurmscripts/${TIME}
echo "SCRIPTS_DIR ${SCRIPTS_DIR}"
mkdir ${SCRIPTS_DIR}

REPO_SHA="${1}"
echo "REPO_SHA ${REPO_SHA}"
shift

for point_rate in 0.0002 0.00006 0.00002; do
    for sequence_rate in 0.001 0.0003 0.0001; do
        for replicate in $(seq 1 10); do
            # JOB_SCRIPT="boolean_calculator+point_rate=${point_rate}+sequence_rate=${sequence_rate}+replicate=${replicate}+ext=.sh"
            JOB_SCRIPT=$(mktemp)

            j2 --format=yaml -o "${JOB_SCRIPT}" $(wget https://raw.githubusercontent.com/mmore500/signalgp-lite/${REPO_SHA}/demos/boolean-calculator/boolean-calculator.slurm.sh.jinja) << J2_HEREDOC_EOF
point_rate: "${point_rate}"
sequence_rate: "${sequence_rate}"
replicate: "${replicate}"
time: "${TIME}"
updates: "10000"
seed: "${replicate}"
absolute_path: "/mnt/home/rodsan/slurmruns/boolean-calculator/${TIME}"
repo_sha: "${REPO_SHA}"
J2_HEREDOC_EOF

            chmod +x ${JOB_SCRIPT}

            JOB_ID="$(sbatch --parsable ${JOB_SCRIPT})"
            echo "JOB_ID ${JOB_ID}"

            cp -v ${JOB_SCRIPT} ${SCRIPTS_DIR}/${JOB_ID}.sh
        done
    done
done

echo "job complete"
