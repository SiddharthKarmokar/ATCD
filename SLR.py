import ply.yacc as yacc
import ply.lex as lex

# Tokens
tokens = ('a', 'b')

t_ignore = ' \t'

def t_a(t):
    r'a'
    return t

def t_b(t):
    r'b'
    return t

def t_error(t):
    print(f"Illegal character {t.value[0]}")
    t.lexer.skip(1)

lexer = lex.lex()

# Grammar Rules
def p_S(p):
    'S : A B'
    p[0] = ('S', p[1], p[2])

def p_A(p):
    'A : a'
    p[0] = ('A', p[1])

def p_B(p):
    'B : b'
    p[0] = ('B', p[1])

def p_error(p):
    print("Syntax error")

parser = yacc.yacc(method='SLR')

# Generate SLR Parsing Table
def generate_slr_table():
    print("SLR Parsing Table")
    print("State | Action")
    for state, actions in parser.action.items():
        print(f"{state} | {actions}")
    print("\nGoto Table")
    for state, gotos in parser.goto.items():
        print(f"{state} | {gotos}")

generate_slr_table()
