#! /usr/bin/python

import os
import os.path
import re
import subprocess
import time

# higher level wrapper to submit jobs
def insert_rootfiles(cur_path, job_dir_path):

    # get job name from the job_dir_path
    job_base_dir, job_dir = os.path.split(job_dir_path)

    # extract run number and mode/peak label
    p = re.compile('^(sp|pr)([0-9]+)r([0-9])')
    m = p.match(job_dir)
    mode_label, run = m.group(2, 3)
    
    # loop over root files in the directory
    for f in os.listdir('{0}/root'.format(job_dir_path)):
        if f.endswith(".root"):
            try:
                command_stmt = ('{0}/bdtaunu_root2postgres '
                            '--cernroot_fname {1}/root/{2} '
                            '--run {3} '
                            '--mode_label {4} '
                            '{0}/bdtaunu.cfg').format(cur_path, job_dir_path, f,
                                                      run, mode_label)
                subprocess.check_call(command_stmt.split())
                time.sleep(1)
            except:
                print 'Invalid call to bdtaunu_root2postgres'

    return

if __name__ == '__main__':

    import argparse
    from argparse import RawTextHelpFormatter

    parser = argparse.ArgumentParser(
            description='Insert all root files for a given SP mode/Run combination.',
            formatter_class=RawTextHelpFormatter)

    parser.add_argument('job_dir', type=str,
        help=(
              'Name of the job directory. e.g.,\n'
              '\tsp1237r4: Generic MC, mode 1237, run 4.\n'
              '\tsp11444r1: Signal MC, mode 11444, run 1.\n'
              '\tpr1r3: On peak data, run 3.\n'
              '\tpr0r5: Off peak data, run 5.\n'
             ))
    parser.add_argument('--job_dir_base', 
                        default='/home/jkim/raid13/ntp',
                        help=('base directory of snippet file. '
                              'job_dir is relative to this directory'))
    args = parser.parse_args()

    job_dir = args.job_dir.strip().strip('/')
    job_dir_path = args.job_dir_base + '/' + job_dir

    # call root2postgres to insert into database
    insert_rootfiles(os.getcwd(), job_dir_path)
