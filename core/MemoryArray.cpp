/*
 * Copyright (c) 2015, University of Kaiserslautern
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Authors: Omar Naji, Matthias Jung, Christian Weis
 */

#include "MemoryArray.h"
#include <math.h>

void 
MemoryArray::calculateSubArrayxy()
{
    // Number of rowcells without redundant cells
    int rowcells = cellsperrow - cellsperrowredundancy;

    // Number of columncells without redundant cells
    int columncells = cellspercolumn - cellspercolumnredundancy;

    // Size of the subarray (value presented in Kbit)
    int sizeofSubArray = (rowcells*columncells)/(1024);

    // Calculate number of subarrays in x direction (rowbuffersize is in
    // kbytes) divided by 2 because half the page is opened per half bank!!
    subproMemoryArrayx = (int)(((float)rowbuffersize*subarray2rowbufferfactor
    *8*1024/2)/(float)rowcells);

    // Size of memoryarray (subarrays in x direction size ) in Mbit
    sizeofMemoryArray = (subproMemoryArrayx * sizeofSubArray)/1024;
}

void 
MemoryArray::calculateSubArrayxylength()
{
    // calculate length of memory array in x direction assuming open
    // bitline array structure
    MemoryArraywidth = subproMemoryArrayx * SubArraywidth + wldwidth;

    // calculate length of memory array in y direction
    MemoryArrayheight = 1 * SubArrayheight;
}

void 
MemoryArray::MemoryArrayinit()
{
    calculateSubArrayxy();
    calculateSubArrayxylength();
}
