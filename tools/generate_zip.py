#!/usr/bin/env python3

from logging import Logger, basicConfig, getLogger
from os import getenv
from pathlib import Path
import zipfile

logger: Logger = getLogger(__name__)

if __name__ == "__main__":
    basicConfig(
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%H:%M:%S",
        level=getenv('LOG_LEVEL', 'INFO'),
    )
    with zipfile.ZipFile('ac-library.zip', 'w') as zipf:
        langs = ['en', 'ja']
        for lang in langs:
            for f in (Path('..') / 'document_{}'.format(lang)).glob('*.html'):
                zipf.write(f, 'document_{}/'.format(lang) + f.name)
            for f in (Path('..') / 'document_{}/lib'.format(lang)).glob('*'):
                zipf.write(f, 'document_{}/lib/'.format(lang) + f.name)
            for f in (Path('..') / 'document_{}/lib/fonts'.format(lang)).glob('**/*'):
                zipf.write(f, 'document_{}/lib/fonts/'.format(lang) + f.name)


        for f in (Path('..') / 'atcoder').glob('*'):
            zipf.write(f, f.relative_to(Path('..')))

        zipf.write('../expander.py', 'expander.py')
