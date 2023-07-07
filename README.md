## SOWhat
The challenge loads an execute a Shared Object. This challenge mimicks a "update system" that performs a check on the last 4 "magic" bytes.


## Static RE Challenge
2. What port does the update service listen on?
3. What is the SO symbol required to be for execution?

## Building
TODO


## PoC Script
The Makefile builds a temporary shared object (```sowut_test.so```)that executes "id" and writes it to a file "lol" int the /tmp directory.
To build the shared object, execute: ```make sharedobject```.

To verify this application is running as intended execute, the following:

``` sh
$> python3 utils/loadNEncode.py -f /tmp/sowut_test.so -d 127.0.0.1 -p 1776
```

The byte array that is created is as follows:
``` sh
[X][X][X][X][Y][Y][Y][....]
```
The first 4 characters (shown above as X)) represent **2 bytes** that specify how large the shared object is **BEFORE** it's compressed.
This value is critical to ensuring a buffer is created of sufficient size to be decompressed into. The shared object is then compressed,
and base64 encoded with the length being pre-pended. The "Ys" in the figure above represent the compressed and encoded Shared Object.
