from pycfg.first_follow import compute_first_follow

rules = {
    "S": ["A B"],
    "A": ["a", "ε"],
    "B": ["b"]
}

first, follow = compute_first_follow(rules)
print("First:", first)
print("Follow:", follow)
