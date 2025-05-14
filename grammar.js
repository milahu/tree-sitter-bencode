/**
 * @file bencode grammar for tree-sitter
 * @author Samasaur1 <30577766+Samasaur1@users.noreply.github.com>
 * @license MIT
 */

/// <reference types="tree-sitter-cli/dsl" />
// @ts-check

module.exports = grammar({
  name: "bencode",

  rules: {
    // TODO: add the actual grammar rules
    source_file: $ => "hello"
  }
});
