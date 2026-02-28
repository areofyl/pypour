# French → Python keyword mappings
KEYWORDS = {
    "si": "if",
    "sinon": "else",
    "sinonsi": "elif",
    "tantque": "while",
    "pour": "for",
    "dans": "in",
    "fonction": "def",
    "retourner": "return",
    "classe": "class",
    "importer": "import",
    "depuis": "from",
    "comme": "as",
    "et": "and",
    "ou": "or",
    "non": "not",
    "vrai": "True",
    "faux": "False",
    "rien": "None",
    "essayer": "try",
    "sauf": "except",
    "finalement": "finally",
    "lever": "raise",
    "avec": "with",
    "passer": "pass",
    "continuer": "continue",
    "casser": "break",
    "affirmer": "assert",
    "supprimer": "del",
    "rendement": "yield",
}

# French → Python builtin mappings
BUILTINS = {
    "afficher": "print",
    "saisir": "input",
    "longueur": "len",
    "portee": "range",
    "type": "type",
    "entier": "int",
    "flottant": "float",
    "chaine": "str",
    "liste": "list",
    "dico": "dict",
    "ensemble": "set",
    "booleen": "bool",
    "ouvrir": "open",
    "enumerer": "enumerate",
    "trier": "sorted",
    "carte": "map",
    "filtrer": "filter",
    "somme": "sum",
    "min": "min",
    "max": "max",
    "abs": "abs",
    "tout": "all",
    "nimporte": "any",
}

# Combined lookup for the transpiler
FR_TO_PY = {**KEYWORDS, **BUILTINS}

# Reverse mapping (Python → French) for error translation
PY_TO_FR = {v: k for k, v in FR_TO_PY.items()}
