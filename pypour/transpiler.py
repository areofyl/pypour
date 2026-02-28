import tokenize
import io
from .lang.fr import FR_TO_PY


def transpile(source):
    """Transpile French Python (.ppour) source to standard Python."""
    tokens = list(tokenize.generate_tokens(io.StringIO(source).readline))
    result = []
    for tok in tokens:
        if tok.type == tokenize.NAME and tok.string in FR_TO_PY:
            result.append(tok._replace(string=FR_TO_PY[tok.string]))
        else:
            result.append(tok)
    return tokenize.untokenize(result)


def transpile_file(path):
    """Read a .ppour file and return transpiled Python source."""
    with open(path, "r", encoding="utf-8") as f:
        return transpile(f.read())
