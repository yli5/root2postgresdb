#! /usr/bin/python

import os
import os.path
import re
import subprocess
import time

# higher level wrapper to submit jobs
def insert_rootfiles(cur_path, modes, runs, cfg_fname, base_dir):

    # extract run number and mode/peak label
    #p = re.compile('^(sp|pr)([0-9]+)r([0-9])')
    #m = p.match(job_dir)
    #mode_label, run = m.group(2, 3)

    #sig_mc_list = ['11444', '11445', '11446', '11447']
    #generic_mc_list = ['998', '1005', '1235', '1237', '3429']
    #data_list = ['0', '1']

    #if not set(modes).issubset(sig_mc_list + generic_mc_list + data_list):
    #    raise ValueError('Invalid mode label.')
    #if not set(runs).issubset([1, 2, 3, 4, 5, 6]):
    #    raise ValueError('Invalid run number.')

    for mode in modes:
        for run in runs:
            data_or_mc = 'pr' if mode in ['0','1'] else 'sp'
            root_dir = base_dir + '/' + data_or_mc + mode + 'r' + run 
            print root_dir
            for f in os.listdir(root_dir):
                if f.endswith('.root'):
                    try:
                        command_stmt = ('{0}/darkphoton_root2postgres '
                                        '--cernroot_fname {1}/{2} '
                                        '--run {3} '
                                        '--mode_label {4} '
                                        '{0}/{5}').format(cur_path, root_dir, f,
                                                          run, mode, cfg_fname)
                        subprocess.check_call(command_stmt.split())
                    except:
                        print 'Invalid call to bdtaunu_root2postgres'
    return

if __name__ == '__main__':

    import argparse
    from argparse import RawTextHelpFormatter

    parser = argparse.ArgumentParser(
            description='Insert all root files for a given SP mode/Run combination.',
            formatter_class=RawTextHelpFormatter)

    parser.add_argument('-m', '--mode', nargs='+', type=str,
                        required=True,
                        help=('The data mode. e.g.,\n'
                              '\t998 1235 ...: sp modes 998 1235\n'
                              '\t0 1 ...: data off/on peak\n'))
    parser.add_argument('-r', '--run', nargs='+', type=str,
                        required=True,
                        help=('The run number. e.g. 1 2 3'))
    parser.add_argument('-c', '--config_file', required=True, type=str, 
                        help=('Configuration file for root2postgres, '
                              'see default.cfg'))
    parser.add_argument('-d', '--base_dir', type= str, 
                        default='/home/jkim/raid13/ntp',
                        help=('Base directory of the root files ' 
                              '(see README for expected layout). '
                              'Change default argument if necessary. '))
    args = parser.parse_args()

    # call root2postgres to insert into database
    insert_rootfiles(os.getcwd(), args.mode, args.run, args.config_file, args.base_dir)
