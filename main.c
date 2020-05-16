/*
  Test vectors check = True;

  Test vectors information:
    Organization:                      Internet Engineering Task Force, IETF
    Network Working Group                                    J. Strombergson
    Internet-Draft                                        Secworks Sweden AB
    Intended status: Informational                         December 31, 2013

  URL:
    https://tools.ietf.org/html/draft-strombergson-chacha-test-vectors-01
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "chacha20.h"
#include "myfunctions.h"

int main (void) {
  uint8_t key    [32] = {0x00};
  uint8_t iv     [ 8] = {0x00};
  uint8_t input  [BLOCK_LEN] = {0x00};
  uint8_t output [BLOCK_LEN] = {0x00};

  uint32_t ctx_len = sizeof(CHACHA20_CTX);

  CHACHA20_CTX * chacha20_ctx = (CHACHA20_CTX *)calloc(1, ctx_len);

  if (chacha20_ctx == NULL) {
    printf("[#] Cannot allocate memory!\n");
    return -1;
  }

  printf("All bits key and iv initialized 0;\nEncrypt %d bits block initialized 0;\n\n", BLOCK_LEN * 8);

  printf("PLAIN_TEXT:\n");
  printhex(1, input, BLOCK_LEN);

  printf("KEY:\n");
  printhex(1, key, 32);

  printf("IV:\n");
  printhex(1, iv, 8);

  putc('\n', stdout);

  chacha20_keysetup(chacha20_ctx, key, 32 * 8);
  chacha20_ivsetup(chacha20_ctx, iv);
  chacha20_crypt(chacha20_ctx, input, output, BLOCK_LEN);

  printf("ENCRYPT_DATA:\n");
  printhex(1, output, BLOCK_LEN);

  memset(chacha20_ctx, 0x00, ctx_len);

  chacha20_keysetup(chacha20_ctx, key, 32 * 8);
  chacha20_ivsetup(chacha20_ctx, iv);
  chacha20_crypt(chacha20_ctx, output, input, BLOCK_LEN);
  
  printf("DECRYPT_DATA:\n");
  printhex(1, input, BLOCK_LEN);

  memset(chacha20_ctx, 0x00, ctx_len);
  free(chacha20_ctx);
  chacha20_ctx = NULL;
  
  return 0;
}
