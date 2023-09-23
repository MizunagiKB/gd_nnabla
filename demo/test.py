# SPDX-License-Identifier: Apache-2.0
# SPDX-FileCopyrightText: 2023 MizunagiKB <mizukb@live.jp>
import nnabla as nn
import nnabla.utils.save
import nnabla.logger as logger
import os
import sys


def main():
    # Create a computation graph to be saved.
    image = nn.Variable([1, 1, 28, 28])
    pred = nn.Variable([1, 10])

    # Save NNP file (used in C++ inference later.).
    runtime_contents = {
        "networks": [
            {
                "name": "runtime",
                "batch_size": 1,
                "outputs": {"y": pred},
                "names": {"x": image},
            }
        ],
        "executors": [
            {"name": "runtime", "network": "runtime", "data": ["x"], "output": ["y"]}
        ],
    }
    # nn.utils.save("test.nnp", runtime_contents)
    nnabla.utils.save.save("test.nnp", runtime_contents)


if __name__ == "__main__":
    main()
