# /usr/bin/env python3
import logging
import subprocess
import sys
from pathlib import Path

logging.basicConfig(level=logging.INFO)
logger = logging.getLogger("full-tests")

if len(sys.argv) <= 1:
    sys.exit(2)

BINARY = sys.argv[-1]
WHERE_TO_SEARCH = Path("tests/full/")
INPUT_SUFFIX, EXPECTED_SUFFIX = ".in", ".exp"
ENVS = {"RAW": "1"}
EPS = 1e-5


def catch_output_float(input_file):
    with open(input_file, "r") as file:
        stdin_value = file.read()
    sp = subprocess.run(
        BINARY,
        input=stdin_value.encode(),
        capture_output=True,
        env=ENVS,
    )
    return float(sp.stdout.decode())


def main():
    is_failed = False
    test_files = WHERE_TO_SEARCH.iterdir()
    passed_number = 0
    for test_input_file in filter(lambda f: f.suffix == INPUT_SUFFIX, test_files):
        test_expected_file = test_input_file.with_suffix(EXPECTED_SUFFIX)
        with open(test_expected_file, "r") as file:
            expected_result = float(file.read())
        actual_result = catch_output_float(test_input_file)
        if abs(expected_result - actual_result) > EPS:
            logger.error('Expected: "%s", actual: "%s"', expected_result, actual_result)
            is_failed = True
        else:
            passed_number += 1
    logger.info("%d passed.", passed_number)
    sys.exit(int(is_failed))


if __name__ == "__main__":
    main()
