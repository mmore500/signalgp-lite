#!/usr/bin/bash

set -e

cd "$(dirname "$0")"
python3 -m uv pip compile --python-version "3.9" requirements.in > requirements.txt
