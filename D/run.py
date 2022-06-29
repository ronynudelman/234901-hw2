#!/usr/bin/env python3


import subprocess
import argparse
import sys
import os


CPP_FILE = 't'
EXEC_FILE = 't'
INPUT_FILE = 't'
OUTPUT_FILE = 't'
CPP = '.cpp'
EXEC = '.run'
INPUT = '.in'
OUTPUT = '.out'


BLUE = '\033[94m'
MAGENTA = '\033[95m'
YELLOW = '\033[93m'
GREEN = '\033[92m'
RED = '\033[91m'
END = '\033[0m'
DEFAULT = 0


def colored_print(str, color=DEFAULT, new_line=True):
    if color == RED:
        print(f"{RED}{str}{END}", end='', flush=True)
    elif color == GREEN:
        print(f"{GREEN}{str}{END}", end='', flush=True)
    elif color == YELLOW:
        print(f"{YELLOW}{str}{END}", end='', flush=True)
    elif color == MAGENTA:
        print(f"{MAGENTA}{str}{END}", end='', flush=True)
    elif color == DEFAULT:
        print(str, end='', flush=True)
    if new_line:
        print('', flush=True)


def get_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('test_num')
    parser.add_argument('-k', '--keep-output', dest='keep_output', action='store_true')
    args = parser.parse_args()
    args.test_num
    colored_print(f'Running task {args.test_num}', MAGENTA)
    return args


def compile(test_num):
    colored_print('Compiling...\t', MAGENTA)
    cmd = ['g++',
           '-std=c++11',
           f'{CPP_FILE}{test_num}{CPP}',
           '-o',
           f'{EXEC_FILE}{test_num}{EXEC}']
    subprocess.run(cmd, check=True)
    colored_print('Passed', color=GREEN)


def run_test(test_num):
    colored_print('Running test...\t', MAGENTA)
    cmd = [f'./t{test_num}.run']
    input_file_name = f'{INPUT_FILE}{test_num}{INPUT}'
    output_file_name = f'{OUTPUT_FILE}{test_num}{OUTPUT}'
    with open(input_file_name, 'r') as in_file, open(output_file_name, 'w') as out_file:
        subprocess.run(cmd,
                       stdin=in_file,
                       stdout=out_file,
                       stderr=out_file,
                       check=True)
    colored_print('Passed', color=GREEN)


def print_output(test_num):
    colored_print('Printing results...\t', MAGENTA)
    output_file = f'{OUTPUT_FILE}{test_num}{OUTPUT}'
    cmd = ['cat',
           output_file]
    subprocess.run(cmd, check=True)


def clean_env(test_num, keep_output):
    try:
        if not keep_output:
            output_file = f'{OUTPUT_FILE}{test_num}{OUTPUT}'
            if os.path.isfile(output_file):
                os.remove(output_file)
            exec_file = f'{EXEC_FILE}{test_num}{EXEC}'
            if os.path.isfile(exec_file):
                os.remove(exec_file)
    except:
        pass


def print_error():
    colored_print('FAILED', color=RED)


def main():
    args = get_args()
    try:
        compile(args.test_num)
        run_test(args.test_num)
        print_output(args.test_num)
    except subprocess.CalledProcessError as e:
        print_error()
    finally:
        clean_env(args.test_num, args.keep_output)


if __name__ == '__main__':
    main()
