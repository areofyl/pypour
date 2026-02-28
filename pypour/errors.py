import re
import traceback
import sys
from .lang.fr import PY_TO_FR

# Python error type → French error type
ERROR_NAMES = {
    "SyntaxError": "ErreurDeSyntaxe",
    "NameError": "ErreurDeNom",
    "TypeError": "ErreurDeType",
    "ValueError": "ErreurDeValeur",
    "IndexError": "ErreurDIndex",
    "KeyError": "ErreurDeCle",
    "AttributeError": "ErreurDAttribut",
    "ZeroDivisionError": "ErreurDeDivisionParZero",
    "FileNotFoundError": "ErreurFichierIntrouvable",
    "ImportError": "ErreurDImportation",
}

# Common English message fragments → French translations
MESSAGE_FRAGMENTS = {
    "is not defined": "n'est pas défini",
    "is not callable": "n'est pas appelable",
    "unexpected indent": "indentation inattendue",
    "expected an indented block": "bloc indenté attendu",
    "invalid syntax": "syntaxe invalide",
    "division by zero": "division par zéro",
    "list index out of range": "index de liste hors limites",
    "string index out of range": "index de chaîne hors limites",
    "object has no attribute": "l'objet n'a pas d'attribut",
    "takes no arguments": "ne prend aucun argument",
    "missing required argument": "argument requis manquant",
    "unexpected keyword argument": "argument nommé inattendu",
    "object is not iterable": "l'objet n'est pas itérable",
    "object is not subscriptable": "l'objet n'est pas indexable",
    "can't convert": "impossible de convertir",
    "invalid literal for": "valeur littérale invalide pour",
    "No module named": "Aucun module nommé",
    "No such file or directory": "Aucun fichier ou répertoire de ce nom",
}


def _reverse_translate_names(msg):
    """Replace Python identifiers back to French names in error messages."""
    for py_name, fr_name in PY_TO_FR.items():
        msg = msg.replace(f"'{py_name}'", f"'{fr_name}'")
    return msg


def _translate_message(msg):
    """Translate common English message fragments to French."""
    for eng, fra in MESSAGE_FRAGMENTS.items():
        msg = msg.replace(eng, fra)
    return msg


def format_french_error(exc, source_path=None):
    """Format an exception as a French error message."""
    etype = type(exc).__name__
    fr_type = ERROR_NAMES.get(etype, etype)
    msg = _reverse_translate_names(str(exc))
    msg = _translate_message(msg)
    return f"{fr_type}: {msg}"


def print_french_error(exc, source_path=None):
    """Print a French-translated error to stderr."""
    print(format_french_error(exc, source_path), file=sys.stderr)
