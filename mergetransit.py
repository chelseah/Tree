#!/usr/bin/env python
import os
import numpy as np
import scipy as sp
import math
from dataio import *
"""
This is a wrapper for sorttransit so that it 
run on a list of file
"""
def fileexists(ID,ap,pmax):
    blsanalf = ID+'.blsanal' 
    reconblsanal = ID+'.AP%d' % ap + '.P%d' % (pmax-1)+ '.blsanal' 
    reconblspost = ID+'.AP%d' % ap + '.P%d' % (pmax-1)+ '.blspost' 
    if(os.path.exists(blsanalf) and os.path.exists(reconblsanal) and os.path.exists(reconblspost)):
        return True
    else:
        return False
def main():
    colp = 2
    coldsp = 14
    maxp = 5
    inpath = '/home/chelsea/KEP/G365/TFA/'
    os.chdir(inpath)
    for ap in xrange(1):
        inlist = '/home/chelsea/KEP/G365/bin/AP%d_test.ls' % ap
        names = []; readcolumn(names,1,inlist,datformat='str')
        for x in names:
            if(fileexists(x,ap,maxp)):
                blsanalf = ID+'.AP%d' % ap + '.P%d' % (pmax-1)+ '.blsanal' 
                blspsotf = os.path.splitext(blsanalf)[0]+'.blspost'
                mergyf = os.path.splitext(blsanalf)[0]+'.blsall'
                os.system("paste %s %s | cut -f 1-31,36- > %s " % (blsanalf,blspostf,mergyf))

                outfile = x+'.mergy.blsanal'
                os.system("sorttransit -i %s -o %s -p %d -d %d -a %d -m %d --noharm -e %s" % (x, outfile, colp,coldsp,ap,maxp,'.blsall'))
                os.remove(mergyf)
    return
if __name__=='__main__':
    main()
