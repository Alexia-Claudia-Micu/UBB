from Grammar import Grammar
from Parser import Parser
from ParserOutput import ParserOutput

def run_for_g1():
    g = Grammar()
    g.read_from_file("g1.in")
    print(g)
    g.make_enhanced_grammar()
    parser = Parser(g)
    parser.create_canonical_collection()
    for state in parser.canonical_collection:
        print(state)

    parser.create_parsing_table()

    print(parser.parsing_table)

    # a c
    # a b c
    # a b b b c

    print("Enter a sequence: ")
    sequence = input()
    output_band = parser.parse_sequence(sequence.split(" "))

    # output_band = parser.parse_sequence(['a', 'b', 'b', 'c'])
    print(output_band)

    parserOutput = ParserOutput(output_band, g)
    parserOutput.compute_parsing_tree()
    for item in parserOutput.parsing_tree:
        print(item)

    parserOutput.print_to_file("out1.txt")

if __name__ == '__main__':
    run_for_g1()
