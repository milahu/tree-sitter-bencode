/**
 * @file bencode grammar for tree-sitter
 * @author Samasaur1 <30577766+Samasaur1@users.noreply.github.com>
 * @license MIT
 */

/// <reference types="tree-sitter-cli/dsl" />
// @ts-check

module.exports = grammar({
  name: "bencode",

  externals: $ => [ $._string_length_prefix, $.string_value ],
  extras: $ => [],

  rules: {
    // TODO: add the actual grammar rules
    source_file: $ => $.atom,


    atom: $ => choice(
      $.dictionary,
      $.list,
      $.string,
      $.int
    ),

    dictionary: $ => seq(
      field('open', "d"),
      repeat(seq($.string, $.atom)),
      field('close', "e")
    ),
    list: $ => seq(
      field('open', "l"),
      repeat($.atom),
      field('close', "e")
    ),
    // string: $ => "5:hello",
    string: $ => seq(
      field('length_prefix', $._string_length_prefix),
      field('colon_separator', ":"),
      field('value', $.string_value)
    ),
    int: $ => seq(
      field('open', "i"),
      field('value', /-?[0-9]+/),
      field('close', "e")
    )
  }
});
