#include "tree_sitter/parser.h"
#include "tree_sitter/alloc.h"
#include "tree_sitter/array.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

enum TokenType {
    STRING_LENGTH_PREFIX,
    STRING_VALUE
};

void * tree_sitter_bencode_external_scanner_create() {
    int *len = ts_malloc(sizeof(int));
    *len = -1;

    return len;
}

void tree_sitter_bencode_external_scanner_destroy(void *payload) {
    ts_free(payload);
}

unsigned tree_sitter_bencode_external_scanner_serialize(
  void *payload,
  char *buffer
) {
    memcpy(buffer, payload, sizeof(int));
    return sizeof(int);
}

void tree_sitter_bencode_external_scanner_deserialize(
  void *payload,
  const char *buffer,
  unsigned length
) {
    if (length != sizeof(int)) {
        *(int*)payload = -1;
        return;
    }
    memcpy(payload, buffer, sizeof(int));
}

bool tree_sitter_bencode_external_scanner_scan(
  void *payload,
  TSLexer *lexer,
  const bool *valid_symbols
) {
    if (valid_symbols[STRING_LENGTH_PREFIX]) {
        if (lexer->lookahead < 48 || lexer->lookahead > 57) {
            // This covers EOF bc it will return 0
            return false;
        }
        int len = lexer->lookahead - 48;
        lexer->advance(lexer, false);
        while (lexer->lookahead >= 48 && lexer->lookahead <= 57) {
            int digit = lexer->lookahead - 48;
            len *= 10;
            len += digit;
            lexer->advance(lexer, false);
        }
        *(int*)payload = len;
        lexer->result_symbol = STRING_LENGTH_PREFIX;
        return true;
    } else if (valid_symbols[STRING_VALUE]) {
        int len = *(int*)payload;
        if (len >= 0) {
            while (len > 0) {
                if (lexer->eof(lexer)) {
                    return false;
                }
                lexer->advance(lexer, false);
                --len;
            }
            lexer->result_symbol = STRING_VALUE;
            return true;
        } else {
            // invalid length; we should never reach this case
            return false;
        }
    } else {
        return false;
    }
}
