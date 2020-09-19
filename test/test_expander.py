#!/usr/bin/env python3

import unittest
from logging import Logger, basicConfig, getLogger
from os import getenv, environ
from pathlib import Path
from shutil import copy
from subprocess import run
from tempfile import TemporaryDirectory
from typing import List

logger = getLogger(__name__)  # type: Logger


class Test(unittest.TestCase):
    def compile_test(self, source: Path, env=None):
        if not env:
            env = environ.copy()
        lib_dir = Path.cwd().resolve()
        expander_path = Path('expander.py').resolve()
        with TemporaryDirectory() as new_dir:
            tmp = Path(new_dir)
            proc = run(['python3', str(expander_path), str(
                source.resolve()), '--lib', str(lib_dir)], cwd=str(tmp), env=env)
            self.assertEqual(proc.returncode, 0)
            proc = run(['g++', 'combined.cpp', '-std=c++14'], cwd=str(tmp))
            self.assertEqual(proc.returncode, 0)

    def test_unionfind(self):
        self.compile_test(Path('test/expander/include_unionfind.cpp'))

    def test_unusual_format(self):
        self.compile_test(Path('test/expander/include_unusual_format.cpp'))

    def test_all(self):
        self.compile_test(Path('test/expander/include_all.cpp'))

    def test_comment_out(self):
        self.compile_test(Path('test/expander/comment_out.cpp'))

    def test_env_value(self):
        env = environ.copy()
        env['CPLUS_INCLUDE_PATH'] = str(Path.cwd().resolve())
        self.compile_test(Path('test/expander/include_all.cpp'), env=env)


if __name__ == "__main__":
    basicConfig(
        level=getenv('LOG_LEVEL', 'DEBUG'),
        format="%(asctime)s %(levelname)s %(name)s : %(message)s"
    )
    unittest.main()
