#!/bin/bash -login
########## Define Resources Needed with SBATCH Lines ##########
#SBATCH --time=48:00:00
#SBATCH --job-name name=boolean_calculator+point_rate={{ point }}+sequence_rate={{ sequence }}
#SBATCH --account=devolab
#SBATCH --output="/mnt/scratch/%u/slurmlogs/boolean_calculator+point_rate={{ point }}+sequence_rate={{ sequence }}+ext.log"
#SBATCH --mem=8G
#SBATCH --ntasks 10
#SBATCH --cpus-per-task 1
#SBATCH --mail-type=FAIL
# No --mail-user, the default value is the submitting user
#SBATCH --exclude=csn-002,amr-250
# Send interrupt when within 5 minutes of end time.
#SBATCH --signal=SIGINT@300
# Job may be requeued after node failure.
#SBATCH --requeue

################################################################################
echo
echo "running boolean-calculator.slurm.sh"
echo "-------------------------------"
################################################################################

singularity exec docker://mmore500/signalgp-lite:GITHUB_ACTION_66 make opt

for replicate in $(seq 1 {{ replicates }}); do
  singularity exec docker://mmore500/signalgp-lite:GITHUB_ACTION_66 ./test-boolean-calculator.out -UPDATES "10000" -LOGGING "1" -LOGGING_FILENAME ${replicate} \
    -SGPL_POINT_MUTATION_RATE "{{ point }}" -SGPL_SEQUENCE_DEFECT_RATE "{{ sequence }}" &
done
