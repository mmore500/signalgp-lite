#!/bin/bash

if (( "$#" != 1 )); then
  echo "USAGE: [source_sha]"
  exit 1
fi

TIME=$(date '+%F_%H-%M-%S')
echo "TIME ${TIME}"

BATCH_DIR=~/slurmscripts/${TIME}
echo "BATCH_DIR ${BATCH_DIR}"
mkdir -p ${BATCH_DIR}

SOURCE_SHA="${1}"
echo "SOURCE_SHA ${SOURCE_SHA}"
shift

for point_rate in 0.0002 0.00006 0.00002; do
    for sequence_rate in 0.001 0.0003 0.0001; do
        for replicate in $(seq 1 10); do
            JOB_SCRIPT="$(mktemp)"

            j2 --format=yaml -o "${JOB_SCRIPT}" "$(wget 'https://raw.githubusercontent.com/mmore500/signalgp-lite/${SOURCE_SHA}/demos/boolean-calculator/boolean-calculator.slurm.sh.jinja')" << J2_HEREDOC_EOF
point_rate: "${point_rate}"
sequence_rate: "${sequence_rate}"
replicate: "${replicate}"
time: "${TIME}"
updates: "10000"
seed: "${replicate}"
kickoff_path: "/mnt/home/%u/slurmruns/boolean-calculator/${TIME}"
SOURCE_SHA: "${SOURCE_SHA}"
J2_HEREDOC_EOF

            chmod +x "${JOB_SCRIPT}"

            JOB_ID="$(sbatch --parsable '${JOB_SCRIPT}')"
            echo "JOB_ID ${JOB_ID}"

            cp -v "${JOB_SCRIPT}" "${BATCH_DIR}/${JOB_ID}.sh"
        done
    done
done

echo "kickoff complete"
