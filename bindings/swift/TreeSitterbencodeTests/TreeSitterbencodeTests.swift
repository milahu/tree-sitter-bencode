import XCTest
import SwiftTreeSitter
import TreeSitterBencode

final class TreeSitterBencodeTests: XCTestCase {
    func testCanLoadGrammar() throws {
        let parser = Parser()
        let language = Language(language: tree_sitter_bencode())
        XCTAssertNoThrow(try parser.setLanguage(language),
                         "Error loading bencode grammar")
    }
}
