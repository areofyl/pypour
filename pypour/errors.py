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


def _reverse_translate_names(msg):
    """Replace Python identifiers back to French names in error messages."""
    for py_name, fr_name in PY_TO_FR.items():
        msg = msg.replace(f"'{py_name}'", f"'{fr_name}'")
    return msg


def format_french_error(exc, source_path=None):
    """Format an exception as a French error message."""
    etype = type(exc).__name__
    fr_type = ERROR_NAMES.get(etype, etype)
    msg = _reverse_translate_names(str(exc))
    return f"{fr_type}: {msg}"


def print_french_error(exc, source_path=None):
    """Print a French-translated error to stderr."""
    print(format_french_error(exc, source_path), file=sys.stderr)
