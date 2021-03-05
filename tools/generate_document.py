#!/usr/bin/env python3

from logging import Logger, basicConfig, getLogger
from os import getenv
import argparse
import re
from pathlib import Path

import markdown
import toml
from jinja2 import DictLoader, Environment, Template, escape

logger: Logger = getLogger(__name__)

sources = toml.load("../test/example/problems.toml")['sources']


class ExampleReader:

    def __init__(self, problem_dir: Path):
        self.problem_dir = problem_dir

    def __getitem__(self, key: str):
        logger.info('read example: {}'.format(key))
        if key not in sources:
            print('example file not found')
            raise RuntimeError()
        problem = sources[key]
        if problem == '':
            s = '### How to Use\n'
        else:
            s = '### AC code of [{}]({})\n'.format(problem, problem)
        example = open(self.problem_dir / (key + '.cpp')).read()
        
        s += '\n'
        s += '<div class="sample-code">'
        s += str(escape(example))
        s += '</div>\n'
        s += '\n'
        
        return s


html_head = open('template_head.html', 'r').read()
html_body = open('template_body.html', 'r').read()

def convert(md_statement: str, base_dir: Path, tag: str) -> str:
    keywords = toml.load(base_dir / 'keywords.toml')
    keywords['tag'] = tag
    if tag == 'production' or re.match(r'v[0-9]\.[0-9]', tag):
        keywords['info'] = ''

    environment = Environment(
        variable_start_string="@{", variable_end_string="}", loader=DictLoader({'task': md_statement}))
    template = environment.get_template('task')

    mid_statement = template.render(
        keyword=keywords,
        example=ExampleReader(Path('..') / 'test' / 'example')
    )

    # evaluate markdown
    statement = markdown.markdown(mid_statement, extensions=[
        'fenced_code',
        'md_in_html',
    ], tab_length=2)


    return html_head + html_body.format(statement)


if __name__ == "__main__":
    basicConfig(
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%H:%M:%S",
        level=getenv('LOG_LEVEL', 'INFO'),
    )
    parser = argparse.ArgumentParser(description='Document generator')
    parser.add_argument('--tag', help='Library version', required=True)
    opts = parser.parse_args()

    langs = ['en', 'ja']
    for lang in langs:
        logger.info('start converting, lang={}'.format(lang))
        base_dir : Path = Path('..') / 'document_{}'.format(lang)        

        for md_file in base_dir.glob('*.md'):
            logger.info('convert {}'.format(md_file))
            statement = convert(open(md_file).read(), base_dir, opts.tag)

            html_file = base_dir / (md_file.stem + '.html')
            with open(html_file, 'w') as f:
                f.write(statement)
