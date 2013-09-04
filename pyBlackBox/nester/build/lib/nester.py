# -*- coding: utf-8 -*-
"""
Created on Wed Sep  4 11:51:57 2013

This is the standard way to include a multiple-line comment in your code.

@author: msaito
"""

def print_lol(the_list):
   """
    This function takes a positional argument called the_list,
    which is any Python list (of, possibly, nested lists). 
    Each data item in the provided list is (recursively) printed to 
    the screen on its own line.
    """
    for each_item in the_list:
            if isinstance(each_item, list):
                print_lol(each_item)
            else:
                print(each_item)