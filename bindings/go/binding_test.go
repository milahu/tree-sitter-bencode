package tree_sitter_bencode_test

import (
	"testing"

	tree_sitter "github.com/tree-sitter/go-tree-sitter"
	tree_sitter_bencode "github.com/samasaur1/tree-sitter-bencode/bindings/go"
)

func TestCanLoadGrammar(t *testing.T) {
	language := tree_sitter.NewLanguage(tree_sitter_bencode.Language())
	if language == nil {
		t.Errorf("Error loading bencode grammar")
	}
}
