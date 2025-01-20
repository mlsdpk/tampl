from typing import List
from typing import AbstractSet, Collection, Dict, Optional, Tuple, cast

from pddl.logic.base import And, Formula, Not
from pddl.logic.terms import Term, Variable, Constant
from pddl.logic.predicates import DerivedPredicate, Predicate

import copy
import re

import os
import networkx as nx
from pylatex import Document, TikZ, TikZNode, TikZDraw, StandAloneGraphic
from pylatex.utils import NoEscape

from pytampl.bt import PlannerBTEngine
from pytampl.core import Action
from pytampl.extensions.pddlgym import PDDLGymEnv
from pytampl.pddl import PlanningGraph
from pytampl.planner import FastForward

# initialize tampl PDDLGym environment
env = PDDLGymEnv("PDDLEnvHanoi-v0")

pddl_domain_file = env.domain.get_file_path()
pddl_problem_file = env.problem.get_file_path()
print(f"Using PDDL domain from {pddl_domain_file}")
print(f"Using PDDL problem from {pddl_problem_file}")

# get pddl domain and problem files
# pddl_domain_file = (
#     "/Users/phone/Documents/projects/tampl/examples/pddl/letseat/domain.pddl"
# )
# pddl_problem_file = (
#     "/Users/phone/Documents/projects/tampl/examples/pddl/letseat/problem.pddl"
# )
# print(f"Using PDDL domain from {pddl_domain_file}")
# print(f"Using PDDL problem from {pddl_problem_file}")

# Create planner engine from task planning behavior tree
engine = PlannerBTEngine(
    bt_xml_path="/Users/phone/Documents/projects/tampl/examples/behavior_trees/task/task_planner.xml"
)

# Run the planner
solved = engine.run()

# visualize the solution as a planning graph
if solved:
    plan: List[Action] = engine.get_plan()

    # create planning graph
    graph = PlanningGraph(domain=pddl_domain_file, problem=pddl_problem_file)

    print(graph._domain)
    print(graph._problem)

    # print(graph._domain.predicates)
    # print(graph._problem.init)

    print("=== graph._domain.actions ===")

    for act in graph._domain.actions:
        print(act)

    # get all available predicates from domain
    print("=== graph._domain.predicates ===")
    print(graph._domain.predicates)

    # def decode(expression):
    #     # Remove outer parentheses and split the expression
    #     expression = expression.strip("()")
    #     print(f"expression: {expression}")
    #     parts = expression.split(" ", 1)
    #     print(f"parts: {parts}")
    #     operator = parts[0]
    #     content = parts[1]

    #     print(f"operator: {operator}, content: {content}")

    #     predicates = []
    #     if operator == "and":
    #         # Split the content into sub-expressions
    #         sub_expressions = re.findall(r"\(.*?\)", content)
    #         for sub_expr in sub_expressions:
    #             predicates.extend(decode(sub_expr))
    #     elif operator == "not":
    #         # Negated predicate
    #         sub_expr = content.strip("()")
    #         inner_predicates = decode(sub_expr)
    #         # predicates.append(inner_predicates)
    #         predicates.append(f"not {inner_predicates}")
    #     else:
    #         # Regular predicate
    #         components = content.split()
    #         name = operator
    #         args = [arg.strip("?") for arg in components]
    #         print(f"*** Predicate({name}, {args}) ***")
    #         # predicates.append(Predicate(name, *args))

    #     return predicates

    # print(f"operator: {operator}, groups: {groups}")

    # stripped_expression = (
    #     expression[1:-1]
    #     if expression.startswith("(") and expression.endswith(")")
    #     else expression
    # )
    # print(f"3rd step: {stripped_expression}")

    state_trasactions = graph.create_plan_graph(plan)

    # def create_plan_graph(plan):

    # create predicates based on effects

    # to create a sequence of predicates
    # next_state: Optional[Collection[Formula]] = None

    def format_predicate(predicate):
        """
        Format a predicate into a LaTeX-friendly string.

        Parameters:
            predicate (str): The predicate string, e.g., "Predicate(on, cupcake, table)".

        Returns:
            str: A formatted string, e.g., "on(cupcake, table)".
        """
        inner_content = predicate[predicate.index("(") + 1 : predicate.rindex(")")]
        return inner_content.replace(", ", ",")

    def generate_tex_from_pddl(filename, graph):
        with open(f"{filename}.tex", "w") as tex_file:
            tex_file.write("\\documentclass{standalone}\n")
            tex_file.write("\\usepackage{tikz}\n")
            tex_file.write("\\usetikzlibrary{graphs}\n")
            tex_file.write("\\begin{document}\n\n")
            tex_file.write("\\tikz {\n")

            col_idx = 0  # Unique identifier for the state
            x_coord = 0  # X-coordinate for the state nodes
            tex_file.write(
                graph.generate_state_nodes(graph._problem.init, graph._problem.init, x_coord, col_idx)
            )

            col_idx += 1
            x_coord += 5
            tex_file.write("\n\n")

            for state in state_trasactions:
                tex_file.write(
                    graph.generate_state_nodes(
                        state, graph._problem.init, x_coord, col_idx
                    )
                )

                col_idx += 1
                x_coord += 5
                tex_file.write("\n\n")

            tex_file.write("}\n\n")
            tex_file.write("\\end{document}\n")

    generate_tex_from_pddl("planning_graph", graph)
    os.system(f"pdflatex planning_graph.tex")

    # G = nx.DiGraph()

    # init_state = graph._problem.init
    # G.add_node("Init", label="\n".join(str(p) for p in init_state))

    # doc = Document(documentclass="standalone")
    # tikz = TikZ()

    # # Automatically position nodes for a layered layout
    # positions = nx.spring_layout(G)

    # # Add nodes to TikZ
    # for node, attr in G.nodes(data=True):
    #     x, y = positions[node]
    #     tikz.append(
    #         TikZNode(
    #             node,
    #             options=NoEscape(f"at ({x},{y}) [circle, draw=blue!50, fill=blue!20]"),
    #             text=NoEscape(attr['label'] if 'label' in attr else node)
    #         )
    #     )

    # doc.append(tikz)
    # doc.generate_tex("planning_graph")

    # os.system(f"pdflatex planning_graph.tex")

    # graph.export("test.pdf")


# frozenset({Predicate(on, cupcake, table), Predicate(on, arm, table), Predicate(path, table, plate), Predicate(arm-empty, )})

# \node (s00) at (0,3) {\texttt{arm-empty}};
# \node (s10) at (0,2) {\texttt{on(cupcake, table)}};
# \node (s20) at (0,1) {\texttt{on(arm, table)}};
# \node (s30) at (0,0) {\texttt{path(table, plate)}};
