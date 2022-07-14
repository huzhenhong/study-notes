# !usr/bin/env python
# -*- coding:utf-8 -*-

'''
 Description  : 
 Version      : 1.0
 Author       : huzhenhong
 Date         : 2022-07-04 14:39:39
 LastEditors  : huzhenhong
 LastEditTime : 2022-07-05 10:43:03
 FilePath     : \\python\\excel\\read_xlsx_for_copy_file.py
 Copyright (C) 2022 huzhenhong. All rights reserved.
'''
import os
import sys
import shutil
import pandas as pd


if __name__ == '__main__':
    xlsx_path = sys.argv[1]
    src_root = sys.argv[2]
    dst_root = sys.argv[3]

    if not os.path.exists(xlsx_path):
        print(f'xlsx_path: {xlsx_path} don\'t exist')
        exit()

    if not os.path.exists(src_root):
        print(f'src_root: {src_root} don\'t exist')
        exit()

    if not os.path.exists(dst_root):
        os.makedirs(dst_root)

    print(f'src_root: {src_root} dst_root: {dst_root}')
    
    df1 = pd.read_excel(xlsx_path)   # 读取xlsx中的第一个sheet
    # df1 = pd.read_excel('/home/huzh/Downloads/test.xlsx')   # 读取xlsx中的第一个sheet
    # df1 = pd.read_excel('/home/huzh/Downloads/test.xlsx', None)   # 读取所有sheet，返回字典{sheet_name, value}

    row, col = df1.shape
    print(f'row x col: {row} x {col}')

    all_img_path = df1['原图地址']

    for line in all_img_path:
        img_path = line[7:]
        print(f'img_path: {img_path}')

        src_path = src_root + img_path
        dst_path = dst_root + img_path
        print(f'[{src_path}] => {[dst_path]}')
        shutil.copytree(src_path, dst_path)

