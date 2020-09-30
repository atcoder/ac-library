#!/usr/bin/env python3

import unittest
from logging import Logger, basicConfig, getLogger
from os import getenv, environ, pathsep
from pathlib import Path
from shutil import copy
from subprocess import run
from tempfile import TemporaryDirectory
from typing import List

logger = getLogger(__name__)  # type: Logger


class Test(unittest.TestCase):
    def compile_test(self, source: Path, expander_args=[], env=None):
        if not env:
            env = environ.copy()
        lib_dir = Path.cwd().resolve()
        expander_path = Path('expander.py').resolve()
        with TemporaryDirectory() as new_dir:
            tmp = Path(new_dir)
            proc = run(['python', str(expander_path), str(
                source.resolve())] + expander_args, cwd=str(tmp), env=env)
            self.assertEqual(proc.returncode, 0)
            proc = run(['g++', 'combined.cpp', '-std=c++14'], cwd=str(tmp))
            self.assertEqual(proc.returncode, 0)

    def test_dsu(self):
        self.compile_test(Path('test/expander/include_dsu.cpp'),
                          expander_args=['--lib', str(Path.cwd().resolve())])

    def test_unusual_format(self):
        self.compile_test(Path('test/expander/include_unusual_format.cpp'),
                          expander_args=['--lib', str(Path.cwd().resolve())])

    def test_all(self):
        self.compile_test(Path('test/expander/include_all.cpp'),
                          expander_args=['--lib', str(Path.cwd().resolve())])

    def test_comment_out(self):
        self.compile_test(Path('test/expander/comment_out.cpp'),
                          expander_args=['--lib', str(Path.cwd().resolve())])

    def test_env_value(self):
        env = environ.copy()
        env['CPLUS_INCLUDE_PATH'] = str(Path.cwd().resolve())
        self.compile_test(Path('test/expander/include_all.cpp'), env=env)
        env['CPLUS_INCLUDE_PATH'] = pathsep + \
            pathsep + str(Path.cwd().resolve()) + pathsep
        self.compile_test(Path('test/expander/include_all.cpp'), env=env)


if __name__ == "__main__":
    basicConfig(
        level=getenv('LOG_LEVEL', 'DEBUG'),
        format="%(asctime)s %(levelname)s %(name)s : %(message)s"
    )
    unittest.main()
