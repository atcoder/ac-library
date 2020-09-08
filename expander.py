#!/usr/bin/env python3

import re
import sys
import argparse
from logging import Logger, basicConfig, getLogger
from os import getenv, environ
from pathlib import Path
from typing import List


logger = getLogger(__name__)  # type: Logger

atcoder_include = re.compile('#include\s*["<](atcoder/[a-z_]*(|.hpp))[">]\s*')

include_guard = re.compile('#.*ATCODER_[A-Z_]*_HPP')

lib_path = Path.cwd()

defined = set()

def dfs(f: str) -> List[str]:
    global defined
    if f in defined:
        logger.info('already included {}, skip'.format(f))
        return []
    defined.add(f)

    logger.info('include {}'.format(f))

    s = open(str(lib_path / f)).read()
    result = []
    for line in s.splitlines():
        if include_guard.match(line):
            continue

        m = atcoder_include.match(line)
        if m:
            result.extend(dfs(m.group(1)))
            continue
        result.append(line)
    return result


if __name__ == "__main__":
    basicConfig(
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%H:%M:%S",
        level=getenv('LOG_LEVEL', 'INFO'),
    )
    parser = argparse.ArgumentParser(description='Expander')
    parser.add_argument('source', help='Source File')
    parser.add_argument('-c', '--console',
                        action='store_true', help='Print to Console')
    parser.add_argument('--lib', help='Path to Atcoder Library')
    opts = parser.parse_args()

    if opts.lib:
        lib_path = Path(opts.lib)
    elif 'CPLUS_INCLUDE_PATH' in environ:
        lib_path = Path(environ['CPLUS_INCLUDE_PATH'])
    s = open(opts.source).read()

    result = []
    for line in s.splitlines():
        m = atcoder_include.match(line)

        if m:
            result.extend(dfs(m.group(1)))
            continue
        result.append(line)

    output = '\n'.join(result) + '\n'
    if opts.console:
        print(output)
    else:
        with open('combined.cpp', 'w') as f:
            f.write(output)
