# !usr/bin/env python
# -*- coding:utf-8 -*-

'''
 Description  : 
 Version      : 1.0
 Author       : huzhenhong
 Date         : 2022-07-04 14:39:39
 LastEditors  : huzhenhong
 LastEditTime : 2022-07-05 10:45:14
 FilePath     : \\python\\excel\\read_xlsx_save_to_txt.py
 Copyright (C) 2022 huzhenhong. All rights reserved.
'''
import os
import sys
import pandas as pd


def convert(xlsx_path):
    if not os.path.exists(xlsx_path):
        print(f'xlsx_path: {xlsx_path} don\'t exist')
        exit()

    df1 = pd.read_excel(xlsx_path)   # 读取xlsx中的第一个sheet
    row, col = df1.shape
    print(f'row x col: {row} x {col}')

    # /picUrl/AIResult/20220705/01/Person_Smoking_Detection_Hand_Face/100306_Person_Smoking_Detection_Hand_Face_1262978554764_origin.jpg
    all_img_path = df1['原图地址']

    f = open(xlsx_path[:-4] + 'txt',mode='w')
    for line in all_img_path:
        img_path = line[7:]
        print(f'img_path: {img_path}')
        f.write(img_path + '\n')
    f.close()


if __name__ == '__main__':
    # xlsx_path = sys.argv[1]
    src_root = sys.argv[1]

    if not os.path.exists(src_root):
        print(f'src_root: {src_root} don\'t exist')
        exit()
    
    for current_root, _, file_list in os.walk(src_root):
        for file in file_list:
            convert(os.path.join(current_root, file))
            
