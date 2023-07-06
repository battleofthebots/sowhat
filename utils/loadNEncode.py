#!/usr/bin/env python3

import argparse
import sys
import zlib
import base64
from dataclasses import dataclass


@dataclass
class customSO:
    size: int
    key: hex
    padding: hex
    payload: bytearray

def krypto(bArray: bytes):
    '''
    XOR a byte array with a hardcoded key of 0x42
    '''
    newArray = []
    for i in bArray:
        newArray.append(i ^ 0x42)
    return bytearray(newArray)


def compress(bStr: bytes):
    """zlib compress the byte array"""
    try:
        cdata = zlib.compress(bStr)
        return cdata
    except Exception as error:
        print(f"{error}")
        sys.exit(1)

def readIn(fName:str):
    """read in file as byte array"""
    try:
        with open(fName, "rb") as fin:
            return fin.read()
    except IOError as err:
        print(f"{err}")
        sys.exit(1)


if __name__ == "__main__":

    args = argparse.ArgumentParser()
    args.add_argument("--file", "-f", required=True,
                      help="Specify shared object to load")

    parser = args.parse_args()
    bArray = readIn(parser.file)
    print("Raw byte array: %s", str(len(bArray)))
    cArray = krypto(compress(bArray))
    encoded_array = base64.b64encode(cArray)
    CSO = customSO(len(encoded_array), 0x42, 0x00, encoded_array)
    import pdb; pdb.set_trace()
