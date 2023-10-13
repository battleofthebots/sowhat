#ifndef LOADNEXEC_H_
#define LOADNEXEC_H_

/**
 * @brief load a shared object into memory for execution
 * @param so_buffer, pointer to a char buffer containing a shared object.
 * @return a return code of zero indicates success, non-zero indicate a failure
 **/
int mem_dlexec(char *so_buffer, int buff_size);


/**
 * @brief b64 decode and zlib decompress a SO buffer.
 * @param enc_buffer, an encoded buffer to decompress.
 * @param buff_size, an integer indicating size of the decompressed buffer.
 * @return a char pointer that contains a shared object.
 **/
char *decode_and_decompress(char *enc_buffer, int buff_size);




#endif // LOADNEXEC_H_
