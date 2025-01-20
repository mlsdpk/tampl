import copy
import re

from typing import List
from typing import AbstractSet, Collection, Dict, Optional, Tuple, cast


from pddl import parse_domain, parse_problem
from pddl.logic.base import And, Formula, Not
from pddl.logic.terms import Term, Variable, Constant
from pddl.logic.predicates import DerivedPredicate, Predicate


class PlanningGraph:
    def __init__(self, domain, problem) -> None:
        self._domain = parse_domain(domain)
        self._problem = parse_problem(problem)

    def to_pddl_action(self):
        """
        Method to convert TAMPL's action to pddl's action
        """
        pass

    """
    TODO:
    for each action in plan:
        get current state and next state from action
        convert TAMPL's specific state to pddl specific
        get affected state(s) from the action applied
        generate tikz nodes from pddl state
        generate tikz node for the action applied
        update graph edges with affected states
    """

    def create_plan_graph(self, plan):
        state_transistions = []
        for i, action in enumerate(plan):
            print(f"{i}: {action.type} ({' '.join(action.parameters)})")

            next_state = self.__get_next_state_as_predicate(action)
            print(f"Next State: {next_state}")
            state_transistions.append(next_state)
        return state_transistions

    def __get_next_state_as_predicate(self, action) -> Optional[Collection[Formula]]:
        next_state = []

        # check whether this action exists in domain
        act_to_check = None
        for act in self._domain.actions:
            if action.type == act.name:
                act_to_check = act
                break

        # if action does not exist, we cannot proceed
        assert act_to_check is not None

        # Convert action effect into a list of predicates with variable terms
        predicates = self.decode_action_effect(str(act_to_check.effect))

        # we can now create a list of states
        # which are also represeted as predicates but with constant terms
        d = {}
        assert len(action.parameters) == len(act_to_check.parameters)
        for i, var_param in enumerate(act_to_check.parameters):
            d[var_param.name] = action.parameters[i]

        for pred in predicates:
            # check if it is Not
            is_not = isinstance(pred, Not)
            if is_not:
                pred = pred.argument

            # go through each variable term in predicate
            const_terms = []
            for var_term in pred.terms:
                const_terms.append(
                    Constant(d[var_term.name], list(var_param.type_tags)[0])
                )

            (
                next_state.append(~Predicate(pred.name, *const_terms))
                if is_not
                else next_state.append(Predicate(pred.name, *const_terms))
            )

        return next_state

    def generate_state_nodes(self, state, init_state, x_coordinate, col_idx):
        tikz_nodes = []
        y = len(state)
        row_idx = 0
        print("1")

        def sort_func(pred):
            return pred.argument if isinstance(pred, Not) else pred

        sorted_init_state = sorted(init_state, key=sort_func)
        sorted_state = sorted(state, key=sort_func)
        for predicate in sorted_state:

            # check whether it is logical negation
            is_not = isinstance(predicate, Not)
            if is_not:
                predicate = predicate.argument

            # get the correct index
            correct_row_idx = None
            for idx, init_pred in enumerate(sorted_init_state):
                if isinstance(init_pred, Not):
                    init_pred = init_pred.argument

                # print(f"idx: {idx}, predicate: {predicate}, init_pred: {init_pred}")
                if predicate.name == init_pred.name:
                    correct_row_idx = idx
                    # print("SAME!!!!!!!!")
                    

            if correct_row_idx is None:
                continue

            terms = ", ".join([term.name for term in predicate.terms])
            formatted_predicate = (
                f"{predicate.name}"
                if predicate.arity == 0
                else f"{predicate.name} ({terms})"
            )

            negation = "$\\neg$" if is_not else ""
            tikz_nodes.append(
                f"\\node (s{correct_row_idx}{col_idx}) at ({x_coordinate},{len(init_state) - correct_row_idx}) {{{negation}\\texttt{{{formatted_predicate}}}}};"
            )
            row_idx += 1
            y -= 1
        return "\n".join(tikz_nodes)

    def decode_action_effect(self, expression) -> Optional[Formula]:

        predicates = []

        # remove white space
        expression = expression.replace(" ", "")

        # Find the operator (first non-whitespace word after '(')
        operator_match = re.search(r"\((\w+)", expression)
        operator = operator_match.group(1) if operator_match else None

        # we always assume operator starts with "and"
        # TODO: is this true always?
        if operator != "and":
            return operator, []

        # Extract groups inside the `and` operator
        groups = []
        stack = []
        current_group = []

        for char in expression[1:-1]:  # Skip the first `(` and last `)`
            if char == "(":
                if stack:  # Nested group
                    current_group.append(char)
                stack.append(char)
            elif char == ")":
                stack.pop()
                if stack:  # Closing a nested group
                    current_group.append(char)
                else:  # Closing an outermost group
                    groups.append("".join(current_group))
                    current_group = []
            else:
                if stack:  # Inside a group
                    current_group.append(char)

        # now we have predicates as in text groups
        # convert each to pddl.Predicate

        for gp in groups:
            neg, op, params = self.__decode_group(gp)

            # print(f"neg: {neg}, op: {op}, params: {params}")

            # find the valid predicate with op from domain
            predicate = None
            for pred in self._domain.predicates:
                if pred.name == op:
                    predicate = copy.deepcopy(pred)

            # print(f"Predicate found: {predicate}")

            # create new terms with correct names
            new_terms = []
            assert len(params) == len(predicate.terms)
            for i, term in enumerate(predicate.terms):
                new_terms.append(Variable(params[i], term.type_tags))

            # finally we create a predicate with correct operator name and terms
            p = Predicate(op, *new_terms)
            print(f"p: {p}")

            predicates.append(~p) if neg else predicates.append(p)

        return predicates

    def __decode_group(self, group: str):
        # Check if the group starts with "not"
        neg = group.startswith("not(")
        if neg:
            # Extract the real group inside parentheses
            inner_group = re.search(r"not\((.+)\)", group)
            if inner_group:
                group = inner_group.group(1)
            else:
                raise ValueError(f"Malformed 'not' group: {group}")

        # Extract the operator (first character before any ? or end of string)
        operator_match = re.match(r"([a-zA-Z-]+)", group)
        operator = operator_match.group(1) if operator_match else None

        # Extract parameters (all occurrences of ? followed by a word)
        parameters = re.findall(r"\?(\w+)", group)

        return neg, operator, parameters
