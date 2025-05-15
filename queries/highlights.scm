(dictionary
  open: "d" @punctuation.delimiter.dictionary.open.bencode
  close: "e" @punctuation.delimiter.dictionary.close.bencode
  )

(list
  open: "l" @punctuation.delimiter.list.open.bencode
  close: "e" @punctuation.delimiter.list.close.bencode
  )

(string
  colon_separator: ":" @punctuation.delimiter
  value: (_) @string
  ) @type ; applies by default to the only non-matching field, which is length_prefix

(int
  open: "i" @punctuation.delimiter.int.open.bencode
  close: "e" @punctuation.delimiter.int.close.bencode
  ) @number
