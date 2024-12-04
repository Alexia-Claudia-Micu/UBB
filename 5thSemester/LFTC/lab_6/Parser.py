import itertools

class Parser:
    class ProductionItem:
        def __init__(self, lhs: str, rhs: list, dot_position: int):
            self.lhs = lhs
            self.rhs = rhs
            self.dot_position = dot_position

        def __eq__(self, other):
            return (self.lhs == other.lhs and 
                    self.rhs == other.rhs and 
                    self.dot_position == other.dot_position)

        def __str__(self):
            result = f"[{self.lhs} -> "
            result += " ".join(
                (". " if idx == self.dot_position else "") + symbol
                for idx, symbol in enumerate(self.rhs)
            )
            if self.dot_position == len(self.rhs):
                result += " ."
            return result.strip() + "]"

    class State:
        id_counter = itertools.count()

        def __init__(self, closure_items, closure):
            self.id = next(self.id_counter)
            self.closure_items = closure_items
            self.closure = closure

        def get_symbols_after_dot(self):
            symbols = []
            for item in self.closure:
                if item.dot_position < len(item.rhs):
                    symbols.append(item.rhs[item.dot_position])
            return symbols

        def __eq__(self, other):
            return self.closure_items == other.closure_items

        def __str__(self):
            result = f"state{self.id} = closure({{"
            result += ", ".join(str(item) for item in self.closure_items) + "}) = {"
            result += ", ".join(str(item) for item in self.closure) + "}"
            return result

    def __init__(self, grammar):
        self.grammar = grammar
        self.canonical_collection = []

    @staticmethod
    def is_item_in_closure(item, closure):
        for closure_item in closure:
            if (item.lhs == closure_item.lhs and 
                item.rhs == closure_item.rhs and 
                item.dot_position == closure_item.dot_position):
                return True
        return False

    def closure(self, items: list) -> State:
        current_closure = items.copy()
        finished = False
        while not finished:
            old_closure = current_closure.copy()
            for closure_item in current_closure:
                if closure_item.dot_position < len(closure_item.rhs) and \
                        closure_item.rhs[closure_item.dot_position] in self.grammar.non_terminals:
                    for production in self.grammar.productions[closure_item.rhs[closure_item.dot_position]]:
                        new_item = self.ProductionItem(
                            closure_item.rhs[closure_item.dot_position], production, 0
                        )
                        if not self.is_item_in_closure(new_item, current_closure):
                            current_closure.append(new_item)
            if current_closure == old_closure:
                finished = True

        return self.State(items, current_closure)

    def goto(self, state: State, symbol: str) -> State:
        items_for_symbol = [
            self.ProductionItem(item.lhs, item.rhs, item.dot_position + 1)
            for item in state.closure
            if item.dot_position < len(item.rhs) and item.rhs[item.dot_position] == symbol
        ]

        for existing_state in self.canonical_collection:
            if existing_state.closure_items == items_for_symbol:
                return existing_state

        return self.closure(items_for_symbol)

    def create_canonical_collection(self):
        self.canonical_collection = [
            self.closure(
                [self.ProductionItem(
                    self.grammar.start_symbol,
                    self.grammar.productions[self.grammar.start_symbol][0],
                    0
                )]
            )
        ]
        index = 0
        while index < len(self.canonical_collection):
            state = self.canonical_collection[index]
            symbols = state.get_symbols_after_dot()
            for symbol in symbols:
                new_state = self.goto(state, symbol)
                if new_state not in self.canonical_collection:
                    self.canonical_collection.append(new_state)
            index += 1

import unittest

class TestParser(unittest.TestCase):
    def setUp(self):
        """Set up a sample grammar and parser for testing."""
        class Grammar:
            def __init__(self):
                self.non_terminals = ["S", "A"]
                self.terminals = ["a", "b"]
                self.start_symbol = "S"
                self.productions = {
                    "S": [["A", "b"], ["b"]],
                    "A": [["a", "A"], ["a"]],
                }

        self.grammar = Grammar()
        self.parser = Parser(self.grammar)

    def test_production_item_str(self):
        """Test string representation of ProductionItem."""
        item = Parser.ProductionItem("S", ["A", "b"], 1)
        expected = "[S -> A . b]"
        self.assertEqual(str(item), expected)

        item = Parser.ProductionItem("S", ["A", "b"], 2)
        expected = "[S -> A b .]"
        self.assertEqual(str(item), expected)

    def test_state_str(self):
        """Test string representation of State."""
        item1 = Parser.ProductionItem("S", ["A", "b"], 0)
        item2 = Parser.ProductionItem("A", ["a"], 0)
        state = Parser.State([item1], [item1, item2])
        expected = "state0 = closure({[S -> . A b]}) = {[S -> . A b], [A -> . a]}"
        self.assertEqual(str(state), expected)

    def test_closure(self):
        """Test the closure computation."""
        items = [
            Parser.ProductionItem("S", ["A", "b"], 0)
        ]
        state = self.parser.closure(items)

        # Expect closure to contain all items relevant to "A".
        expected_closure_items = [
            Parser.ProductionItem("S", ["A", "b"], 0),
            Parser.ProductionItem("A", ["a", "A"], 0),
            Parser.ProductionItem("A", ["a"], 0),
        ]
        self.assertCountEqual(state.closure, expected_closure_items)

    def test_goto(self):
        """Test the goto function."""
        start_item = Parser.ProductionItem("S", ["A", "b"], 0)
        closure = self.parser.closure([start_item])
        new_state = self.parser.goto(closure, "A")

        # Expect goto to advance dot position for items with "A" after dot.
        expected_items = [
            Parser.ProductionItem("S", ["A", "b"], 1)
        ]
        self.assertEqual(new_state.closure_items, expected_items)

    def test_create_canonical_collection(self):
        """Test the creation of the canonical collection."""
        self.parser.create_canonical_collection()
        collection = self.parser.canonical_collection

        # Validate the number of states and their content.
        self.assertGreater(len(collection), 0)

        # Check first state is properly initialized.
        start_item = Parser.ProductionItem("S", ["A", "b"], 0)
        initial_closure_items = [
            start_item,
            Parser.ProductionItem("A", ["a", "A"], 0),
            Parser.ProductionItem("A", ["a"], 0),
        ]
        self.assertCountEqual(collection[0].closure, initial_closure_items)

    def test_is_item_in_closure(self):
        """Test the is_item_in_closure method."""
        closure = [
            Parser.ProductionItem("S", ["A", "b"], 0),
            Parser.ProductionItem("A", ["a", "A"], 0),
        ]
        item = Parser.ProductionItem("A", ["a", "A"], 0)
        self.assertTrue(Parser.is_item_in_closure(item, closure))

        non_existing_item = Parser.ProductionItem("B", ["a", "A"], 0)
        self.assertFalse(Parser.is_item_in_closure(non_existing_item, closure))


if __name__ == "__main__":
    unittest.main()


